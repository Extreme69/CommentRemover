/**
 * @file       tests.c
 * @author     Horak
 * @date       2019.6
 * @brief      Unit tests for inplementation of functions in functions.c file
 * ******************************************
 * @par       COPYRIGHT NOTICE (c) 2019 TBU in Zlin. All rights reserved.
 */

/*Private includes: ---------------------------------------------------------*/
#include <inttypes.h>
#include "../src/functions.h"
#include "minunit.h"

////////////////////////////// IMPORTANT //////////////////////////////////////
/////////// Source repository: https://github.com/siu/minunit /////////////////
/////////// For more info consult with this page //////////////////////////////

static char **arguments;

/**
 * @brief Compare 2 files char by char and report differences using line and
 * column numbers.
 */
int CompareFile(FILE *file1, FILE *file2, int *line, int *col);

MU_TEST(test_LoadStream_InputOutputFile) {
  FILE *input = NULL;
  FILE *output = NULL;

  input = Functions_LoadStream(_IN, 2, arguments);
  output = Functions_LoadStream(_OUT, 2, arguments);

  mu_assert(input != NULL, "Input (file) was not loaded properly");
  mu_assert(output != NULL, "Output (file) was not loaded properly");

  if (input != NULL && input != stdin) {
    fclose(input);
  }
  if (output != NULL && output != stdout) {
    fclose(output);
  }
}

MU_TEST(test_LoadStream_InputFileOutputStd) {
  FILE *input = NULL;
  FILE *output = NULL;
  char *emptyArray[3] = {""};

  input = Functions_LoadStream(_IN, 1, arguments);
  output = Functions_LoadStream(_OUT, 1, emptyArray);

  mu_assert(input != NULL, "Input (file) was not loaded properly");
  mu_assert(output != NULL, "Output (stdout) was not loaded properly");

  if (input != NULL && input != stdin) {
    fclose(input);
  }
  if (output != NULL && output != stdout) {
    fclose(output);
  }
}

MU_TEST(test_LoadStream_InputOutputStd) {
  FILE *input = NULL;
  FILE *output = NULL;
  char *emptyArray[3] = {""};

  input = Functions_LoadStream(_IN, 0, emptyArray);
  output = Functions_LoadStream(_OUT, 0, emptyArray);

  mu_assert(input != NULL, "Input (stdin) was not loaded properly");
  mu_assert(output != NULL, "Output (stdout) was not loaded properly");

  if (input != NULL && input != stdin) {
    fclose(input);
  }
  if (output != NULL && output != stdout) {
    fclose(output);
  }
}

MU_TEST(test_RemoveNotes) {
  mu_assert(arguments[1] != NULL, "No argument (input file)");
  mu_assert(arguments[2] != NULL, "No argument (output file)");
  mu_assert(arguments[3] != NULL, "No argument (expected output file)");

  FILE *input = fopen(arguments[1], "r");
  mu_assert(input != NULL,
            "Failed to open input file for reading (r)! Does file exist?");

  FILE *output = fopen(arguments[2], "w");
  mu_assert(output != NULL,
            "Failed to open output file for write (w)!");

  FILE *expectedOutput = fopen(arguments[3], "r");
  mu_assert(expectedOutput != NULL,
            "Failed to open expectedOutput file for reading (r)! Does file exist?");

  // Run tested function and save processed file into output
  Functions_RemoveNotes(input, output);
  mu_assert(fflush(output) == 0, "Failed to flush buffer to output file!");

  fclose(output);
  output = fopen(arguments[2], "r");
  mu_assert(output != NULL,
            "Failed to open output file for reading (r)!");

  // Compare output file with expectedOutput file
  int line = 1, col = 0;
  int diff = CompareFile(output, expectedOutput, &line, &col);

  if (diff != 0) {
    printf("Line: %d, col: %d\n", line, col);
    mu_fail("File contents of output and expected output file are not the same!");
  }

  fclose(output);
  fclose(expectedOutput);
  fclose(input);
}

int CompareFile(FILE *file1, FILE *file2, int *line, int *col) {
  char ch1 = fgetc(file1);
  char ch2 = fgetc(file2);

  while (ch1 != EOF && ch2 != EOF) {
    if (ch1 == '\n') {
      *line += 1;
      *col = 0;
    }

    if (ch1 != ch2) {
      printf("\nFound different characters. Want = 0x%02x, got = 0x%02x\n", ch1, ch2);
      return -1;
    }

    *col += 1;

    ch1 = fgetc(file1);
    ch2 = fgetc(file2);
  }

  if (ch1 == EOF && ch2 == EOF)
    return 0;
  else
    return -1;
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_LoadStream_InputOutputFile);
  MU_RUN_TEST(test_LoadStream_InputFileOutputStd);
  MU_RUN_TEST(test_LoadStream_InputOutputStd);
  MU_RUN_TEST(test_RemoveNotes);
}

int main(int argc, char *argv[]) {
  (void) argc;
  arguments = argv;
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return 0;
}
