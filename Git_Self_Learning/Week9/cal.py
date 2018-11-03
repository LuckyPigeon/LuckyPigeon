'''
>>> appleAndPen('Apple', 'Banana')
'AppleBanana'
'''
def appleAndPen(str1, str2):
    return str1 + str2

if __name__ == '__main__':
    import doctest
    print(doctest.testmod())
