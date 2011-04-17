from random import randint
import sys
from time import time


def multiply_ij(v, A, x):
    start = time()
    for i in xrange(len(A)):
        for j in xrange(len(A[0])):
            v[i][0] += A[i][j] * x[j][0]

    elapsed_time = time() - start
    return elapsed_time


def multiply_ji(v, A, x):
    start = time()
    for j in xrange(len(A[0])):
        for i in xrange(len(A)):
            v[i][0] += A[i][j] * x[j][0]

    elapsed_time = time() - start
    return elapsed_time


def compute(n, multiply):
    v = [[0] for i in xrange(n)]
    A = [[randint(-500, 500) for j in xrange(n)] for i in xrange(n)]
    x = [[randint(-500, 500)] for i in xrange(n)]
    return multiply(v, A, x)

def main():
    if len(sys.argv) != 4:
        print >> sys.stderr, "Usage: %s N_MIN N_MAX COUNT" % sys.argv[0]
        sys.exit(1)
    n_min, n_max, count = map(int, sys.argv[1:])
    step = (n_max - n_min) / (count - 1)
    
    print "[1] Compute v = Ax looping through rows then columns (i, j)"
    print "[2] Compute v = Ax looping through columns then rows (j, i)"
    print "%6s\t%10s\t%10s" % ("N", "[1]", "[2]")

    for n in xrange(n_min, n_max + 1, step):
        print "%6d\t%10f\t%10f" % (n, compute(n, multiply_ij), compute(n, multiply_ji))


if __name__ == '__main__':
    main()
