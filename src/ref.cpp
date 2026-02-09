#include "ffcc/ref.h"

extern "C" void __dl__FPv(void*);
extern "C" void* __vt__4CRef;

/*
 * --INFO--
 * PAL Address: 0x80043d58
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CRef::CRef()
{
	this->refCount = 1;
}

/*
 * --INFO--
 * PAL Address: 0x80043d10
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CRef* dtor_80043D10(CRef* ref, short param_2)
{
	if (ref != 0) {
		*(void**)ref = &__vt__4CRef;
		if (0 < param_2) {
			__dl__FPv(ref);
		}
	}
	return ref;
}
