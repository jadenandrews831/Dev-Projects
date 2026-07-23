import socket
import os

def udp_client(host, port):
	print(f"[CLIENT MESSAGE] >>> Connecting to {host}:{port}")
	with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
		try:
			while True:
				sock.sendto(input("UDPClientPy> ").encode(), (host, port))
				data, addr = sock.recvfrom(4096);
				print(f"[MESSAGE FROM SERVER] >>> {data.decode()}")
		except KeyboardInterrupt:
			sock.sendto(f"Closing Connection from {sock.getsockname()}".encode(), (host, port))
			os._exit(0)

def main():
	print("-="*8, "Python UDP Client", "=-"*8)
	host = input("Remote Host: ")
	port = int(input("Remote Port: "))
	udp_client(host, port)

if __name__ == "__main__":
	main()
