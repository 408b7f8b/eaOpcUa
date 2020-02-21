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

	if(argc < 3){
	    std::cout << "eaOpcUa für Kunbus Revolution Pi" << std::endl
                  << "Starten mit Parametern:" << std::endl
                  << "-a pfad_zu_adresstabelle" << std::endl
                  << "-o pfad_zu_operationentabelle" << std::endl;

	    return -1;
	}

	std::string adressen, operationen;
	uint16_t port = 4840;

	for(int i = 1; i < argc; ++i){
        if(strncmp(argv[i], "-a", 2) == 0){
            adressen = std::string(argv[++i]);
        }else if(strncmp(argv[i], "-o", 2) == 0){
            operationen = std::string(argv[++i]);
        }else if(strncmp(argv[i], "-p", 2) == 0){
            port = std::stoi(std::string(argv[++i]));
        }
	}

	if(adressen.empty() || operationen.empty()) return -1;

	std::map<std::string, address> io_addresses = readIODescription(adressen);
	std::map<std::string, operation> operations = readOpDescription(operationen, &io_addresses);

	server(io_addresses, operations, &lauf, port);

	return 0;
}