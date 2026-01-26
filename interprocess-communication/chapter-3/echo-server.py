import socket


HOST = 'localhost'
PORT = 6041

try:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((HOST, PORT))
        server_socket.listen(5)
        print("Server is listening...")

        conn, addr = server_socket.accept()
        while True:
            with conn:
                print("Connection established\n")
                print(f"Connected by {addr}")
                
                while True:
                    data = conn.recv(1024)
                    if not data:
                        break
                    print(f"Received {data.decode('utf-8')}")
                    if data == 'exit':
                        break
                    

except socket.error as e:
    print(f"Error: {e}")