#include <packet_capture_params.h>

PacketCaptureParams::PacketCaptureParams(const std::string& arNetworkArayuzAdi, const std::string& arPcapFiltresi) : 
filtreIfadesi(arPcapFiltresi),
arayuzAdi(arNetworkArayuzAdi)
{
	agMaskesi = 0xFFFFFFFF;
	optimizeEt = 0;
	snapshotUzunlugu = 65536;
	tumPaketleriYakala = 1;
}
