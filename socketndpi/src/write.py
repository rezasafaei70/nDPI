import datetime
import os

import dpkt
from src.providers import q
from config.global_config import logging
from src.prometheus import c,c1
import shutil
def write_file():
    data_len = 0
    while True:
        try:
            data = q.get()
            if data_len == 0:
                name = str(int(datetime.datetime.now().timestamp()))
                file_path = 'in/{name}.pcap'.format(name=name)
                f = open(file_path, "wb")
                fd = dpkt.pcap.Writer(f, linktype=101)
                data_len = 1
            data_len = data_len + len(data)
            if data_len >= 1536:   #34423
                logging.info('pcap_len='+str(data_len))
                c1.inc()
                data_len = 0
                f.flush()
                f.close()
                src_path = file_path
                print("end file " + src_path)
                name = os.path.basename(file_path)
                dest_path = 'out/{name}'.format(name=name)
                shutil.move(src_path,dest_path)
                logging.info("moved file src="+src_path+" dest_path="+dest_path)

            if data_len < 1536 and data_len !=0:
                c.inc()
                fd.writepkt(data)
        except Exception as e:
            logging.error(str(e))
