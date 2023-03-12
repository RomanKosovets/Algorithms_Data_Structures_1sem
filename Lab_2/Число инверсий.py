fin = open("filein1.txt", 'r')
fout = open('fileout1.txt', 'w')
x = fin.readlines()[1]
lst = [int(i) for i in x.split()]


def count_inversion(lst):
    return merge_sort(lst)


def merge_sort(lst):
    if len(lst) <= 1:
        return lst, 0
    middle = int(len(lst) / 2)
    left, a = merge_sort(lst[:middle])
    right, b = merge_sort(lst[middle:])
    result, c = merge_count_split_inversion(left, right)
    return result, (a + b + c)


def merge_count_split_inversion(left, right):
    result = []
    count = 0
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            count += len(left) - i
            j += 1
    result += left[i:]
    result += right[j:]
    return result, count


print(count_inversion(lst)[1], file=fout)
