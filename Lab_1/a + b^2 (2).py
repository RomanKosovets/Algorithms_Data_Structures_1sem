f = open("aplusbb.in", "r")
fout = open("aplusbb.out", "w")
a, b = map(int, f.readline().split())
print(a + b * b, file=fout)
fout.close()