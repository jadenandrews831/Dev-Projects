import argparse
import socket
import threading


def udp_server():
	bport = int(input("Bind Port: "))
	with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
		sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		sock.bind(("0.0.0.0", bport))
		while True:
			data, addr = sock.recvfrom(4096)
			print(f"[Message from {addr}] >>> {data.decode()}")
			sock.sendto(b"Hello, client", addr)
	

def handler_client(sock, addr):
	while True:
		try:
			data = sock.recv(4096)
			print(f"[MESSAGE FROM {addr}] >>> {data.decode()}")
			sock.send(b"Hello, client from TCP")
		except KeyboardInterrupt:
			sock.send(b"Connection is Closing")
			break

def tcp_server():
	port = int(input("Bind Port: "))
	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
		sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		sock.bind(("0.0.0.0", port))
		sock.listen(5)
		while True:
			s, addr = sock.accept()
			client_handler = threading.Thread(target=handler_client, args=(s, addr,))
			client_handler.start()	

def main():
	print("-="*8, "Python Adaptable Server", "=-"*8)
	server_type = input("UDP or TCP: ")
	while server_type.casefold() not in ("udp", "tcp"):
		server_type = input("Please type \"UDP\" or \"TCP\": ")
	if server_type == 'udp': udp_server()
	else: tcp_server()
		
	


if __name__ == "__main__":
	main()
