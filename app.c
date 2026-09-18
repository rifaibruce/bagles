#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char *compare_guess(int user_guess, int computer_guess) {
  int computer_guess_arr[3] = {0};
  int user_guess_arr[3] = {0};

  char *answer = (char *)malloc((strlen("Fermi ") * 3) + 1);
  memset(answer, 0, (strlen("Fermi ") * 3) + 1);

  if (answer == NULL) {
    perror("Malloc fail in compare_guess");
    return NULL;
  }

  for (int i = 2; i >= 0; i--) {
    int computer_guess_digit = computer_guess % 10;
    int user_guess_digit = user_guess % 10;

    computer_guess_arr[i] = computer_guess_digit;
    user_guess_arr[i] = user_guess_digit;

    user_guess /= 10;
    computer_guess /= 10;
  }
  // Duct tape solution: Updating the index to skip the rest of the loop once a
  // decision is made
  for (int i = 0; i < 3; i++) {
    if (computer_guess_arr[i] == user_guess_arr[i]) {
      strcat(answer, "Fermi ");
      continue;
    }

    for (int j = 0; j < 3; j++) {
      if (user_guess_arr[j] == computer_guess_arr[i]) {
        strcat(answer, "Pico ");
        j = 3;
      }
    }
  }

  if (strlen(answer) == 0) {
    strcat(answer, "Bagles");
  }

  return answer;
}

int main(int argc, char *argv[]) {
  printf("Welcome to the Bagles game!\n");
  printf("To play this game, you must try to guess the three digit number the "
         "computer is thinking of\n");
  printf("For each guess you give you will get a string containing one or more "
         "of the following phrases:\n");
  printf("\t1. Pico means one digit is correct but in the wrong position\n\t2. "
         "Fermi means one digit is correct is correct and in the right "
         "position\n\t3. Bagles means no digit is correct in the guess");
  printf("To quit enter -1 as a guess\n");

  int computer_guess = generate_guess();

  do {
    int user_guess = get_guess_from_user();

    if (user_guess == -1) {
      printf("Thank you for playing!!\n");
      printf("The computer guess was %d\n", computer_guess);
      return -1;
    }

    char *result = compare_guess(user_guess, computer_guess);
    printf("%s\n", result);
    if (strcmp(result, "Fermi Fermi Fermi ") == 0) {
      printf("You won!!!\n");
      free(result);
      return 1;
    }
    free(result);
  } while (1);
}
