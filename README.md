# COMP7300 - Lab3

[![Build Status](https://travis-ci.com/Kautenja/comp7300-lab3.svg?token=FCkX2qMNHzx2qWEzZZMP&branch=master)](https://travis-ci.com/Kautenja/comp7300-lab3)

## Getting Started

These instructions will get you a copy of the project up and running on your
local machine for development and testing purposes. See deployment for notes on
how to deploy the project on a live system.

### Prerequisites

This code is written in C and compiled with `cc`.

## Usage

### Compilation

The code uses threads with `pthread`.

	cc -pthread <code_file> -o <output_executable>

##### Example

	cc -pthread rowwise.c -o rowwise

### Test Automation

The 5 test runs are automated with a shell script. Make sure the permissions
are set correctly first:

	chmod 0755 run.sh

A test can be executed using the following command:

	run.sh <code file name>

This will route the shell output to a file in the [`build`](./build) directory
called `<code file name>.out`.

##### Example

	run.sh myInitializeMatrix

#### [`rowwise.c`](./rowwise.c)

To run the _Row-Wise_ initialization (and optimized transposition):

	run.sh rowwise

#### [`columnwise.c`](columnwise.c)

To run the _Column-Wise_ initialization (and optimized transposition):

	run.sh columnwise
