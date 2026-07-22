import socket

def udp_client(host, port):
	print(f"[CLIENT MESSAGE] >>> Connecting to {host}:{port}")
	with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
		sock.sendto(b"Hello, Server", (host, port))
		data, addr = sock.recvfrom(4096);
		printf(f"[MESSAGE FROM SERVER] >>> {data.decode()}")

def main():
	print("-="*8, "UDP Client", "=-"*8)
	host = input("Remote Host: ")
	port = input("Remote Port: ")
	udp_client(host, port)

if __name__ == "__main__":
	main()
