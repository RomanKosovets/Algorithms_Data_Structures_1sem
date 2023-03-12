import random
fin = open('sort.in', 'r')
fout = open('sort.out', 'w')
x = fin.readlines()[1]
numbers = [int(i) for i in x.split()]


def quick_sort(numbers):
    if len(numbers) <= 1:
        return numbers
    index = random.randint(0, len(numbers) - 1)
    elem = numbers[index]
    left = list(filter(lambda x: x < elem, numbers))
    center = [i for i in numbers if i == elem]
    right = list(filter(lambda x: x > elem, numbers))
    return quick_sort(left) + center + quick_sort(right)


print(*quick_sort(numbers), file=fout)