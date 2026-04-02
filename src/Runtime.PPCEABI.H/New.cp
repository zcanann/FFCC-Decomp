#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/alloc.h"
#include "PowerPC_EABI_Support/Runtime/New.h"

inline void operator delete(void* arg0) throw() {
    if (arg0 != 0) {
        free(arg0);
    }
}

namespace std {

class exception {
public:
    virtual ~exception();
    virtual const char* what() const;
};

/*
 * --INFO--
 * PAL Address: 0x801AF7FC
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
exception::~exception() {
    // Empty virtual destructor - compiler generates vtable setup
}

const char* exception::what() const {
    return "exception";
}

} // namespace std
