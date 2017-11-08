# README: this makefile contains shortcuts for running programs in this
#         repository
# GLOBALS:
CC = cc
BUILD = ./build


#
# MARK: Build Artifacts
#


# make the build folder for compiled code
build_folder:
	mkdir -p ${BUILD}

# clean out the build folder
clean: build_folder
	rm -rf ${BUILD}/*


#
# MARK: Provided Files
#


# compile the original file provided by Dr. Biaz
og: build_folder
	${CC} myInitializeMatrix.c -o ${BUILD}/myInitializeMatrix


#
# MARK: Experiment 1
#


# compile the code for Experiment 1 (improve initialization)
exp1: build_folder
	${CC} exp1.c -o ${BUILD}/exp1

# run experiment 1 5 times and produce a graph of the execution
run_exp1: exp1
	build/exp1
	build/exp1
	build/exp1
	build/exp1
	build/exp1


#
# MARK: Experiment 2
#


# compile the code for experiment 2 (improve transpose)
exp2: build_folder
	${CC} exp2.c -o ${BUILD}/exp2

# run experiment 2 5 times and produce a graph of the execution
run_exp1: exp2
	build/exp2
	build/exp2
	build/exp2
	build/exp2
	build/exp2