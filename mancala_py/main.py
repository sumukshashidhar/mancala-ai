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


if __name__ == "__main__":
    b = Board()
    print(b)