import subprocess
import time

from src.prometheus import c2
from config.global_config import logging
import os

# This is our shell command, executed by Popen.
def split_row(row):
    data = row.split(':')
    return data[0],data[1]
def analize():
    try:
        while True:
            dirs = os.listdir('out')
            logging.debug(dirs)
            for file in dirs:
                p = subprocess.Popen("../example/ndpiReader -i "+file, stdout=subprocess.PIPE, shell=True)
                data = p.communicate()[0].decode()
                data = data.split('Detected protocols')
                detect_protcol = data[1].split('detect_protcol')[0]
                info = data[0].split('\n\t')[2:]
                protocols = detect_protcol.split('Protocol statistics')[0]
                protocols = detect_protcol.split('\n\t')
                ctx = {}
                arr = []
                logging.log(protocols)
                logging.log(info)
                for item in info:
                    val1,val2 = split_row(item)
                    ctx[val1] = val2.strip()
                for item in protocols[1:]:
                    pr = item.strip()
                    pr = pr.split('           ')

                    ctx1={}
                    for item1 in pr :
                        val1 , val2 = split_row(item1)
                        val1 , val2 = split_row(item1)
                        ctx1[val1.strip()] = val2.strip()
                    arr.append(ctx1)
                    print(arr)
                    c2.inc()
            time.sleep(5)
    except Exception as e:
        logging.error(str(e))
    
   
    


# print(data)

