# -*- coding: utf-8 -*-

class Corridor:

    _P1 = '1'
    _P2 = '2'

    def __init__(self, N=5, walls_per_player=5):
        self.N = N
        self._walls_per_player = walls_per_player

        self._p1 = (0, N // 2)
        self._p2 = (N - 1, N // 2)
        self._nextPlayer = self._P1

        self._walls_left = {
            self._P1: walls_per_player,
            self._P2: walls_per_player
        }

        self._H = set()  # murs horizontaux (coin sup-gauche)
        self._V = set()  # murs verticaux (coin sup-gauche)

        self._stack = []  # pour permettre undo()

    def is_game_over(self):
        return self.result() is not None

    def result(self):
        if self._p1[0] == self.N - 1:
            return self._P1
        if self._p2[0] == 0:
            return self._P2
        return None

    def _current_position(self):
        return self._p1 if self._nextPlayer == self._P1 else self._p2

    def _opponent_position(self):
        return self._p2 if self._nextPlayer == self._P1 else self._p1

    def legal_moves(self):
        moves = []
        r, c = self._current_position()

        for dr, dc in [(-1,0),(1,0),(0,-1),(0,1)]:
            nr, nc = r + dr, c + dc
            if 0 <= nr < self.N and 0 <= nc < self.N:
                if (nr, nc) != self._opponent_position():
                    moves.append(("M", (nr, nc)))

        if self._walls_left[self._nextPlayer] > 0:
            for r in range(self.N - 1):
                for c in range(self.N - 1):
                    if (r, c) not in self._H:
                        moves.append(("W", (r, c, "H")))
                    if (r, c) not in self._V:
                        moves.append(("W", (r, c, "V")))

        return moves

    def play(self, move):
        self._stack.append((self._nextPlayer, self._p1, self._p2, dict(self._walls_left), set(self._H), set(self._V), move))

        kind = move[0]

        if kind == "M":
            _, (r, c) = move
            if self._nextPlayer == self._P1:
                self._p1 = (r, c)
            else:
                self._p2 = (r, c)
        elif kind == "W":
            _, (r, c, ori) = move
            if ori == "H":
                self._H.add((r, c))
            else:
                self._V.add((r, c))
            self._walls_left[self._nextPlayer] -= 1

        self._nextPlayer = self._P2 if self._nextPlayer == self._P1 else self._P1

    def undo(self):
        (player, p1, p2, walls_left, H, V, _) = self._stack.pop()
        self._nextPlayer = player
        self._p1 = p1
        self._p2 = p2
        self._walls_left = walls_left
        self._H = H
        self._V = V

    def __str__(self):
        rows = []
        for r in range(self.N):
            line = ""
            for c in range(self.N):
                pos = (r, c)
                if pos == self._p1:
                    line += " 1 "
                elif pos == self._p2:
                    line += " 2 "
                else:
                    line += " . "

                # Mur vertical à droite de la case
                if (r, c) in self._V:
                    line += "|"
                else:
                    line += " "
            rows.append(line)

            # Ligne de murs horizontaux
            if r < self.N - 1:
                wall_line = ""
                for c in range(self.N):
                    if (r, c) in self._H:
                        wall_line += "__ "
                    else:
                        wall_line += "   "
                rows.append(wall_line)

        return "\n".join(rows) + f"\nNext player: {self._nextPlayer}"

    __repr__ = __str__
