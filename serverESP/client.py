import socket

# ESP32 server IP and port
server_ip = "192.168.4.1"  # Replace with the actual IP of the ESP32 server
server_port = 8080

# Create a TCP/IP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the server
try:
    print(f"Connecting to {server_ip}:{server_port}")
    client_socket.connect((server_ip, server_port))
    print("Connected!")

    # Send a message to the server
    message = "Hello from Python Client\n"
    client_socket.sendall(message.encode())

    # Wait for the response from the server
    response = client_socket.recv(1024).decode()
    print("Received:", response)

finally:
    # Close the connection
    client_socket.close()
    print("Connection closed")
