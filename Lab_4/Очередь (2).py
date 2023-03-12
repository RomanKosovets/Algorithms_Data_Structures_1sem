fin = open("queue.in", "r")
fout = open("queue.out", "w")
x = int(fin.readline())
all = fin.readlines()

queue = []
line = 0
for line in range(0, x):
    if all[line].split()[0] == "-":
        print(queue[0], file=fout)
        queue.pop(0)
    else:
        x, y = all[line].split()
        queue.append(y)