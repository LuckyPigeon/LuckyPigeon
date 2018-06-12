#! /usr/bin/python3
import huffman
import numpy as np
import scipy as sp
import matplotlib.pyplot as plt
from pydub import AudioSegment
'''Main idea -- to compare each sample data which is in the dict and record if they are different, and then use huffman tree to encode it.'''
'''Try two ways -- first one for if different then add to dict else count += 1, second one for if different then add to new array and record it's name(index), else add it's name(index) and count += 1, the second one can be implemented by array'''

name = "01_"

extension = ".mp3"

# Assume there's 480 files
n = 480
count = 0

# two ways
sam_count = [] # the first way
name_count = {} # the second way
OS = {} # Object name and # of song samples

def cmp_samples():
	for i in range(1, 480):
		song_name = name + ("0" + str(i) if i < 10 else str(i)) + extension
		song1 = AudioSegment.from_mp3(song_name)
		sam1 = song1.get_array_of_samples()

		'''if key of sam_count / name_count is empty, then add song1 to dict, and count += 1'''
		'''The first way'''
		if not bool(sam_count):
			sam_count.append({'count': 0, 'samples': sam1, 'song_name': song_name, 'song_index': [i]})
			continue
		'''compare'''
		flag = True
		for j in range(len(sam_count)):
			flag = True
			for k in range(0, len(sam_count[j]['samples']), 10):
				if abs(sam1[k] - sam_count[j]['samples'][k]) > 50:
					flag = False

			if flag:
				sam_count[j]['count'] += 1
				sam_count[j]['song_index'].append(i)
				break

		if not flag:
			sam_count.append({'count': 0, 'samples': sam1, 'song_name': song_name, 'song_index': [i]})

	return sam_count

def Huf(inputs):
	output = []
	for i in range(len(inputs)):
		output.append((inputs[i]['song_name'], inputs[i]['count']))
	
	output = huffman.codebook(output)
	print(output)

def main():
	inputs = cmp_samples()
	# inputs = '\\n'.join(inputs)
	# f = open('output.txt', 'w')
	# f.write(inputs)
	for i in range(len(inputs)):
		print("(" + inputs[i]['song_name'] + ", " + inputs[i]['count'] + ")")
	# inputs = []
	# for i in range(len(count)):
	#	inputs.append((name[i], count[i]))
	# Huf()

# if __name__ == '__main__':
#	main()
