Input Format:
    value of N followed by space and then value of K and then value of rowInc
    Values of entries in the matrix such that rows are seperated by newline and values are seperated by spaces.

    N K rowIncr
    matrix A

Input file should be named as "inp.txt" and should be placed in the same folder as of the code.

To compile the program:
    Open terminal in this folder and run the command
    g++ -pthread filename.cpp -o ./filename
    Ex: g++ -pthread Assgn3_Src-CS22BTECH11050_TAS.cpp -o ./Assgn3_Src-CS22BTECH11050_TAS

To execute :
    Run the command
    ./filename
    Ex : ./Assgn3_Src-CS22BTECH11050_TAS

Output Format :
    Output files are created which contain the entries of output matrix along with the time taken for computation.
    Output file names would be as "out_TAS.txt" , "out_CAS.txt","out_BCAS.txt","out_Atomic.txt".