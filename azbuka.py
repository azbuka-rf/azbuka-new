import chess
import chess.engine
import socket

q = []

def genMove():
  if(len(q) == 2):
    s = ""
    e = ""
    for x, y, m in q:
      if(m == 0):
        s = chr(ord('a')+x)+chr(ord('0')+y+1)
      else:
        e = chr(ord('a')+x)+chr(ord('0')+y+1)

    if(len(s) == 0 or len(e) == 0):
      return None
    
    return s+e
  else:
    s = []
    e = ""
    for x, y, m in q:
      if(m == 0):
        s.append(chr(ord('a')+x)+chr(ord('0')+y+1))
      else:
        e = chr(ord('a')+x)+chr(ord('0')+y+1)

    if(s[0] == e):  
      return s[1]+e
    else:
      return s[0]+e



# Chess init
engine = chess.engine.SimpleEngine.popen_uci("/usr/bin/stockfish")
board = chess.Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")

# TCP init
HOST = "192.168.43.185"
PORT = 1234

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)
print('Socket created')

s.bind((HOST, PORT))

s.listen(5)
print('Socket awaiting messages')
(conn, addr) = s.accept()
print('Connected')

while(1):
  data = str(conn.recv(1024))[2:-1]
  # data = input()
  print(data)
  data = data.split()

  if(data[0] == "M"):
    q.append((int(data[1]),int(data[2]),int(data[3])))
    if(len(q) >= 2):
      move = genMove()
      if(move != None):
        board.push_uci(move)
        res = engine.play(board, chess.engine.Limit(depth=20))
        conn.send(str(res.move))
        print(res.move)
  
  if(board.is_checkmate()):
    print("МАТ!!!")
    exit()
  if(board.is_check()):
    print("ШАХ!!!")
  if(board.is_stalemate()):
    print("ПАТ!!!")
    exit()
  
    
