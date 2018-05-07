#include <queue_strategy.h>
#include <packet.h>
#include <assert.h>
#include <pcap.h>

QueueStrategy::QueueStrategy(tbb::concurrent_bounded_queue<Packet*>* apQueue) :
	mpQueue(apQueue) {
	assert(mpQueue);
}

QueueStrategy::~QueueStrategy() {

}

void QueueStrategy::operator()(const pcap_pkthdr* apBaslik, const u_char* apPaketVerisi) {
	mpQueue->push(new Packet(apBaslik->len, apBaslik->ts.tv_sec, apPaketVerisi));
}
