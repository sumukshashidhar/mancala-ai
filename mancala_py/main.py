NUM_SEEDS = 5
LEN_BOARD = 14
BOARD_WIDTH = 7
class Board:

    def __init__(self) -> None:
        self.board = [NUM_SEEDS] * LEN_BOARD
        # self.board = [i for i in range(LEN_BOARD)]
        self.scores = [0, 0]
    
    def __str__(self) -> str:
        s = "-" * 4 * BOARD_WIDTH + "\n"
        s += f"|"
        for hole in self.board[-1:BOARD_WIDTH - 1:-1]:
            s += f"{hole:2} |"
        s += "\n" + "-" * 4 * BOARD_WIDTH + "\n|"
        for hole in self.board[:BOARD_WIDTH]:
            s += f"{hole:2} |"
        s += "\n"
        s += "-" * 4 * BOARD_WIDTH + "\n"
        s += f"Player 1: {self.scores[0]} | Player 2: {self.scores[1]}\n"
        return s

    def _is_valid_hole(self, move):
        return self.board[move] > 0

    def get_valid_moves(self):
        return [i for i in range(LEN_BOARD) if self.board[i] > 0]
            


    def make_move(self, player, move):
        # first, check if the move is valid
        if (not self._is_valid_hole(move)):
            raise ValueError("Invalid move")
        # this means that the move is valid
        num_seeds = self.board[move]
        self.board[move] = 0
        # now, we need to distribute the seeds
        self.scores[player] += self._distribute_seeds(move, num_seeds)
        return
    
    def _get_next_hole(self, pos):
        # wrap around
        if pos + 1 == LEN_BOARD:
            pos = 0
        else:
            pos += 1
        # we have to check if there are piggies / bankruptcies
        while self.board[pos] < 0:
            # this works, because everyone CAN'T be bankrupt at the same time
            pos += 1
        return pos

    def _collect_seeds(self, pos):
        # run the 4 seed update
        self._four_seed_update()
        # we need to collect the seeds in this particular hole, as well as the opposite hole
        score = self.board[pos]
        self.board[pos] = 0
        # now, we need to check the opposite hole
        opposite_hole = LEN_BOARD - pos - 1
        if self._is_valid_hole(opposite_hole):
            score += self.board[opposite_hole]
            self.board[opposite_hole] = 0
        return score
        

    
    def _distribute_seeds(self, pos, num_seeds):
        while True:
            self.board[pos] += 1
            num_seeds -= 1
            pos = self._get_next_hole(pos)

            if num_seeds == 0:
                # we need to essentially "pick up" the seed in the next hole
                num_seeds = self.board[pos]
                self.board[pos] = 0
                pos = self._get_next_hole(pos)
                # now, we need to handle the case in which the num seeds is 0.
                # is is when we run the collection algorithm
                if num_seeds == 0:
                    return self._collect_seeds(pos)
                # otherwise, we just have to continue, nothing else to do

    def _four_seed_update(self):
        # for player 1s iteration
        for i in range(BOARD_WIDTH):
            if self.board[i] == 4:
                self.board[i] = 0
                self.scores[0] += 4
        # for player 2s iteration
        for i in range(BOARD_WIDTH, LEN_BOARD):
            if self.board[i] == 4:
                self.board[i] = 0
                self.scores[1] += 4

    def can_play(self, player):
        if player == 0:
            pos = 0
            while pos < BOARD_WIDTH:
                if self.board[pos] > 0:
                    return True
                pos += 1
            return False
        else:
            pos = BOARD_WIDTH
            while pos < LEN_BOARD:
                if self.board[pos] > 0:
                    return True
            return False
        


if __name__ == "__main__":
    b = Board()
    print(b)
    b.make_move(0, 4)
    print(b)