#ifndef QUEUE_STRATEGY_H
#define QUEUE_STRATEGY_H

#include <packet_capture_strategy.h>
#include <tbb/concurrent_queue.h>

struct pcap_pkthdr;
typedef unsigned char u_char;
struct Packet;

class QueueStrategy : public IPacketCaptureStrategy
{
public:
	explicit QueueStrategy(tbb::concurrent_bounded_queue<Packet*>* apQueue);

	~QueueStrategy() override;
	void operator()(const pcap_pkthdr* apBaslik, const u_char* apPaketVerisi) override;

private:
	tbb::concurrent_bounded_queue<Packet*>* mpQueue;
};

#endif // !QUEUE_STRATEGY_H