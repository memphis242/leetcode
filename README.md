# My LeetCode Solutions Notebook :green_book:
Tracking my LeetCode solutions here, with the intent to initially perform all the solutions in C, and eventually to try C++, Python, Rust, and JavaScript. The goal is to use LeetCode as a sharpening tool for my DS&A skills in each of those languages.

## To Build...
I have a [`Common.mk`](./Common.mk) at the root of the repository that includes a common definition of compiler settings and rules that are repeatedly used to build each solution program. Each solution program is in its own subdirectory - e.g., [`2 Add Two Numbers`](./2%20Add%20Two%20Numbers/) - with a simple `Makefile` that specifies the name of the source file (without the extension) and includes the `Common.mk` file - e.g., [`2 Add Two Numbers/Makefile`](./2%20Add%20Two%20Numbers/Makefile).  

The build will do the following:  
- Produce an executable of the solution program
   - The solution program is written with some example test cases and a `main` function, so when it is run, it runs the internal test cases against the solution.
   - :spiral_notepad::grey_exclamation:FUTURE TODO:grey_exclamation:: Separate test program that passes in various test case inputs
- Run a static analysis check against the source
- Produce a disassembly of the executable

### C
Tools Used:
- gcc
- cppcheck
- objdump