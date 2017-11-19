# COMP7300 - Lab3

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

	run.sh <code file name (WITHOUT.c)>

##### Example

	run.sh myInitializeMatrix
