greef = ['Hi', 'Hello', 'How do you do', 'How are you']

count = 0

while True:
	a = input()

	if a is '\n':
		break

	if a in greef:
		print(greef[count % 4])
		count += 1
	else:
		print('Sorry')
		count -= 1
