#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N_MAX 30000
#define min(a, b) (((a) < (b)) ? (a) : (b))

int v[N_MAX][1];
int A[N_MAX][N_MAX];
int x[N_MAX][1];
int N;

int randint(a, b) {
  return a + (rand() % (b - a + 1));
}

void init(int n) {
  srand(time(NULL));

  N = min(n, N_MAX);
  int i, j;
  for (i = 0; i < N; i++) {
    v[i][0] = 0;
    x[i][0] = randint(-500, 500);
    for (j = 0; j < N; j++) {
      A[i][j] = randint(-500, 500);
    }
  }
}

void pprint_matrices() {
  int i, j;
  printf("\n[A]\n");
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }

  printf("\n[x]\n");
  for (i = 0; i < N; i++) {
    printf("%d\n", x[i][0]);
  }

  printf("\n[v]\n");
  for (i = 0; i < N; i++) {
    printf("%d\n", v[i][0]);
  }
}

void multiply1() {
  clock_t start = clock();

  int i, j;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      v[i][0] += A[i][j] * x[j][0];
    }
  }

  printf("Time elapsed: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s N\n", argv[0]);
    return 1;
  }

  init(atoi(argv[1]));

  multiply1();

  printf("The number was %d\n", N);
  //pprint_matrices();

  return 0;
}
