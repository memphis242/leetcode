FZMap = { 3 : "Fizz", 5 : "Buzz" }

outstr = ""
for i in range(1, 100 + 1):
    itrstr = ""
    for div,fzstr in FZMap.items():
        if i % div == 0:
            itrstr += fzstr

    if not itrstr:
        itrstr += str(i)

    outstr += itrstr + " "

print(outstr)
