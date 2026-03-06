#include "ffcc/p_chara.h"
#include "ffcc/chunkfile.h"
#include "ffcc/graphic.h"
#include "ffcc/memory.h"
#include "ffcc/partMng.h"

#include <string.h>

extern CMemory Memory;
extern CPartMng PartMng;
extern unsigned char PartPcs[];
extern u8* lbl_8032EDC0;
extern "C" void __dla__FPv(void*);
extern "C" void __dl__FPv(void*);
extern "C" int sprintf(char*, const char*, ...);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __dt__4CRefFv(void*, int);
extern "C" void ReleasePdt__8CPartPcsFi(void*, int);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern unsigned char PTR_s_CCharaPcs_GAME__801fce10[];

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
    if (setSize(m_numItems + 1) == 0) {
        return false;
    }

    m_items[m_numItems] = item;
    m_numItems = m_numItems + 1;
    return true;
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
    m_numItems = 0;
    m_size = 0;
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
int CCharaPcs::GetTable(unsigned long index)
{
    unsigned char* table = PTR_s_CCharaPcs_GAME__801fce10;
    unsigned long offset = index * 0x15c;
    return (int)(table + offset);
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
 * PAL Address: 0x80079754
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::SetSpecularAlpha(int alpha)
{
    lbl_8032EDC0[0x6B] = (u8)alpha;
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
 * PAL Address: 800783d0
 * PAL Size: 488b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::LoadCam(int index, char* fileName)
{
    static char s_p_chara_cpp[] = "p_chara.cpp";
    char path[0x104];
    CChunkFile::CChunk chunk;

    int* cameraCounts = reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x04);
    void** cameraData = reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x14);
    void*& cameraBuffer = cameraData[index];

    if (cameraBuffer != 0) {
        __dla__FPv(cameraBuffer);
        cameraBuffer = 0;
    }

    sprintf(path, "dvd/cft/%s.cmd", fileName);
    CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
    if (fileHandle == 0) {
        return;
    }

    File.Read(fileHandle);
    File.SyncCompleted(fileHandle);

    CChunkFile chunkFile(File.m_readBuffer);
    while (chunkFile.GetNextChunk(chunk)) {
        if (chunk.m_id != 'CAM ') {
            continue;
        }

        cameraCounts[index] = static_cast<int>(chunk.m_arg0);

        CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(this) + 0xD4);
        cameraBuffer = __nwa__FUlPQ27CMemory6CStagePci(
            static_cast<unsigned long>(cameraCounts[index] << 5), stage, s_p_chara_cpp, 0x4D4);

        float* values = reinterpret_cast<float*>(cameraBuffer);
        for (int i = 0; i < cameraCounts[index] * 8; i++) {
            values[i] = chunkFile.GetF4();
        }
    }

    File.Close(fileHandle);
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
		&& (checkModelField == 0 || *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(m_model) + 0xB0) != 0))
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
 * PAL Address: 8007435c
 * PAL Size: 572b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::CHandle::LoadModelASync(int charaKind, unsigned long charaNo, unsigned long textureVariant)
{
    if (m_asyncFileHandle != 0)
	{
		File.Close(m_asyncFileHandle);
		m_asyncFileHandle = (CFile::CHandle*)0;
	}

	m_asyncState = 0;
	Graphic._WaitDrawDone((char*)"p_chara.cpp", 0x8C9);
	PartMng.pppDeleteCHandle(this);

	if (m_model != 0)
	{
		int* modelRef = reinterpret_cast<int*>(m_model);
		int refCount = modelRef[1] - 1;
		modelRef[1] = refCount;
		if (refCount == 0)
		{
			(*(void (**)(void*, int))(*modelRef + 8))(m_model, 1);
		}
		m_model = (CChara::CModel*)0;
	}

	if (m_textureSet != 0)
	{
		int* textureRef = reinterpret_cast<int*>(m_textureSet);
		int refCount = textureRef[1] - 1;
		textureRef[1] = refCount;
		if (refCount == 0)
		{
			(*(void (**)(void*, int))(*textureRef + 8))(m_textureSet, 1);
		}
		m_textureSet = (CTextureSet*)0;
	}

	if (m_modelLoadRef != 0)
	{
		int* modelLoadRef = reinterpret_cast<int*>(m_modelLoadRef);
		int refCount = modelLoadRef[1] - 1;
		modelLoadRef[1] = refCount;
		if (refCount == 0)
		{
			(*(void (**)(void*, int))(*modelLoadRef + 8))(m_modelLoadRef, 1);
		}
		m_modelLoadRef = (CRef*)0;
	}

	if (m_texLoadRef != 0)
	{
		int* texLoadRef = reinterpret_cast<int*>(m_texLoadRef);
		int refCount = texLoadRef[1] - 1;
		texLoadRef[1] = refCount;
		if (refCount == 0)
		{
			(*(void (**)(void*, int))(*texLoadRef + 8))(m_texLoadRef, 1);
		}
		m_texLoadRef = (CRef*)0;
	}

	if (m_pdtLoadRef != 0)
	{
		int* pdtLoadRef = reinterpret_cast<int*>(m_pdtLoadRef);
		int refCount = pdtLoadRef[1] - 1;
		pdtLoadRef[1] = refCount;
		if (refCount == 0)
		{
			(*(void (**)(void*, int))(*pdtLoadRef + 8))(m_pdtLoadRef, 1);
		}
		m_pdtLoadRef = (CRef*)0;
	}

	CharaPcs.releaseUnuseLoadModel(0);
	m_asyncCharaKind = charaKind;
	m_asyncCharaNo = static_cast<int>(charaNo);
	m_asyncTextureVariant = static_cast<int>(textureVariant);
	m_asyncState = 1;
	loadModelASyncFrame();
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
    void* model = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x18);
    if (model != 0) {
        int* refData = reinterpret_cast<int*>(model);
        int refCount = refData[1] - 1;
        refData[1] = refCount;
        if (refCount == 0) {
            (*(void (**)(void*, int))(*refData + 8))(model, 1);
        }
        *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x18) = 0;
    }

    __dt__4CRefFv(this, 0);
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
    void* anim = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x28);
    if (anim != 0) {
        int* refData = reinterpret_cast<int*>(anim);
        int refCount = refData[1] - 1;
        refData[1] = refCount;
        if (refCount == 0) {
            (*(void (**)(void*, int))(*refData + 8))(anim, 1);
        }
        *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x28) = 0;
    }

    __dt__4CRefFv(this, 0);
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
    void* texture = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x1C);
    if (texture != 0) {
        int* refData = reinterpret_cast<int*>(texture);
        int refCount = refData[1] - 1;
        refData[1] = refCount;
        if (refCount == 0) {
            (*(void (**)(void*, int))(*refData + 8))(texture, 1);
        }
        *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x1C) = 0;
    }

    __dt__4CRefFv(this, 0);
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
    int& pdtSlot = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x14);
    if (pdtSlot >= 0) {
        ReleasePdt__8CPartPcsFi(PartPcs, pdtSlot);
        pdtSlot = -1;
    }

    __dt__4CRefFv(this, 0);
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
