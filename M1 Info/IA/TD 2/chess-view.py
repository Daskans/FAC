import pygame
import chess
import sys
from starter_chess import ABBestMoves
from starter_chess_correction import IDAlphaBeta

TILE_SIZE = 80
BOARD_SIZE = TILE_SIZE * 8
FPS = 30

WHITE = (240, 217, 181)
BLACK = (181, 136, 99)
HIGHLIGHT = (186, 202, 68)
MOVE_HIGHLIGHT = (100, 200, 100)


def load_images():
    pieces = {}
    names = ["p", "r", "n", "b", "q", "k"]
    for n in names:
        pieces[n.upper()] = pygame.transform.scale(
            pygame.image.load(f"pieces/white/{n.upper()}.png"), (TILE_SIZE, TILE_SIZE)
        )
        pieces[n] = pygame.transform.scale(
            pygame.image.load(f"pieces/black/{n}.png"), (TILE_SIZE, TILE_SIZE)
        )
    return pieces


def draw_board(screen, pieces, board, selected_square, legal_moves):
    for row in range(8):
        for col in range(8):
            color = WHITE if (row + col) % 2 == 0 else BLACK
            pygame.draw.rect(screen, color, (col*TILE_SIZE, row*TILE_SIZE, TILE_SIZE, TILE_SIZE))

    if selected_square is not None:
        r = 7 - (selected_square // 8)
        c = selected_square % 8
        pygame.draw.rect(screen, HIGHLIGHT, (c*TILE_SIZE, r*TILE_SIZE, TILE_SIZE, TILE_SIZE))

    for sq in legal_moves:
        r = 7 - (sq // 8)
        c = sq % 8
        pygame.draw.circle(screen, MOVE_HIGHLIGHT, (c*TILE_SIZE + TILE_SIZE//2, r*TILE_SIZE + TILE_SIZE//2), 10)

    for square, piece in board.piece_map().items():
        img = pieces[piece.symbol()]
        r = 7 - (square // 8)
        c = square % 8
        screen.blit(img, (c*TILE_SIZE, r*TILE_SIZE))


def choose_promotion(screen, is_white):
    font = pygame.font.SysFont(None, 36)
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit(); sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_q: return chess.QUEEN
                if event.key == pygame.K_r: return chess.ROOK
                if event.key == pygame.K_b: return chess.BISHOP
                if event.key == pygame.K_n: return chess.KNIGHT
        screen.fill((50,50,50))
        color = "White" if is_white else "Black"
        txt = font.render(f"{color} pawn promotion: Press Q R B N", True, (255,255,255))
        screen.blit(txt, (20, BOARD_SIZE//2))
        pygame.display.flip()


def main():
    pygame.init()
    screen = pygame.display.set_mode((BOARD_SIZE, BOARD_SIZE))
    pygame.display.set_caption("Chess vs AI")
    clock = pygame.time.Clock()

    pieces = load_images()
    board = chess.Board()

    selected_square = None
    legal_moves = []

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit(); sys.exit()

            if event.type == pygame.MOUSEBUTTONDOWN:
                mx, my = pygame.mouse.get_pos()
                col = mx // TILE_SIZE
                row = my // TILE_SIZE
                square = (7 - row) * 8 + col

                if selected_square is None:
                    piece = board.piece_at(square)
                    if piece and piece.color == board.turn:
                        selected_square = square
                        legal_moves = [m.to_square for m in board.legal_moves if m.from_square == square]
                else:
                    pawn = board.piece_at(selected_square)
                    if pawn and pawn.piece_type == chess.PAWN and (square < 8 or square >= 56):
                        promo = choose_promotion(screen, pawn.color == chess.WHITE)
                        move = chess.Move(selected_square, square, promotion=promo)
                    else:
                        move = chess.Move(selected_square, square)

                    if move in board.legal_moves:
                        board.push(move)
                        selected_square = None
                        legal_moves = []

                        if not board.is_game_over():
                            ai_move = IDAlphaBeta(board, limittime=1)
                            if ai_move:
                                board.push(ai_move)
                    else:
                        selected_square = None
                        legal_moves = []

        draw_board(screen, pieces, board, selected_square, legal_moves)
        pygame.display.flip()
        clock.tick(FPS)


if __name__ == "__main__":
    main()
