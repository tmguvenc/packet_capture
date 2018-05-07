#ifndef PACKET_CAPTURE_VERSION_H
#define PACKET_CAPTURE_VERSION_H

extern "C" {
	char* packet_captureVersionString();
	int packet_captureVersionMajor();
	int packet_captureVersionMinor();
	int packet_captureVersionType();
	int packet_captureVersionBuild();
}

#endif // !PACKET_CAPTURE_VERSION_H
