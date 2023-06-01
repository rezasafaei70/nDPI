from elasticsearch import Elasticsearch
from config.global_config import config
client = Elasticsearch(config['ELASTIC_HOST'])