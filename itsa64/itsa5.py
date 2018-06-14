n = int(raw_input())
for i in range(n):
  ans = 0
  case = int(raw_input())
  t1 = raw_input()
  t2 = raw_input()

  t1 = t1.split(' ')
  t2 = t2.split(' ')

  t1 = [int(x) for x in t1]
  t2 = [int(x) for x in t2]

  t1.sort()
  t2.sort()

  tmp1 = 0
  tmp2 = 0

  check = False

  while True:
	if t1[tmp1] <= t2[tmp2]:
	  tmp1 += 1
	else:
	  ans += case - tmp1
	  tmp2 += 1

	if tmp1 = case - 1 and t1[tmp1] <= t2[tmp2]:
	  break
	elif tmp2 == case - 1 and t1[tmp2] > t2[tmp2]:
	  ans += case - tmp1
	  break


  # ans += 1 if ans > 0 else 0
  print(ans)
