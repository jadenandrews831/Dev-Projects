#!/bin/python3

import socket

def client(host, port):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.send(f"GET / HTTP/1.1\r\nHost: {host}\r\n\r\n".encode())

        resp = s.recv(4096)

        print(resp.decode())



def main():
    addr = input("Host Domain/Address: ")
    port = int(input("Host Port: "))
    client(addr, port)

if __name__ == "__main__":
    main()
