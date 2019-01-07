#include "types.hpp"

inline static void funktion1(operation* o){
    if(o->v == nullptr){
        o->v = std::calloc(1, sizeof(UA_Double));
    }

    UA_Int16 w1 = *(UA_Int16*)o->io_addresses->at("InputValue_1").v;

    UA_Double d = w1/2000;

    memcpy(o->v, &d, sizeof(UA_Double));
}
