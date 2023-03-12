def UpperBound(numbers, key):
    left = -1
    right = n
    while right - left > 1:
        mid = (left + right) // 2
        if numbers[mid] <= key:
            left = mid
        else:
            right = mid
    return right


def LowerBound(numbers, key):
    left = -1
    right = n
    while right - left > 1:
        mid = (left + right) // 2
        if numbers[mid] < key:
            left = mid
        else:
            right = mid
    return right

fin = open("filein.txt")
fout = open("fileout.txt")

n = int(fin.readline())  # кол-во чисел
numbers = [int(i) for i in fin.readline().split()]

m = int(fin.readline())  # кол-во запросов
z = [int(i) for i in fin.readline().split()]

for key in z:
    lower = LowerBound(numbers, key)
    upper = UpperBound(numbers, key)
    if lower < n and numbers[lower] == key:
        print(lower + 1, upper)
    else:
        print(-1, -1)
