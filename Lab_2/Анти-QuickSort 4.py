fin = open("filein1.txt", "r")
fout = open("fileout1.txt", "w")
n = int(fin.readline())
mas = []
i = 1
j = 2
for i in range(1, n + 1):
    mas.append(i)
for j in range(j, n):
    mas[j], mas[int(j / 2)] = mas[int(j / 2)], mas[j]
print(*mas, file=fout)
