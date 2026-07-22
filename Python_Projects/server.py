import socket
import argparse

def udp_server():
	bport = input("Bind Port: ")
	with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
		sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		sock.bind(("0.0.0.0", bport))
		sock.listen(5)
		while True:
			data, addr = sock.recvfrom(4096)
			print(f"[Message from {addr}] >>> {data.decode()}")
	

def tcp_server():
	pass

def main():
	print("-="*8, "Python Adaptable Server", "=-"*8)
	udp_server()
	


if __name__ == "__main__":
	main()
