import re

def enc(data):
	data = sorted(data, key = lambda tup: tup[1], reverse = True)
	s = [re.sub('0b', '', x + 1) for x in range(len(data))]

	return s
