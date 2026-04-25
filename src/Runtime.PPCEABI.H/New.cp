#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/alloc.h"
#include "PowerPC_EABI_Support/Runtime/New.h"

namespace std {
class exception {
public:
	virtual ~exception();
	virtual const char* what() const;
};
} // namespace std

__declspec(weak) void operator delete(void* arg0) throw()
{
    if (arg0 != 0) {
        free(arg0);
    }
}

namespace std {
exception::~exception() {}
const char* exception::what() const { return "exception"; }
} // namespace std
