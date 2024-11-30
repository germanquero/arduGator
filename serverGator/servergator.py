import socket
import threading

from teeth import buf

# Función para manejar la conexión con cada cliente
def handle_client(client_socket):
    client_socket.send(buf)
    client_socket.close()

# Configura el servidor para escuchar conexiones
def server_loop():
    bind_ip = "0.0.0.0"
    bind_port = 9999

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((bind_ip, bind_port))
    server.listen(5)

    print(f"[*] Escuchando en {bind_ip}:{bind_port}")

    while True:
        client_socket, addr = server.accept()
        print(f"[*] Conexión aceptada de: {addr[0]}:{addr[1]}")

        # Maneja el cliente en un hilo separado
        client_handler = threading.Thread(target=handle_client, args=(client_socket,))
        client_handler.start()

if __name__ == "__main__":
    server_loop()

