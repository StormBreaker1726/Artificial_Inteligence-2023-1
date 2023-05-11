import sys
import numpy as np

def defines(path):
    m = 0
    n = 0
    
    f = open(path, "r")
    
    
    m = int(f.readline())
    n = int(f.readline())

    perfect_board = np.zeros((m,n))
    my_board = np.zeros((m,n))
    
    i, j = 0, 0
    
    pp = np.zeros(n*m)
    hh = np.zeros(n*m)
    
    dump = f.readline()
    
    i, j = 0, 0
    
    print(i)
    print(j)
    
    for i in range((m*n)-1):
        pp[i] = int(f.readline())

    print(pp)
    
    dump = f.readline()
    
    for i in range((m*n)-1):
        hh[i] = int(f.readline())

    print(hh)

    return perfect_board, my_board, m, n