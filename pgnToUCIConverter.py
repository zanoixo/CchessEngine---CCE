import io
import chess.pgn

pgn = """
1. d4 d5 2. e3 Nc6 3. c4 e5 4. cxd5 Qxd5 5. Nc3 Bb4 6. Bd2 Bxc3 7. Bxc3 exd4 8. f3 Qe5 9. Bxd4 Nxd4 10. Qxd4 Qxd4 11. exd4 Nf6 12. Bc4 Be6 13. Bb3 O-O-O 14. Bxe6+ fxe6 15. O-O-O Rhe8 16. Rd2 e5 17. dxe5 Rxe5 18. Ne2 Nd5 19. Rhd1 Rde8 20. Nc3 Nxc3 21. bxc3 Rh5 22. g4 Rh3 23. Kb2 Rxf3 24. Rd7 Rf2+ 25. Kb3 Rg8 26. h3 Rf3 27. g5 Rxh3 28. Re7 Rd8 29. Rf1 Rhd3 30. Rxg7 R3d7 31. Rff7 Rxf7 32. Rxf7 Rg8 33. Rxh7 Rxg5 34. a4 Re5 35. Rf7 Re3 36. Rf8+ Kd7 37. Rf7+ Kc6 38. Rh7 Kb6 39. a5+ Kc6 40. Rh5 Kd6 41. Rh4 Re5 42. Kc4 Rxa5 43. Rh6+ Kd7 44. Rh7+ Kc6 45. Rh6+ Kd7 46. Rh7+ Kc6 47. Rh6+
"""

game = chess.pgn.read_game(io.StringIO(pgn))
board = game.board()

moves = []
for move in game.mainline_moves():
    moves.append(move.uci())
    board.push(move)

print("position startpos moves", " ".join(moves))