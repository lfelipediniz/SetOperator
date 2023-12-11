# SetOperator

Welcome to the SetOperator program, a specialized tool designed to manage and manipulate sets in computing. In the realm of mathematics, particularly in Set Theory, a set is a fundamental concept representing a collection of distinct objects, each referred to as an element. The pivotal relationship in set theory is the membership relation, which establishes whether an element belongs to a specific set or not. Sets have a wide range of applications in computer systems, featuring prominently in various programming languages as a Data Structure (DS) and in solving mathematical, optimization, and statistical problems.

## Objective
The primary objective of SetOperator is to implement the Abstract Data Type (ADT) for sets in such a way that the chosen Data Structure facilitates the execution of specific operations with the lowest possible computational complexity. The program focuses on two categories of operations:

### General ADT Operations:
- Create: Initialize a new set.
- Delete: Remove an existing set.
- Insert: Add an element to a set.
- Remove: Delete an element from a set.
- Print: Display the elements/items stored in the ADT.

### Set-Specific Operations:
- Membership: Determine whether an element is present in a set.
- Union: Combine two sets into one, containing all the elements from both sets.
- Intersection: Create a set containing only the elements common to two sets.

## Getting Started

To use SetOperator, follow the instructions below:

### Prerequisites

- GCC (GNU Compiler Collection)
- Make

### Installation

1. Clone the repository

    ```bash
    git clone https://github.com/lfelipediniz/SetOperator.git
    ```

2. Navigate to the project directory

    ```bash
    cd SetOperator
    ```

### Run

You can test the program manually through the Makefile

1. Give permission for the script to become executable

    ```bash
    make
    ```

2. Execute the program (with either of the two commands)

    ```bash
    make run
    ```

3. To delete the generated files run

    ```bash
    make clean
    ```


Or use the sh script that runs all test cases present in the test folder, indicating which cases passed

1. Compile and run the program using the provided Makefile

    ```bash
    sudo chmod +x runTests.sh
    ```

2. Execute the case tests

    ```bash
    ./runTests.sh
    ```

## Usage

To manage sets effectively, users have access to a variety of commands. Each command is to be used within code blocks for clarity. Here’s a breakdown of these commands:

1. Create a new set

    ```bash
    create-set <set name>
    ```

2. Delete an existing set

    ```bash
    delete-set <set name>
    ```

3. A

    ```bash
    delete-set <set name>
    ```



### Explaining the use in more detail

## Test case
All test cases are in the test folder


## Authors

| Names                       | USP Number |
| :---------------------------| ---------- |
| Luiz Felipe Diniz Costa     | 13782032   |
| Nicolas Carreiro Rodrigues  | 14600801   |

Project for the course ["Algorithm and Data Structure"](https://uspdigital.usp.br/jupiterweb/obterDisciplina?sgldis=SSC0902) at the Institute of Mathematics and Computer Science, University of Sao Paulo



