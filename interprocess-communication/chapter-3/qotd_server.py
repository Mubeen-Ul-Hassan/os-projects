import socket
import random

HOST = 'localhost'
PORT = 6041

quotes = ["The purpose of life is a life with purpose.",
          "Be yourself, everyone else is already taken",
          "A room without books is like a body without a soul.",
          "You only live once, but if you do it right, once is enough.",
          "Be the change that you wish to see in the world.",
          "In three words I can sum up everything I've learned about life: it goes on.",
          "If you tell the truth, you don't have to remember anything.",
          "To live is the rarest thing in the world. Most people exist, that is all.",
          "If you look at what you have in life, you'll always have more. If you look at what you don't have in life, you'll never have enough.",
          ]

try:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:

        # Bind the socket to an address and port
        server_socket.bind((HOST, PORT))

        # Backlog queue size
        server_socket.listen(5)
        print("Server is listening...");
        
        conn, addr = server_socket.accept();

        with conn:
            print(f"Connected by {addr}")
            quote = random.choice(quotes)
            quote += '\n'

            quote_bytes = quote.encode('utf-8')
            res = conn.sendall(quote_bytes)
            if res is None:
                print("Message delivered successfully")
            else:
                print("Message delivery failed")
            conn.shutdown(socket.SHUT_WR)

except socket.error as e:
    print(f"Error: {e}")