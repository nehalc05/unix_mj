# UNIX Mini Judge

A lightweight command-line programming judge developed as a UNIX Programming project.

## Overview

UNIX Mini Judge allows a user to select a programming problem, submit a C program, compile it automatically, and test it against multiple predefined test cases.

The judge executes the submitted program as a separate process and compares its output with the expected output.

## Features

* Problem selection
* Problem description display
* Automatic C program compilation
* Multiple test cases
* Automatic test-case discovery
* Numerical test-case ordering
* Output comparison
* Accepted / Wrong Answer detection
* Runtime Error detection
* Time Limit Exceeded detection
* Final test summary

## UNIX Concepts Used

The project demonstrates important UNIX concepts and system calls:

* `fork()` – creates a child process
* `exec()` – executes the submitted program
* `waitpid()` – monitors the child process
* `dup2()` – redirects standard input and output
* `open()` – opens input and output files
* `opendir()` / `readdir()` – discovers test cases
* `kill()` – terminates programs exceeding the time limit

## Project Structure

```text
unix_minijudge/
├── main.c
├── judge.c
├── judge.h
├── runner.c
├── runner.h
├── Makefile
├── problems/
│   ├── problem1/
│   │   ├── problem.txt
│   │   ├── test1.in
│   │   ├── test1.out
│   │   ├── test2.in
│   │   └── test2.out
│   └── problem2/
│       ├── problem.txt
│       ├── test1.in
│       ├── test1.out
│       ├── test2.in
│       └── test2.out
└── submissions/
    ├── sum.c
    └── max.c
```

## How to Run

### 1. Open the project

```bash
cd ~/unix_minijudge
```

### 2. Compile the judge

```bash
gcc main.c runner.c judge.c -o minijudge
```

### 3. Run the judge

```bash
./minijudge
```

### 4. Select a problem

For example:

```text
Enter problem number: 1
```

### 5. Provide the submission

```text
Enter solution file path: submissions/sum.c
```

The judge will compile the submission, run all available test cases, compare the outputs, and display the final result.

## Example Output

```text
Running test cases...

Test Case 1: test1.in
Result: ACCEPTED

Test Case 2: test2.in
Result: ACCEPTED

====================
       SUMMARY
====================
Total Tests     : 2
Accepted        : 2
Wrong Answers   : 0
Runtime Errors  : 0
Time Limit      : 0
--------------------
Final Result    : ACCEPTED
```

## Technologies

* C
* UNIX/Linux
* GCC
* UNIX system calls
* File handling
* Process management

## Project Type

UNIX Programming / Operating Systems Project
