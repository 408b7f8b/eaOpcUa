#include <signal.h>

#include "src/file.hpp"
#include "src/server.hpp"

//#define PC

static bool lauf = true;

void int_handler(int l) {
	lauf = false;
}

int main() {
	signal(SIGINT, int_handler);

	std::map<std::string, address> io_addresses = readIODescription("../example.txt");

	server(io_addresses, &lauf);

	return 0;
}