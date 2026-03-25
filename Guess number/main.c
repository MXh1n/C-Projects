#include <stdio.h>
#include "random.h"
#include <stdbool.h>

#define MAX 100

int main(void){
    //initilization 
    int i, random_no, user_guess = -1;
    int correct, round = 0; 
    int guessed_no[100] = {0}; //array for storing user input
    bool repeat_no = false;

    random_no = random_int(100); // generating random number
    while(1){
                
        printf("\n--- Round %d ---\n", round + 1);
        printf("Number guessed: ");
        
        //displaying the guessed numbers
        for (i = 0; i < round; i++){
            printf("%d ", guessed_no[i]);    
        } 
        
        printf("\nEnter your guess: ");
        scanf("%d", &user_guess);
        
        correct = check_guess(random_no, user_guess); //validating user input
        
        //checking for repetition
        for (i = 0; i < round; i++){
            if (user_guess == guessed_no[i])
                repeat_no = true;
        }

        if (repeat_no){
            printf("\nYou already entered this number!!\n");
            repeat_no = false; 
            continue; 
        } 
        
        guessed_no[round] = user_guess; //keeping track of number guessed        

        if (correct == CORRECT_GUESS) break;  
        else if (correct == OUT_OF_RANGE) continue; 
        
        
        round++;
    }

    return 0;
}

