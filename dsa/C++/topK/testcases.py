import random
from typing import Set, Optional
import sys

class RotatingNumber:
    """
    RotatingNumber manages a set of integers and allows retrieval of elements in a rotating fashion.

    Attributes:
        _numset (Set[int]): The original set of numbers.
        _workingset (Set[int]): The current working set of numbers to be returned.

    Methods:
        __init__(numset: Set[int]):
            Initializes the RotatingNumber with a given set of integers.

        getnum() -> Optional[int]:
            Returns and removes an integer from the working set. When the working set is empty,
            it is reset to the original set and an integer is returned. Returns None if the set is empty.
    """
    _numset: Set[int]
    _workingset: Set[int]

    def __init__(self, numset: Set[int]):
        self._numset = set(numset)
        self._workingset = set(numset)

    def getnum(self) -> Optional[int]:
        num = None

        if self._workingset:
            num = self._workingset.pop()

        else:
            self._workingset.update(self._numset)
            if self._workingset:
                num = self._workingset.pop()

        return num

def generate_testcases(
        NUM_OF_TESTCASES: int = 20,
        LENS: Set[int] = { 10, 100, 1000, 10_000, 100_000 }
    ) -> str:
    """
    Generate a string that will represent the file contents of the output C++
    test cases source file. This will be a vector of vectors of int, each of
    length from the set { 10, 100, 1000, 10,000, 100,000 } and with a random set
    of integers from -10,000 to 10,000. The last test vector, however, will simply
    be a sequence from 1 to 10,000.
    """
    BOT_OF_RNG = -10_000
    TOP_OF_RNG = 10_000

    assert NUM_OF_TESTCASES > 0, "Number of test cases needs to be > 0"

    fstr = """#include <vector>

    std::vector<std::vector<int>> testcases =
    {"""

    # Let's generate 20 test cases, with at least one from each of the following
    # lengths used as the vector length of the test case.
    rotnum = RotatingNumber(LENS)

    for _ in range(NUM_OF_TESTCASES - 2):
        vlen = rotnum.getnum()
        if not vlen:
            vlen = 0
        vec = [ random.randint(BOT_OF_RNG, TOP_OF_RNG) for _ in range(vlen) ]
        lstr = "\n\t{ "
        for idx, num in enumerate(vec):
            # Add a new line every 25 numbers, just so a line doesn't go too far
            if idx > 0 and idx % 25 == 0:
                lstr += "\n\t  "
            lstr += str(num) + ", "
        lstr = lstr[:-2] # Remove trailing comma and space from last element
        lstr += " },\n"
        fstr += lstr
    
    # One empty vector as a test case
    fstr += "\n\t{ },\n"

    # One more test case, which will just be a sequence of increasing numbers
    lstr = "\n\t{ "
    vec = [i for i in range(10_000)]
    for idx, num in enumerate(vec):
        if idx > 0 and idx % 25 == 0:
            lstr += "\n\t  "
        lstr += str(num) + ", "
    lstr = lstr[:-2] # Remove trailing comma and space for last element
    lstr += " },\n"
    fstr += lstr

    fstr += "\n};"

    assert len(fstr) > 0, "Error: Somehow, the file content string is empty after generation."
    return fstr


##################################### MAIN #####################################

if __name__ == "__main__":

    fcontent = generate_testcases()
    if fcontent:
        try:
            with open("testcases.cpp", "w") as f:
                f.write(fcontent)
                print("Successfully generated testcases.cpp file.")

        except FileNotFoundError:
            print("Error: Could not create the file. The directory might not exist.", file=sys.stderr)
        except PermissionError:
            print("Permission denied. Check if you have write permissions for this directory.", file=sys.stderr)
        except IsADirectoryError:
            print("The specified path is a directory, not a file.", file=sys.stderr)
        except IOError as e:
            print(f"General I/O error occurred: {e}", file=sys.stderr)
        except Exception as e:
            print(f"An unexpected error occurred: {e}", file=sys.stderr)
    
    else:
        print("No content generated, nothing to write to file.")
        sys.exit(1)
