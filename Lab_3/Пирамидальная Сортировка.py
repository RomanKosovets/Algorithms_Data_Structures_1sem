def heapsort(numbers):
    build_max_heap(numbers)
    for i in range(len(numbers) - 1, 0, -1):
        numbers[0], numbers[i] = numbers[i], numbers[0]
        max_heapify(numbers, index=0, size=i)


def parent(i):
    return (i - 1) // 2


def left(i):
    return 2 * i + 1


def right(i):
    return 2 * i + 2


def build_max_heap(numbers):  # меняем местами первый и последний
    length = len(numbers)
    start = parent(length - 1)
    while start >= 0:
        max_heapify(numbers, index=start, size=length)
        start = start - 1


def max_heapify(numbers, index, size):
    l = left(index)
    r = right(index)
    if l < size and numbers[l] > numbers[index]:
        largest = l
    else:
        largest = index
    if r < size and numbers[r] > numbers[largest]:
        largest = r
    if largest != index:
        numbers[largest], numbers[index] = numbers[index], numbers[largest]
        max_heapify(numbers, largest, size)


fin = open("sort.in", "r")
fout = open("sort.out", "w")

n = int(fin.readline())
numbers = [int(i) for i in fin.readline().split()]

heapsort(numbers)
print(*numbers, file=fout)

'''
1)Создадим функцию heapsort, которая принимает на вход список.
2)Вызовем функцию build_max_heap c параметром numbers для представления листа в виде пирамиды (heap).
3)Поменяем местами первый и последний элемент пирамиды.
4)Вызовем функцию max_heapify, учитывая что новая пирамида имеет размер на единицу меньше. Установим index=0 для удовлетворения параметрам пирамиды.
5)Повторим шаги 3 и 4, пока размер пирамиды не станет 0 и весь список не отсортируется.
6)Определим функцию parent, которая принимает index и возвращает индекс родителя.
7)Определим функцию left, которая принимает index и возвращает индекс левого элемента.
8)Определим функцию right, которая принимает index и возвращает индекс правого элемента.
9)Определим функцию build_max_heap, которая принимает список аргументов и переставляет их в соостветсвии с max heap.
10)build_max_heap вызывает max_heapify на каждом родительском ноде и проходит до вершины.
11)Определим функцию max_heapify, которая принимает индекс и изменяет структуру пирамиды на ноде и снизу от индекса так, чтобы удовлетворять правилам пирамиды.
'''