#include "ffcc/p_chara.h"
#include "ffcc/memory.h"

#include <string.h>

extern CMemory Memory;
extern "C" void __dla__FPv(void*);
extern "C" void __dl__FPv(void*);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);

static char s_collection_ptrarray_h[] = "collection_ptrarray.h";
static char s_ptrarray_grow_error[] = "CPtrArray grow error";

template <class T>
class CPtrArray
{
public:
    void** m_vtable;
    int m_size;
    int m_numItems;
    int m_defaultSize;
    T* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;

    CPtrArray();
    ~CPtrArray();
    bool Add(T item);
    int GetSize();
    void ReleaseAndRemoveAll();
    void RemoveAt(unsigned long index);
    T operator[](unsigned long index);
    void SetStage(CMemory::CStage* stage);
    void SetDefaultSize(unsigned long defaultSize);
    void SetGrow(int growCapacity);
    int setSize(unsigned long newSize);
    T GetAt(unsigned long index);
    void RemoveAll();
};

template <class T>
CPtrArray<T>::CPtrArray()
{
    m_vtable = 0;
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}

template <class T>
CPtrArray<T>::~CPtrArray()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

template <class T>
bool CPtrArray<T>::Add(T item)
{
    if (setSize(m_numItems + 1) != 0) {
        m_items[m_numItems] = item;
        m_numItems = m_numItems + 1;
        return true;
    }
    return false;
}

template <class T>
int CPtrArray<T>::GetSize()
{
    return m_numItems;
}

template <class T>
void CPtrArray<T>::ReleaseAndRemoveAll()
{
    int offset = 0;

    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        int* item = *(int**)((int)m_items + offset);
        if (item != 0) {
            int refCount = item[1];
            item[1] = refCount - 1;
            if (refCount - 1 == 0 && item != 0) {
                (*(void (**)(int*, int))(*item + 8))(item, 1);
            }
            *(unsigned int*)((int)m_items + offset) = 0;
        }
        offset += 4;
    }

    RemoveAll();
}

template <class T>
void CPtrArray<T>::RemoveAt(unsigned long index)
{
    int offset = (int)(index * 4);

    m_items[index] = 0;
    for (; index < (unsigned long)m_numItems; index++) {
        unsigned int* current = (unsigned int*)((int)m_items + offset);
        offset += 4;
        *current = current[1];
    }

    m_numItems = m_numItems - 1;
}

template <class T>
T CPtrArray<T>::operator[](unsigned long index)
{
    return GetAt(index);
}

template <class T>
void CPtrArray<T>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

template <class T>
void CPtrArray<T>::SetDefaultSize(unsigned long defaultSize)
{
    m_defaultSize = defaultSize;
}

template <class T>
void CPtrArray<T>::SetGrow(int growCapacity)
{
    m_growCapacity = growCapacity;
}

template <class T>
int CPtrArray<T>::setSize(unsigned long newSize)
{
    T* newItems;

    if ((unsigned long)m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(s_ptrarray_grow_error);
            }
            m_size = m_size << 1;
        }

        newItems = (T*)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, (unsigned long)(m_size << 2), m_stage, s_collection_ptrarray_h, 0xFA, 0);
        if (newItems == 0) {
            return 0;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems << 2);
        }
        if (m_items != 0) {
            __dla__FPv(m_items);
            m_items = 0;
        }
        m_items = newItems;
    }

    return 1;
}

template <class T>
T CPtrArray<T>::GetAt(unsigned long index)
{
    return m_items[index];
}

template <class T>
void CPtrArray<T>::RemoveAll()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

template class CPtrArray<CCharaPcs::CLoadPdt*>;
template class CPtrArray<CCharaPcs::CLoadTexture*>;
template class CPtrArray<CCharaPcs::CLoadAnim*>;
template class CPtrArray<CCharaPcs::CLoadModel*>;

/*
 * --INFO--
 * PAL Address: 8007b904
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CCharaPcs::CLoadPdt*>* dtor_8007B904(CPtrArray<CCharaPcs::CLoadPdt*>* ptrArray, short shouldDelete)
{
    if (ptrArray != 0) {
        ptrArray->~CPtrArray<CCharaPcs::CLoadPdt*>();
        if (shouldDelete > 0) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
}

/*
 * --INFO--
 * PAL Address: 8007b9b4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CCharaPcs::CLoadTexture*>* dtor_8007B9B4(CPtrArray<CCharaPcs::CLoadTexture*>* ptrArray, short shouldDelete)
{
    if (ptrArray != 0) {
        ptrArray->~CPtrArray<CCharaPcs::CLoadTexture*>();
        if (shouldDelete > 0) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
}

/*
 * --INFO--
 * PAL Address: 8007ba64
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CCharaPcs::CLoadAnim*>* dtor_8007BA64(CPtrArray<CCharaPcs::CLoadAnim*>* ptrArray, short shouldDelete)
{
    if (ptrArray != 0) {
        ptrArray->~CPtrArray<CCharaPcs::CLoadAnim*>();
        if (shouldDelete > 0) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
}

/*
 * --INFO--
 * PAL Address: 8007bb14
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CCharaPcs::CLoadModel*>* dtor_8007BB14(CPtrArray<CCharaPcs::CLoadModel*>* ptrArray, short shouldDelete)
{
    if (ptrArray != 0) {
        ptrArray->~CPtrArray<CCharaPcs::CLoadModel*>();
        if (shouldDelete > 0) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GET_CHARA_ALLOC_STAGE_S(int, CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CCharaPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::~CCharaPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::GetTable(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::createLoad()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::Reset(CCharaPcs::RESET)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::correctLoadAnimAmem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::onScriptChanging(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::calcAfter()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::ReleaseAllAnimBank()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::ReleaseUnusedAnimBank()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::TryReleaseAnimBank(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::SetSpecularAlpha(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::InitEnv(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::GetNumTexShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::GetTexShadow(int, int, _GXTexObj*, Vec*, float (*) [3][4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawBefore()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawMakeTexShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::createTextureSet(void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::releaseUnuseLoadModel(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::releaseUnuseLoadAnim(CCharaPcs::CLoadAnim*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::DumpLoad()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::searchModel(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::searchTexture(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::searchAnim(int, int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::searchPdt(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::LoadCam(int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::LoadMergeFile(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::FreeMergeFile(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::isCached(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::loadModel(void*, int, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::loadTexture(void*, int, int, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::loadAnimBuffer(void*, char*, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawOverlap()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 8007717c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CCharaPcs::CHandle::operator new(unsigned long size, CMemory::CStage* stage, char* file, int line)
{
    return ::operator new(size, stage, file, line);
}

/*
 * --INFO--
 * PAL Address: 80077080
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CCharaPcs::CHandle::CHandle()
{
	m_previous = (CCharaPcs::CHandle*)nullptr;
	m_next = (CCharaPcs::CHandle*)nullptr;
	m_model = (CChara::CModel*)nullptr;
	m_textureSet = (CTextureSet*)nullptr;
	m_modelLoadRef = (CRef*)nullptr;
	m_texLoadRef = (CRef*)nullptr;

	for (int i = 0; i < 64; ++i)
	{
		m_animSlot[i] = (CRef*)nullptr;
	}

	// PDT load ref
	m_pdtLoadRef = (CRef*)nullptr;

	// Playback / state
	m_currentAnimIndex = -1;
	m_flags = 0;

	m_colorPhase = 1.0f; // FLOAT_8033028c
	m_sortZ = 0.0f; // FLOAT_80330288
	m_shadowTexturePtr = nullptr;

	m_asyncState = 0;
	m_asyncFileHandle = (CFile::CHandle*)nullptr;

	m_fogBlend = m_sortZ;
	m_unk0x158 = 0;
	m_drawListFlags &= 0x80;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CHandle::~CHandle()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 80076cf4
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::CHandle::Add()
{
    if (m_next == nullptr && m_previous == nullptr)
	{
		CCharaPcs::CHandle* head = *reinterpret_cast<CCharaPcs::CHandle**>(
			reinterpret_cast<char*>(&CharaPcs) + 0x4C);

		m_previous = head;
		m_next = head->m_next;

		head->m_next->m_previous = this;
		head->m_next = this;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::ChangeTexture(int, unsigned long, unsigned long, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::LoadModel(int, unsigned long, unsigned long, unsigned long, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::LoadAnim(char*, int, int, int, int, int, int)
{
	// TODO
}

bool CCharaPcs::CHandle::IsModelLoaded(int checkModelField)
{
	if ((m_asyncState == 0 || m_asyncState == 7)
		&& m_model != nullptr
		// TODO: Pending CModel decomp
		&& (checkModelField == 0 || *reinterpret_cast<int*>(reinterpret_cast<char*>(m_model) + 0xB0) != 0))
	{
			return true;
	}

	return false;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::LoadAnim(int, int, char*, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::FreeModel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::FreeAnim(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::SetAnim(int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::Calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::Draw(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::draw(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::LoadModelASync(int, unsigned long, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::loadModelASyncFrame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CCharaPcs::CHandle::IsLoadModelASyncCompleted()
{
    if (m_asyncState == 7)
	{
		return true;
	}

	return false;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::CancelLoadModelASync()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadModel::CLoadModel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadModel::~CLoadModel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadAnim::CLoadAnim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadAnim::~CLoadAnim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadTexture::CLoadTexture()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadTexture::~CLoadTexture()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadPdt::CLoadPdt()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadPdt::~CLoadPdt()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::GetAnimStage()
{
	// TODO
}
