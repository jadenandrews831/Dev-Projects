#!/bin/python3

import socket

def client(host, port):
	try:
		with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
			s.connect((host, port))	
			s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
			while True:
				s.send(input("TCPClient> ").encode())
				resp = s.recv(4096)
				print(resp.decode())
	except Exception as e:
		print("[CLIENT MESSAGE] >>> An Error Occurred: {e}")
		return

def main():
	addr = input("Host Domain/Address: ")
	port = int(input("Host Port: "))
	client(addr, port)

if __name__ == "__main__":
	main()
