# COMP7300 - Lab3

## Getting Started

These instructions will get you a copy of the project up and running on your
local machine for development and testing purposes. See deployment for notes on
how to deploy the project on a live system.

### Prerequisites

This code is written in C and compiled with `cc`.

### Makefile

[Makefile](./Makefile) contains quick shortcuts for basic activities in the
command line. These shortcuts create build folders, compile code, and manage
the automated sequential execution of experiments for averaged results.

## Usage

**Execute all commands from the top level of the project's file structure.**

### Original Code

[myInitializeMatrix.c](myInitializeMatrix.c) contains the code provided by Dr.
Biaz. to compile and execute it run:

```shell
./run.sh myInitializeMatrix
```

### Optimized Initialization

[exp1.c](exp1.c) contains the optimized matrix _initialization_ code. To
compile and execute it run:

```shell
./run.sh exp1
```

### Optimized Transpose

[exp2.c](exp2.c) contains the optimized matrix _transpose_ code. To compile
and execute it run:

```shell
./run.sh exp2
```
