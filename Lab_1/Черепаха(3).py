fin = open('filein.txt', 'r')
fout = open('fileout.txt', 'w')
x = fin.read()  # считываем наши данные
lines = x.split('\n')  # разделяем на строки
h, w = [int(i) for i in lines[0].split()]  # считываем первые два числа
matrix = [[int(i) for i in line.split()] for line in lines[1:]]  # считываем саму матрицу

for i in range(h - 1, -1, -1):
    for j in range(w):
        if i == h - 1:
            if j != 0:
                matrix[i][j] = matrix[i][j] + matrix[i][j - 1]
        else:
            if j == 0:
                matrix[i][j] = matrix[i][j] + matrix[i + 1][j]
            else:
                matrix[i][j] = matrix[i][j] + max(matrix[i][j - 1], matrix[i + 1][j])

print(str(matrix[0][w - 1]), file=fout)