#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "pipeline.h"
#include "machine.h"
#include "inst_process.h"

#define reg(x) reg_memory[x * 4].mem_data
#define mem(x) data_memory[x].mem_data


void inst_fetch(char* inst)
{
	/*更新PC*/
	if(pipeline_next_stage_null(IFID)==true)
	{

		char *OP;
		char tmp[128];
		strcpy(tmp, inst);
		OP = strtok(tmp, "\t"); 
		char* operands = OP + strlen(OP) + 1;
		if (strcmp(operands, "") == 0)
			return;
		strcpy(IFID.op, OP);
		strcpy(IFID.inst, operands);
		printf("OP: %s operands: %s\n", OP, operands);
		PC += 4;
		
	}
	return;
}
void inst_decode(void)
{
	/*拿到register資料如果是branch instruction會在這階段算出結果*/
	long r_d, r_s, r_t, C, shamt;
	char reg_dest[128];
	if (pipeline_next_stage_null(IDEX) == true)
	{			
		
		clear_pipeline_register_content(&IFID);
	}
	return;
}
void inst_execute(void)
{
	//HOMEWORK
	/*將結果算出*/

		 return;
}
void mem_writeback(void)
{
	//HOMEWORK
	/*將data寫入memory*/
		 return;
}
void reg_update(void)
{
	//HOMEWORK
	/*將修改後的資料寫回register*/
		return;
}
void flush_pipeline(void)
{
	return;
}
bool if_hazard(void)   //HOMEWORK
{
	return false;
}
bool pipeline_null(void)
{
	if(DATAPATH_TYPE==PIPELINE)
	{
		if (pipeline_next_stage_null(IFID) == true && pipeline_next_stage_null(IDEX) == true && pipeline_next_stage_null(EXMEM) == true && pipeline_next_stage_null(MEMWB) == true)
			return false;
		else
			return true;
	}
	else
	{
		return false;
	}
}
void print_pipeline_register_content(void)
{
	printf("IFID\n");
	printf("rs: $%d rt: $%d rd: $%d imm: %d temp: %d\n", IFID.rs, IFID.rt,IFID.rd,IFID.imm,IFID.temp);
	printf("op: %s inst: %s\n",IFID.op,IFID.inst);
	printf("IDEX\n");
	printf("rs: $%d rt: $%d rd: $%d imm: %d temp: %d\n", IDEX.rs, IDEX.rt,IDEX.rd,IDEX.imm,IDEX.temp);
	printf("op: %s inst: %s\n",IDEX.op,IDEX.inst);
	printf("EXMEM\n");
	printf("rs: $%d rt: $%d rd: $%d imm: %d temp: %d\n", EXMEM.rs, EXMEM.rt,EXMEM.rd,EXMEM.imm,EXMEM.temp);
	printf("op: %s inst: %s\n",EXMEM.op,EXMEM.inst);
	printf("MEMWB\n");
	printf("rs: $%d rt: $%d rd: $%d imm: %d temp: %d\n", MEMWB.rs, MEMWB.rt,MEMWB.rd,MEMWB.imm,MEMWB.temp);
	printf("op: %s inst: %s\n",MEMWB.op,MEMWB.inst);
	return;

}
void clear_pipeline_register_content(PIPELINE_MEMORY *temp)
{
	temp->rs=-1;
	temp->rt=-1;
	temp->rd=-1;
	temp->imm=-1;
	temp->temp = -1;
	strcpy(temp->op,"null");
	strcpy(temp->inst,"null");
	return;
}
void pass_register_content(PIPELINE_MEMORY *source,PIPELINE_MEMORY *destination)
{
	destination->rs=source->rs;
	destination->rt=source->rt;
	destination->rd=source->rd;
	destination->imm=source->imm;
	destination->temp=source->temp;
	strcpy(destination->op,source->op);
	strcpy(destination->inst,source->inst);
	return;

}
bool pipeline_next_stage_null(PIPELINE_MEMORY temp)
{

	if(	temp.rs==-1&&temp.rt==-1&&temp.rd==-1&&temp.imm==-1&&strcmp(temp.op,"null")==0&&strcmp(temp.inst,"null")==0)
		return true;
	return false;
}
