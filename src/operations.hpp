#include "types.hpp"

inline static void funktion1(operation* o){
    if(o->v == nullptr){
        o->v = std::calloc(1, sizeof(UA_Double));
    }
    if(o->input.empty() || o->param.empty()){
        return;
    }

    UA_Int16 w1 = *(UA_Int16*)o->io_addresses->at(o->input.at(0)).v;

    UA_Double d = (UA_Double)w1/std::stod(o->param[0]);

    memcpy(o->v, &d, sizeof(UA_Double));
}

const std::map<std::string, std::function<void(operation*)>> funktionen = {
        {"funktion1", funktion1}
};

const std::map<std::string, operation::Type> funktionenTypen = {
        {"funktion1", operation::Type::Double}
};