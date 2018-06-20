/*
   Functional simulation of all instructions 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
//#include <sys/time.h>

#include "machine.h"
#include "inst_process.h"
#include "pipeline.h"
#include "sim.h"

#define reg(x) reg_memory[x * 4].mem_data
#define mem(x) data_memory[x].mem_data


void inst_func_simulation(char* inst){
	// if(DATAPATH_TYPE!=3)
	int	i, j, k; 
	char *OP; 
	long r_d, r_s, r_t, C, shamt;
	char reg_dest[32];

	/* instruction: ADD $1, $2, $3 */
	char tmp[128];
	strcpy(tmp, inst);
	OP = strtok(tmp, "\t"); 
	char* operands = OP + strlen(OP) + 1;
	printf("OP: %s operands: %s\n", OP, operands);
	PC += 4;
	if(strcmp(OP, "ADD") == 0)                     //ADD的範例已經寫好了，請依照此範例填滿下列九個指令 
    {             
		sscanf(operands, "$%ld, $%ld, $%ld", &r_d, &r_s, &r_t);
		reg(r_d) = reg(r_s) + reg(r_t);

		switch(DATAPATH_TYPE)
		{
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				sim_cycles += sim_cycles == 0 ? 4 : 1;
				break;
		}
		return;
	}
	/* finish the rest of the operations */
	if(strcmp(OP, "SUB") == 0)
	{
		sscanf(operands, "$%ld, $%ld, $%ld", &r_d, &r_s, &r_t);
		reg(r_d) = reg(r_s) - reg(r_t);

		switch(DATAPATH_TYPE)
		{
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				sim_cycles += sim_cycles == 0 ? 4 : 1;
				break;
		}
		return;
	}

	if(strcmp(OP, "ADDI") == 0)
	{
		// try use %ld for immediate column
		sscanf(operands, "$%ld, $%ld, %ld", &r_d, &r_s, &shamt);
		reg(r_d) = reg(r_s) + shamt;

		switch(DATAPATH_TYPE)
		{
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				sim_cycles += sim_cycles == 0 ? 4 : 1;
				break;
		}
		return;
	}

	if(strcmp(OP, "OR") == 0)
	{
		sscanf(operands, "$%ld, $%ld, $%ld", &r_d, &r_s, &r_t);
		reg(r_d) = reg(r_s) | reg(r_t);

		switch(DATAPATH_TYPE)
		{
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				sim_cycles += sim_cycles == 0 ? 4 : 1;
				break;
		}
		return;
	}

	if(strcmp(OP, "AND") == 0)
	{
		sscanf(operands, "$%ld, $%ld, $%ld", &r_d, &r_s, &r_t);
		reg(r_d) = reg(r_s) & reg(r_t);

		switch(DATAPATH_TYPE)
		{
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				sim_cycles += sim_cycles == 0 ? 4 : 1;
				break;
		}
		return;
	}

	if(strcmp(OP, "SLL") == 0)
	{
		sscanf(operands, "$%ld, $%ld, %ld", &r_d, &r_s, &shamt);
		reg(r_d) = reg(r_s) << shamt;

		switch(DATAPATH_TYPE)
		{
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				sim_cycles += sim_cycles == 0 ? 4 : 1;
				break;
		}
		return;
	}


	if(strcmp(OP, "LW") == 0)
	{
		sscanf(operands, "$%ld, %ld($%ld)", &r_d, &C, &r_s);
		reg(r_d) = mem(C + reg(r_s));

		switch(DATAPATH_TYPE)
		{
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 5;
				break;
			case PIPELINE:
				sim_cycles += sim_cycles == 0 ? 5 : 1;
				break;
		}
		return;
	}

	if(strcmp(OP, "SW") == 0)
	{
		sscanf(operands, "$%ld, %ld($%ld)", &r_d, &C, &r_s);
		r_s = C + reg(r_s);
		mem(r_s) = reg(r_d);

		switch(DATAPATH_TYPE)
		{
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				sim_cycles += sim_cycles == 0 ? 4 : 1;
				break;
		}
		return;
	}
		if(strcmp(OP, "SLT") == 0)
	{
		sscanf(operands, "$%ld, $%ld, $%ld", &r_d, &r_s, &r_t);
		reg(r_d) = reg(r_s) < reg(r_t) ? 1 : 0;

		switch(DATAPATH_TYPE)
		{
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 4;
				break;
			case PIPELINE:
				sim_cycles += sim_cycles == 0 ? 4 : 1;
				break;
		}
		return;
	}


	if(strcmp(OP, "BEQ") == 0)
	{
		sscanf(operands, "$%ld, $%ld, %ld", &r_s, &r_t, &shamt);
		if(reg(r_s) == reg(r_t)) PC += shamt << 2;
		switch(DATAPATH_TYPE)
		{
			case SINGLE:
				sim_cycles++;
				break;
			case MULTI:
				sim_cycles += 3;
				break;
			case PIPELINE:
				sim_cycles += sim_cycles == 0 ? 3 : 1;
				break;
		}
		return;
	}

	else
	{
		reg_update();
		mem_writeback();
		inst_execute();
		inst_decode();
		inst_fetch(inst);
		print_pipeline_register_content();
		sim_cycles++;
	}
	return;
}

