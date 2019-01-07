#include <csignal>

#include "src/operations.hpp"

#include "src/file.hpp"
#include "src/server.hpp"

#define PC

static bool lauf = true;

void int_handler(int l) {
	lauf = false;
}

int main() {
	signal(SIGINT, int_handler);

	std::map<std::string, address> io_addresses = readIODescription("../example.txt");
	std::map<std::string, operation> operations;

	operation o(operation::Type::Double, &io_addresses, funktion1);

	operations.insert({"Druck1", o});

	server(io_addresses, operations, &lauf);

	return 0;
}