import logging
from dotenv import dotenv_values

config = dotenv_values('.env')

logging.basicConfig(filename='log/log.debug',
                    filemode='a',
                    format='%(asctime)s,%(msecs)d %(name)s %(levelname)s %(message)s',
                    datefmt='%H:%M:%S',
                    level=eval(config['LOG']))
