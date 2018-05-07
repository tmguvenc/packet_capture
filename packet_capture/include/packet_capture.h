#ifndef PACKET_CAPTURE_H
#define PACKET_CAPTURE_H

#include <Makrolar.h>
#include <tbb/concurrent_queue.h>
#include <string>
#include <future>
#include <atomic>

struct Packet;
class IPacketCapture;
class IPacketCaptureStrategy;

class PACKET_CAPTURE_EXPORT PacketCapture {
	
public:
	explicit PacketCapture(std::string interfaceName, std::string captureFilter, uint16_t port);
	~PacketCapture();
	void start();
	void stop();

private:
	tbb::concurrent_bounded_queue<Packet*> mQueue;
	uint16_t mPort;
	std::future<void> mFutureCapture;
	std::future<void> mFutureSend;
	IPacketCapture* mpPacketCapture;
	IPacketCaptureStrategy* mpCaptureStrategy;
	std::atomic<bool> mRun;
};

#endif // !PACKET_CAPTURE_H