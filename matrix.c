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

void multiply_ij(int n, int **v, int **A, int **x) {
  clock_t start = clock();

  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      v[i][0] += A[i][j] * x[j][0];
    }
  }

  printf("[multiply_ij] Time elapsed: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s N\n", argv[0]);
    exit(1);
  }

  int n = atoi(argv[1]);
  int **v;
  int **A;
  int **x;

  init(n, &v, &A, &x);
  multiply_ij(n, v, A, x);

  printf("The number was %d\n", n);
  pprint_matrix("A", A, n, n);
  pprint_matrix("x", x, n, 1);
  pprint_matrix("v", v, n, 1);

  finalize(n, &v, &A, &x);

  return 0;
}
