#include <zmq.h>
#include <packet_capture.h>
#include <online_packet_capture.h>
#include <packet_capture_params.h>
#include <queue_strategy.h>
#include <sstream>
#include <packet.h>

PacketCapture::PacketCapture(std::string interfaceName, std::string captureFilter, uint16_t port) :
	mPort(port),
	mpPacketCapture(nullptr),
	mpCaptureStrategy(nullptr),
	mRun(false) {
	mpCaptureStrategy = new QueueStrategy(&mQueue);
	mpPacketCapture = new OnlinePacketCapture(PacketCaptureParams(interfaceName, captureFilter));
}

PacketCapture::~PacketCapture() {
	if (mpPacketCapture) {
		delete mpPacketCapture;
		mpPacketCapture = nullptr;
	}
	if (mpCaptureStrategy) {
		delete mpCaptureStrategy;
		mpCaptureStrategy = nullptr;
	}
}

void PacketCapture::start() {
	if (mRun) return;

	mRun.store(true);

	mFutureCapture = std::async([&]() {
		mpPacketCapture->capture(mpCaptureStrategy, 0);
	});

	mFutureSend = std::async([&]() {
		auto ctx = zmq_ctx_new();

		auto senderSocket = zmq_socket(ctx, ZMQ_PUB);

		std::stringstream ss;
		ss << "tcp://*:" << mPort;

		zmq_bind(senderSocket, ss.str().c_str());

		while (mRun) {
			Packet* lpPacket = nullptr;
			mQueue.pop(lpPacket);

			if (lpPacket) {
				zmq_send(senderSocket, &lpPacket->timestamp, sizeof(lpPacket->timestamp), ZMQ_SNDMORE);
				zmq_send(senderSocket, &lpPacket->length, sizeof(lpPacket->length), ZMQ_SNDMORE);
				zmq_send(senderSocket, lpPacket->data, sizeof(lpPacket->length), 0);
				delete lpPacket;
			}
		}

		zmq_close(senderSocket);
		zmq_ctx_destroy(ctx);
	});
}

void PacketCapture::stop() {
	// TODO: 
	mRun.store(false);
}
