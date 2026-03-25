#ifndef RANDOM_H
#define RANDOM_H

enum {CORRECT_GUESS, OUT_OF_RANGE};

int random_int(int n);
int check_guess(int rand_int, int guess);

#endif
