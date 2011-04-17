#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void malloc_matrix(int ***array, int nrows, int ncolumns) {
  *array = malloc(nrows * sizeof(int *));
  if(*array == NULL) {
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  int i;
  for(i = 0; i < nrows; i++) {
    (*array)[i] = malloc(ncolumns * sizeof(int));
    if((*array)[i] == NULL) {
      fprintf(stderr, "out of memory\n");
      exit(1);
    }
  }
}

void zero_matrix(int ***array, int nrows, int ncolumns) {
  int i, j;
  for(i = 0; i < nrows; i++) {
    for(j = 0; j < ncolumns; j++) {
      (*array)[i][j] = 0;
    }
  }
}

int randint(int a, int b) {
  return a + (rand() % (b - a + 1));
}

void rand_matrix(int ***array, int nrows, int ncolumns) {
  int i, j;
  for(i = 0; i < nrows; i++) {
    for(j = 0; j < ncolumns; j++) {
      (*array)[i][j] = randint(-500, 500);
    }
  }
}

void init(int n, int ***v, int ***A, int ***x) {
  srand(time(NULL));

  malloc_matrix(v, n, 1);
  malloc_matrix(A, n, n);
  malloc_matrix(x, n, 1);

  zero_matrix(v, n, 1);
  rand_matrix(A, n, n);
  rand_matrix(x, n, 1);
}

void free_matrix(int ***array, int nrows) {
  int i;
  for(i = 0; i < nrows; i++) {
    free((*array)[i]);
  }
  free(*array);
  *array = NULL;
}

void finalize(int n, int ***v, int ***A, int ***x) {
  free_matrix(v, n);
  free_matrix(A, n);
  free_matrix(x, n);
}

void pprint_matrix(char *name, int **array, int nrows, int ncolumns) {
  int i, j;
  printf("\n[%s]\n", name);
  for (i = 0; i < nrows; i++) {
    for (j = 0; j < ncolumns; j++) {
      printf("%d ", array[i][j]);
    }
    printf("\n");
  }
}

void debug_info(int n, int **v, int **A, int **x) {
  printf("The number was %d\n", n);
  pprint_matrix("A", A, n, n);
  pprint_matrix("x", x, n, 1);
  pprint_matrix("v", v, n, 1);
}

double multiply_ij(int n, int **v, int **A, int **x) {
  clock_t start = clock();

  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      v[i][0] += A[i][j] * x[j][0];
    }
  }

  double elapsed_time = ((double)clock() - start) / CLOCKS_PER_SEC;
  //printf("[multiply_ij(n=%8d)] Time elapsed: %f\n", n, elapsed_time);
  return elapsed_time;
}

double multiply_ji(int n, int **v, int **A, int **x) {
  clock_t start = clock();

  int i, j;
  for (j = 0; j < n; j++) {
    for (i = 0; i < n; i++) {
      v[i][0] += A[i][j] * x[j][0];
    }
  }

  double elapsed_time = ((double)clock() - start) / CLOCKS_PER_SEC;
  //printf("[multiply_ji(n=%8d)] Time elapsed: %f\n", n, elapsed_time);
  return elapsed_time;
}

double compute(int n, double (*multiply)(int, int **, int **, int **)) {
  int **v;
  int **A;
  int **x;

  init(n, &v, &A, &x);
  double elapsed_time = multiply(n, v, A, x);

  //debug_info(n, v, A, x);

  finalize(n, &v, &A, &x);

  return elapsed_time;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s MIN MAX COUNT\n", argv[0]);
    exit(1);
  }

  int n;
  int min = atoi(argv[1]), max = atoi(argv[2]);
  int step = (max - min) / (atoi(argv[3]) - 1);

  printf("[1] Compute v = Ax looping through rows then columns (i, j)\n", step);
  printf("[2] Compute v = Ax looping through columns then rows (j, i)\n");
  printf("%6s\t%10s\t%10s\n", "N", "[1]", "[2]");
  for (n = min; n <= max; n += step) {
    printf("%6d\t%10f\t%10f\n", n, compute(n, &multiply_ij), compute(n, &multiply_ji));
  } 

  return 0;
}
