#include <cstdlib>

#include "serverWeatherServer.h"

#define PORT_POS 1

int main(int argc, const char* argv[]) {
	Socket skt;
	WeatherServer server(skt, argv[PORT_POS]);
	server();
	return EXIT_SUCCESS;
}
