# C++ Projects

This repository contains the following C++ assignments:

1. Binary Search Tree (BST) Extension
2. Maze Generator (Mentioned in the CV)
3. Knight's Tour

## Binary Search Tree (BST) Extension

This assignment extends a simple Binary Search Tree (BST) from Assignment W6 by adding a function called `prettyPrint()`. The function displays the structure of the BST that is built up when inserting nodes.
## Maze Generator

This program generates random mazes and finds a path from a beginning to an end position. It then prints the maze on the screen. The program reads from the command line parameters the number of rows and columns of the maze and an optional third parameter to be used as a seed value for the random generator.

## Knight's Tour

This program finds a knight's tour from a start square to an end square on a chess board of a given size. Each square on the board must be used at most once. The knight's tour does not need to be the shortest possible. The program reads the problem description (board size, start square, end square) from the command line parameters and prints a possible tour to std::cout.

## Compilation and Execution

To compile and execute the programs, navigate to the respective folder and follow the instructions below:

1. For the BST extension, run:
    ```
    g++ -o bst bst.cpp
    ./bst
    ```

2. For the Maze Generator, run:
    ```
    g++ -o mazegen maze_generator.cpp
    ./mazegen <rows> <columns> [<seed>]
    ```

3. For the Knight's Tour, run:
    ```
    g++ -o knight knights_tour.cpp
    ./knight <board_size> <start_square> <end_square>
    ```

Replace `<rows>`, `<columns>`, `<seed>`, `<board_size>`, `<start_square>`, and `<end_square>` with appropriate values according to the assignment requirements.
