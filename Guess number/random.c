#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "random.h"

int random_int(int n){
    srand((unsigned) time(NULL));

    return rand() % (n + 1);
}

int check_guess(int rand_int, int guess){
    
    if (rand_int == guess){
        printf("\n\t--- YOU WIN! ---\n");
        printf("The correct number was: %d\n", rand_int);

        return CORRECT_GUESS;
    } 
    
    else if (guess < 0 || guess > 100){
        printf("\n\t--- NUMBER OUT OF RANGE ---\n");
        return OUT_OF_RANGE; 
    } 

    else if (rand_int < guess)
        printf("\tTOO HIGH!\n");

    else if (rand_int > guess)
        printf("\tTOO LOW!\n");
    
    
    return -1;
}

