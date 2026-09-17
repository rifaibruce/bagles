#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * The game works as follows
 * The three digit number is generated randomly (pseduorandomly)
 * The user guesses an answer
 * The guess is saved with a number and the game responds with one of three
 * options
 * 1. Pico means one digit is correct but in the wrong position
 * 2. Fermi means one digit is correct is correct and in the right position
 * 3. Bagles means no digit is correct in the guess
 * So for each guess the game checks the guess digits and compares them to the
 * generated number In the cases where the guess has correct digits it returns
 * Pico or Fermi for the number of correct digits Then if no digit is correct
 * return bagles.
 */

int generate_guess() {
  srand(time(NULL));

  int min = 100;
  int max = 999;

  int random_num = (rand() % (max - min + 1)) + min;

  return random_num;
}

int main(int argc, char *argv[]) { printf("%d\n", generate_guess()); }
