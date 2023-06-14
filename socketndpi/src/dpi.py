import subprocess
import time
from datetime import datetime

from src.prometheus import c2
from config.global_config import logging
from src.models.db import client
import os
# todo Add special character to split inside ndpi
# This is our shell command, executed by Popen.
def split_row(row):
    data = row.split(':')
    return data[0],data[1]
def analize():
    try:
        while True:
            dirs = os.listdir('out')
            logging.debug("analize dirs " +''.join(map(str, dirs)))
            for file in dirs:
                try:
                    p = subprocess.Popen("../example/ndpiReader -i "+'out/'+file, stdout=subprocess.PIPE, shell=True)
                    data = p.communicate()[0].decode()
                    data = data.split('Detected protocols')
                    protocols = data[1].split('endDetected protocols')[0]
                    info = data[0].split('\n\t')[2:]

                    protocols = protocols.split('boshra')
                    ctx = {}
                    arr = []
                    logging.info("ananlize protcols "+''.join(map(str, protocols)))
                    logging.info('ananlize info '+''.join(map(str, info)))
                    for item in info:
                        try:
                            val1,val2 = split_row(item)
                            ctx[val1] = val2.strip()
                        except Exception as e:
                            logging.warning(str(e))
                    for item in protocols[1:]:
                        try:
                            pr = item.strip()
                            pr = pr.split('ff')

                            ctx1={}
                            for item1 in pr :
                                val1 , val2 = split_row(item1)
                                ctx1[val1.strip()] = val2.replace('\nend','').strip()
                            arr.append(ctx1)
                            c2.inc()

                        except Exception as e:
                            logging.error(str(e))

                    doc = {
                        'info': ctx,
                        'protocols': arr,
                        'timestamp': int(datetime.now().timestamp()),
                    }
                    day = datetime.now().strftime('%Y-%m-%d')
                    index_name = f'dpi{day}'.format(day=day)
                    resp = client.index(index=index_name, body=doc)
                    os.unlink('out/'+file)
                    logging.info("remove file "+str(file))
                except Exception as e:
                    logging.error("analize in side for  "+str(e))
                    os.unlink('out/' + file)

            time.sleep(5)
    except Exception as e:
        logging.error('analize '+str(e))
    
   
    


