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
 * @note Address: 801AFA6C
 * @note Size: 184b
 */
extern "C" void dtor_801AFA6C() {
	// TODO: Implement destructor function
	// Based on address 801AFA6C, size 184 bytes
}

/**
 * @note Address: 801afc28
 * @note Size: 556b
 */
extern "C" char __throw_catch_compare(const char* throwtype, const char* catchtype, int* offset_result)
{
	char cVar1;
	char cVar2;
	int iVar3;
	const char* pcVar4;
	const char* pcVar5;

	*offset_result = 0;
	if (catchtype == nullptr) {
		return 1;
	}

	if (*catchtype == 'P') {
		pcVar4 = catchtype + 1;
		if (*pcVar4 == 'C') {
			pcVar4 = catchtype + 2;
		}
		if (*pcVar4 == 'V') {
			pcVar4 = pcVar4 + 1;
		}
		if ((*pcVar4 == 'v') && ((*throwtype == 'P' || (*throwtype == '*')))) {
			return 1;
		}
	}

	cVar1 = *throwtype;
	if ((cVar1 == '*') || ((cVar1 < '*' && (cVar1 == '!')))) {
		pcVar4 = throwtype + 1;
		pcVar5 = catchtype + 1;
		if (*throwtype != *catchtype) {
			return 0;
		}
		while (true) {
			while (true) {
				cVar1 = *pcVar5;
				pcVar5 = pcVar5 + 1;
				cVar2 = *pcVar4;
				if (cVar2 != cVar1) break;
				pcVar4 = pcVar4 + 1;
				if (cVar2 == '!') {
					iVar3 = 0;
					for (; *pcVar4 != '!'; pcVar4 = pcVar4 + 1) {
						iVar3 = (int)*pcVar4 + iVar3 * 10 - 0x30;
					}
					*offset_result = iVar3;
					return 1;
				}
			}
			do {
				cVar1 = *pcVar4;
				pcVar4 = pcVar4 + 1;
			} while (cVar1 != '!');
			do {
				cVar1 = *pcVar4;
				pcVar4 = pcVar4 + 1;
			} while (cVar1 != '!');
			if (*pcVar4 == '\0') break;
			pcVar5 = catchtype + 1;
		}
		return 0;
	}

	while (true) {
		cVar1 = *throwtype;
		if (((cVar1 != 'P') && (cVar1 != 'R')) || (cVar1 != *catchtype)) {
			while (true) {
				if (*throwtype != *catchtype) {
					return 0;
				}
				if (*throwtype == '\0') break;
				throwtype = throwtype + 1;
				catchtype = catchtype + 1;
			}
			return 1;
		}
		pcVar4 = throwtype + 1;
		pcVar5 = catchtype + 1;
		if (catchtype[1] == 'C') {
			if (*pcVar4 == 'C') {
				pcVar4 = throwtype + 2;
			}
			pcVar5 = catchtype + 2;
		}
		catchtype = pcVar5;
		throwtype = pcVar4;
		if (*throwtype == 'C') break;
		if (*catchtype == 'V') {
			if (*throwtype == 'V') {
				throwtype = throwtype + 1;
			}
			catchtype = catchtype + 1;
		}
		if (*throwtype == 'V') {
			return 0;
		}
	}
	return 0;
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
 * @note Address: 801afb24
 * @note Size: 260b
 */
extern "C" void* __construct_new_array(void* ptr, ConstructorDestructor ctor, ConstructorDestructor dtor, size_t elementSize, size_t count) {
	// TODO: Implement new array construction
	return nullptr;
}

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
