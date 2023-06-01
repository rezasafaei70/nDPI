import os
import shutil
import time

from config.global_config import logging
import socket
import threading

from src.providers import q

from prometheus_client import start_http_server

from src.dpi import analize
from src.write import write_file






def server_program():
    # get the hostname
    host = socket.gethostname()
    port = 6000  # initiate port no above 1024

    server_socket = socket.socket()  # get instance
    # look closely. The bind() function takes tuple as argument
    server_socket.bind((host, port))  # bind host address and port together

    # configure how many client the server can listen simultaneously
    server_socket.listen(2)
    conn, address = server_socket.accept()  # accept new connection
    print("Connection from: " + str(address))
    message = 'ok'
    while True:
        # receive data stream. it won't accept data packet greater than 1024 bytes
        try:
            data = conn.recv(1536)  # receive response
            if data:
                q.put(data)
                conn.send(message.encode())
            else:
                break
            conn.send(message.encode())

        except Exception as e:
            logging.error(str(e))
            time.sleep(10)






    conn.close()  # close the connection

if __name__ == '__main__':
    start_http_server(8000)
    dirs = os.listdir('in')
    for item in dirs:
        shutil.move('in/'+item,'out/'+item)
    t = threading.Thread(target=write_file)
    t.start()
    t1 = threading.Thread(target=analize)
    t1.start()
    server_program()



