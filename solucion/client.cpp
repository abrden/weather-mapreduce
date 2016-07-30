#include <cstdlib>

#include "clientWeatherClient.h"

#define HOSTNAME_POS 1
#define PORT_POS 2

int main(int argc, const char* argv[]) {
	Socket skt;
	WeatherClient client(skt, argv[HOSTNAME_POS], argv[PORT_POS]);
	client();
	return EXIT_SUCCESS;
}
