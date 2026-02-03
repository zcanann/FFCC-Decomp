#include "PowerPC_EABI_Support/Runtime/NMWException.h"
#include "PowerPC_EABI_Support/Runtime/MWCPlusLib.h"

#define ARRAY_HEADER_SIZE 16

extern "C" {
extern void abort();
extern void __dla__FPv(void*);
}

namespace std {
/**
 * @note Address: N/A
 * @note Size: 0x20
 */
static void dthandler() { abort(); }

static terminate_handler thandler = dthandler;

/**
 * @note Address: N/A
 * @note Size: 0x28
 */
static void duhandler() { terminate(); }

static unexpected_handler uhandler = duhandler;

/**
 * @note Address: N/A
 * @note Size: 0x28
 */
extern void terminate() { thandler(); }

/**
 * @note Address: N/A
 * @note Size: 0x28
 */
extern void unexpected() { uhandler(); }
} // namespace std

/**
 * @note Address: N/A
 * @note Size: 0x22C
 */
extern char __throw_catch_compare(const char* throwtype, const char* catchtype, s32* offset_result)
{
	const char *cptr1, *cptr2;

	*offset_result = 0;

	if ((cptr2 = catchtype) == 0) {
		return true;
	}

	cptr1 = throwtype;

	if (*cptr2 == 'P') {
		cptr2++;
		if (*cptr2 == 'C')
			cptr2++;
		if (*cptr2 == 'V')
			cptr2++;
		if (*cptr2 == 'v') {
			if (*cptr1 == 'P' || *cptr1 == '*') {
				return true;
			}
		}
		cptr2 = catchtype;
	}

	switch (*cptr1) {
	case '*':
	case '!':
		if (*cptr1++ != *cptr2++)
			return false;
		for (;;) {
			if (*cptr1 == *cptr2++) {
				if (*cptr1++ == '!') {
					s32 offset;

					for (offset = 0; *cptr1 != '!';) {
						offset = offset * 10 + *cptr1++ - '0';
					}
					*offset_result = offset;
					return true;
				}
			} else {
				while (*cptr1++ != '!') { }
				while (*cptr1++ != '!') { }
				if (*cptr1 == 0)
					return false;

				cptr2 = catchtype + 1;
			}
		}
		return false;
	}

	while ((*cptr1 == 'P' || *cptr1 == 'R') && *cptr1 == *cptr2) {
		cptr1++;
		cptr2++;

		if (*cptr2 == 'C') {
			if (*cptr1 == 'C')
				cptr1++;
			cptr2++;
		}
		if (*cptr1 == 'C')
			return false;

		if (*cptr2 == 'V') {
			if (*cptr1 == 'V')
				cptr1++;
			cptr2++;
		}
		if (*cptr1 == 'V')
			return false;
	}

	for (; *cptr1 == *cptr2; cptr1++, cptr2++) {
		if (*cptr1 == 0)
			return true;
	}

	return false;
}

class __partial_array_destructor {
private:
	void* p;
	size_t size;
	size_t n;
	ConstructorDestructor dtor;

public:
	size_t i;

	__partial_array_destructor(void* array, size_t elementsize, size_t nelements, ConstructorDestructor destructor)
	{
		p    = array;
		size = elementsize;
		n    = nelements;
		dtor = destructor;
		i    = n;
	}

	~__partial_array_destructor()
	{
		char* ptr;

		if (i < n && dtor) {
			for (ptr = (char*)p + size * i; i > 0; i--) {
				ptr -= size;
				DTORCALL_COMPLETE(dtor, ptr);
			}
		}
	}
};

/**
 * @note Address: 801af970
 * @note Size: 252b
 */
extern "C" void __construct_array(void* ptr, ConstructorDestructor ctor, ConstructorDestructor dtor, size_t size, size_t n) {
	void* current = ptr;
	size_t i;
	
	for (i = 0; i < n; i++) {
		CTORCALL_COMPLETE(ctor, current);
		current = (void*)((char*)current + size);
	}
	
	if (i < n && dtor != nullptr) {
		current = (void*)((char*)ptr + size * i);
		for (; i != 0; i--) {
			current = (void*)((char*)current - size);
			DTORCALL_COMPLETE(dtor, current);
		}
	}
}

/**
 * @note Address: 801af8f8
 * @note Size: 120b
 */
extern "C" void __destroy_arr(void* block, ConstructorDestructor* dtor, size_t size, size_t n) {
	char* current = (char*)block + size * n;
	
	for (; n != 0; n--) {
		current -= size;
		DTORCALL_COMPLETE(*dtor, current);
	}
}

/**
 * @note Address: 801af87c
 * @note Size: 124b
 */
extern "C" void __destroy_new_array(void* block, ConstructorDestructor dtor) {
	if (block != nullptr) {
		char* arrayStart = (char*)block;
		
		if (dtor != nullptr) {
			size_t elementSize = *(size_t*)(arrayStart - 0x10);
			size_t elementCount = *(size_t*)(arrayStart - 0xc);
			char* current = arrayStart + elementSize * elementCount;
			
			for (size_t i = 0; i < elementCount; i++) {
				current -= elementSize;
				DTORCALL_COMPLETE(dtor, current);
			}
		}
		
		// Call delete operator on the allocation header
		__dla__FPv((void*)(arrayStart - 0x10));
	}
}
