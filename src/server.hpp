#ifndef EAOPCUA_SERVER_HPP
#define EAOPCUA_SERVER_HPP

#include <map>
#include <iostream>
#include <unistd.h>

#include "types.hpp"
#include "EA.hpp"

#include "open62541.h"

static std::pair<std::string, UA_NodeId> addNode(const UA_Server* server, const std::string& name, const address& adr){
	UA_VariableAttributes attr = UA_VariableAttributes_default;

	int d = -1;
	void* v = nullptr;

	switch(adr.datatype){
		case address::Bit: {
			d = UA_TYPES_BOOLEAN;
			v = calloc(1, sizeof(UA_Boolean));
#ifndef PC
			auto state = (UA_Boolean) readBit(adr);
			memcpy(v, &state, sizeof(UA_Boolean));
#endif
			break;
		}
		case address::Byte: {
			d = UA_TYPES_BYTE;
			v = calloc(1, sizeof(UA_Byte));
#ifndef PC
			UA_Byte state;
			if(readBytes(adr, &state)){
				memcpy(v, &state, sizeof(UA_Byte));
			}else{
				free(v);
				return {};
			}
#endif
			break;
		}
		case address::Int16: {
			d = UA_TYPES_INT16;
			v = calloc(1, sizeof(UA_Int16));
#ifndef PC
			UA_Int16 state;
			if(readBytes(adr, 4, (std::uint8_t*) &state)){
				memcpy(v, &state, sizeof(UA_Int16));
			}else{
				free(v);
				return {};
			}
#endif
			break;
		}
		default: break;
	}

	if(d == -1)
		return {};

	UA_Variant_setScalar(&attr.value, v, &UA_TYPES[d]);

	attr.dataType = UA_TYPES[d].typeId;
	attr.accessLevel = UA_ACCESSLEVELMASK_READ;
	attr.displayName = UA_LOCALIZEDTEXT((char*)std::string("de-DE").c_str(), (char*)name.c_str());

	UA_NodeId nNodeId = UA_NODEID_STRING(1, (char*)name.c_str());
	UA_QualifiedName nNodeName = UA_QUALIFIEDNAME(1, (char*)name.c_str());
	UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
	UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);

	UA_NodeId ret;

	UA_Server_addVariableNode((UA_Server*)server, nNodeId, parentNodeId,
							  parentReferenceNodeId, nNodeName,
							  UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attr, NULL, &ret);

	free(v);

	return {name, ret};
}

static void aktNode(const UA_Server* server, const address& adr, const UA_NodeId* nodeId){
	int d = -1;
	void* v = nullptr;

	switch(adr.datatype){
		case address::Bit: {
			d = UA_TYPES_BOOLEAN;
			v = calloc(1, sizeof(UA_Boolean));
#ifndef PC
			auto state = (UA_Boolean) readBit(adr);
			memcpy(v, &state, sizeof(UA_Boolean));
#endif
			break;
		}
		case address::Byte: {
			d = UA_TYPES_BYTE;
			v = calloc(1, sizeof(UA_Byte));
#ifndef PC
			UA_Byte state;
			if(readBytes(adr, &state)){
				memcpy(v, &state, sizeof(UA_Byte));
			}else{
				free(v);
				return;
			}
#endif
			break;
		}
		case address::Int16: {
			d = UA_TYPES_INT16;
			v = calloc(1, sizeof(UA_Int16));
#ifndef PC
			UA_Int16 state;
			if(readBytes(adr, 4, (std::uint8_t*) &state)){
				memcpy(v, &state, sizeof(UA_Int16));
			}else{
				free(v);
				return;
			}
#endif
			break;
		}
		default: break;
	}

	if(d == -1)
		return;

	UA_Variant var;
	UA_Variant_init(&var);

	UA_Variant_setScalar(&var, v, &UA_TYPES[d]);
	UA_Server_writeValue((UA_Server*)server, *(UA_NodeId*)nodeId, var);
}

unsigned int sleep_time = 50000;

void server(const std::map<std::string, address>& io_addresses, const bool* lauf){
	int state = 0;

	UA_Server *server = nullptr;
	UA_ServerConfig *config = nullptr;
	std::map<std::string, UA_NodeId> nodeVerzeichnis;

	while(*lauf){
		switch(state){
			case 0:{
				config = UA_ServerConfig_new_minimal(4840, NULL);
				server = UA_Server_new(config);

				UA_StatusCode r1 = UA_Server_run_startup(server);

				++state;
				break;
			}
			case 1:{
				for(auto& n : io_addresses){
					std::pair<std::string, UA_NodeId> nNode = addNode(server, n.first, n.second);
					if(!nNode.first.empty()){
						nodeVerzeichnis.insert(nNode);
					}
				}

				++state;
				break;
			}
			case 2:{
				for(auto& n : nodeVerzeichnis){
					aktNode(server, io_addresses.at(n.first), &(n.second));
				}
			}
			default: break;
		}

		UA_UInt16 r_t = UA_Server_run_iterate(server, true);
		usleep(sleep_time);
	}

	UA_Server_delete(server);
	UA_ServerConfig_delete(config);
}

#endif //EAOPCUA_SERVER_HPP
