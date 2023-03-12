fin = open("stack.in", "r")
fout = open("stack.out", "w")
x = int(fin.readline())
all = fin.readlines()

myStack = []
line = 0
for line in range(0, x):
    if all[line].split()[0] == "-":
        print(myStack[-1], file=fout)
        myStack.pop()
    else:
        x, y = all[line].split()
        myStack.append(y)