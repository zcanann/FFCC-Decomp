#include "ffcc/ref.h"

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
CRef::~CRef()
{
}