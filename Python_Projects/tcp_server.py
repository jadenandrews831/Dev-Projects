
#!/bin/usr/env python3

import os
import socket
import sys
import threading

def exit_program():
    os._exit(0)

def handler_client(s, addr):
    while True:
        try:
            msg = s.recv(4096)
            print(f"[CLIENT EVENT: {addr}] Message Received >>> {msg.decode()}")
            s.send(f"Message from SERVER >>> {msg.decode()}\n>>> ".encode())
        except (BrokenPipeError, OSError):
            print(f"[CLIENT EVENT: {addr}] Connection closed")
            s.close()
            break



def main():
    print("\t\t\t\t-=[ TCP ECHO SERVER ]=-")
    host = "0.0.0.0"
    port = int(input("Listening Port: "))
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen(5)
        print(f"[SERVER EVENT] >>> Listening on >>>Port:{port}<<<")

        try:
            while True:
                client_s, addr = s.accept()
                print(f"[SERVER EVENT] New connection from >>>{addr}<<<")
                client_handler = threading.Thread(target=handler_client, args=(client_s, addr,))
                client_handler.start()
        except KeyboardInterrupt:
            print(f"[SERVER EVENT] Connection Closing...")
            exit_program()


if __name__ == '__main__':
    main()
