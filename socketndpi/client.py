import logging
import os
import shutil
import socket
import time
import dpkt

from src.dpi import analize

from src.write import write_file
from prometheus_client import start_http_server

import threading
fie_path = '/home/boshra/pcap/pp/'

def client_program():
    host = socket.gethostname()  # as both code is running on same pc
    port = 6000  # socket server port number

    client_socket = socket.socket()  # instantiate
    while True:
        try:
            client_socket.connect((host, port))  # connect to the server
            print("connected")
            break
        except Exception as e:
            logging.error(str(e))
        time.sleep(5)
    message = 'ok'
    # client_socket.send(message.encode())
    packet_len = 0
    while True:
        print("asd")
        arr = os.listdir(fie_path)

        for name in arr:

            with open(fie_path+name, 'rb') as pcap_file:
                capture = dpkt.pcap.Reader(pcap_file)  # We use dpkt pcap capture handler
                # message='start'
                # conn.send(message.encode())
                for ts, packet in capture:
                    data = packet[0:1536]
                    packet_len = packet_len+len(data)
                    client_socket.send(data)
                    print(packet_len)
                    print("///////")
                    time.sleep(1)

    client_socket.close()  # close the connection






if __name__ == '__main__':
    # dirs = os.listdir('in')
    # for item in dirs:
    #     shutil.move('in/'+item,'out/'+item)
    # t = threading.Thread(target=write_file)
    # t.start()
    # t1 = threading.Thread(target=analize)
    # t1.start()
    client_program()
