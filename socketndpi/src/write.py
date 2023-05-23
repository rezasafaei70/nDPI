import datetime
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
            if data_len >= 34424:
                logging.info(data_len)
                c1.inc()
                data_len = 0
                f.flush()
                f.close()
                src_path = 'in/{file}'.format(file=file_path)
                dest_path = 'out/{file}'.format(file=file_path)
                shutil.move(src_path,dest_path)
                print("end file")
            if data_len < 34424:
                c.inc()
                data_len = data_len + len(data)
                print(data_len)
                print("//////")
                fd.writepkt(data)
        except Exception as e:
            logging.error(str(e))
