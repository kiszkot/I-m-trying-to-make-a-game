import sys
import os

file = open(sys.argv[1], "r")
tmp = open("tmp", "w")
line = file.readline()

while line:
    line = line.replace("\n", "")
    tmp_digits = line.split(",") #re.sub(r"\b\d\b", "0.", line)
    tmp_line = ""
    for i in tmp_digits:
        if(len(i) == 1):
            tmp_line = tmp_line + "0" + i + ","
        else:
            tmp_line = tmp_line + i + ","
    tmp_line = tmp_line[-len(tmp_line):-1]
    tmp.write(tmp_line + "\n")
    line = file.readline()

file.close()
tmp.close()

os.remove(sys.argv[1])
os.rename("tmp", sys.argv[1])