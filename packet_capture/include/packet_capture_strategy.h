#ifndef PACKET_CAPTURE_STRATEGY_H
#define PACKET_CAPTURE_STRATEGY_H

struct pcap_pkthdr;
typedef unsigned char u_char;

class IPacketCaptureStrategy {
public:
	virtual ~IPacketCaptureStrategy() { }
	virtual void operator()(const pcap_pkthdr* apBaslik, const u_char* apPaketVerisi) = 0;
};

#endif // !PACKET_CAPTURE_STRATEGY_H