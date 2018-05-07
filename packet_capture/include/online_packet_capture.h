#ifndef ONLINE_PACKET_CAPTURE_H
#define ONLINE_PACKET_CAPTURE_H

#include <packet_capture_base.h>
#include <string>
#include <Makrolar.h>

struct PacketCaptureParams;
class IPacketCaptureStrategy;
struct pcap;

class PACKET_CAPTURE_EXPORT OnlinePacketCapture : public IPacketCapture {
public:

	explicit OnlinePacketCapture(const PacketCaptureParams& arParametreler);
	~OnlinePacketCapture();
	bool capture(IPacketCaptureStrategy* apCallback, int aPacketCount) override;

protected:

	void initialize();
	void destroy();

private:
	char mpHataTamponu[256];
	int mSnapshotUzunlugu;
	int mAgMaskesi;
	int mOptimizeEt;
	int mTumPaketleriYakala;
	std::string mArayuzAdi;
	std::string mFiltreIfadesi;
	pcap* mpHandle;
	int mPaketBoyutu;
};

#endif // !ONLINE_PACKET_CAPTURE_H
