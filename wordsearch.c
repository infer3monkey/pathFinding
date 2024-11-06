
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables

void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
void printSolution(int** arr);
int bSize;

// Main function, DO NOT MODIFY

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;
    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }
    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));
    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);
    printf("Enter the word to search: ");
    scanf("%s", word);
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    return 0;
}

void printPuzzle(char** arr) {
    // This function will print out the complete puzzle grid (arr).
    // It must produce the output in the SAME format as the samples
    // in the instructions.
    // Your implementation here...
    for(int i = 0; i < bSize; i++){ //looping through each row

        if(i != 0){
            printf("\n");
        }
        
        for(int j = 0; j < bSize; j++){ //looping through each character

            if(j != 0){
                printf(" ");
            }

            printf("%c", *(*(arr+i)+j));
        }
    }
}

void printSolution(int** arr) {
    //prints out the solution path in the same manner as the prompt

    for(int i = 0; i < bSize; i++){ //looping through each row

        printf("\n");
        
        for(int j = 0; j < bSize; j++){ //looping through each character
            int num = *(*(arr+i)+j);
            printf("%d", num);
            if(j != bSize-1){
                if(num >= 10000){//5 digits
                    printf("   ");
                } else if(num >= 1000){//4 digits
                    printf("    ");
                } else if(num >= 100){//3 digits
                    printf("     ");
                } else if(num >= 10){//2 digits
                    printf("      ");
                } else { //1 digit
                    printf("       ");
                }
            }
        }
    }
}

int checkIfSolutionExists(char** arr, char* word, int count, int** copyarr){

    int size = strlen(word);
    int **finalarr = copyarr;
    int LookingFor = *(word+count);//converting to ascii
    int adjacent; //0 for false, 1 for true

    if (count == size){
        printf("\n\nWord found!\n");
        printf("Printing the search path:");
        printSolution(finalarr);
        return 1;
    }
        
    for(int i = 0; i < bSize; i++){ //looping through each row
        
        for(int j = 0; j < bSize; j++){ //looping through each character
                
            int Current = *(*(arr+i)+j);//converting to ascii

            if(LookingFor == Current || LookingFor-32 == Current){//checking if = and accounting for lowercase/uppercase
                //Found the corresponding Letter
                //Once I found the corresponding Letter I need to make sure it's adjacent to something
            
                adjacent = 0;
                for(int x = -1; x < 2; x++){//row
                    for(int z = -1; z < 2; z++){//column
                        //Checking For Adjacency which is essentially a 3x3 matrix
                        //need to make sure it is in bounds then check if there is a value around it
    
                        if((x+i >= 0 && x+i < bSize) && (z+j >= 0 && z+j < bSize) && ((*(*(finalarr+i+x)+j+z) == count) 
                            || (((*(*(finalarr+i+x)+j+z))-((*(*(finalarr+i+x)+j+z))%10))/10 == count)
                            || (((*(*(finalarr+i+x)+j+z))-((*(*(finalarr+i+x)+j+z))%100))/100 == count)
                            || (((*(*(finalarr+i+x)+j+z))-((*(*(finalarr+i+x)+j+z))%1000))/1000 == count)
                            || (((*(*(finalarr+i+x)+j+z))-((*(*(finalarr+i+x)+j+z))%10000))/10000 == count)
                        )){ //making sure the adjacent value is it's predecessor
                            //so if we're on letter 2 we're only looking for 1 being adjacent
                            adjacent = 1;
                        }
                    }
                }
                if(adjacent == 1){
                    int temp = *(*(finalarr+i)+j);

                    if(*(*(finalarr+i)+j) != 0){
                        if(*(*(finalarr+i)+j)<10){//2 digits
                                *(*(finalarr+i)+j) = *(*(finalarr+i)+j) + ((count+1)*10);
                        } else if(*(*(finalarr+i)+j) < 100){//3 digits
                                *(*(finalarr+i)+j) = *(*(finalarr+i)+j) + ((count+1)*100);
                        } else if(*(*(finalarr+i)+j)<1000){ //4 digits
                                *(*(finalarr+i)+j) = *(*(finalarr+i)+j) + ((count+1)*1000);
                        } else if(*(*(finalarr+i)+j)<10000){ //5 digits
                                *(*(finalarr+i)+j) = *(*(finalarr+i)+j) + ((count+1)*10000);
                        }
                    } else {
                            *(*(finalarr+i)+j) = count+1;
                    }
                    
                    if(checkIfSolutionExists(arr, word,count+1, finalarr) == 0){
                        *(*(finalarr+i)+j) = temp;//restore the value and find a new one that works
                    } else {
                        return 1;//recursion is done
                    }
                }
            }
        }
    }
    return 0; //function failed reached the end with no valid paths on this matrix
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the
    // word appears in arr, it will print out a message and the path
    // as shown in the sample runs. If not found, it will print a
    // different message as shown in the sample runs.
    // Your implementation here...

    int **finalarr = (int**)malloc(bSize * sizeof(int*));

    for(int i = 0; i < bSize; i++){ //initializing finalarr with 0's

        *(finalarr + i) = (int*)malloc(bSize * sizeof(int)); //creating the pointers that the double pointer is pointing to

        for(int j = 0; j < bSize; j++){
            *(*(finalarr+i)+j) = 0;
        }
    }

    if(checkIfSolutionExists(arr, word, 0, finalarr) == 0){
        printf("\n\nWord not found!");
    }
}