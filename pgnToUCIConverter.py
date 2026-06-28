import io
import re
import chess.pgn

pgn = """ 1. e4 {+0.38/14 0.15s} e5 2. Nf3 {+0.24/13 0.15s} Nc6 3. Bc4 {+0.39/13 0.15s}
Nb4 4. Nxe5 {+1.68/14 0.15s} Nxa2 5. Bxf7+ {+6.68/16 0.15s} Ke7
6. Bxa2 {+6.84/17 0.15s} Nh6 7. d3 {+8.12/16 0.15s} Nf5
8. O-O {+10.59/15 0.15s, Black disconnects} 1-0"""

pgn = re.sub(r"\{[^}]*\}", "", pgn)

game = chess.pgn.read_game(io.StringIO(pgn))
board = game.board()

moves = []
for move in game.mainline_moves():
    moves.append(move.uci())
    board.push(move)

print("position startpos moves", " ".join(moves))