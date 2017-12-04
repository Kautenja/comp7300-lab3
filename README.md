# COMP7300 - Lab3

[![Build Status](https://travis-ci.org/Kautenja/comp7300-lab3.svg?branch=master)](https://travis-ci.org/Kautenja/comp7300-lab3)

## Usage

### Compilation

The code uses threads with `-pthread` flag. The usage of the `-Ofast` flag
enables all compile-time optimizations.

	cc -Ofast -pthread <code_file> -o <output_executable>

##### Example

	cc -Ofast -pthread rowwise.c -o rowwise

### Test Automation

The 5 test runs are automated with a shell script. Make sure the permissions
are set correctly first by executing the following from the top level of the
project:

	chmod 0755 ./run.sh

A test can be executed using the following command from the top level:

	./run.sh <code file name>

This will route the shell output to a file in the [`build`](./build) directory
called `<code file name>.out`. Note that the `.c` **IS NOT** included in this
command.

##### Example

To run the default provided code (adjusted for 7 tests):

	./run.sh myInitializeMatrix

#### [`rowwise.c`](./rowwise.c)

contains the code for row-wise initialization and transpose. To compile and run
the row-wise initialization (and optimized transposition):

	mkdir -p build
	cc -Ofast -pthread rowwise.c -o build/rowwise
	./build/rowwise

To compile and run the 5 consecutive tests saving the output to a file:

	./run.sh rowwise

#### [`columnwise.c`](columnwise.c)

contains the code for column-wsie intialization and transpose. To compile and
run the column-wise initialization (and optimized transposition):

	mkdir -p build
	cc -Ofast -pthread columnwise.c -o build/columnwise
	./build/columnwise

To compile and run the 5 consecutive tests saving the output to a file:

	./run.sh columnwise
