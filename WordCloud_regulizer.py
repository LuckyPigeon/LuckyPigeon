import re, sys

def regulizer(inputtext):
	tmp = ''
	num = ''
	CW = ''
	inputtext.split(',')
	for i in inputtext:
		for j in range(len(i)):
			if i[j].isdigit():
				num += i[j]
			else:
				CW += i[j]

		try:
			for j in range(int(num)):
				tmp += CW
		except ValueError as e:
			print(Blank!)

	return tmp

def main():
	inputfile = sys.argv[0]
	outuputfile = sys.argv[1]

	fin = open(inputfile, 'r')
	inputtext = fin.read()
	fin.close()

	outputtext = regulizer(inputtext)

	fout = open(outputfile, 'w')
	fout.write(outputtext)
	fout.close()

if __name__ == '__main__':
	main()
