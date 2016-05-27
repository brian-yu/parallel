from functools import reduce
num, mult = 2013, 1
while True:
    numStr = str(num)
    if '0' not in numStr and num%reduce(lambda x, y: x*y, [int(i) for i in numStr])==0: print("{}: {}".format(mult, num))
    num, mult = num+2013, mult+1