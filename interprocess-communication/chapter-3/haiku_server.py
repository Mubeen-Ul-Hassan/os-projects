import socket
import random
from time import sleep

HOST = "localhost"
PORT = 5575

haiku_list = [
    "A file that big?\nIt might be very useful.\nBut now it is gone.",
    "Yesterday it worked.\nToday it is not working.\nWindows is like that.",
    "Stay the patient course.\nOf little worth is your ire.\nThe network is down.",
    "Windows NT crashed.\nI am the Blue Screen of Death.\nNo one hears your screams.",
    "You step in the stream.\nBut the water has moved on.\nPage not found.",
    "Login incorrect.\nOnly perfect spellers may\nEnter this system.",
    "Printer not ready.\nCould be a fatal error.\nHave a pen handy?",
    "Chaos reigns within.\nReflect, repent, and reboot.\nOrder shall return."
]

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
                    haiku = random.choice(haiku_list)
                    haiku += "\n\n"

                    haiku_bytes = haiku.encode("utf-8")
                    res = conn.sendall(haiku_bytes)
                    if res is None:
                        print(f"Message delivered successfully.")
                    else:
                        print(f"Message delivery failed")
                    sleep(5)

except socket.error as e:
    print(f"Error: {e}")
        

# Use this command to hit server
# ncat 127.0.0.1 PORT