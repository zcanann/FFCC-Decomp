#include "ffcc/memorycard.h"
#include "ffcc/file.h"
#include "ffcc/chara.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"

#include "dolphin/card.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"
#include "string.h"

class CardConst
{
public:
    static char* MC_ICONIMG_FNAME;
    static char* MC_FNAME;
    static char* MC_COMMENT;
    static char* MCDAT_MAKER;
    static char* MCDAT_TITLE;
    static char* MCDAT_MACHINE;
    static char* MCDAT_VERSION;
};

CMemoryCardMan MemoryCardMan;

extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" int memcmp(const void* lhs, const void* rhs, unsigned long count);
extern const char sMcOdekakeReturn[];
// CRC32 lookup table
static const unsigned int crcTable[256] = {
    0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9,
    0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005,
    0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
    0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd,
    0x4c11db70, 0x48d0c6c7, 0x4593e01e, 0x4152fda9,
    0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
    0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011,
    0x791d4014, 0x7ddc5da3, 0x709f7b7a, 0x745e66cd,
    0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,
    0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5,
    0xbe2b5b58, 0xbaea46ef, 0xb7a96036, 0xb3687d81,
    0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
    0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49,
    0xc7361b4c, 0xc3f706fb, 0xceb42022, 0xca753d95,
    0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
    0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d,
    0x34867077, 0x30476dc0, 0x3d044b19, 0x39c556ae,
    0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
    0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16,
    0x018aeb13, 0x054bf6a4, 0x0808d07d, 0x0cc9cdca,
    0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,
    0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02,
    0x5e9f46bf, 0x5a5e5b08, 0x571d7dd1, 0x53dc6066,
    0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
    0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e,
    0xbfa1b04b, 0xbb60adfc, 0xb6238b25, 0xb2e29692,
    0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,
    0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a,
    0xe0b41de7, 0xe4750050, 0xe9362689, 0xedf73b3e,
    0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
    0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686,
    0xd5b88683, 0xd1799b34, 0xdc3abded, 0xd8fba05a,
    0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,
    0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb,
    0x4f040d56, 0x4bc510e1, 0x46863638, 0x42472b8f,
    0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
    0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47,
    0x36194d42, 0x32d850f5, 0x3f9b762c, 0x3b5a6b9b,
    0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,
    0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623,
    0xf12f560e, 0xf5ee4bb9, 0xf8ad6d60, 0xfc6c70d7,
    0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
    0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f,
    0xc423cd6a, 0xc0e2d0dd, 0xcda1f604, 0xc960ebb3,
    0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
    0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b,
    0x9b3660c6, 0x9ff77d71, 0x92b45ba8, 0x9675461f,
    0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
    0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640,
    0x4e8ee645, 0x4a4ffbf2, 0x470cdd2b, 0x43cdc09c,
    0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,
    0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24,
    0x119b4be9, 0x155a565e, 0x18197087, 0x1cd86d30,
    0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
    0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088,
    0x2497d08d, 0x2056cd3a, 0x2d15ebe3, 0x29d4f654,
    0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,
    0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c,
    0xe3a1cbc1, 0xe760d676, 0xea23f0af, 0xeee2ed18,
    0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
    0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0,
    0x9abc8bd5, 0x9e7d9662, 0x933eb0bb, 0x97ffad0c,
    0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,
    0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
};
static const char sMemoryCardManagerName[] = "CMemoryCardMan";
static const char sMcOdekakeFmt[] = {
    0x43, 0x4D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x43, 0x61, 0x72, 0x64, 0x4D,
    0x61, 0x6E, 0x2E, 0x4F, 0x64, 0x65, 0x6B, 0x61, 0x6B, 0x65, 0x3A, 0x20,
    (char)0x83, 0x4C, (char)0x83, (char)0x83, (char)0x83, (char)0x89, (char)0x83,
    0x6F, (char)0x83, (char)0x93, 0x25, 0x64, (char)0x82, (char)0xA9, (char)0x82,
    (char)0xE7, (char)0x83, 0x4C, (char)0x83, (char)0x83, (char)0x83, (char)0x89,
    (char)0x83, 0x6F, (char)0x83, (char)0x93, 0x25, 0x64, (char)0x82, (char)0xC9,
    0x25, 0x73, (char)0x82, (char)0xB5, (char)0x82, (char)0xDC, (char)0x82,
    (char)0xB7, (char)0x81, 0x42, 0x0A, 0x00,
};
static const char sMcOdekakeOut[] = {
    (char)0x82, (char)0xA8, (char)0x8F, 0x6F, (char)0x82, (char)0xA9, (char)0x82,
    (char)0xAF, 0x00,
};
static const char sMemoryCardSourceFile[] = "memorycard.cpp";
static const char sMemoryAllocationError[] = {
    0x25, 0x73, 0x28, 0x25, 0x64, 0x29, 0x3A, 0x20, 0x45, 0x72, 0x72, 0x6F,
    0x72, 0x3A, 0x20, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x20, 0x61, 0x6C,
    0x6C, 0x6F, 0x63, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x65, 0x72, 0x72,
    0x6F, 0x72, 0x0A, 0x00, 0x4D, 0x63, 0x52, 0x65, 0x61, 0x64, 0x28, 0x25,
    0x64, 0x29, 0x20, 0x65, 0x72, 0x72, 0x6F, 0x72, 0x28, 0x25, 0x64, 0x29,
    0x0A, 0x00, 0x00, 0x00, 0x4D, 0x63, 0x46, 0x6F, 0x72, 0x6D, 0x61, 0x74,
    0x28, 0x25, 0x64, 0x29, 0x20, 0x65, 0x72, 0x72, 0x6F, 0x72, 0x28, 0x25,
    0x64, 0x29, 0x0A, 0x00, 0x4D, 0x63, 0x43, 0x72, 0x65, 0x61, 0x74, 0x65,
    0x28, 0x25, 0x64, 0x29, 0x20, 0x65, 0x72, 0x72, 0x6F, 0x72, 0x28, 0x25,
    0x64, 0x29, 0x0A, 0x00, 0x4D, 0x63, 0x47, 0x65, 0x74, 0x53, 0x74, 0x61,
    0x74, 0x28, 0x25, 0x64, 0x29, 0x20, 0x65, 0x72, 0x72, 0x6F, 0x72, 0x28,
    0x25, 0x64, 0x29, 0x0A,
};
static const char sMemoryCardIconPathFmt[] = "dvd/%smenu/%s";
static const char sMemoryCardOpenErrorFmt[] = "%s(%d): Error: %s open error";
static const char sMemoryCardDataErrorFmt[] = "%s(%d): Error: [%s] data error";
static const char DAT_801db044[] = {
    0x43, 0x4D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x43, 0x61, 0x72, 0x64, 0x4D,
    0x61, 0x6E, 0x2E, 0x44, 0x65, 0x62, 0x75, 0x67, 0x52, 0x65, 0x61, 0x64,
    0x57, 0x72, 0x69, 0x74, 0x65, 0x3A, 0x20, (char)0x83, 0x74, (char)0x83, 0x48,
    (char)0x81, 0x5B, (char)0x83, (char)0x7D, (char)0x83, (char)0x62, (char)0x83, (char)0x67,
    (char)0x82, (char)0xB5, (char)0x82, (char)0xDC, (char)0x82, (char)0xB7, (char)0x81, 0x42,
    0x0A, 0x00, 0x00, 0x00, 0x00,
};
static const char DAT_801db07c[] = {
    0x43, 0x4D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x43, 0x61, 0x72, 0x64, 0x4D,
    0x61, 0x6E, 0x2E, 0x44, 0x65, 0x62, 0x75, 0x67, 0x52, 0x65, 0x61, 0x64,
    0x57, 0x72, 0x69, 0x74, 0x65, 0x3A, 0x20, (char)0x8E, (char)0xB8, (char)0x94, 0x73,
    (char)0x82, (char)0xB5, (char)0xDC, (char)0x82, (char)0xB5, (char)0xBD, (char)0x81, 0x42,
    0x0A, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char sMcMountErrorFmt[] = "McMount(%d) error(%d)";
static const char sMcGetStatErrorFmt[] = "McGetStat(%d) error(%d)";
static const char sMcWriteErrorFmt[] = "McWrite(%d) error(%d)";
static const char sMcSetStatErrorFmt[] = "McSetStat(%d) error(%d)";
static const char sMcOpenErrorFmt[] = "McOpen(%d) error(%d)";

static inline CChara* GetCharaGlobal()
{
    return &gChara;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMemoryCardMan::CMemoryCardMan()
{
}

/*
 * --INFO--
 * PAL Address: 0x800c4d24
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::Init()
{
    CARDInit();

    m_result = 0;
    m_opDoneFlag = 0;
    m_currentSlot = -1;
    m_state = 0;
    m_saveBuffer = (char*)nullptr;
    m_stage = reinterpret_cast<CStage*>(Memory.CreateStage(0x16000, const_cast<char*>(sMemoryCardManagerName), 0));
    m_mountWorkArea =
        new (reinterpret_cast<CMemory::CStage*>(m_stage), const_cast<char*>(sMemoryCardSourceFile), 0x88) char[0xA000];

    m_currentSlot = -1;
}

/*
 * --INFO--
 * PAL Address: 0x800c4ccc
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::Quit()
{ 
  m_currentSlot = -1;
  
  if (m_mountWorkArea != (void*)nullptr)
  {
    delete[] m_mountWorkArea;
    m_mountWorkArea = (void*)nullptr;
  }
  
  Memory.DestroyStage(reinterpret_cast<CMemory::CStage*>(m_stage));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::DebugReadWrite(int isWrite, char* filename, void* buffer, int length)
{
    bool success = false;
    bool abort   = false;
    int  result;

    // Mount card
    result = CARDMount(1, m_mountWorkArea, 0);

    bool canUseCard = false;
	
    if (result != 0 && result != -6)
    {
        canUseCard = true;
    }
    else if (CARDCheckAsync(1, 0) >= 0)
    {
        canUseCard = true;
    }

    if (canUseCard)
    {
        // Wait until card is ready; optionally format if needed.
        while (true)
        {
            result = CARDGetResultCode(1);
			
            if (result == 0)
                break; // card ready

            if ((result == -6 || result == -13) && isWrite == 0)
            {
                System.Printf("%s", const_cast<char*>(DAT_801db044));

                if (CARDFormat(1) < 0)
                {
                    abort = true;
                    break;
                }
            }
            else
            {
                abort = true;
                break;
            }
        }

        if (!abort)
        {
            unsigned long sectorSizeTmp;
            if (CARDGetSectorSize(1, &sectorSizeTmp) >= 0)
            {
                if (isWrite != 0)
                {
                    CARDFileInfo fileInfo;
                    result = CARDOpen(1, filename, &fileInfo);

                    if (result < 0)
                    {
                        int      fileNo;
                        CARDStat stat;

                        for (fileNo = 0; fileNo < 0x7F; ++fileNo)
                        {
                            if (CARDGetStatus(1, fileNo, &stat) >= 0 &&
                                strcmp(filename, (char*)&stat) == 0)
                            {
                                break;
                            }
                        }

                        if (fileNo >= 0x7F ||
                            CARDFastOpen(1, fileNo, &fileInfo) < 0)
                        {
                            abort = true;
                        }
                    }

                    if (!abort)
                    {
                        if (CARDRead(&fileInfo, buffer, length, 0) >= 0)
                            success = true;

                        CARDClose(&fileInfo);
                    }
                }
                else
                {
                    CARDDelete(1, filename);

                    CARDFileInfo fileInfo;
                    if (CARDCreate(1, filename, length, &fileInfo) >= 0)
                    {
                        if (CARDWrite(&fileInfo, buffer, length, 0) >= 0)
                            success = true;

                        CARDClose(&fileInfo);
                    }
                }
            }
        }
    }

    CARDUnmount(1);

    if (!success)
        System.Printf("%s", const_cast<char*>(DAT_801db07c));
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CMemoryCardMan::AsyncFinished()
{ 
	return m_opDoneFlag != 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::GetResult()
{
	return m_result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McMount(int chan)
{ 
    m_opDoneFlag = 0;
    m_state = 1;

    int result = CARDMountAsync(chan, m_mountWorkArea, &Detach, &Attach);

    if (result < 0)
	{
        m_opDoneFlag = 1;
    }

    m_result = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McUnmount(int chan)
{
	m_result = CARDUnmount(chan);
	m_opDoneFlag = 1;
	m_state = '\x02';
	m_currentSlot = 0xff;

	return m_result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McOpen(int chan)
{ 
	m_result = CARDOpen(chan, CardConst::MC_FNAME, &m_fileInfo);
	m_opDoneFlag = 1;
	m_state = 3;

	return m_result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McClose()
{
	int chan = m_fileInfo.chan;

	if (chan < 0 || chan > 1)
	{
		m_opDoneFlag = 1;
		m_state = 4;
		m_result = -3;

		return m_result;
	}

	int result = CARDClose(&m_fileInfo);
	
	m_result = result;
	m_opDoneFlag = 1;
	m_state = 4;

	return m_result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McCreate(int chan)
{
    m_opDoneFlag = 0;
    m_state = 5;

    int result = CARDCreateAsync(
        chan,
        CardConst::MC_FNAME,
        0x2C000, // size
        &m_fileInfo,
        &Attach
    );

    if (result < 0)
    {
        m_opDoneFlag = 1;
    }

    m_result = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McGetStat(int chan)
{
	int result = CARDGetStatus(
		chan,
		m_fileInfo.fileNo,
		&m_cardStat
	);

	m_result = result;
	m_opDoneFlag = 1;
	m_state = 6;

	return m_result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McSetStat(int chan)
{
	int result = CARDSetStatus(
		chan,
		m_fileInfo.fileNo,
		&m_cardStat
	);

	m_result = result;
	m_opDoneFlag = 1;
	m_state = 7;

	return m_result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::CreateMcBuff()
{
    if (m_saveBuffer == 0)
    {
        m_saveBuffer = reinterpret_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
            0xA000, reinterpret_cast<CMemory::CStage*>(m_stage), const_cast<char*>(sMemoryCardSourceFile), 0x2AB));

        if (m_saveBuffer == 0 && static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            System.Printf(const_cast<char*>(sMemoryAllocationError), const_cast<char*>(sMemoryCardSourceFile), 0x2AD);
        }
    }

    // Zero buffer every call, allocated or not
    memset(m_saveBuffer, 0, 0xA000);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::DestroyMcBuff()
{ 
  if (m_saveBuffer != (char*)nullptr)
  {
    delete[] m_saveBuffer;
	m_saveBuffer = (char*)nullptr;
  }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McEnd()
{
    int chan = 0;

    while (chan < 2)
    {
        int attempt = 0;

        while (attempt < 10)
        {
            int result = CARDUnmount(chan);

            m_result = result;
            m_opDoneFlag = 1;
            m_state = 2;
            m_currentSlot = 0xFF;

            // IMPORTANT: compare m_result, not result
            if (m_result != -1)
            {
                break;
            }

            attempt++;
        }

        chan++;
    }

    if (m_saveBuffer != 0)
    {
        delete[] m_saveBuffer;
        m_saveBuffer = 0;
    }

    m_result = 0;
    m_opDoneFlag = 0;
    m_currentSlot = 0xFF;
    m_state = 0;
    m_saveBuffer = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::SetMcIconImage()
{
    if (m_saveBuffer == (char*)nullptr)
    {
        if (m_saveBuffer == (char*)nullptr)
        {
            m_saveBuffer = reinterpret_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
                0xA000, reinterpret_cast<CMemory::CStage*>(m_stage), const_cast<char*>(sMemoryCardSourceFile), 0x2AB));
        }

        if (m_saveBuffer == (char*)nullptr && static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            System.Printf(const_cast<char*>(sMemoryAllocationError), const_cast<char*>(sMemoryCardSourceFile), 0x2AD);
        }

        memset(m_saveBuffer, 0, 0xA000);
    }
	
    char path[136];

    const char* lang = Game.GetLangString();
    sprintf(path, const_cast<char*>(sMemoryCardIconPathFmt), lang, CardConst::MC_ICONIMG_FNAME);
    CFile::CHandle* h = File.Open(path, 0, CFile::PRI_LOW);

    if (h == nullptr && static_cast<unsigned int>(System.m_execParam) >= 1)
    {
        System.Printf(const_cast<char*>(sMemoryCardOpenErrorFmt), const_cast<char*>(sMemoryCardSourceFile), 0x2EF, path);
    }

    File.Read(h);
    File.SyncCompleted(h);

    int len = File.GetLength(h);

    if (len != 0x2A00 && static_cast<unsigned int>(System.m_execParam) >= 1)
    {
        System.Printf(const_cast<char*>(sMemoryCardDataErrorFmt), const_cast<char*>(sMemoryCardSourceFile), 0x2F6, path);
    }

    char* saveBuffer = m_saveBuffer;
    memcpy(saveBuffer + 0x40, File.m_readBuffer, len);

    File.Close(h);

    m_cardStat.commentAddr = 0;
    m_cardStat.iconAddr    = 0x40;

    m_cardStat.bannerFormat = (m_cardStat.bannerFormat & ~0x03) | 0x02; // lower 2 bits = 2

    m_cardStat.iconFormat = (m_cardStat.iconFormat & ~0x0003) | 0x0001;
    m_cardStat.iconSpeed  = (m_cardStat.iconSpeed  & ~0x0003) | 0x0002;

    m_cardStat.iconFormat = (m_cardStat.iconFormat & ~0x000C) | 0x0004;
    m_cardStat.iconSpeed  = (m_cardStat.iconSpeed  & ~0x000C) | 0x0008;

    m_cardStat.iconFormat = (m_cardStat.iconFormat & ~0x0030) | 0x0010;
    m_cardStat.iconSpeed  = (m_cardStat.iconSpeed  & ~0x0030) | 0x0020;

    m_cardStat.iconFormat = (m_cardStat.iconFormat & ~0x00C0) | 0x0040;
    m_cardStat.iconSpeed  = (m_cardStat.iconSpeed  & ~0x00C0) | 0x0080;

    m_cardStat.iconFormat &= ~0x0300;
    m_cardStat.iconSpeed  &= ~0x0300;

    m_cardStat.offsetIcon[4] = 0xFFFFFFFF;
    m_cardStat.iconFormat &= ~0x0C00;
    m_cardStat.iconSpeed  &= ~0x0C00;

    m_cardStat.offsetIcon[5] = 0xFFFFFFFF;
    m_cardStat.iconFormat &= ~0x3000;
    m_cardStat.iconSpeed  &= ~0x3000;

    m_cardStat.offsetIcon[6] = 0xFFFFFFFF;
    m_cardStat.iconFormat &= ~0xC000;
    m_cardStat.iconSpeed  &= ~0xC000;

    m_cardStat.offsetIcon[7] = 0xFFFFFFFF;
    m_cardStat.bannerFormat &= ~0x04;

    m_cardStat.offsetIconTlut = 0x2840;
    m_cardStat.offsetIconTlut = 0x2A40;

    size_t titleLen = strlen(CardConst::MC_COMMENT);
    memcpy(saveBuffer, CardConst::MC_COMMENT, titleLen);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McRead(char* buffer, int length, int offset)
{
    if (buffer == nullptr)
    {
        buffer = m_saveBuffer;
    }

    m_opDoneFlag = 0;
    m_state = 8;

    int result = CARDReadAsync(&m_fileInfo, buffer, length, offset, &Attach);

    if (result < 0)
    {
        m_opDoneFlag = 1;
    }

    m_result = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McWrite(char* buffer, int length, int offset)
{
    if (buffer == nullptr)
    {
        buffer = m_saveBuffer;
    }

    m_opDoneFlag = 0;
    m_state = 9;

    int result = CARDWriteAsync(
        &m_fileInfo,
        buffer,
        length,
        offset,
        &Attach
    );

    if (result < 0)
    {
        m_opDoneFlag = 1;
    }

    m_result = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McFormat(int chan)
{
    m_opDoneFlag = 0;
    m_state = 10;
	
    int result = CARDFormatAsync(
        chan,
        &Attach
    );

    if (result < 0)
    {
        m_opDoneFlag = 1;
    }

    m_result = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McCheck(int chan)
{
    m_opDoneFlag = 0;
    m_state = 11;

    int result = CARDCheckAsync(chan, &Attach);

    if (result < 0)
    {
        m_opDoneFlag = 1;
    }

    m_result = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McFreeBlocks(int chan, int* bytesFree, int* filesFree)
{
    int result;
    long localBytes;
    long localFiles;

    result = CARDFreeBlocks(chan, &localBytes, &localFiles);

    m_result = result;
    *bytesFree = localBytes;
    *filesFree = localFiles;
    m_state = 12;
    m_opDoneFlag = 1;

    return m_result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McDelFile(int chan)
{
    m_opDoneFlag = 0;
    m_state = 13;
	
    int result = CARDDeleteAsync(
        chan,
        CardConst::MC_FNAME,
        &Attach
    );

    if (result < 0)
    {
        m_opDoneFlag = 1;
    }

    m_result = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CMemoryCardMan::IsBrokenFile()
{
    if (m_cardStat.iconAddr == 0xFFFFFFFF || m_cardStat.commentAddr == 0xFFFFFFFF)
    {
		return 1;
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800c369c
 * PAL Size: 2576b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::MakeSaveData()
{
    if (m_saveBuffer == (char*)nullptr)
    {
        m_saveBuffer = new char[0xA000];
        if (m_saveBuffer == (char*)nullptr)
        {
            if (System.m_execParam != 0)
            {
                System.Printf("%s", 0);
            }
            return;
        }
    }

    memset(m_saveBuffer, 0, 0xA000);

    u8* save = reinterpret_cast<u8*>(m_saveBuffer);
    u8* game = reinterpret_cast<u8*>(&Game);
    u8* gameWork = game + 0x08;

    const u64 now = OSGetTime();
    memcpy(save + 0x8AD0, &now, sizeof(now));

    memcpy(save + 0x00, CardConst::MCDAT_MAKER, strlen(CardConst::MCDAT_MAKER));
    memcpy(save + 0x04, CardConst::MCDAT_TITLE, strlen(CardConst::MCDAT_TITLE));
    memcpy(save + 0x08, CardConst::MCDAT_MACHINE, strlen(CardConst::MCDAT_MACHINE));
    memcpy(save + 0x0C, CardConst::MCDAT_VERSION, strlen(CardConst::MCDAT_VERSION));
    save[0x10] = 'E';
    save[0x11] = static_cast<u8>(*reinterpret_cast<u32*>(gameWork + 0x13D8) & 0xFF);
    save[0x12] = 0;
    *reinterpret_cast<u32*>(save + 0x18) = *reinterpret_cast<u32*>(gameWork + 0x13D8);

    for (int i = 0; i < 4; i++)
    {
        const int wm = *reinterpret_cast<int*>(gameWork + 0x18 + i * 4);
        if (wm < 0 || wm >= 9)
        {
            *reinterpret_cast<int*>(gameWork + 0x18 + i * 4) = -1;
            continue;
        }
        u8* cv = game + 0x13F0 + wm * 0xC30;
        if (*reinterpret_cast<int*>(cv + 0x3A4) == 0 || cv[0xBA5] != 0)
        {
            *reinterpret_cast<int*>(gameWork + 0x18 + i * 4) = -1;
        }
    }

    save[0x20] = gameWork[0x08];
    save[0x21] = gameWork[0x09];
    save[0x22] = gameWork[0x0A];
    save[0x23] = gameWork[0x0B];
    *reinterpret_cast<int*>(save + 0x24) = *reinterpret_cast<int*>(gameWork + 0x0C);
    *reinterpret_cast<int*>(save + 0x28) = *reinterpret_cast<int*>(gameWork + 0x10);
    *reinterpret_cast<int*>(save + 0x2C) = *reinterpret_cast<int*>(gameWork + 0x14);
    memcpy(save + 0x30, gameWork + 0x18, 0x10);
    memcpy(save + 0x40, gameWork + 0x28, 0x3C);
    memcpy(save + 0x7C, gameWork + 0x64, 0x3C);
    *reinterpret_cast<int*>(save + 0xB8) = *reinterpret_cast<int*>(gameWork + 0x10B4);
    memcpy(save + 0xC0, gameWork + 0xA0, 0x1000);
    memcpy(save + 0x10C0, gameWork + 0x10A0, 0x10);
    memcpy(save + 0x10D0, gameWork + 0x10CC, 0x100);
    memcpy(save + 0x11D0, gameWork + 0x11CC, 0x200);
    *reinterpret_cast<u32*>(save + 0x13D0) = *reinterpret_cast<u32*>(gameWork + 0x13E0);
    *reinterpret_cast<u32*>(save + 0x13D4) = *reinterpret_cast<u32*>(gameWork + 0x13E4);
    *reinterpret_cast<u32*>(save + 0x13D8) = *reinterpret_cast<u32*>(gameWork + 0x13D8);
    save[0x13DC] = gameWork[0x13D6];
    save[0x13DD] = gameWork[0x13DD];
    save[0x13DE] = gameWork[0x13DE];
    save[0x13DF] = gameWork[0x13DF];
    save[0x13E0] = gameWork[0x01] ? 1 : 0;
    save[0x13E1] = gameWork[0x02] ? 1 : 0;
    save[0x13E2] = gameWork[0x03] ? 1 : 0;
    save[0x13E3] = gameWork[0x04] ? 1 : 0;
    save[0x13E4] = gameWork[0x05] ? 1 : 0;

    for (int c = 0; c < 8; c++)
    {
        u8* dst = save + 0x14D0 + c * 0x9C0;
        u8* cv = game + 0x13F0 + c * 0xC30;

        if (*reinterpret_cast<int*>(cv + 0x3A4) == 0)
        {
            *reinterpret_cast<int*>(cv + 0xC20) = 0;
            cv[0xC1E] = 0;
        }
        else if (cv[0xC1E] == 0)
        {
            *reinterpret_cast<int*>(cv + 0xC20) = *reinterpret_cast<int*>(gameWork + 0x13D8);
            cv[0xC1E] = 1;
        }

        memcpy(dst + 0x00, cv + 0x14, 0x10);
        memcpy(dst + 0x12, cv + 0x3B8, 0x0E);
        *reinterpret_cast<u16*>(dst + 0x28) = *reinterpret_cast<u16*>(cv + 0x3C4);
        *reinterpret_cast<u16*>(dst + 0x2A) = *reinterpret_cast<u16*>(cv + 0xB4);
        memcpy(dst + 0x2C, cv + 0x3DC, 0x0A);
        memcpy(dst + 0x34, cv + 0x3AC, 0x08);
        memcpy(dst + 0x3C, cv + 0xB6, 0x80);
        *reinterpret_cast<u32*>(dst + 0xB8) = *reinterpret_cast<u32*>(cv + 0x3B4);
        *reinterpret_cast<u32*>(dst + 0xBC) = 0;
        *reinterpret_cast<u32*>(dst + 0xC0) = 0;
        *reinterpret_cast<u32*>(dst + 0xC4) = 0;
        memcpy(dst + 0xC8, cv + 0x3CA, 0x10);
        *reinterpret_cast<u32*>(dst + 0xD8) = *reinterpret_cast<u32*>(cv + 0x3E8);
        memcpy(dst + 0x104, cv + 0x3EC, 100 * 0x0C);

        for (int artifact = 0; artifact < 96; artifact++)
        {
            const int slot = artifact >> 5;
            const u32 bit = 1u << (artifact & 31);
            if (*reinterpret_cast<s16*>(cv + 0x136 + artifact * 2) > 0)
            {
                *reinterpret_cast<u32*>(dst + 0xBC + slot * 4) |= bit;
            }
        }

        memcpy(dst + 0x0C8, cv + 0x3CA, 0x10);
        memcpy(dst + 0x0C8 + 0x100, cv + 0x4CA, 0x2B0);

        memcpy(dst + 0x0C4 + 0x4D4, cv + 0x204, 0x10);
        memcpy(dst + 0x0D4 + 0x4D4, cv + 0x214, 0x10);

        *reinterpret_cast<int*>(dst + 0x1A84) = *reinterpret_cast<int*>(cv + 0x3A4);
        memcpy(dst + 0x1A88, cv + 0x8A4, 0x100);
        memcpy(dst + 0x1B88, cv + 0x9A4, 0x200);
        *reinterpret_cast<int*>(dst + 0x1D88) = *reinterpret_cast<int*>(cv + 0x3A8);
        *reinterpret_cast<int*>(dst + 0x1D8C) = *reinterpret_cast<int*>(cv + 0x3AC);
        dst[0x1D90] = cv[0xBA5];
        dst[0x1D91] = cv[0xBA6];
        dst[0x1D92] = cv[0xC1E];
        *reinterpret_cast<int*>(dst + 0x1D94) = *reinterpret_cast<int*>(cv + 0xC20);
        *reinterpret_cast<int*>(dst + 0x1D98) = *reinterpret_cast<int*>(cv + 0xC28);
        *reinterpret_cast<int*>(dst + 0x1D9C) = *reinterpret_cast<int*>(cv + 0xC2C);
        *reinterpret_cast<int*>(dst + 0x1DA0) = *reinterpret_cast<int*>(cv + 0xC24);
        *reinterpret_cast<int*>(dst + 0x1DA4) = *reinterpret_cast<int*>(cv + 0x10);
    }

    Game.SaveScript(reinterpret_cast<char*>(save + 0x62D0));
    GetCharaGlobal()->SaveFurTexBuffer(reinterpret_cast<unsigned short*>(save + 0x6AD0));
    *reinterpret_cast<u32*>(save + 0x1C) = CalcCrc((Mc::SaveDat*)nullptr);
    EncodeData();
}

/*
 * --INFO--
 * PAL Address: 0x800c2dbc
 * PAL Size: 2272b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::SetLoadData()
{
    if (m_saveBuffer == (char*)nullptr)
    {
        return;
    }

    u8* save = reinterpret_cast<u8*>(m_saveBuffer);
    u8* game = reinterpret_cast<u8*>(&Game);
    u8* gameWork = game + 0x08;

    if (memcmp(save + 0x00, CardConst::MCDAT_MAKER, strlen(CardConst::MCDAT_MAKER)) != 0)
    {
        return;
    }
    if (memcmp(save + 0x04, CardConst::MCDAT_TITLE, strlen(CardConst::MCDAT_TITLE)) != 0)
    {
        return;
    }
    if (memcmp(save + 0x08, CardConst::MCDAT_MACHINE, strlen(CardConst::MCDAT_MACHINE)) != 0)
    {
        return;
    }
    if (memcmp(save + 0x0C, CardConst::MCDAT_VERSION, strlen(CardConst::MCDAT_VERSION)) != 0)
    {
        return;
    }
    if (save[0x10] != 'E')
    {
        return;
    }

    gameWork[0x08] = save[0x20];
    gameWork[0x09] = save[0x21];
    gameWork[0x0A] = save[0x22];
    gameWork[0x0B] = save[0x23];
    *reinterpret_cast<int*>(gameWork + 0x0C) = *reinterpret_cast<int*>(save + 0x24);
    *reinterpret_cast<int*>(gameWork + 0x10) = *reinterpret_cast<int*>(save + 0x28);
    *reinterpret_cast<int*>(gameWork + 0x14) = *reinterpret_cast<int*>(save + 0x2C);
    memcpy(gameWork + 0x18, save + 0x30, 0x10);
    memcpy(gameWork + 0x28, save + 0x40, 0x3C);
    memcpy(gameWork + 0x64, save + 0x7C, 0x3C);
    *reinterpret_cast<int*>(gameWork + 0x10B4) = *reinterpret_cast<int*>(save + 0xB8);
    memcpy(gameWork + 0xA0, save + 0xC0, 0x1000);
    memcpy(gameWork + 0x10A0, save + 0x10C0, 0x10);
    memcpy(gameWork + 0x10CC, save + 0x10D0, 0x100);
    memcpy(gameWork + 0x11CC, save + 0x11D0, 0x200);
    *reinterpret_cast<u32*>(gameWork + 0x13E0) = *reinterpret_cast<u32*>(save + 0x13D0);
    *reinterpret_cast<u32*>(gameWork + 0x13E4) = *reinterpret_cast<u32*>(save + 0x13D4);
    *reinterpret_cast<u32*>(gameWork + 0x13D8) = *reinterpret_cast<u32*>(save + 0x13D8);
    gameWork[0x13D6] = save[0x13DC];
    Sound.SetBgmMasterVolume(static_cast<s8>(save[0x13DD]));
    Sound.SetSeMasterVolume(static_cast<s8>(save[0x13DE]));
    Sound.SetStereo(static_cast<s8>(save[0x13DF]));
    gameWork[0x01] = (save[0x13E0] != 0);
    gameWork[0x02] = (save[0x13E1] != 0);
    gameWork[0x03] = (save[0x13E2] != 0);
    gameWork[0x04] = (save[0x13E3] != 0);
    gameWork[0x05] = (save[0x13E4] != 0);

    for (int c = 0; c < 8; c++)
    {
        u8* src = save + 0x14D0 + c * 0x9C0;
        u8* cv = game + 0x13F0 + c * 0xC30;

        int itemCount = 0;
        for (int i = 0; i < 64; i++)
        {
            if (*reinterpret_cast<s16*>(src + 0x3C + i * 2) != -1)
            {
                itemCount++;
            }
        }
        if (itemCount != *reinterpret_cast<u16*>(src + 0x2A))
        {
            *reinterpret_cast<u16*>(src + 0x2A) = static_cast<u16>(itemCount);
        }

        memcpy(cv + 0x14, src + 0x00, 0x10);
        memcpy(cv + 0x3B8, src + 0x12, 0x0E);
        *reinterpret_cast<u16*>(cv + 0x3C4) = *reinterpret_cast<u16*>(src + 0x28);
        *reinterpret_cast<u16*>(cv + 0xB4) = *reinterpret_cast<u16*>(src + 0x2A);
        memcpy(cv + 0x3DC, src + 0x2C, 0x0A);
        memcpy(cv + 0x3AC, src + 0x34, 0x08);
        memcpy(cv + 0xB6, src + 0x3C, 0x80);
        *reinterpret_cast<u32*>(cv + 0x3B4) = *reinterpret_cast<u32*>(src + 0xB8);
        *reinterpret_cast<u32*>(cv + 0x200) = *reinterpret_cast<u32*>(src + 0xBC);
        memcpy(cv + 0x3CA, src + 0xC8, 0x10);
        *reinterpret_cast<u32*>(cv + 0x3E8) = *reinterpret_cast<u32*>(src + 0xD8);
        memcpy(cv + 0x3EC, src + 0x104, 100 * 0x0C);

        for (int artifact = 0; artifact < 96; artifact++)
        {
            const int slot = artifact >> 5;
            const u32 bit = 1u << (artifact & 31);
            if ((*reinterpret_cast<u32*>(src + 0xBC + slot * 4) & bit) == 0)
            {
                *reinterpret_cast<s16*>(cv + 0x136 + artifact * 2) = -1;
            }
            else
            {
                *reinterpret_cast<s16*>(cv + 0x136 + artifact * 2) = static_cast<s16>(0x9F + artifact);
            }
        }

        memcpy(cv + 0x204, src + 0x598, 0x10);
        memcpy(cv + 0x214, src + 0x5A8, 0x10);

        *reinterpret_cast<int*>(cv + 0x3A4) = *reinterpret_cast<int*>(src + 0x1A84);
        memcpy(cv + 0x8A4, src + 0x1A88, 0x100);
        memcpy(cv + 0x9A4, src + 0x1B88, 0x200);
        *reinterpret_cast<int*>(cv + 0x3A8) = *reinterpret_cast<int*>(src + 0x1D88);
        *reinterpret_cast<int*>(cv + 0x3AC) = *reinterpret_cast<int*>(src + 0x1D8C);
        cv[0xBA5] = src[0x1D90];
        cv[0xBA6] = src[0x1D91];
        cv[0xC1E] = src[0x1D92];
        *reinterpret_cast<int*>(cv + 0xC20) = *reinterpret_cast<int*>(src + 0x1D94);
        *reinterpret_cast<int*>(cv + 0xC24) = *reinterpret_cast<int*>(src + 0x1DA0);
        *reinterpret_cast<int*>(cv + 0xC2C) = *reinterpret_cast<int*>(src + 0x1D9C);
        *reinterpret_cast<int*>(cv + 0xC28) = *reinterpret_cast<int*>(src + 0x1D98);
        *reinterpret_cast<int*>(cv + 0x10) = *reinterpret_cast<int*>(src + 0x1DA4);
        *reinterpret_cast<u16*>(cv + 0x1A) = reinterpret_cast<CCaravanWork*>(cv)->GetArtifactIncludeHpMax();

    }

    for (int i = 0; i < 4; i++)
    {
        const int wm = *reinterpret_cast<int*>(gameWork + 0x18 + i * 4);
        if (wm < 0 || wm >= 9)
        {
            *reinterpret_cast<int*>(gameWork + 0x18 + i * 4) = -1;
            continue;
        }
        u8* cv = game + 0x13F0 + wm * 0xC30;
        if (*reinterpret_cast<int*>(cv + 0x3A4) == 0 || cv[0xBA5] != 0)
        {
            *reinterpret_cast<int*>(gameWork + 0x18 + i * 4) = -1;
        }
    }

    Game.LoadScript(reinterpret_cast<char*>(save + 0x62D0));
    GetCharaGlobal()->LoadFurTexBuffer(reinterpret_cast<unsigned short*>(save + 0x6AD0));

}

/*
 * --INFO--
 * PAL Address: 0x800c2d28
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMemoryCardMan::CalcCrc(Mc::SaveDat* saveData)
{
    int count;
    unsigned char* ptr;
    unsigned int crc;
    unsigned char* data = (unsigned char*)saveData;

    if (data == nullptr)
    {
        data = (unsigned char*)m_saveBuffer;
    }

    crc = 0xFFFFFFFF;
    count = 0x1C;
    ptr = data;
    while (--count >= 0)
    {
        crc = (crc << 8) ^ crcTable[(crc >> 24) ^ *ptr];
        ptr += 1;
    }

    ptr = data + 0x20;
    count = 0x8BB0;
    while (--count >= 0)
    {
        crc = (crc << 8) ^ crcTable[(crc >> 24) ^ *ptr];
        ptr += 1;
    }

    return ~crc;
}

/*
 * --INFO--
 * PAL Address: 0x800c2c70
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMemoryCardMan::ChkCrc(Mc::SaveDat* saveData)
{
    unsigned char byte;
    unsigned int crc;
    int count;
    unsigned char* ptr;
    unsigned char* data = (unsigned char*)saveData;

    if (data == nullptr)
    {
        data = (unsigned char*)m_saveBuffer;
    }

    ptr = data;
    if (data == nullptr)
    {
        ptr = (unsigned char*)m_saveBuffer;
    }

    crc = 0xFFFFFFFF;
    count = 0x1C;
    while (--count >= 0)
    {
        byte = *ptr;
        ptr++;
        crc = (crc << 8) ^ crcTable[(crc >> 24) ^ byte];
    }

    ptr = data + 0x20;
    count = 0x8BB0;
    while (--count >= 0)
    {
        byte = *ptr;
        ptr++;
        crc = (crc << 8) ^ crcTable[(crc >> 24) ^ byte];
    }

    return (unsigned int)__cntlzw((~crc) - *(unsigned int*)(data + 0x1C)) >> 5;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::DummySave()
{
    int result;

    m_opDoneFlag = 0;
    m_state = 1;

    result = CARDMountAsync(0, m_mountWorkArea, &Detach, &Attach);
    if (result < 0)
    {
        m_opDoneFlag = 1;
    }
    m_result = result;

    // Busy-wait for async completion
    while ((-((int)m_opDoneFlag) | (int)m_opDoneFlag) >= 0)
    {
    }

    if (m_result == -6)
    {
        m_opDoneFlag = 0;
        m_state = 10;

        result = CARDFormatAsync(0, &Attach);
        if (result < 0)
        {
            m_opDoneFlag = 1;
        }
        m_result = result;

        while ((-((int)m_opDoneFlag) | (int)m_opDoneFlag) >= 0)
        {
        }

        if (m_result != 0)
        {
            if (System.m_execParam != 0)
            {
                // "%s(%d) McFormat(%d) error(%d)"
                System.Printf("%s", const_cast<char*>(sMemoryAllocationError + 0x40));
            }

            result = CARDUnmount(0);
            m_result = result;
            m_opDoneFlag = 1;
            m_state = 2;
            m_currentSlot = 0xFF;

            return m_result;
        }
    }

    // Handle general mount error
    if (m_result != 0)
    {
        if (System.m_execParam != 0)
        {
            // "%s(%d) McMount(%d) error(%d)"
            System.Printf("%s", const_cast<char*>(sMcMountErrorFmt));
        }

        result = CARDUnmount(0);
        m_result = result;
        m_opDoneFlag = 1;
        m_state = 2;
        m_currentSlot = 0xFF;

        return m_result;
    }

    result = CARDOpen(0, CardConst::MC_FNAME, &m_fileInfo);
    m_result = result;
    m_opDoneFlag = 1;
    m_state = 3;

    if (m_result == -4)
    {
        m_opDoneFlag = 0;
        m_state = 5;

        result = CARDCreateAsync(
            0,
            CardConst::MC_FNAME,
            0x2C000,
            &m_fileInfo,
            &Attach
        );

        if (result < 0)
        {
            m_opDoneFlag = 1;
        }
        m_result = result;

        while ((-((int)m_opDoneFlag) | (int)m_opDoneFlag) >= 0)
        {
        }

        if (m_result != 0)
        {
            if (System.m_execParam != 0)
            {
                // "McCreate(%d) error(%d)"
                System.Printf("%s", const_cast<char*>(sMemoryAllocationError + 0x58));
            }

            result = CARDUnmount(0);
            m_result = result;
            m_opDoneFlag = 1;
            m_state = 2;
            m_currentSlot = 0xFF;

            return m_result;
        }

        result = CARDGetStatus(0, m_fileInfo.fileNo, &m_cardStat);
        m_result = result;
        m_opDoneFlag = 1;
        m_state = 6;

        if (m_result != 0)
        {
            if (System.m_execParam != 0)
            {
                // "McGetStat(%d) error(%d)"
                System.Printf("%s", const_cast<char*>(sMcGetStatErrorFmt));
            }

            result = CARDUnmount(0);
            m_result = result;
            m_opDoneFlag = 1;
            m_state = 2;
            m_currentSlot = 0xFF;

            return m_result;
        }

        if (m_saveBuffer == 0)
        {
            m_saveBuffer = (char*)0;  
            // __nwa__(0xA000, mStage, s_memorycard_cpp_801daea8, 0x2AB);

            if (m_saveBuffer == 0 && System.m_execParam != 0)
            {
                // "%s(%d): Error: memory allocation"
                System.Printf("%s", const_cast<char*>(sMemoryAllocationError));
            }
        }

        memset(m_saveBuffer, 0, 0xA000);
		
        SetMcIconImage();

        m_opDoneFlag = 0;
        m_state = 9;

        result = CARDWriteAsync(
            &m_fileInfo,
            m_saveBuffer,
            0x4000,
            0,
            &Attach
        );

        if (result < 0)
        {
            m_opDoneFlag = 1;
        }
        m_result = result;

        while ((-((int)m_opDoneFlag) | (int)m_opDoneFlag) >= 0)
        {
        }

        if (m_result != 0)
        {
            if (System.m_execParam != 0)
            {
                System.Printf("%s", const_cast<char*>(sMcWriteErrorFmt));
            }

            result = CARDUnmount(0);
            m_result = result;
            m_opDoneFlag = 1;
            m_state = 2;
            m_currentSlot = 0xFF;

            if (m_saveBuffer != 0)
            {
                delete[] m_saveBuffer;
                m_saveBuffer = 0;
            }

            return m_result;
        }

        result = CARDSetStatus(0, m_fileInfo.fileNo, &m_cardStat);
        m_result = result;
        m_opDoneFlag = 1;
        m_state = 7;

        if (m_result != 0)
        {
            if (System.m_execParam != 0)
            {
                System.Printf("%s", const_cast<char*>(sMcSetStatErrorFmt));
            }

            result = CARDUnmount(0);
            m_result = result;
            m_opDoneFlag = 1;
            m_state = 2;
            m_currentSlot = 0xFF;

            if (m_saveBuffer != 0)
            {
                delete[] m_saveBuffer;
                m_saveBuffer = 0;
            }

            return m_result;
        }
    }
    else
    {
        if (m_saveBuffer == 0)
        {
            m_saveBuffer = (char*)0;
            // __nwa__(0xA000, ...)

            if (m_saveBuffer == 0 && System.m_execParam != 0)
            {
                System.Printf("%s", const_cast<char*>(sMemoryAllocationError));
            }
        }

        memset(m_saveBuffer, 0, 0xA000);
    }

    MakeSaveData();
	
    m_opDoneFlag = 0;
    m_state = 9;

    result = CARDWriteAsync(
        &m_fileInfo,
        m_saveBuffer,
        0xA000,
        0x4000,
        &Attach
    );

    if (result < 0)
    {
        m_opDoneFlag = 1;
    }
    m_result = result;

    while ((-((int)m_opDoneFlag) | (int)m_opDoneFlag) >= 0)
    {
    }

    if (m_result == 0)
    {
        if (m_saveBuffer != 0)
        {
            delete[] m_saveBuffer;
            m_saveBuffer = 0;
        }

        int chan = m_fileInfo.chan;

        if (chan < 0 || chan > 1)
        {
            m_opDoneFlag = 1;
            m_state = 4;
            m_result = -3;
        }
        else
        {
            result = CARDClose(&m_fileInfo);
            m_result = result;
            m_opDoneFlag = 1;
            m_state = 4;
        }

        result = CARDUnmount(0);
        m_result = result;
        m_opDoneFlag = 1;

        m_state = 2;
        m_currentSlot = 0xFF;

        return 0;
    }

    if (System.m_execParam != 0)
    {
        System.Printf("%s", const_cast<char*>(sMcWriteErrorFmt));
    }

    int chan = m_fileInfo.chan;

    if (chan < 0 || chan > 1)
    {
        m_opDoneFlag = 1;
        m_state = 4;
        m_result = -3;
    }
    else
    {
        result = CARDClose(&m_fileInfo);
        m_result = result;
        m_opDoneFlag = 1;
        m_state = 4;
    }

    result = CARDUnmount(0);
    m_result = result;
    m_opDoneFlag = 1;
    m_state = 2;
    m_currentSlot = 0xFF;

    if (m_saveBuffer != 0)
    {
        delete[] m_saveBuffer;
        m_saveBuffer = 0;
    }

    return m_result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::DummyLoad()
{
    int result;

    // Begin mount
    m_opDoneFlag = 0;
    m_state = 1;

    result = CARDMountAsync(0, m_mountWorkArea, &Detach, &Attach);
    if (result < 0)
    {
        m_opDoneFlag = 1;
    }
    m_result = result;

    // Busy wait for async completion
    while ( ((-(int)m_opDoneFlag) | (int)m_opDoneFlag) >= 0 )
    {
    }

    // If mount failed
    if (m_result != 0)
    {
        if (System.m_execParam != 0)
        {
            // "McMount(%d) error(%d)"
            System.Printf("%s", const_cast<char*>(sMcMountErrorFmt));
        }

        result = CARDUnmount(0);
        m_result = result;
        m_opDoneFlag = 1;
        m_state = 2;
        m_currentSlot = 0xFF;

        return m_result;
    }

    result = CARDOpen(0, CardConst::MC_FNAME, &m_fileInfo);
    m_result = result;
    m_opDoneFlag = 1;
    m_state = 3;

    if (m_result != 0)
    {
        // Open failed
        if (System.m_execParam != 0)
        {
            // "McOpen(%d) error(%d)"
            System.Printf("%s", const_cast<char*>(sMcOpenErrorFmt));
        }

        result = CARDUnmount(0);
        m_result = result;
        m_opDoneFlag = 1;
        m_state = 2;
        m_currentSlot = 0xFF;

        return m_result;
    }

    if (m_saveBuffer == 0)
    {
        m_saveBuffer = (char*)0; 
        // __nwa__(0xA000, mStage, s_memorycard_cpp_801daea8, 0x2AB);

        if (m_saveBuffer == 0 && System.m_execParam != 0)
        {
            System.Printf("%s", const_cast<char*>(sMemoryAllocationError));
        }
    }

    memset(m_saveBuffer, 0, 0xA000);
    m_opDoneFlag = 0;
    m_state = 8;

    result = CARDReadAsync(
        &m_fileInfo,
        m_saveBuffer,
        0xA000,
        0x4000,
        &Attach
    );

    if (result < 0)
    {
        m_opDoneFlag = 1;
    }

    m_result = result;

    // Wait for read to finish
    while ( ((-(int)m_opDoneFlag) | (int)m_opDoneFlag) >= 0 )
    {
    }

    if (m_result == 0)
    {
        int chan = m_fileInfo.chan;

        if (chan < 0 || chan > 1)
        {
            m_opDoneFlag = 1;
            m_state = 4;
            m_result = -3;
        }
        else
        {
            result = CARDClose(&m_fileInfo);
            m_result = result;
            m_opDoneFlag = 1;
            m_state = 4;
        }

        result = CARDUnmount(0);
        m_result = result;
        m_opDoneFlag = 1;
        m_state = 2;
        m_currentSlot = 0xFF;

        // Game.LoadInit();
        SetLoadData();
        // Game.LoadFinished();

        if (m_saveBuffer != 0)
        {
            delete[] m_saveBuffer;
            m_saveBuffer = 0;
        }

        return 0;
    }

    if (System.m_execParam != 0)
    {
        // "McRead(%d) error(%d)"
        System.Printf("%s", const_cast<char*>(sMemoryAllocationError + 0x28));
    }

    int chan = m_fileInfo.chan;

    if (chan < 0 || chan > 1)
    {
        m_opDoneFlag = 1;
        m_state = 4;
        m_result = -3;
    }
    else
    {
        result = CARDClose(&m_fileInfo);
        m_result = result;
        m_opDoneFlag = 1;
        m_state = 4;
    }

    result = CARDUnmount(0);
    m_result = result;
    m_opDoneFlag = 1;
    m_state = 2;
    m_currentSlot = 0xFF;

    if (m_saveBuffer != 0)
    {
        delete[] m_saveBuffer;
        m_saveBuffer = 0;
    }

    return m_result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::CnvPlayTime(unsigned int frames, int* hours, int* minutes)
{
    int total_minutes = frames / 1500;
	
    *minutes = total_minutes % 60;
    *hours = total_minutes / 60;
	
    if (*hours >= 999)
	{
        *hours = 999;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McChkConnect(int chan)
{
    long type;
    long sectorSize;
	int result;

    // CARDProbeEx returns:
    //  0   = ready
    // -1   = no card
    // -2   = busy
    // -5   = broken
    int probeResult = CARDProbeEx(chan, &type, &sectorSize);

    if (probeResult == -1)
    {
        result = 1;
    }
    else if (probeResult == 0)
    {
        if (sectorSize != 0x2000)
        {
            result = -2;
        }
        else
        {
            result = 0;
        }
    }
    else if (probeResult == -2)
    {
        result = -3;
    }
    else if (probeResult == -5)
    {
        result = -4;
    }
    else
    {
        result = -1;
    }

    return result;
}

inline int rotlwi(int, int)
{
	return 0;
}

inline int rotrwi(int, int)
{
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800C1FF0
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::EncodeData()
{
    const int rotAmount = reinterpret_cast<unsigned char*>(m_saveBuffer)[0x11] % 0x20;
    u32* ptr = reinterpret_cast<u32*>(m_saveBuffer + 0x18);

    for (int count = 0; count < 0x5B6; count++)
    {
        u32 rotated = __rlwnm(ptr[0], rotAmount, 0, 31);
        ptr[0] = __lwbrx(&rotated, 0);
        rotated = __rlwnm(ptr[1], rotAmount, 0, 31);
        ptr[1] = __lwbrx(&rotated, 0);
        rotated = __rlwnm(ptr[2], rotAmount, 0, 31);
        ptr[2] = __lwbrx(&rotated, 0);
        rotated = __rlwnm(ptr[3], rotAmount, 0, 31);
        ptr[3] = __lwbrx(&rotated, 0);
        rotated = __rlwnm(ptr[4], rotAmount, 0, 31);
        ptr[4] = __lwbrx(&rotated, 0);
        rotated = __rlwnm(ptr[5], rotAmount, 0, 31);
        ptr[5] = __lwbrx(&rotated, 0);
        rotated = __rlwnm(ptr[6], rotAmount, 0, 31);
        ptr[6] = __lwbrx(&rotated, 0);
        ptr += 7;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800C1F20
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::DecodeData()
{
    u32* ptr = reinterpret_cast<u32*>(m_saveBuffer + 0x18);
    const int rotAmount = 0x20 - (reinterpret_cast<unsigned char*>(m_saveBuffer)[0x11] % 0x20);

    for (int count = 0; count < 0x5B6; count++)
    {
        u32 word = ptr[0];
        ptr[0] = __rlwnm(__lwbrx(&word, 0), rotAmount, 0, 31);
        word = ptr[1];
        ptr[1] = __rlwnm(__lwbrx(&word, 0), rotAmount, 0, 31);
        word = ptr[2];
        ptr[2] = __rlwnm(__lwbrx(&word, 0), rotAmount, 0, 31);
        word = ptr[3];
        ptr[3] = __rlwnm(__lwbrx(&word, 0), rotAmount, 0, 31);
        word = ptr[4];
        ptr[4] = __rlwnm(__lwbrx(&word, 0), rotAmount, 0, 31);
        word = ptr[5];
        ptr[5] = __rlwnm(__lwbrx(&word, 0), rotAmount, 0, 31);
        word = ptr[6];
        ptr[6] = __rlwnm(__lwbrx(&word, 0), rotAmount, 0, 31);
        ptr += 7;
    }
}

void CMemoryCardMan::CalcSaveDatHpMax(Mc::SaveDat* saveDat)
{
    int charSlot = 0;

    do
    {
        if (*(int*)((char*)saveDat + 0x1A84) != 0)
        {
            short equippedItems[4];
            int itemSlot = 0;
            int accessoryCount = 0x49;

            do
            {
                if (itemSlot > 0x44)
                {
                    int bitShift = itemSlot >> 0x1F;
                    if ((*(unsigned int*)((char*)saveDat + (itemSlot >> 5) * 4 + 0x158C) &
                         1 << ((bitShift * 0x20 | (unsigned int)(itemSlot * 0x8000000 + bitShift) >> 0x1B) - bitShift)) == 0)
                    {
                        equippedItems[itemSlot - 0x45] = -1;
                    }
                    else
                    {
                        equippedItems[itemSlot - 0x45] = (short)itemSlot + 0x9F;
                    }
                }

                itemSlot++;
                accessoryCount--;
            }
            while (accessoryCount != 0);

            unsigned int totalHpBonus = 0;
            int itemData = *reinterpret_cast<int*>((char*)&Game + 0xC5B8);

            if (equippedItems[0] >= 0)
            {
                totalHpBonus = (unsigned int)*(unsigned short*)(itemData + equippedItems[0] * 0x48 + 6);
            }
            if (equippedItems[1] >= 0)
            {
                totalHpBonus += *(unsigned short*)(itemData + equippedItems[1] * 0x48 + 6);
            }
            if (equippedItems[2] >= 0)
            {
                totalHpBonus += *(unsigned short*)(itemData + equippedItems[2] * 0x48 + 6);
            }
            if (equippedItems[3] >= 0)
            {
                totalHpBonus += *(unsigned short*)(itemData + equippedItems[3] * 0x48 + 6);
            }

            unsigned short finalHpMax = 0x10;
            if (totalHpBonus + 8 < 0x10)
            {
                finalHpMax = (unsigned short)(totalHpBonus + 8);
            }

            *(unsigned short*)((char*)saveDat + 0x14D6) = finalHpMax;
        }

        charSlot++;
        saveDat = (Mc::SaveDat*)((char*)saveDat + 0x9C0);
    }
    while (charSlot < 8);
}

/*
 * --INFO--
 * PAL Address: 0x800c18fc
 * PAL Size: 1572b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::Odekake(int mode, Mc::SaveDat& srcSave, int srcChar, Mc::SaveDat& dstSave, int dstChar)
{
    if (static_cast<unsigned int>(System.m_execParam) > 2)
    {
        const char* label = sMcOdekakeReturn;
        if (mode != 0)
        {
            label = sMcOdekakeOut;
        }
        System.Printf(const_cast<char*>(sMcOdekakeFmt), srcChar, dstChar, label);
    }

    u8* srcSaveData = reinterpret_cast<u8*>(&srcSave);
    u8* dstSaveData = reinterpret_cast<u8*>(&dstSave);
    u8* srcCharData = srcSaveData + srcChar * 0x9C0 + 0x14D0;
    u8* dstCharData = dstSaveData + dstChar * 0x9C0 + 0x14D0;

    if (mode == 0)
    {
        memcpy(dstCharData + 0xBC, srcCharData + 0xBC, 0x0C);

        u8* srcWork = srcSaveData + srcChar * 0x208;
        for (int i = 0; i < 2; i++)
        {
            srcWork[0xC0] = 0;
            srcWork[0xC1] = 0;
            srcWork[0xC2] = 0;
            srcWork[0xC3] = 0;
            srcWork[0xC4] = 0;
            srcWork[0xC5] = 0;
            srcWork[0xC6] = 0;
            srcWork[0xC7] = 0;
            srcWork[0x100] = 0;
            srcWork[0x101] = 0;
            srcWork[0x102] = 0;
            srcWork[0x103] = 0;
            srcWork[0x104] = 0;
            srcWork[0x105] = 0;
            srcWork[0x106] = 0;
            srcWork[0x107] = 0;
            srcWork[0x140] = 0;
            srcWork[0x141] = 0;
            srcWork[0x142] = 0;
            srcWork[0x143] = 0;
            srcWork[0x144] = 0;
            srcWork[0x145] = 0;
            srcWork[0x146] = 0;
            srcWork[0x147] = 0;
            srcWork[0x180] = 0;
            srcWork[0x181] = 0;
            srcWork[0x182] = 0;
            srcWork[0x183] = 0;
            srcWork[0x184] = 0;
            srcWork[0x185] = 0;
            srcWork[0x186] = 0;
            srcWork[0x187] = 0;
            srcWork += 0x100;
        }

        dstCharData[0x8C0] = 0;
        srcCharData[0x8C2] = 0;
        memset(srcCharData, 0, 0x9C0);
        dstCharData[0x6C2] = 0;
        dstCharData[0x6C3] = 0x0C;
    }
    else
    {
        memset(dstCharData, 0, 0x9C0);

        *reinterpret_cast<u16*>(dstCharData + 0x00) = *reinterpret_cast<u16*>(srcCharData + 0x00);
        *reinterpret_cast<u16*>(dstCharData + 0x02) = *reinterpret_cast<u16*>(srcCharData + 0x02);
        *reinterpret_cast<u16*>(dstCharData + 0x04) = *reinterpret_cast<u16*>(srcCharData + 0x04);
        *reinterpret_cast<u16*>(dstCharData + 0x06) = *reinterpret_cast<u16*>(srcCharData + 0x06);
        *reinterpret_cast<u16*>(dstCharData + 0x08) = *reinterpret_cast<u16*>(srcCharData + 0x08);
        *reinterpret_cast<u16*>(dstCharData + 0x0A) = *reinterpret_cast<u16*>(srcCharData + 0x0A);
        *reinterpret_cast<u16*>(dstCharData + 0x0C) = *reinterpret_cast<u16*>(srcCharData + 0x0C);
        *reinterpret_cast<u16*>(dstCharData + 0x0E) = *reinterpret_cast<u16*>(srcCharData + 0x0E);
        *reinterpret_cast<u16*>(dstCharData + 0x10) = *reinterpret_cast<u16*>(srcCharData + 0x10);
        memcpy(dstCharData + 0x12, srcCharData + 0x12, 0x12);
        *reinterpret_cast<u16*>(dstCharData + 0x24) = *reinterpret_cast<u16*>(srcCharData + 0x24);
        *reinterpret_cast<u16*>(dstCharData + 0x26) = *reinterpret_cast<u16*>(srcCharData + 0x26);
        *reinterpret_cast<u16*>(dstCharData + 0x2A) = *reinterpret_cast<u16*>(srcCharData + 0x2A);
        *reinterpret_cast<u16*>(dstCharData + 0x2C) = *reinterpret_cast<u16*>(srcCharData + 0x2C);
        *reinterpret_cast<u16*>(dstCharData + 0x2E) = *reinterpret_cast<u16*>(srcCharData + 0x2E);
        *reinterpret_cast<u16*>(dstCharData + 0x30) = *reinterpret_cast<u16*>(srcCharData + 0x30);
        *reinterpret_cast<u16*>(dstCharData + 0x32) = *reinterpret_cast<u16*>(srcCharData + 0x32);
        memcpy(dstCharData + 0x34, srcCharData + 0x34, 8);
        memcpy(dstCharData + 0xBC, srcCharData + 0xBC, 0x0C);
        *reinterpret_cast<u32*>(dstCharData + 0xE8) = *reinterpret_cast<u32*>(srcCharData + 0xE8);
        memcpy(dstCharData + 0xF0, srcCharData + 0xF0, 0x10);
        *reinterpret_cast<u32*>(dstCharData + 0x5B4) = *reinterpret_cast<u32*>(srcCharData + 0x5B4);
        memcpy(dstCharData + 0x5B8, srcCharData + 0x5B8, 0x100);
        memcpy(dstCharData + 0x6B8, srcCharData + 0x6B8, 0x200);
        *reinterpret_cast<u32*>(dstCharData + 0x8B8) = *reinterpret_cast<u32*>(srcCharData + 0x8B8);
        *reinterpret_cast<u32*>(dstCharData + 0x8BC) = *reinterpret_cast<u32*>(srcCharData + 0x8BC);
        dstCharData[0x8C2] = srcCharData[0x8C2];
        *reinterpret_cast<u32*>(dstCharData + 0x8C4) = *reinterpret_cast<u32*>(srcCharData + 0x8C4);
        *reinterpret_cast<u32*>(dstCharData + 0x8C8) = *reinterpret_cast<u32*>(srcSaveData + 0x13D0);
        *reinterpret_cast<u32*>(dstCharData + 0x8CC) = *reinterpret_cast<u32*>(srcSaveData + 0x13D4);
        *reinterpret_cast<u32*>(dstCharData + 0x8D0) = *reinterpret_cast<u32*>(srcSaveData + 0x13D8);

        u8* dstWork = dstSaveData + dstChar * 0x200;
        for (int i = 0; i < 8; i++)
        {
            u8* item = dstWork + dstChar * 8;
            int row = 0;
            for (int j = 0; j < 2; j++)
            {
                item[0xC0] = ((i == 0) && (row == 0)) ? 0x32 : 0;
                item[0xC1] = ((i == 0) && (row == -1)) ? 0x32 : 0;
                item[0xC2] = ((i == 0) && (row == -2)) ? 0x32 : 0;
                item[0xC3] = ((i == 0) && (row == -3)) ? 0x32 : 0;
                row += 4;
                item += 4;
            }
            dstWork += 0x40;
        }

        memset(dstCharData + 0xC8, 0xFF, 0x10);
        memset(dstCharData + 0xD8, 0, 0x10);
        dstCharData[0x28] = 0;
        dstCharData[0x29] = 0;
        memset(dstCharData + 0x3C, 0xFF, 0x80);

        int artifact = static_cast<int>(*reinterpret_cast<s16*>(dstCharData + 0x34));
        if (artifact >= 0 && artifact < 0x40)
        {
            artifact = artifact * 2 + 0x3C;
            *reinterpret_cast<u16*>(dstCharData + artifact) = *reinterpret_cast<u16*>(srcCharData + artifact);
            *reinterpret_cast<s16*>(dstCharData + 0x28) = *reinterpret_cast<s16*>(dstCharData + 0x28) + 1;
        }

        artifact = static_cast<int>(*reinterpret_cast<s16*>(dstCharData + 0x36));
        if (artifact >= 0 && artifact < 0x40)
        {
            artifact = artifact * 2 + 0x3C;
            *reinterpret_cast<u16*>(dstCharData + artifact) = *reinterpret_cast<u16*>(srcCharData + artifact);
            *reinterpret_cast<s16*>(dstCharData + 0x28) = *reinterpret_cast<s16*>(dstCharData + 0x28) + 1;
        }

        artifact = static_cast<int>(*reinterpret_cast<s16*>(dstCharData + 0x38));
        if (artifact >= 0 && artifact < 0x40)
        {
            artifact = artifact * 2 + 0x3C;
            *reinterpret_cast<u16*>(dstCharData + artifact) = *reinterpret_cast<u16*>(srcCharData + artifact);
            *reinterpret_cast<s16*>(dstCharData + 0x28) = *reinterpret_cast<s16*>(dstCharData + 0x28) + 1;
        }

        artifact = static_cast<int>(*reinterpret_cast<s16*>(dstCharData + 0x3A));
        if (artifact >= 0 && artifact < 0x40)
        {
            artifact = artifact * 2 + 0x3C;
            *reinterpret_cast<u16*>(dstCharData + artifact) = *reinterpret_cast<u16*>(srcCharData + artifact);
            *reinterpret_cast<s16*>(dstCharData + 0x28) = *reinterpret_cast<s16*>(dstCharData + 0x28) + 1;
        }

        srcCharData[0x8C0] = 1;
        dstCharData[0x8C1] = 1;
        dstCharData[0x6C2] = 0;
        dstCharData[0x6C3] = 3;
    }

    *reinterpret_cast<u32*>(srcSaveData + 0x18) = Math.Rand(0x7FFFFFFF);
    *reinterpret_cast<u32*>(srcSaveData + 0x1C) = CalcCrc(reinterpret_cast<Mc::SaveDat*>(srcSaveData));

    *reinterpret_cast<u32*>(dstSaveData + 0x18) = Math.Rand(0x7FFFFFFF);
    *reinterpret_cast<u32*>(dstSaveData + 0x1C) = CalcCrc(reinterpret_cast<Mc::SaveDat*>(dstSaveData));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Detach(long currentSlot, long result)
{ 
	MemoryCardMan.m_result = result;
	MemoryCardMan.m_opDoneFlag = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Attach(long currentSlot, long result)
{
    MemoryCardMan.m_result = result;
    MemoryCardMan.m_opDoneFlag = '\x01';

    if (MemoryCardMan.m_state != '\x01')
        return;
    if (result != 0)
        return;

    MemoryCardMan.m_currentSlot = (char)currentSlot;
}
