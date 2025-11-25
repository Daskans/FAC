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
        opp_r, opp_c = self._opponent_position()

        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        for dr, dc in directions:
            nr, nc = r + dr, c + dc

            if not (0 <= nr < self.N and 0 <= nc < self.N):
                continue

            # Skip move if blocked by wall
            if self._is_blocked(r, c, nr, nc):
                continue

            if (nr, nc) == (opp_r, opp_c):
                # Attempt jump over opponent
                jr, jc = nr + dr, nc + dc
                if 0 <= jr < self.N and 0 <= jc < self.N and not self._is_blocked(nr, nc, jr, jc):
                    moves.append(("M", (jr, jc)))
                else:
                    # If blocked, allow side steps
                    if dr == 0:  # horizontal
                        for sdr in [-1, 1]:
                            sr, sc = nr + sdr, nc
                            if 0 <= sr < self.N and not self._is_blocked(nr, nc, sr, sc):
                                moves.append(("M", (sr, sc)))
                    else:  # vertical
                        for sdc in [-1, 1]:
                            sr, sc = nr, nc + sdc
                            if 0 <= sc < self.N and not self._is_blocked(nr, nc, sr, sc):
                                moves.append(("M", (sr, sc)))
            else:
                moves.append(("M", (nr, nc)))

        # Wall moves
        if self._walls_left[self._nextPlayer] > 0:
            for r in range(self.N - 1):
                for c in range(self.N - 1):
                    if self._can_place_wall(r, c, "H"):
                        moves.append(("W", (r, c, "H")))
                    if self._can_place_wall(r, c, "V"):
                        moves.append(("W", (r, c, "V")))

        return moves

    def _is_blocked(self, r1, c1, r2, c2):
        # Check if a wall blocks the movement from (r1,c1) to (r2,c2)
        if r1 == r2:
            # Horizontal move
            c_min = min(c1, c2)
            return (r1, c_min) in self._V
        else:
            # Vertical move
            r_min = min(r1, r2)
            return (r_min, c1) in self._H

    def _can_place_wall(self, r, c, ori):
        # Returns True if wall can be placed at (r,c) with orientation ori
        if ori == "H":
            if (r, c) in self._H:
                return False
            if (r, c) in self._V or (r, c + 1) in self._V:
                return False
        else:
            if (r, c) in self._V:
                return False
            if (r, c) in self._H or (r + 1, c) in self._H:
                return False

        # Temporarily add the wall
        if ori == "H":
            self._H.add((r, c))
        else:
            self._V.add((r, c))

        # Check if both players still have a path to their goal
        can_place = self._path_exists(self._p1, target_row=self.N - 1) and \
                    self._path_exists(self._p2, target_row=0)

        # Remove temporary wall
        if ori == "H":
            self._H.remove((r, c))
        else:
            self._V.remove((r, c))

        return can_place

    def _path_exists(self, start, target_row):
        from collections import deque

        queue = deque([start])
        visited = set()
        visited.add(start)

        while queue:
            r, c = queue.popleft()
            if r == target_row:
                return True

            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < self.N and 0 <= nc < self.N:
                    if not self._is_blocked(r, c, nr, nc) and (nr, nc) not in visited:
                        visited.add((nr, nc))
                        queue.append((nr, nc))
        return False


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
