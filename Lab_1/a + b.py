f = open("aplusb.in", "r")
fout = open("aplusb.out", "w")
a, b = map(int, f.readline().split())  # map позволяет обращаться к каждому объекту
print(a + b, file=fout)
f.close()
fout.close()
