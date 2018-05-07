#include <online_packet_capture.h>
#include <packet_capture_params.h>
#include <pcap.h>
#include <packet_capture_strategy.h>
#include <stdexcept>

static inline void istisnaFirlat(char* apIstisnaMesaji, int aUzunluk) {
	throw std::runtime_error(std::string(apIstisnaMesaji, aUzunluk));
}

#if defined(WIN32) && defined(_MSC_VER)
#define SPRINTF sprintf_s
#else
#define SPRINTF sprintf
#endif

#define PCAP_CHECK(expr) \
	if(!expr) { \
		static char lpTampon[1024]; \
		auto lUzunluk = SPRINTF(lpTampon, "[%d] nolu satirda PCAP HATASI!: %s", \
		 __LINE__, pcap_geterr(mpHandle)); istisnaFirlat(lpTampon, lUzunluk); \
	}

#define PCAP_CHECK_ZERO(ex) PCAP_CHECK((ex == 0))
#define PCAP_CHECK_GTE_ZERO(ex) PCAP_CHECK((ex >= 0))
#define PCAP_CHECK_LT_ZERO(ex) PCAP_CHECK((ex < 0))
#define PCAP_CHECK_NOT_NULL(ex) PCAP_CHECK((ex != nullptr))

OnlinePacketCapture::OnlinePacketCapture(const PacketCaptureParams& arParametreler) :
	mSnapshotUzunlugu(arParametreler.snapshotUzunlugu),
	mAgMaskesi(arParametreler.agMaskesi),
	mOptimizeEt(arParametreler.optimizeEt),
	mTumPaketleriYakala(arParametreler.tumPaketleriYakala),
	mArayuzAdi(arParametreler.arayuzAdi),
	mFiltreIfadesi(arParametreler.filtreIfadesi),
	mpHandle(nullptr)
{
	// adaptor ismini kontrol etmek icin ilklendirme yap.
	// adaptor ismi yanlis ise veya herhangi bir sebepten network kartine erisim yapilamazsa
	// exception firlatilir ve ust katmanda yakalanip kullanici bilgilendirilir.
	initialize();
	destroy();
}

OnlinePacketCapture::~OnlinePacketCapture()
{
}

bool OnlinePacketCapture::capture(IPacketCaptureStrategy* apCallback, int aMaksimumPaketSayisi)
{
	initialize();

	pcap_loop(mpHandle, aMaksimumPaketSayisi, [](u_char* args, const pcap_pkthdr* header, const u_char* packet) {
		(*reinterpret_cast<IPacketCaptureStrategy*>(args))(header, packet);
	}, reinterpret_cast<u_char*>(apCallback));

	destroy();

	return true;
}

void OnlinePacketCapture::initialize()
{
	// eger pcap baslamissa durdur
	destroy();

	// paket toplamak için network arayüzünü aç
	PCAP_CHECK_NOT_NULL((mpHandle = pcap_create(mArayuzAdi.c_str(), mpHataTamponu)));
	PCAP_CHECK_ZERO(pcap_set_buffer_size(mpHandle, 1024 * 1024 * 1024));
	PCAP_CHECK_ZERO(pcap_set_snaplen(mpHandle, mSnapshotUzunlugu));
	//PCAP_CHECK_ZERO(pcap_set_timeout(mpHandle, mZamanAsimi));
	PCAP_CHECK_ZERO(pcap_set_promisc(mpHandle, mTumPaketleriYakala));
	PCAP_CHECK_ZERO(pcap_activate(mpHandle));

	bpf_program program;

	// gerekli filtreyi oluþtur
	PCAP_CHECK_GTE_ZERO(pcap_compile(mpHandle, &program, mFiltreIfadesi.c_str(), mOptimizeEt, mAgMaskesi));
	PCAP_CHECK_GTE_ZERO(pcap_setfilter(mpHandle, &program));
}

void OnlinePacketCapture::destroy()
{
	if (mpHandle) {
		pcap_breakloop(mpHandle);
		pcap_close(mpHandle);
		mpHandle = nullptr;
	}
}