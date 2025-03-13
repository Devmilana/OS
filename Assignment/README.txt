#####  SUDOKU SOLUTION VALIDATOR  #####

This program checks if a given 9x9 sudoku solution is valid or not

1. To run this program, first compile all files by running:

        make

1.1 Running the make command each time will remove previous object files before recompiling
    If you want to remove all object files without recompiling, simply run:

        make clean

2. After successfull compilation of files through the 'make' command, run the program using:

        ./mssv <file.txt> <delay_time> 
    
    where file.txt is the text file with the solution to be validated
    delay time is the delay time per thread for the program

3. Be sure to place the solution text file in the same location as the program files

4. Please allow approximately 5 secs for the program to finish computations



####  GIVING YOUR OWN SOLUTION FILE  ####

A valid solution file will have 9 rows and 9 columns of integer numbers from 1 to 9, where each column of numbers is separated by a whitespace

eg: 

6 2 4 5 3 9 1 8 7
5 1 9 7 2 8 6 3 4
8 3 7 6 1 4 2 9 5
1 4 3 8 6 5 7 2 9
9 5 8 2 4 7 3 6 1
7 6 2 3 9 1 4 5 8
3 7 1 9 5 6 8 4 2
4 9 6 1 8 2 5 7 3
2 8 5 4 7 3 9 1 6


You are free to make your own solution file for testing as long as it adheres to the above format