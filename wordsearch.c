
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
void printSolution(int** arr);
int bSize;

int main(int argc, char **argv) {
    //main function given by school along with the txt files. Everything else was coded by me
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    fscanf(fptr, "%d\n", &bSize);
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

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
    
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    searchPuzzle(block, word);
    return 0;
}

void printPuzzle(char** arr) {
    // This function will print out the complete puzzle grid (arr).

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
    int LookingFor = *(word+count);
    int adjacent;

    if (count == size){
        printf("\n\nWord found!\n");
        printf("Printing the search path:");
        printSolution(finalarr);
        return 1;
    }
        
    for(int i = 0; i < bSize; i++){ //looping through each row
        
        for(int j = 0; j < bSize; j++){ //looping through each character
                
            int Current = *(*(arr+i)+j);

            if(LookingFor == Current || LookingFor-32 == Current){
                //Once I found the corresponding Letter I need to make sure it's adjacent to something
            
                adjacent = 0;
                for(int x = -1; x < 2; x++){//row
                    for(int z = -1; z < 2; z++){//column
                        //Checking For Adjacency which is essentially a 3x3 matrix
    
                        if((x+i >= 0 && x+i < bSize) && (z+j >= 0 && z+j < bSize) && ((*(*(finalarr+i+x)+j+z) == count) 
                            || (((*(*(finalarr+i+x)+j+z))-((*(*(finalarr+i+x)+j+z))%10))/10 == count)
                            || (((*(*(finalarr+i+x)+j+z))-((*(*(finalarr+i+x)+j+z))%100))/100 == count)
                            || (((*(*(finalarr+i+x)+j+z))-((*(*(finalarr+i+x)+j+z))%1000))/1000 == count)
                            || (((*(*(finalarr+i+x)+j+z))-((*(*(finalarr+i+x)+j+z))%10000))/10000 == count)
                        )){ //making sure the adjacent value is it's predecessor
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
    int **finalarr = (int**)malloc(bSize * sizeof(int*));

    for(int i = 0; i < bSize; i++){

        *(finalarr + i) = (int*)malloc(bSize * sizeof(int)); 

        for(int j = 0; j < bSize; j++){
            *(*(finalarr+i)+j) = 0;
        }
    }

    if(checkIfSolutionExists(arr, word, 0, finalarr) == 0){
        printf("\n\nWord not found!");
    }
}