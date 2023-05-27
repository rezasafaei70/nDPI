import socket
import dpkt
import time

fie_path = '/home/boshra/pcap/bale.pcap'


def server_program():
    # get the hostname
    host = socket.gethostname()
    port = 8000  # initiate port no above 1024

    server_socket = socket.socket()  # get instance
    # look closely. The bind() function takes tuple as argument
    server_socket.bind((host, port))  # bind host address and port together

    # configure how many client the server can listen simultaneously
    server_socket.listen(2)
    conn, address = server_socket.accept()  # accept new connection
    print("Connection from: " + str(address))
    packet_len = 0
    while True:
        # receive data stream. it won't accept data packet greater than 1024 bytes
        data = conn.recv(1536).decode()

        if not data:
            # if data is not received break
            break

        print("from connected user: " + str(data))
        with open(fie_path, 'rb') as pcap_file:
            capture = dpkt.pcap.Reader(pcap_file)  # We use dpkt pcap capture handler
            # message='start'
            # conn.send(message.encode())
            for ts, packet in capture:
                data = packet[0:1536]
                packet_len = packet_len+len(data)
                conn.send(data)
                print(packet_len)
                print("///////")
                time.sleep(1)

        print("end file ")
        # message = 'end'
        # conn.send(message.encode())
        time.sleep(5)



    conn.close()  # close the connection

if __name__ == '__main__':
    server_program()
