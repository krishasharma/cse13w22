# Assignment 7 : Author Identification

## Short Description: 
        Assignment 7: Author Identification has the overall task of creating a program that attempts to identify the most likely authors for an anonymous sample of text given a large database of texts with known authors. Modern-day stylometry usually is performed using machine learning, achieving high identification accuracies by learning over time, but implementing this from scratch would take an extraordinary effort. Instead during this assignment, we will be using an algorithm that’s commonly used in machine learning to identify authors of anonymous samples of text, albeit less accurately. 
 
## Build 
        To build the program manually, type "clang -Wall -Wextra -Werror -Wpedantic -o identify identify.c" on the command line.
        Alternatively, type "make" on the command line, using the Makefile provided.

## Running 
        To run the program on the command line follow this structure for what to type on the command line, "./identify -i <infile> -o <outfile>"
        To get the usage statements and synopsis type "./identify -h" on the command line.

## Errors
        The current version of the code does not work as intended. identify.c incomplete.

## Error Handling
        The current version of the code does not work as intended. Running ./identify  would not output all of the desired results
        If there is another error please refrence the usage statements given by -h

## Cleaning 
        make clean
