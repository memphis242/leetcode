import random
from typing import List, Set

class RotatingNumber:
    _NUMSET: Set[int]
    _workingset: Set[int]

    def __init__(self, numset: Set[int]):
        self._NUMSET = set(numset)
        self._workingset = set(numset)

    def getnum(self) -> int | None:
        num = None

        if self._workingset:
            num = self._workingset.pop()

        else:
            self._workingset.update(self._NUMSET)
            if self._workingset:
                num = self._workingset.pop()

        return num


with open("testcases.cpp", "w") as file:

    fstr = """#include <vector>

std::vector<std::vector<int>> testcases =
{"""

    # Let's generate 20 test cases, with at least one from each of the following
    # lengths used as the vector length of the test case.
    lens = { 10, 100, 1000, 10_000, 100_000 }
    rotnum = RotatingNumber(lens)

    for i in range(20):
        vlen = rotnum.getnum()
        vec = [ random.randint(-10_000, 10_000) for _ in range(vlen) ]
        lstr = "\n\t{ "
        for idx, num in enumerate(vec):
            if idx > 0 and idx % 25 == 0:
                lstr += "\n\t  "
            lstr += str(num) + ", "
        lstr = lstr[:-2] # Remove trailing comma and space for last element
        lstr += " },\n"
        fstr += lstr

    fstr += "\n};"

    file.write(fstr);

