.POSIX:
CROSS	= 
CC = $(CROSS)gcc
COMPILER_WARNING_FLAGS = -Wall -Wextra -Wconversion -Wdouble-promotion -Wnull-dereference -Wwrite-strings -Wformat=2 -Wcast-align=strict -Wswitch-enum -Wpedantic
# COMPILER_SANITIZERS =
COMPILER_SANITIZERS = -fsanitize=bool -fsanitize=undefined -fsanitize-trap
COMPILER_OPTIMIZATION_LEVEL = -Og -g3
COMPILER_OPTIMIZATION_LEVEL_SPEED = -O3
COMPILER_OPTIMIZATION_LEVEL_SPACE = -Os
CFLAGS = $(COMPILER_WARNING_FLAGS) $(COMPILER_SANITIZERS) $(COMPILER_OPTIMIZATION_LEVEL)
CFLAGS_FAST = $(COMPILER_WARNING_FLAGS) $(COMPILER_OPTIMIZATION_LEVEL_SPEED)
CFLAGS_SMALL = $(COMPILER_WARNING_FLAGS) $(COMPILER_OPTIMIZATION_LEVEL_SPACE)
LDFLAGS = 

# Ensure SOURCE_FILE is defined in the subfolder Makefile
ifndef DSA_SOURCE_NAME
$(error SOURCE_FILE is not defined. Please define it in the subfolder Makefile.)
endif

ifndef TEST_FILE_NAME
$(error TEST_FILE is not defined. Please define it in the subfolder Makefile.)
endif

# Rules for building the executable, object file, and listing file

# Run it, baby!
.PHONY: run
run: $(TEST_FILE_NAME).exe $(TEST_FILE_NAME).lst	# Don't actually need the .lst file but want to force the disassembly generation
	@echo
	@echo "----------------------------------------"
	@echo "Running the test..."
	@echo
	./$(TEST_FILE_NAME).exe

# Produces an object dump that includes the disassembly of the executable
$(TEST_FILE_NAME).lst: $(TEST_FILE_NAME).exe
	@echo
	@echo "----------------------------------------"
	@echo "Disassembly of $<..."
	@echo
	objdump -D $< > $@

# Build the executable
$(TEST_FILE_NAME).exe: $(TEST_FILE_NAME).o lib$(DSA_SOURCE_NAME).a
	@echo
	@echo "----------------------------------------"
	@echo "Linking $< and the DSA static lib into executable..."
	@echo
	$(CC) $(LDFLAGS) $< -L. -l$(DSA_SOURCE_NAME) -o $@

# Build the object file and run static analysis against it
$(TEST_FILE_NAME).o: $(TEST_FILE_NAME).c
	@echo
	@echo "----------------------------------------"
	@echo "Compiling the test file: $<..."
	@echo
	$(CC) -c $(CFLAGS) $< -o $@
	@echo
	@echo "----------------------------------------"
	@echo "Running static analysis on $<..."
	@echo
	cppcheck $<

# Build the library of the DS in question
lib$(DSA_SOURCE_NAME).a : $(DSA_SOURCE_NAME).o
	@echo
	@echo "----------------------------------------"
	@echo "Constructing static library of DSA: $<..."
	@echo
	ar rcs $@ $<

# Compile the DSA source file into an object file
$(DSA_SOURCE_NAME).o : $(DSA_SOURCE_NAME).c
	@echo
	@echo "----------------------------------------"
	@echo "Compiling the DSA source file: $<..."
	@echo
	$(CC) -c $(CFLAGS) $< -o $@
	@echo
	@echo "----------------------------------------"
	@echo "Running static analysis on $<..."
	@echo
	cppcheck --template='{severity}: {file}:{line}: {message}' $< 2>&1 | tee cppcheck.log | python ../../../colorize_cppcheck.py

# Clean rule to remove generated files
.PHONY: clean
clean:
	rm -f *.exe *.o *.lst