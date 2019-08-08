#include <csignal>

#include "src/operations.hpp"

#include "src/file.hpp"
#include "src/server.hpp"

static volatile bool lauf = true;

void int_handler(int l) {
	lauf = false;
}

int main(int argc, char** argv) {
	signal(SIGINT, int_handler);
	signal(SIGABRT, int_handler);
	signal(SIGKILL, int_handler);
	signal(SIGQUIT, int_handler);
	signal(SIGTERM, int_handler);

	std::map<std::string, address> io_addresses = readIODescription("addresses.txt");
	std::map<std::string, operation> operations = readOpDescription("operations.txt", &io_addresses);

	server(io_addresses, operations, &lauf);

	return 0;
}