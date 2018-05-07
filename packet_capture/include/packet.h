#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>
#include <malloc.h>
#include <memory>
#include <utility>

struct Packet {
	explicit Packet(uint64_t len, uint64_t ts, const unsigned char* data) :
		length(len), timestamp(ts), data(nullptr) {
		this->data = static_cast<unsigned char*>(malloc(len));
		memcpy(this->data, data, len);
	}

	~Packet() {
		if (this->data) {
			free(this->data);
			this->data = nullptr;
		}
	}

	uint64_t length;
	uint64_t timestamp;
	unsigned char* data;

	Packet(Packet&& other)
		: length(other.length),
		  timestamp(other.timestamp),
		  data(other.data) {
	}

	Packet& operator=(Packet&& other) {
		using std::swap;
		swap(*this, other);
		return *this;
	}

private:
	Packet(const Packet&);
	Packet& operator=(const Packet&);
};

#endif // !PACKET_H

