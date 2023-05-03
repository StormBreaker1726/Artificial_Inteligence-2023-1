import numpy as np


class Board:
    def __init__(self, id, m, n):
        self.board = np.zeros((m, n))
        self.id = id
        self.m = m
        self.n = n
        self.h1 = 0
        self.h2 = 0

    def init_board(self, board):
        self.board = board

    def mod_board(self, pos_to_change):
        self.board = np.zeros((self.m, self.n))

    def h1(self, new_h1):
        self.h1 = new_h1

    def h2(self, new_h2):
        self.h2 = new_h2
