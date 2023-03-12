f = open('filein.txt', 'r')
fout = open('fileout.txt', 'w')

n = int(f.readline().strip())
x = [int(i) for i in f.readline().split()]
for i in range(n, 1, -1):
    for j in range(i - 1):
        if int(x[j]) > int(x[j + 1]):
            x[j], x[j + 1] = x[j + 1], x[j]

print(' '.join(([str(i) for i in x])), file=fout)
