f = open("sortland.in", "r")
fout = open("sortland.out", "w")
n = int(f.readline())  # длина массива
x = [float(i) for i in f.readline().split()]  # наш массив
ind = []  # массив индексов
for i in range(1, n + 1):
    ind.append(i)
for i in range(n, 1, -1):
    for j in range(i - 1):
        if int(x[j]) > int(x[j + 1]):
            x[j], x[j + 1] = x[j + 1], x[j]
            ind[j], ind[j + 1] = ind[j + 1], ind[j]
mean = (n // 2)  # нахождение среднего чела
print(ind[0], ind[mean], ind[-1], file=fout)
