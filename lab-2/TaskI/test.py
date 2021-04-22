f = open("test1.txt", "w")

for i in range(1, 1000) :
  f.write("a " + str(i) + "\n")
f.close()