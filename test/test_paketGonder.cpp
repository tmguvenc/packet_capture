#include <zmq.h>
#include <packet_capture.h>

int main(int argc, char *argv[])
{
	const std::string networkArayuzu("\\Device\\NPF_{067CAD5A-1424-4A12-8309-8484FD9398F0}");
	const std::string filter("tcp");

	auto ctx = zmq_ctx_new();
	auto socket = zmq_socket(ctx, ZMQ_SUB);
	zmq_setsockopt(socket, ZMQ_SUBSCRIBE, "", 0);
	zmq_connect(socket, "tcp://127.0.0.1:5555");

	PacketCapture capture(networkArayuzu, filter, 5555);
	capture.start();

	unsigned char buffer[64 * 1024];

	while (true) {
		uint64_t ts;
		uint64_t len;
		zmq_recv(socket, &ts, sizeof(ts), 0);
		zmq_recv(socket, &len, sizeof(len), 0);
		zmq_recv(socket, buffer, sizeof(buffer), 0);
		printf("%I64d uzunlukta paket alindi\n", len);
	}


	zmq_close(socket);
	zmq_ctx_destroy(ctx);
}