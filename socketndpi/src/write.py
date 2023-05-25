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
            data_len = data_len + len(data)
            print(data_len)
            if data_len >= 34423:
                logging.info(data_len)
                c1.inc()
                data_len = 0
                f.flush()
                f.close()
                src_path = file_path
                name = os.path.basename(file_path)
                dest_path = 'out/{name}.pcap'.format(name=name)
                shutil.move(src_path,dest_path)
                logging.info("moved file")
            if data_len < 34423:
                c.inc()
                fd.writepkt(data)
        except Exception as e:
            logging.error(str(e))
