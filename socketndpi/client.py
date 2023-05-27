import logging
import os
import shutil
import socket
import time

from src.dpi import analize
from src.providers import q
from src.write import write_file
from prometheus_client import start_http_server

import threading


def client_program():
    host = socket.gethostname()  # as both code is running on same pc
    port = 8000  # socket server port number

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
    client_socket.send(message.encode())
    while True:
        # send message
        data = client_socket.recv(1536)  # receive response
        if data:
            q.put(data)
            client_socket.send(message.encode())
        client_socket.send(message.encode())

    client_socket.close()  # close the connection






if __name__ == '__main__':
    dirs = os.listdir('in')
    for item in dirs:
        shutil.move('in/'+item,'out/'+item)
    start_http_server(9000)
    t = threading.Thread(target=write_file)
    t.start()
    t1 = threading.Thread(target=analize)
    t1.start()
    client_program()
