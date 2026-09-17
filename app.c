#include <setjmp.h>
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

int get_guess_from_user() {
  int buffer_size = 32;
  char *read_line = (char *)malloc(buffer_size * sizeof(int));
  printf("Enter your guess: ");

  if (fgets(read_line, buffer_size, stdin) != NULL) {
    int user_guess;
    int bytes_converted = sscanf(read_line, "%d", &user_guess);
    if (bytes_converted != EOF && bytes_converted >= 1) {
      free(read_line);
      return user_guess;
    }
  }

  free(read_line);
  return -1;
}

int main(int argc, char *argv[]) {
  printf("%d\n", generate_guess());
  int user_guess = get_guess_from_user();

  if (user_guess == -1) {
    perror("Failed to get user guess");
    return -1;
  }

  printf("%d\n", user_guess);
}
