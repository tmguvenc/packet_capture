#ifndef PACKET_CAPTURE_PARAMS_H
#define PACKET_CAPTURE_PARAMS_H

#include <string>
#include <stdint.h>
#include <Makrolar.h>

struct PACKET_CAPTURE_EXPORT PacketCaptureParams {

	explicit PacketCaptureParams(const std::string& arNetworkArayuzAdi, const std::string& arPcapFiltresi);

	uint32_t snapshotUzunlugu;
	uint32_t agMaskesi;
	uint32_t optimizeEt;
	uint32_t tumPaketleriYakala;
	std::string filtreIfadesi;
	std::string arayuzAdi;
};

#endif // !PACKET_CAPTURE_PARAMS_H
