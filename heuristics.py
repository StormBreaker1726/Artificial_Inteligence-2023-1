import board
import numpy as np
from scipy.spatial.distance import cityblock


def calculate_h1(my_board):
    h1 = 0

    for i in range(my_board.m):
        for i in range(my_board.n):
            i1, j1 = np.where(my_board.board == my_board.board[my_board.m][my_board.n])
            i2, j2 = np.where(my_board.perfec_board == my_board.board[my_board.m][my_board.n])
            h1 += cityblock((i1[0], j1[0]), (i2[0], j2[0]))

    return h1
