#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 50
#define LETTERS 26
//prototypes

int menu(void);
void random_word(char *word, int category);
void make_secret(char *secret, char *word);
void display_word(char *word);
bool validate_guess(char guess, char *word, char *secret);


int main(void){
  // contains the random word 
  char word[MAX + 1]; 
  
  // holds the underscored version of random word
  char secret[MAX + 1]; 
  
  // keeps track of characters given by the user
  bool letters[LETTERS] = {false};
  
  //contains the letters guessed by the user
  char guessed_letters[LETTERS];
  int round, i;
  int choice;
  char user_guess, discard; 
  int lives; 
  bool match;
  
  //menu
  choice = menu(); 
  discard = getchar(); //gets rid of \n in the buffer when user enters a choice 

  random_word(word, choice); //getting a random word
  make_secret(secret, word);// replacing the word with underscore
  lives = 5; //user lives 
  
  //ui
  printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
  printf("\t\t   GAME BEGINS");
  printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
  if (choice == 1){
    printf("\t\tCategory: animal\n");
  } 
  else if (choice == 2){
    printf("\t\tCategory: fruit\n");
  } 
  
  else if (choice == 3){
    printf("\t\tCategory: objects\n");
  } 
  
  
  round = 0;
  for (;;){
    //game beginning interface 
    printf("\n\t\tRound: %d\n", round + 1);
    printf("\n-----------------------------------------\n"); 
    printf("Word to guess: "); 
    display_word(secret); 
    printf("\n-----------------------------------------\n"); 
     
    printf("Remaining lives: %d\n", lives); 
    
    //printing user guesses
    printf("Your guesses: ");  
    for (i = 0; i < round; i++){
      printf("%c  ", guessed_letters[i]); 
    }
    printf("\n");

    //prompting the user for a character
    printf("\nEnter your guess: ");
    user_guess = getchar(); 
    while ((discard = getchar()) != '\n'); //gets rid of extra characters including \n 

    //checking if character repeated
    if (letters[user_guess - 'a']){
      printf("\tCharacter already used!\n");
      continue;  
    }
    
    letters[user_guess - 'a'] = true;
    guessed_letters[round++] = user_guess;  
    

    //checking if correct guess or not
    match = validate_guess(user_guess, word, secret); 
    if (!match)
      lives--;
    
    //deciding whether won or lose!
    if (lives == 0){
      printf("\t\tYou lose!\n");
      printf("\t\tCorrect word was %s!\n", word); 
      break;
    } 
    if (strcmp(secret, word) == 0){
      printf("\t\tYou win\n");
      printf("\t\tYou guessed the correct word %s\n", word); 
      break;
    } 
  }
  
  
  return 0;
}

int menu(void){
  int choice = 0; 
  
  while (true){
    printf("Welcome to Hangman game :)\n");
    printf("-----------------------------------\n");
    printf("\n1. animal name.\n");
    printf("2. fruit name.\n");
    printf("3. random name.\n");
    printf("4. exit.\n");

    printf("\nEnter choice (1 - 4): ");
    scanf("%d", &choice);
     
    if (choice < 1 || choice > 4){
      printf("\nInvalid input\n");
      continue; 
    } 
   
    else if (choice == 4)
      exit(EXIT_SUCCESS);       
      
    else 
      return choice;
  }

}


void random_word(char *word, int category){
  
  //three categories with 20 names from each
  char *animal_words[] = {
      "elephant", "giraffe", "zebra", "tiger", "lion",
      "monkey", "panda", "kangaroo", "koala", "penguin",
      "dolphin", "whale", "shark", "eagle", "parrot",
      "crocodile", "hippopotamus", "rhinoceros", "cheetah", "gorilla"
  };

  char *fruit_words[] = {
      "apple", "banana", "orange", "mango", "pineapple",
      "strawberry", "blueberry", "grape", "kiwi", "watermelon",
      "peach", "pear", "cherry", "plum", "apricot",
      "lemon", "lime", "papaya", "pomegranate", "fig"
  };

  char *object_words[] = {
      "computer", "keyboard", "monitor", "mouse", "phone",
      "table", "chair", "lamp", "book", "pencil",
      "notebook", "backpack", "umbrella", "clock", "mirror",
      "bottle", "cup", "plate", "spoon", "television"
  };
  
  int i; 

  srand((unsigned int) time(NULL)); //generating a random seed
  
  i = rand() % 20; //random i from 0 - 19
  
  //choosing the correct array of strings
  if (category == 1){
    strcpy(word, animal_words[i]);
  }
  
  else if (category == 2){
    strcpy(word, fruit_words[i]);
  }
  
  else if (category == 3){
    strcpy(word, object_words[i]);
  }


}

void make_secret(char *secret, char *word){
  while (*word != '\0'){
    *secret++ = '_';
    word++; 
  }
  *secret = '\0';
}

void display_word(char *word){
  for (; *word != '\0'; word++){
    printf("%c ", *word); //printing the secret word with underscore and space
  }   
}

bool validate_guess(char guess, char *word, char *secret){
  int pos; 
  bool match;
  
  guess = tolower(guess); //makes sure it is not case sensitive
  match = false;
  for (pos = 0; word[pos] != '\0'; pos++){
    if (guess == word[pos]){
      secret[pos] = guess;
      match = true; 
    }
  }
  return match;
}

