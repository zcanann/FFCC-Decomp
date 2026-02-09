#include "ffcc/p_FunnyShape.h"

// Forward declarations for template instantiation
struct _GXTexObj;
struct OSFS_TEXTURE_ST;

// CPtrArray template class definition based on Ghidra decomp analysis
// TODO: This should be using CPtrArray.h surely?
template <class T>
class CPtrArray
{
public:
    void **items;     // Array of pointers
    int numItems;     // Number of items currently in array
    int size;         // Allocated capacity

    CPtrArray() : items(0), numItems(0), size(0) {}
    
    void RemoveAll();
    void DeleteAndRemoveAll();
};

// Template specialization declarations to ensure proper mangling
template class CPtrArray<_GXTexObj*>;
template class CPtrArray<OSFS_TEXTURE_ST*>;

// Global delete functions (from GameCube/Dolphin OS)
extern "C" void __dl__FPv(void* ptr);
extern "C" void __dla__FPv(void* ptr);

/*
 * --INFO--
 * PAL Address: 0x8004e7ac
 * PAL Size: 76b
 */
template <>
void CPtrArray<_GXTexObj*>::RemoveAll()
{
    if (items != 0) {
        __dla__FPv(items);
        items = 0;
    }
    size = 0;
    numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8004e7f8
 * PAL Size: 76b
 */
template <>
void CPtrArray<OSFS_TEXTURE_ST*>::RemoveAll()
{
    if (items != 0) {
        __dla__FPv(items);
        items = 0;
    }
    size = 0;
    numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8004e69c
 * PAL Size: 136b
 */
template <>
void CPtrArray<_GXTexObj*>::DeleteAndRemoveAll()
{
    int offset = 0;
    for (unsigned int i = 0; i < (unsigned int)numItems; i++) {
        if (*(int*)((int)items + offset) != 0) {
            __dl__FPv(*(void**)((int)items + offset));
            *(int*)((int)items + offset) = 0;
        }
        offset += 4;
    }
    RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x8004e724
 * PAL Size: 136b
 */
template <>
void CPtrArray<OSFS_TEXTURE_ST*>::DeleteAndRemoveAll()
{
    int offset = 0;
    for (unsigned int i = 0; i < (unsigned int)numItems; i++) {
        if (*(int*)((int)items + offset) != 0) {
            __dl__FPv(*(void**)((int)items + offset));
            *(int*)((int)items + offset) = 0;
        }
        offset += 4;
    }
    RemoveAll();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFunnyShapePcs::CFunnyShapePcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFunnyShapePcs::~CFunnyShapePcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShapePcs::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShapePcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8004e5cc
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFunnyShapePcs::GetTable(unsigned long index)
{
    return static_cast<int>(index) * 0x15c + -0x7fe15858;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShapePcs::createViewer()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShapePcs::destroyViewer()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShapePcs::calcViewer()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShapePcs::drawViewer()
{
	// TODO
}
