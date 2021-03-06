// MIPS Single Cycle CPU
// Written by Iveth and LaFrance
// CSE 140 - Spring 2022
// University of California - Merced

/*
Work Distribution:
*/

/*
instructions if using linux... to run you have to compile using gcc
use: gcc LaFrance_Iveth.c --this compiles the program (only use if you dont want to name an executable file)
next we have to create an executable file to show output:
use: gcc LaFrance_Iveth.c -o LaFrance_Iveth (this is prefered and make sure to use everytime you add or delete code)
finally we have to run the program using the executable file which we name after "-o")
use: ./LaFrance_Iveth (always use after compiling to see output, run the executable file that contains output)
*/

/*
Any Used Resources to be Cited:
For the Fetch Function (While Loop Process): https://stackoverflow.com/questions/3501338/c-read-file-line-by-line

*/

#include <stdio.h> //a standard C library that includes the print function
#include <string.h>
#include <stdlib.h>
#include "Decoder.h"
#include "Execute.h"

#define MAX_LENGTH 256 // using a length variable to help with reading the line of text

// global variables:
int PC = 0;                                        // Starting Instruction
char *instruction_counter[10][32]; // to act as a container pointing to an instruction
unsigned char current_instruction[32];     // a universal pointer for instructions
int i = 0;                                         // representing the instruction in the array:
int instruction_index = 4;                         // representing the index in the instruction counter

///////////////////////////////////////////////////////////////////////

// never changing filename (obviously change when you recieve a finalized file):
const char *filename = "sample_ins.txt";

//////////////////////////////////////////////////////////////////////

// functions declarations:
void CPU_Process(); // to act as the main CPU function
char fetch();       // to fetch instructions for the PC counter

//////////////////////////////////////////////////////////////////////

int main()
{
    printf("Welcome to our Single Cycle MIPS CPU!\n");
    // char instruction_catch; //will catch the results after fetch() is called (will be considered int in output)
    
    //////////////--attempt to read instructions--////////////////

    // creating an File Pointer object:
    FILE *file_accessor; // object

    file_accessor = fopen("sample_ins.txt", "r"); // using the fopen function to read from a file

    char instr_table[3][32];
    int i,j;

     // CONDITIONS:
    if (file_accessor == NULL) // if theres nothing in the text file then we cant continue
    {
        printf("This file is empty, no instruction... now ending process!\n");
        exit(1); // to exit the function with a failure
    }            // end of if
   // else{ //where we have some text:

    //loading text onto the array
    for(i=0; i<3; i++) {
        for(j=0; j<32; j++) {
                //fprintf(stderr, "No character found");
                 //   return 1;
                 // to get rid of the newline (for each line):
                if (j == 32)
                {
                    instr_table[i][32] = '\0';
                    fscanf(file_accessor,"%c",&instr_table[i][j]);//scanning for every character

                }else{
                    fscanf(file_accessor,"%c",&instr_table[i][j]);//scanning for every character
                }
                
            
        }
        printf("\n");
    }


    //printing the text
    for(i=0; i<3; i++) {
        for(j=0; j<32; j++) {
            printf("Instruction:%c",instr_table[i][j]); //printing the strings 
            
        }
    }
    printf("\n");
    //} //end of else
    //fclose(file_accessor);

    for (int k= 0;k < 32; k++)
    {
         printf("Some instruction: %c\n", instr_table[2][k]);
    }
    
   
    /////////////////////////////////////////////////////////////

    CPU_Process(); //start the CPU

    return 0; // ending the program
} // end of main function

void CPU_Process()
{
    // unsigned char current_instruction =

    printf("Preparing to fectch the 32 bit instruction....\n");
    printf("\n");

    // current_instruction = fetch();
    //fetch();

    // printf("\n");
    // printf("Decoding the Instruction.....");
    // Decode(instruction_counter[12][32]);

} // end of CPU Process Function

// A function to both fetch and decode a given instruction:
char fetch()
{
    // we need a bit string (character array) to carry the instruction:
    char instruction[MAX_LENGTH]; // to carry the new 32 bit instruction

    printf("Fetching the Instruction...\n");

    // creating an File Pointer object:
    FILE *file_accessor; // object

    file_accessor = fopen(filename, "r"); // using the fopen function to read from a file

    // CONDITIONS:
    if (file_accessor == NULL) // if theres nothing in the text file then we cant continue
    {
        printf("This file is empty, no instruction... now ending process!\n");
        exit(1); // to exit the function with a failure
    }            // end of if
    else
    {

        printf("Instruction(s) Detected... now fetching!\n");
        printf("\n");

    for(int x = 4; x < 14; x=x+4){
        // to read the file, line by line and add the contents to our carry variable
        fgets(instruction, 32, file_accessor);
         // going to the line

            // indicating that instruction was fetched:
            printf("\n");
            printf("Instruction Fetched!\n");

            // to get rid of the newline (for each line):
            instruction[strcspn(instruction, "\n")] = 0;

            instruction_counter[x][32] = instruction; // the instruction gets loaded at a particular location 4 spaces from one another or PC(4)

            // to print the instruction bit by bit -- tests:
            printf("Your 32 bit instruction was: %s\n", instruction_counter[x][32]);
            printf("\n");
            printf("Instruction List Index position: %d\n", x);

            // printf("\n");
            // printf("Decoding the Instruction.....");
            // Decode(instruction_counter[PC][32]);

            ////////// -- increments -- ///////////
            //instruction_index = instruction_index + 4; // because we need to allow for 4 bytes per instruction

            i++; // representing the instruction (everytime we grab an instruction we must update i by 1 so the PC counter can point to it)
            printf("printing the number of the instruction we are looking at:  %d\n", i);

            PC = 4 * i; // always update the PC everytime you read an instruction
            printf("printing the PC char:  %d\n", PC);

            int next_PC = PC + 4;
            printf("printing the next_pc: %d\n", next_PC);

            printf("\n");
         // end of while

        fclose(file_accessor); // closing the read file (will need to be controlled by the PC)
    } //end of while
    } //end of first for
    printf("Printing the Instruction Index: %d\n", instruction_index);

    for (int j = 4; j < instruction_index; j = j + 4)
    {
        printf("Printing j: %d\n", j);
        printf("Printing contents of the instruction list: %s\n", instruction_counter[j][32]);
    }
    printf("\n");
    printf("Printing some random instruction: %s\n", instruction_counter[4][32]);
    // 00000001000010011000100000100000

    return 0; // ending the instruction
} // end of fetch


///////////////////// ---first ver of code --///////////////////
// #include <stdio.h> //a standard C library that includes the print function
// #include <string.h>
// #include <stdlib.h>
// #include "Decoder.h"
// #include "Execute.h"

// #define MAX_LENGTH 256 // using a length variable to help with reading the line of text

// // global variables:
// int PC = 0;                                        // Starting Instruction
// char *instruction_counter[MAX_LENGTH][MAX_LENGTH]; // to act as a container pointing to an instruction
// // char *instruction[MAX_LENGTH];                     // a universal pointer for instructions
// int i = 0;                 // starting location in the instruction counter:
// int instruction_index = 0; // the instruction_index to be added by 4 everytime;
// int cycles;

// // never changing filename (obviously change when you recieve a finalized file):
// const char *filename = "sample_ins.txt";

// void CPU_Process(); // to act as the main CPU function
// int fetch();        // to fetch instructions for the PC counter

// int main()
// {
//     printf("Welcome to our Single Cycle MIPS CPU!\n");
//     // char instruction_catch; //will catch the results after fetch() is called (will be considered int in output)

//     CPU_Process(); //start the CPU

//     return 0; // ending the program

// } // end of main function

// void CPU_Process()
// {
//     printf("Preparing to fectch the 32 bit instruction....\n");
//     printf("\n");

//     fetch();

// } // end of CPU Process Function

// // A function to both fetch and decode a given instruction:
// int fetch()
// {
//     // we need a bit string (character array) to carry the instruction:
//     char instruction[MAX_LENGTH]; // to carry the new 32 bit instruction

//     printf("Fetching the Instruction...\n");

//     // creating an File Pointer object:
//     FILE *file_accessor; // object

//     file_accessor = fopen(filename, "r"); // using the fopen function to read from a file

//     // CONDITIONS:
//     if (file_accessor == NULL) // if theres nothing in the text file then we cant continue
//     {
//         printf("This file is empty, no instruction... now ending process!\n");
//         exit(1); // to exit the function with a failure
//     }            // end of if

//     printf("Instruction Detected... now fetching!\n");
//     printf("\n");

//     // to read the file, line by line and add the contents to our carry variable
//     while (fgets(instruction, MAX_LENGTH, file_accessor))
//     { // going to the line

//         // indicating that instruction was fetched:
//         printf("\n");
//         printf("Instruction Fetched!\n");

//         // to get rid of the newline (for each line):
//         instruction[strcspn(instruction, "\n")] = 0;

//         instruction_counter[instruction_index][32] = instruction; // the instruction gets loaded at a particular location 4 spaces from one another or PC(4)

//         printf("\n");
//         printf("Loading instruction onto table....\n");

//         // to print the instruction bit by bit -- tests:
//         // printf("Your 32 bit instruction was: %s\n", instruction_counter[i][32]);
//         // printf("\n");
//         // printf("Instruction counter position: %d\n", i);

//         // the first instruction to always be decoded be decoded:
//         printf("\n");
//         printf("Decoding the Instruction.....");
//         Decode(instruction_counter[PC][32]);

//         instruction_index = instruction_index + 4; // updating the instruction_index by 4 to place it in the instruction counter
//         i = i + 1;                                 // Relates to the instruction that was just fetched
//         PC = 4 * i;                                // points to the current instruction
//         int next_PC = PC + 4;                      // always update the PC everytime you read an instruction

//         printf("\n");
//         printf("Instruction loaded!\n");

//     } // end of while

//     fclose(file_accessor); // closing the read file (will need to be controlled by the PC)

//     //a quick test to see i can decode from a set place
//     printf("\n");
//     printf("Decoding the Instruction.....");
//     PC = 8;
//     Decode(instruction_counter[PC][32]);

//     return 0; // ending the instruction
// } // end of fetch
