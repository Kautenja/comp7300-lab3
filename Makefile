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

# the original program
OG = ${BUILD}/myInitializeMatrix

# compile the original file provided by Dr. Biaz
og: build_folder
	${CC} myInitializeMatrix.c -o ${OG}

# run the original code 5 times and collect the output
run_og: og
	${OG} > ${OG}.out
	${OG} >> ${OG}.out
	${OG} >> ${OG}.out
	${OG} >> ${OG}.out
	${OG} >> ${OG}.out


#
# MARK: Experiment 1
#

# the exp1 program
EXP1 = ${BUILD}/exp1

# compile the code for Experiment 1 (improve initialization)
exp1: build_folder
	${CC} exp1.c -o ${EXP1}

# run experiment 1 5 times and produce a graph of the execution
run_exp1: exp1
		${EXP1} > ${EXP1}.out
		${EXP1} >> ${EXP1}.out
		${EXP1} >> ${EXP1}.out
		${EXP1} >> ${EXP1}.out
		${EXP1} >> ${EXP1}.out

#
# MARK: Experiment 2
#

# the exo2 program
EXP2 = ${BUILD}/exp2

# compile the code for experiment 2 (improve transpose)
exp2: build_folder
	${CC} exp2.c -o ${EXP2}

# run experiment 2 5 times and produce a graph of the execution
run_exp2: exp2
		${EXP2} > ${EXP2}.out
		${EXP2} >> ${EXP2}.out
		${EXP2} >> ${EXP2}.out
		${EXP2} >> ${EXP2}.out
		${EXP2} >> ${EXP2}.out


#
# MARK: Full Stack
#

# run all the experiments sequentially
run_all: run_og, run_exp1, run_exp2
