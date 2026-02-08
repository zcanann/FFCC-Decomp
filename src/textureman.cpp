#include "ffcc/textureman.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTextureMan::CTextureMan()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8003BDF4
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTextureMan::Init()
{
	m_memoryStage = Memory.CreateStage(0x40000, (char*)"CTexture.texture", 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003BDC4
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTextureMan::Quit()
{
	Memory.DestroyStage(m_memoryStage);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTextureMan::SetTexture(_GXTexMapID, CTexture*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTextureMan::SetTextureTev(CTexture*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexture::CTexture()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexture::~CTexture()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::InitTexObj()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::Create(CChunkFile&, CMemory::CStage*, CAmemCacheSet*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::CacheLoadTexture(CAmemCacheSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::CacheUnLoadTexture(CAmemCacheSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::CacheRefCnt0UpTexture(CAmemCacheSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::CacheDumpTexture(CAmemCacheSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::CheckName(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::SetExternalTlut(void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::GetTlutColor(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::GetExternalTlutColor(void*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::SetTlutColor(int, _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::SetExternalTlutColor(void*, int, int, _GXColor&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::FlushTlut()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::FlushExternalTlut(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::FlushExternalTlut(void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTextureSet::CTextureSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTextureSet::~CTextureSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTextureSet::Create(void*, CMemory::CStage*, int, CAmemCacheSet*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTextureSet::Create(CChunkFile&, CMemory::CStage*, int, CAmemCacheSet*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTextureSet::Find(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTextureSet::ReleaseTextureIdx(int, CAmemCacheSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::GetNumTlut()
{
	// TODO
}
