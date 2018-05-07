#ifndef PACKET_CAPTURE_BASE_H
#define PACKET_CAPTURE_BASE_H

class IPacketCaptureStrategy;

class PacketCaptureBase {
public:
	virtual ~PacketCaptureBase() { }
	virtual bool capture(IPacketCaptureStrategy* apCallback, int aPacketCount) = 0;
};

#endif // !PACKET_CAPTURE_BASE_H
