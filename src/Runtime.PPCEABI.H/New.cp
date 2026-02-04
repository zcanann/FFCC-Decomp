#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/alloc.h"
#include "PowerPC_EABI_Support/Runtime/New.h"

namespace std {

class exception {
public:
    virtual ~exception();
    virtual const char* what() const;
};

exception::~exception() {
    // Empty virtual destructor - compiler generates vtable setup
}

const char* exception::what() const {
    return "exception";
}

} // namespace std

void operator delete(void* arg0) throw() {
    if (arg0 != 0) {
        free(arg0);
    }
}
