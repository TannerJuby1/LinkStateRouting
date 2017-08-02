*******************************************************
*  Name      :  Tanner Juby        
*  Student ID:  101680435               
*  Class     :  CSCI 4761           
*  LAB#      :  3                
*  Due Date  :  May 3, 2017
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

Implementing Link State Routing (Dijkstra’s Algorithm)
that will simulate generating a forwarding table for 
a graph sent in as a text file


*******************************************************
*  Source files
*******************************************************

Name:  LinkStateRouting.cpp
   The Link State Routing algorithm. Reads in a file,
   runs Dijkstra’s Algorithm, and prints the results

   
*******************************************************
*  Circumstances of programs
*******************************************************

   This program works and runs as intended.

   The test input files must use the number 1073741824 
   for connections that don’t exist. If it is a different 
   number it will recognize it as a connection with the 
   cost of whatever you have in there instead
  
   The program was tested on 
	Computer: My Personal Mac Book Pro
	C++ Version: 4.2.1

   The program was also tested on:
	Computer: CSEGrid
	C++ Version: 4.4.7

*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the tar file
        tar -xvzf JUB0435.tar

   Now you should see a directory named homework with the files:
	LinkStateRouting.cpp
	LinkStateRouting.hpp
        makefile
	README.txt
	test10nodes
	test100nodes
	test1000nodes

2. Build the program.

    Change to the directory that contains the file by:
    cd Lab3

    Compile the program by:
    make

5. Run the client side (from another terminal window:
   ./LinkStateRouting <test-input-file> <node i> <flag>

6. Delete the obj files, executables, and core dump by
   ./make clean
