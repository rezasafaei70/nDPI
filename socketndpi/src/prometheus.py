from prometheus_client import Counter

c = Counter('packet_count', 'number of packet')
c1 = Counter('pcap_count','number of pcap')
c2 = Counter('protocol_count','number of detect protocol')