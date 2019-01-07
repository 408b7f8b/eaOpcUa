#include <csignal>

#include "src/operations.hpp"

#include "src/file.hpp"
#include "src/server.hpp"

static bool lauf = true;

void int_handler(int l) {
	lauf = false;
}

int main(int argc, char** argv) {
	signal(SIGINT, int_handler);

	std::map<std::string, address> io_addresses = readIODescription("addresses.txt");
	std::map<std::string, operation> operations;

	operation o(operation::Type::Double, &io_addresses, funktion1);
	operation o2(operation::Type::Double, &io_addresses, funktion2);

	operations.insert({"Durchfluss 1 [l/min]", o});
	operations.insert({"Durchfluss 2 [l/min]", o2});

	server(io_addresses, operations, &lauf);

	return 0;
}