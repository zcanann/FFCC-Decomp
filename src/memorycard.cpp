#include "ffcc/memorycard.h"
#include "ffcc/file.h"
#include "ffcc/chara.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/game.h"
#include "ffcc/RedSound/RedSound.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"

#include "dolphin/card.h"
#include "string.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

static const char sCardGameCode[] = "FFCC";
static const char sCardMakerCode[] = "GDS";
static const char sCardMachineCode[] = "GC";
static const char sCardVersion[] = "1.00";

static const char sMemoryCardGbaDvdDir[] = "dvd/gba/";
static const char sMemoryCardGbaClientBinaryName[] = "ffcc_cli.bin";
static const char sMemoryCardObjDataScriptName[] = "objdat.spt";
static const char sMemoryCardIconFileName[] = "icon.dat";
static const char sMemoryCardCommentText[] = "FF Crystal Chronicles";

namespace CardConst {
static char* MC_ICONIMG_FNAME = const_cast<char*>(sMemoryCardIconFileName);
static char* MC_FNAME = const_cast<char*>(sCardGameCode);
static char* MC_COMMENT = const_cast<char*>(sMemoryCardCommentText);
static char* MCDAT_MAKER = const_cast<char*>(sCardMakerCode);
static char* MCDAT_TITLE = const_cast<char*>(sCardGameCode);
static char* MCDAT_MACHINE = const_cast<char*>(sCardMachineCode);
static char* MCDAT_VERSION = const_cast<char*>(sCardVersion);
}

CMemoryCardMan MemoryCardMan;

const char sMcOdekakeReturn[] = "\202\250\213A\202\350";
// CRC32 lookup table
static const unsigned int s_CrcTable[256] = {
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

enum {
    kMemoryCardStageSize = 0x16000,
    kMemoryCardSaveBufferSize = 0xA000,
    kMemoryCardSaveLetterOffset = 0x104,
};

STATIC_ASSERT(offsetof(Mc::SaveDat, m_region) == 0x10);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_rotateKey) == 0x11);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_random) == 0x18);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_crc) == 0x1C);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_linkTable) == 0xC0);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_mcSerial) == 0x13D0);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_mcRandom) == 0x13D8);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_mcHasSerial) == 0x13DC);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_bgmVolume) == 0x13DD);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_seVolume) == 0x13DE);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_stereoFlag) == 0x13DF);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_gameInitFlag) == 0x13E0);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_spModeFlags[0]) == 0x13E1);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_spModeFlags[1]) == 0x13E2);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_spModeFlags[2]) == 0x13E3);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_spModeFlags[3]) == 0x13E4);
STATIC_ASSERT(offsetof(Mc::SaveDat, m_characters) == 0x14D0);
STATIC_ASSERT(sizeof(Mc::CharaDat) == 0x9C0);
STATIC_ASSERT(offsetof(Mc::CharaDat, m_tribeId) == 0x2E);
STATIC_ASSERT(offsetof(Mc::CharaDat, m_genderFlag) == 0x30);
STATIC_ASSERT(offsetof(Mc::CharaDat, m_appearanceVariant) == 0x32);
STATIC_ASSERT(offsetof(Mc::CharaDat, m_exists) == 0x5B4);
STATIC_ASSERT(offsetof(Mc::CharaDat, m_isAway) == 0x8C0);
STATIC_ASSERT(offsetof(Mc::CharaDat, m_isGuest) == 0x8C1);
STATIC_ASSERT(offsetof(Mc::CharaDat, m_hasCharacterId) == 0x8C2);
STATIC_ASSERT(offsetof(Mc::CharaDat, m_characterId) == 0x8C4);
STATIC_ASSERT(offsetof(Mc::CharaDat, m_originSerial) == 0x8C8);
STATIC_ASSERT(offsetof(Mc::CharaDat, m_originRandom) == 0x8D0);
STATIC_ASSERT(offsetof(Mc::CharaDat, m_baseDataIndex) == 0x8D4);
STATIC_ASSERT(sizeof(Mc::SaveDat) == 0x8BD0);

static inline CChara* GetCharaGlobal()
{
    return &Chara;
}

static inline Mc::SaveDat* GetSaveDat(char* saveBuffer)
{
    return reinterpret_cast<Mc::SaveDat*>(saveBuffer);
}

static inline Mc::SaveDat* GetSaveDat(u8* saveBuffer)
{
    return reinterpret_cast<Mc::SaveDat*>(saveBuffer);
}

static inline const Mc::SaveDat* GetSaveDat(const char* saveBuffer)
{
    return reinterpret_cast<const Mc::SaveDat*>(saveBuffer);
}

static inline const Mc::SaveDat* GetSaveDat(const u8* saveBuffer)
{
    return reinterpret_cast<const Mc::SaveDat*>(saveBuffer);
}

static inline u32* GetSaveEncodedWords(Mc::SaveDat* save)
{
    return &save->m_random;
}

static inline u32 LoadSwapped(u32* p)
{
    return __lwbrx(p, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800C4D24
 * PAL Size: 148b
 * EN Address: 0x800D8D40
 * EN Size: 600b
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
    m_stage = Memory.CreateStage(kMemoryCardStageSize, "CMemoryCardMan", 0);
    m_mountWorkArea =
        new (m_stage, "memorycard.cpp", 0x88)
            char[kMemoryCardSaveBufferSize];

    m_currentSlot = -1;
}

/*
 * --INFO--
 * PAL Address: 0x800C4CCC
 * PAL Size: 88b
 * EN Address: 0x800D8F98
 * EN Size: 92b
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

  Memory.DestroyStage(m_stage);
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static inline int FindCardFile(char* filename, CARDStat* stat)
{
    int fileNo = 0;
    while (fileNo < 0x7F)
    {
        if (CARDGetStatus(1, fileNo, stat) >= 0)
        {
            if (strcmp(filename, reinterpret_cast<char*>(stat)) == 0)
            {
                return fileNo;
            }
        }
        fileNo++;
    }
    return -1;
}

/*
 * --INFO--
 * PAL Address: 0x800C4AD4
 * PAL Size: 504b
 * EN Address: 0x800D9074
 * EN Size: 564b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::DebugReadWrite(int isWrite, char* filename, void* buffer, int length)
{
    int success = 0;
    int result;
    unsigned long sectorSize;
    CARDFileInfo fileInfo;
    CARDStat stat;

    result = CARDMount(1, m_mountWorkArea, 0);
    if (((result != 0) && (result != -6)) || (result = CARDCheckAsync(1, 0), result >= 0))
    {
checkResult:
        result = CARDGetResultCode(1);
        if (result != 0)
        {
            if (((result != -6) && (result != -13)) || (isWrite != 0))
            {
                goto done;
            }

            System.Printf("CMemoryCardMan.DebugReadWrite: \203t\203H\201[\203}\203b\203g\202\265\202\334\202\267\201B\012");
            result = CARDFormat(1);
            if (result < 0)
            {
                goto done;
            }

            goto checkResult;
        }

        result = CARDGetSectorSize(1, &sectorSize);
        if (result >= 0)
        {
            if (isWrite != 0)
            {
                result = CARDOpen(1, filename, &fileInfo);
                if (result >= 0)
                {
                    goto readFile;
                }

                result = FindCardFile(filename, &stat);

                if ((result >= 0) && (CARDFastOpen(1, result, &fileInfo) >= 0))
                {
readFile:
                    if (CARDRead(&fileInfo, buffer, length, 0) < 0)
                    {
                        goto closeFile;
                    }
                    goto setSuccess;
                }
            }
            else
            {
                CARDDelete(1, filename);
                result = CARDCreate(1, filename, length, &fileInfo);
                if (result >= 0)
                {
                    result = CARDWrite(&fileInfo, buffer, length, 0);
                    if (result >= 0)
                    {
setSuccess:
                        success = 1;
                    }
closeFile:
                    CARDClose(&fileInfo);
                }
            }
        }
    }

done:
    CARDUnmount(1);

    if (success == 0)
    {
        System.Printf("CMemoryCardMan.DebugReadWrite: \216\270\224s\202\265\202\334\202\265\202\275\201B\012");
    }
}

/*
 * --INFO--
 * PAL Address: 0x800C4ABC
 * PAL Size: 24b
 * EN Address: 0x800D92A8
 * EN Size: 32b
 * JP Address: TODO
 * JP Size: TODO
 */
void Detach(long currentSlot, long result)
{
	MemoryCardMan.m_result = result;
	MemoryCardMan.m_opDoneFlag = 1;
}

/*
 * --INFO--
 * PAL Address: 0x800C4A8C
 * PAL Size: 48b
 * EN Address: 0x800D92C8
 * EN Size: 84b
 * JP Address: TODO
 * JP Size: TODO
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

/*
 * --INFO--
 * PAL Address: 0x800C4A74
 * PAL Size: 24b
 * EN Address: 0x800D9370
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMemoryCardMan::AsyncFinished()
{
	return m_opDoneFlag != 0;
}

/*
 * --INFO--
 * PAL Address: 0x800C4A6C
 * PAL Size: 8b
 * EN Address: 0x800D93A4
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMemoryCardMan::GetResult()
{
	return m_result;
}

/*
 * --INFO--
 * PAL Address: 0x800C4A04
 * PAL Size: 104b
 * EN Address: 0x800D9470
 * EN Size: 240b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C49B4
 * PAL Size: 80b
 * EN Address: 0x800D9560
 * EN Size: 204b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C4964
 * PAL Size: 80b
 * EN Address: 0x800D962C
 * EN Size: 372b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C48E8
 * PAL Size: 124b
 * EN Address: 0x800D97A0
 * EN Size: 248b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C487C
 * PAL Size: 108b
 * EN Address: 0x800D9898
 * EN Size: 244b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C482C
 * PAL Size: 80b
 * EN Address: 0x800D998C
 * EN Size: 204b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C47DC
 * PAL Size: 80b
 * EN Address: 0x800D9A58
 * EN Size: 204b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C4738
 * PAL Size: 164b
 * EN Address: 0x800D9B24
 * EN Size: 228b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::CreateMcBuff()
{
    if (m_saveBuffer == 0)
    {
        m_saveBuffer = new (m_stage, "memorycard.cpp", 0x2AB)
            char[kMemoryCardSaveBufferSize];

        if (m_saveBuffer == 0 && static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            System.Printf("%s(%d): Error: memory allocation error\n", "memorycard.cpp", 0x2AD);
        }
    }

    // Zero buffer every call, allocated or not
    memset(m_saveBuffer, 0, kMemoryCardSaveBufferSize);
}

/*
 * --INFO--
 * PAL Address: 0x800C46F8
 * PAL Size: 64b
 * EN Address: 0x800D9C08
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C464C
 * PAL Size: 172b
 * EN Address: 0x800D9C4C
 * EN Size: 168b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C4344
 * PAL Size: 776b
 * EN Address: 0x800D9CF4
 * EN Size: 728b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::SetMcIconImage()
{
    if (m_saveBuffer == (char*)nullptr)
    {
        if (m_saveBuffer == (char*)nullptr)
        {
            m_saveBuffer = new (m_stage, "memorycard.cpp", 0x2AB)
                char[kMemoryCardSaveBufferSize];

            if (m_saveBuffer == (char*)nullptr && static_cast<unsigned int>(System.m_execParam) >= 1)
            {
                System.Printf("%s(%d): Error: memory allocation error\n", "memorycard.cpp", 0x2AD);
            }
        }

        memset(m_saveBuffer, 0, kMemoryCardSaveBufferSize);
    }

    char path[136];

    const char* lang = Game.GetLangString();
    sprintf(path, "dvd/%smenu/%s", lang, CardConst::MC_ICONIMG_FNAME);
    CFile::CHandle* h = File.Open(path, 0, CFile::PRI_LOW);

    if (h == nullptr && static_cast<unsigned int>(System.m_execParam) >= 1)
    {
        System.Printf("%s(%d): Error: %s open error\n", "memorycard.cpp", 0x2EF, path);
    }

    File.Read(h);
    File.SyncCompleted(h);

    int len = File.GetLength(h);

    if (len != 0x2A00 && static_cast<unsigned int>(System.m_execParam) >= 1)
    {
        System.Printf("%s(%d): Error: [%s] data error\n", "memorycard.cpp", 0x2F6, path);
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
 * PAL Address: 0x800C42DC
 * PAL Size: 104b
 * EN Address: 0x800D9FCC
 * EN Size: 268b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C4274
 * PAL Size: 104b
 * EN Address: 0x800DA0D8
 * EN Size: 268b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C4214
 * PAL Size: 96b
 * EN Address: 0x800DA1E4
 * EN Size: 228b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C41B4
 * PAL Size: 96b
 * EN Address: 0x800DA2C8
 * EN Size: 228b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C413C
 * PAL Size: 120b
 * EN Address: 0x800DA3AC
 * EN Size: 244b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C40DC
 * PAL Size: 96b
 * EN Address: 0x800DA4A0
 * EN Size: 232b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C40AC
 * PAL Size: 48b
 * EN Address: 0x800DA588
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C369C
 * PAL Size: 2576b
 * EN Address: 0x800DA5B8
 * EN Size: 2356b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::MakeSaveData()
{
    if (m_saveBuffer == (char*)nullptr)
    {
        if (m_saveBuffer == (char*)nullptr)
        {
            m_saveBuffer = new (m_stage, "memorycard.cpp", 0x2AB)
                char[kMemoryCardSaveBufferSize];
            if (m_saveBuffer == (char*)nullptr && static_cast<unsigned int>(System.m_execParam) >= 1)
            {
                System.Printf("%s(%d): Error: memory allocation error\n", "memorycard.cpp", 0x2AD);
            }
        }
        memset(m_saveBuffer, 0, kMemoryCardSaveBufferSize);
    }
    else
    {
        memset(m_saveBuffer, 0, kMemoryCardSaveBufferSize);
    }

    u8* save = reinterpret_cast<u8*>(m_saveBuffer);
    Mc::SaveDat* saveDat = GetSaveDat(save);

    const u64 now = OSGetTime();
    memcpy(save + 0x8AD0, &now, sizeof(now));

    memcpy(saveDat->m_maker, CardConst::MCDAT_MAKER, strlen(CardConst::MCDAT_MAKER));
    memcpy(saveDat->m_title, CardConst::MCDAT_TITLE, strlen(CardConst::MCDAT_TITLE));
    memcpy(saveDat->m_machine, CardConst::MCDAT_MACHINE, strlen(CardConst::MCDAT_MACHINE));
    memcpy(saveDat->m_version, CardConst::MCDAT_VERSION, strlen(CardConst::MCDAT_VERSION));
    saveDat->m_region = 'E';
    saveDat->m_random = Math.Rand(0x7FFFFFFF);
    saveDat->m_rotateKey = static_cast<u8>(Math.Rand(0xFF));
    saveDat->m_flags = 0;

    CGame* g = &Game;
    for (int i = 0; i < 4; i++)
    {
        int idx = g->m_gameWork.m_wmBackupParams[i];
        if (g->m_caravanWorkArr[idx].m_shopState == 0)
        {
            g->m_gameWork.m_wmBackupParams[i] = -1;
        }
        if (g->m_caravanWorkArr[idx].m_shopBusyFlag != 0)
        {
            g->m_gameWork.m_wmBackupParams[i] = -1;
        }
    }

    *reinterpret_cast<u32*>(save + 0x20) = *reinterpret_cast<u32*>(&Game.m_gameWork.m_scriptSysVal0);
    *reinterpret_cast<int*>(save + 0x24) = Game.m_gameWork.m_timerA;
    *reinterpret_cast<int*>(save + 0x28) = Game.m_gameWork.m_scriptGlobalTime;
    *reinterpret_cast<int*>(save + 0x2C) = Game.m_gameWork.m_frameCounter;
    memcpy(save + 0x30, Game.m_gameWork.m_wmBackupParams, 0x10);
    memcpy(save + 0x40, Game.m_gameWork.m_bossArtifactStageTable, 0x3C);
    memcpy(save + 0x7C, Game.m_gameWork.m_unkStageTable, 0x3C);
    *reinterpret_cast<int*>(save + 0xB8) = Game.m_gameWork.m_chaliceElement;
    memcpy(saveDat->m_linkTable, Game.m_gameWork.m_linkTable, sizeof(saveDat->m_linkTable));
    memcpy(save + 0x10C0, Game.m_gameWork.m_townName, 0x10);
    memcpy(save + 0x10D0, Game.m_gameWork.m_eventFlags, 0x100);
    memcpy(save + 0x11D0, Game.m_gameWork.m_eventWork, 0x200);
    memcpy(save + 0x11D0, Game.m_gameWork.m_eventWork, 0x200);
    saveDat->m_mcSerial = Game.m_gameWork.m_mcSerial;
    saveDat->m_mcRandom = Game.m_gameWork.m_mcRandom;
    saveDat->m_mcHasSerial = Game.m_gameWork.m_mcHasSerial;
    saveDat->m_bgmVolume = static_cast<s8>(Sound.GetBgmMasterVolume());
    saveDat->m_seVolume = static_cast<s8>(Sound.GetSeMasterVolume());
    saveDat->m_seVolume = static_cast<s8>(Sound.GetSeMasterVolume());
    saveDat->m_stereoFlag = Sound.IsStereo() != 0;
    saveDat->m_gameInitFlag = Game.m_gameWork.m_gameInitFlag != 0;
    for (int i = 0; i < 4; i++)
    {
        saveDat->m_spModeFlags[i] = g->m_gameWork.m_spModeFlags[i] != 0;
    }

    for (int c = 0; c < 8; c++)
    {
        int letter;
        Mc::CharaDat& savedCharacter = saveDat->m_characters[c];
        u8* dst = reinterpret_cast<u8*>(&savedCharacter);
        CCaravanWork* caravanWork = &g->m_caravanWorkArr[c];

        int shopState = caravanWork->m_shopState;
        if (shopState != 0 && static_cast<s8>(caravanWork->unk_0xc1e) == 0)
        {
            caravanWork->m_shopRandSeed = Math.Rand(0x7FFFFFFF);
            caravanWork->unk_0xc1e = 1;
        }
        else if (shopState == 0)
        {
            caravanWork->m_shopRandSeed = 0;
            caravanWork->unk_0xc1e = 0;
        }

        *reinterpret_cast<u16*>(dst + 0x00) = caravanWork->m_id;
        *reinterpret_cast<u16*>(dst + 0x02) = caravanWork->m_param1;
        *reinterpret_cast<u16*>(dst + 0x04) = caravanWork->m_param2;
        *reinterpret_cast<u16*>(dst + 0x06) = caravanWork->m_maxHp;
        *reinterpret_cast<u16*>(dst + 0x08) = caravanWork->m_hp;
        *reinterpret_cast<u16*>(dst + 0x0A) = caravanWork->m_strength;
        *reinterpret_cast<u16*>(dst + 0x0C) = caravanWork->m_magic;
        *reinterpret_cast<u16*>(dst + 0x0E) = caravanWork->m_defense;
        for (int i = 0; i < 8; i++)
        {
            *reinterpret_cast<u16*>(dst + 0x12 + i * 2) = caravanWork->m_letterMeta[i];
        }
        *reinterpret_cast<u16*>(dst + 0x24) = caravanWork->unk_0x3c8;
        *reinterpret_cast<u16*>(dst + 0x28) = caravanWork->m_inventoryItemCount;
        *reinterpret_cast<u16*>(dst + 0x2A) = caravanWork->unk_0x3dc;
        *reinterpret_cast<u16*>(dst + 0x2C) = caravanWork->m_progressValue;
        savedCharacter.m_tribeId = caravanWork->m_tribeId;
        savedCharacter.m_genderFlag = caravanWork->m_genderFlag;
        savedCharacter.m_appearanceVariant = caravanWork->m_appearanceVariant;
        *reinterpret_cast<s16*>(dst + 0x34) = caravanWork->m_equipment[0];
        *reinterpret_cast<s16*>(dst + 0x36) = caravanWork->m_equipment[1];
        *reinterpret_cast<s16*>(dst + 0x38) = caravanWork->m_equipment[2];
        *reinterpret_cast<s16*>(dst + 0x3A) = caravanWork->m_equipment[3];
        for (int i = 0; i < 64; i++)
        {
            *reinterpret_cast<s16*>(dst + 0x3C + i * 2) = caravanWork->m_inventoryItems[i];
        }
        *reinterpret_cast<u32*>(dst + 0xE8) = caravanWork->m_joybusCaravanId;
        *reinterpret_cast<u32*>(dst + 0xEC) = caravanWork->m_gil;
        memcpy(dst + 0xF0, caravanWork->m_name, 0x10);
        *reinterpret_cast<u32*>(dst + 0x100) = caravanWork->m_letterCount;
        for (letter = 0; letter < 100; letter++)
        {
            reinterpret_cast<CCaravanWork::CLetterWork*>(dst + letter * 0xC + 0x104)->FlagsBits().m_attachmentIsGil =
                reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + letter * 0xC + 0x3EC)->FlagsBits().m_attachmentIsGil;
            reinterpret_cast<CCaravanWork::CLetterWork*>(dst + letter * 0xC + 0x104)->HeaderBitsRef().m_messageType =
                reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + letter * 0xC + 0x3EC)->HeaderBitsRef().m_messageType;
            reinterpret_cast<CCaravanWork::CLetterWork*>(dst + letter * 0xC + 0x104)->WordBitsRef().m_senderId =
                reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + letter * 0xC + 0x3EC)->WordBitsRef().m_senderId;
            reinterpret_cast<CCaravanWork::CLetterWork*>(dst + letter * 0xC + 0x104)->AttachmentBitsRef().m_value =
                reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + letter * 0xC + 0x3EC)->AttachmentBitsRef().m_value;
            memcpy(dst + letter * 0xC + 0x108, reinterpret_cast<u8*>(caravanWork) + letter * 0xC + 0x3F0, 8);
            reinterpret_cast<CCaravanWork::CLetterWork*>(dst + letter * 0xC + 0x104)->FlagsBits().m_opened =
                reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + letter * 0xC + 0x3EC)->FlagsBits().m_opened;
            reinterpret_cast<CCaravanWork::CLetterWork*>(dst + letter * 0xC + 0x104)->FlagsBits().m_attachmentClaimed =
                reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + letter * 0xC + 0x3EC)->FlagsBits().m_attachmentClaimed;
            reinterpret_cast<CCaravanWork::CLetterWork*>(dst + letter * 0xC + 0x104)->FlagsBits().m_replySent =
                reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + letter * 0xC + 0x3EC)->FlagsBits().m_replySent;
            reinterpret_cast<CCaravanWork::CLetterWork*>(dst + letter * 0xC + 0x104)->FlagsBits().m_hasReply =
                reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + letter * 0xC + 0x3EC)->FlagsBits().m_hasReply;
        }

        for (int artifact = 0; artifact < 96; artifact++)
        {
            const int slot = artifact + 64;
            if (caravanWork->m_inventoryItems[slot] > 0)
            {
                *reinterpret_cast<u32*>(dst + 0xBC + (artifact >> 5) * 4) |= 1u << (artifact % 32);
            }
        }

        for (int i = 0; i < 8; i++)
        {
            *reinterpret_cast<s16*>(dst + 0xC8 + i * 2) = caravanWork->m_commandListInventorySlotRef[i];
            *reinterpret_cast<s16*>(dst + 0xD8 + i * 2) = caravanWork->m_commandListExtra[i];
        }

        *reinterpret_cast<int*>(dst + 0x5B4) = caravanWork->m_shopState;
        memcpy(dst + 0x5B8, caravanWork->m_evtFlags, 0x100);
        memcpy(dst + 0x6B8, caravanWork->m_evtWordArr, 0x200);
        *reinterpret_cast<int*>(dst + 0x8B8) = caravanWork->unk_0x3a8;
        *reinterpret_cast<int*>(dst + 0x8BC) = caravanWork->unk_0x3ac;
        dst[0x8C0] = caravanWork->m_shopBusyFlag;
        dst[0x8C1] = caravanWork->m_caravanLocalFlags;
        dst[0x8C2] = caravanWork->unk_0xc1e;
        *reinterpret_cast<int*>(dst + 0x8C4) = caravanWork->m_shopRandSeed;
        *reinterpret_cast<int*>(dst + 0x8D0) = caravanWork->m_shopData0;
        *reinterpret_cast<u64*>(dst + 0x8C8) = *reinterpret_cast<u64*>(&caravanWork->m_shopData1);
        *reinterpret_cast<int*>(dst + 0x8D4) = caravanWork->m_baseDataIndex;
    }

    Game.SaveScript(reinterpret_cast<char*>(save + 0x62D0));
    GetCharaGlobal()->SaveFurTexBuffer(reinterpret_cast<unsigned short*>(save + 0x6AD0));
    saveDat->m_crc = CalcCrc(0);
    EncodeData();
}

/*
 * --INFO--
 * PAL Address: 0x800C2DBC
 * PAL Size: 2272b
 * EN Address: 0x800DAEEC
 * EN Size: 2292b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::SetLoadData()
{
    u8* save = reinterpret_cast<u8*>(m_saveBuffer);
    Mc::SaveDat* saveDat = GetSaveDat(save);

    if (memcmp(saveDat->m_maker, CardConst::MCDAT_MAKER, strlen(CardConst::MCDAT_MAKER)) != 0)
    {
        if (static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            System.Printf("Bloken load data!!\n");
        }
        return;
    }
    if (memcmp(saveDat->m_title, CardConst::MCDAT_TITLE, strlen(CardConst::MCDAT_TITLE)) != 0)
    {
        if (static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            System.Printf("Bloken load data!!\n");
        }
        return;
    }
    if (memcmp(saveDat->m_machine, CardConst::MCDAT_MACHINE, strlen(CardConst::MCDAT_MACHINE)) != 0)
    {
        if (static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            System.Printf("Bloken load data!!\n");
        }
        return;
    }
    if (memcmp(saveDat->m_version, CardConst::MCDAT_VERSION, strlen(CardConst::MCDAT_VERSION)) != 0)
    {
        if (static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            System.Printf("The version of load data is different\n");
        }
        return;
    }
    if (saveDat->m_region != 'E')
    {
        if (static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            System.Printf("Bloken load data!!\n");
        }
        return;
    }

    *reinterpret_cast<u32*>(&Game.m_gameWork.m_scriptSysVal0) = *reinterpret_cast<u32*>(save + 0x20);
    Game.m_gameWork.m_timerA = *reinterpret_cast<int*>(save + 0x24);
    Game.m_gameWork.m_scriptGlobalTime = *reinterpret_cast<int*>(save + 0x28);
    Game.m_gameWork.m_frameCounter = *reinterpret_cast<int*>(save + 0x2C);
    memcpy(Game.m_gameWork.m_wmBackupParams, save + 0x30, 0x10);
    memcpy(Game.m_gameWork.m_bossArtifactStageTable, save + 0x40, 0x3C);
    memcpy(Game.m_gameWork.m_unkStageTable, save + 0x7C, 0x3C);
    Game.m_gameWork.m_chaliceElement = *reinterpret_cast<int*>(save + 0xB8);
    memcpy(Game.m_gameWork.m_linkTable, saveDat->m_linkTable, sizeof(saveDat->m_linkTable));
    memcpy(Game.m_gameWork.m_townName, save + 0x10C0, 0x10);
    memcpy(Game.m_gameWork.m_eventFlags, save + 0x10D0, 0x100);
    memcpy(Game.m_gameWork.m_eventWork, save + 0x11D0, 0x200);
    Game.m_gameWork.m_mcSerial = saveDat->m_mcSerial;
    Game.m_gameWork.m_mcRandom = saveDat->m_mcRandom;
    Game.m_gameWork.m_mcHasSerial = saveDat->m_mcHasSerial;
    Sound.SetBgmMasterVolume(saveDat->m_bgmVolume);
    Sound.SetSeMasterVolume(saveDat->m_seVolume);
    Sound.SetStereo(Sound.IsStereo());

    CGame* g = &Game;
    g->m_gameWork.m_gameInitFlag = saveDat->m_gameInitFlag != 0;
    for (int i = 0; i < 4; i++)
    {
        g->m_gameWork.m_spModeFlags[i] = saveDat->m_spModeFlags[i] != 0;
    }

    int count;
    int i;
    for (int c = 0; c < 8; c++)
    {
        Mc::CharaDat& savedCharacter = saveDat->m_characters[c];
        u8* src = reinterpret_cast<u8*>(&savedCharacter);
        CCaravanWork* caravanWork = &Game.m_caravanWorkArr[c];

        for (i = count = 0; i < 64; i++)
        {
            if (*reinterpret_cast<s16*>(src + 0x3C + i * 2) != -1)
            {
                count++;
            }
        }
        if (count != *reinterpret_cast<u16*>(src + 0x28))
        {
            if (static_cast<unsigned int>(System.m_execParam) >= 1)
            {
                System.Printf("\012\012\012Error:load data\202\314NumItem\202\314\220\256\215\207\220\253\202\252\215\207\202\301\202\304\202\242\202\334\202\271\202\361!!(%d)\012\012\012", c);
            }
            *reinterpret_cast<u16*>(src + 0x28) = static_cast<u16>(count);
        }

        caravanWork->m_id = *reinterpret_cast<u16*>(src + 0x00);
        caravanWork->m_param1 = *reinterpret_cast<u16*>(src + 0x02);
        caravanWork->m_param2 = *reinterpret_cast<u16*>(src + 0x04);
        caravanWork->m_maxHp = *reinterpret_cast<u16*>(src + 0x06);
        caravanWork->m_hp = *reinterpret_cast<u16*>(src + 0x08);
        caravanWork->m_strength = *reinterpret_cast<u16*>(src + 0x0A);
        caravanWork->m_magic = *reinterpret_cast<u16*>(src + 0x0C);
        caravanWork->m_defense = *reinterpret_cast<u16*>(src + 0x0E);
        for (int i = 0; i < 8; i++)
        {
            caravanWork->m_letterMeta[i] = *reinterpret_cast<u16*>(src + 0x12 + i * 2);
        }
        caravanWork->unk_0x3c8 = *reinterpret_cast<u16*>(src + 0x24);
        caravanWork->m_inventoryItemCount = *reinterpret_cast<u16*>(src + 0x28);
        caravanWork->unk_0x3dc = *reinterpret_cast<u16*>(src + 0x2A);
        caravanWork->m_progressValue = *reinterpret_cast<u16*>(src + 0x2C);
        caravanWork->m_tribeId = savedCharacter.m_tribeId;
        caravanWork->m_genderFlag = savedCharacter.m_genderFlag;
        caravanWork->m_appearanceVariant = savedCharacter.m_appearanceVariant;
        caravanWork->m_equipment[0] = *reinterpret_cast<s16*>(src + 0x34);
        caravanWork->m_equipment[1] = *reinterpret_cast<s16*>(src + 0x36);
        caravanWork->m_equipment[2] = *reinterpret_cast<s16*>(src + 0x38);
        caravanWork->m_equipment[3] = *reinterpret_cast<s16*>(src + 0x3A);
        for (int i = 0; i < 64; i++)
        {
            caravanWork->m_inventoryItems[i] = *reinterpret_cast<s16*>(src + 0x3C + i * 2);
        }
        caravanWork->m_joybusCaravanId = *reinterpret_cast<int*>(src + 0xE8);
        caravanWork->m_gil = *reinterpret_cast<int*>(src + 0xEC);
        memcpy(caravanWork->m_name, src + 0xF0, 0x10);
        caravanWork->m_letterCount = *reinterpret_cast<int*>(src + 0x100);
        for (count = 0; count < 100; count++)
        {
            reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + count * 0xC + 0x3EC)->FlagsBits().m_attachmentIsGil =
                reinterpret_cast<CCaravanWork::CLetterWork*>(src + count * 0xC + 0x104)->FlagsBits().m_attachmentIsGil;
            reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + count * 0xC + 0x3EC)->HeaderBitsRef().m_messageType =
                reinterpret_cast<CCaravanWork::CLetterWork*>(src + count * 0xC + 0x104)->HeaderBitsRef().m_messageType;
            reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + count * 0xC + 0x3EC)->WordBitsRef().m_senderId =
                reinterpret_cast<CCaravanWork::CLetterWork*>(src + count * 0xC + 0x104)->WordBitsRef().m_senderId;
            reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + count * 0xC + 0x3EC)->AttachmentBitsRef().m_value =
                reinterpret_cast<CCaravanWork::CLetterWork*>(src + count * 0xC + 0x104)->AttachmentBitsRef().m_value;
            memcpy(reinterpret_cast<u8*>(caravanWork) + count * 0xC + 0x3F0, src + count * 0xC + 0x108, 8);
            reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + count * 0xC + 0x3EC)->FlagsBits().m_opened =
                reinterpret_cast<CCaravanWork::CLetterWork*>(src + count * 0xC + 0x104)->FlagsBits().m_opened;
            reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + count * 0xC + 0x3EC)->FlagsBits().m_attachmentClaimed =
                reinterpret_cast<CCaravanWork::CLetterWork*>(src + count * 0xC + 0x104)->FlagsBits().m_attachmentClaimed;
            reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + count * 0xC + 0x3EC)->FlagsBits().m_replySent =
                reinterpret_cast<CCaravanWork::CLetterWork*>(src + count * 0xC + 0x104)->FlagsBits().m_replySent;
            reinterpret_cast<CCaravanWork::CLetterWork*>(reinterpret_cast<u8*>(caravanWork) + count * 0xC + 0x3EC)->FlagsBits().m_hasReply =
                reinterpret_cast<CCaravanWork::CLetterWork*>(src + count * 0xC + 0x104)->FlagsBits().m_hasReply;
        }

        for (int artifact = 0; artifact < 96; artifact++)
        {
            const int slot = artifact + 64;
            if ((*reinterpret_cast<u32*>(src + 0xBC + (artifact >> 5) * 4) & (1u << (artifact % 32))) != 0)
            {
                caravanWork->m_inventoryItems[slot] = static_cast<u16>(0x9F + artifact);
            }
            else
            {
                caravanWork->m_inventoryItems[slot] = 0xFFFF;
            }
        }

        for (int i = 0; i < 8; i++)
        {
            caravanWork->m_commandListInventorySlotRef[i] = *reinterpret_cast<s16*>(src + 0xC8 + i * 2);
            caravanWork->m_commandListExtra[i] = *reinterpret_cast<s16*>(src + 0xD8 + i * 2);
        }

        caravanWork->m_shopState = *reinterpret_cast<int*>(src + 0x5B4);
        memcpy(caravanWork->m_evtFlags, src + 0x5B8, 0x100);
        memcpy(caravanWork->m_evtWordArr, src + 0x6B8, 0x200);
        caravanWork->unk_0x3a8 = *reinterpret_cast<int*>(src + 0x8B8);
        caravanWork->unk_0x3ac = *reinterpret_cast<int*>(src + 0x8BC);
        caravanWork->m_shopBusyFlag = src[0x8C0];
        caravanWork->m_caravanLocalFlags = src[0x8C1];
        caravanWork->unk_0xc1e = src[0x8C2];
        caravanWork->m_shopRandSeed = *reinterpret_cast<int*>(src + 0x8C4);
        caravanWork->m_shopData0 = *reinterpret_cast<int*>(src + 0x8D0);
        *reinterpret_cast<u64*>(&caravanWork->m_shopData1) = *reinterpret_cast<u64*>(src + 0x8C8);
        caravanWork->m_baseDataIndex = *reinterpret_cast<int*>(src + 0x8D4);
        caravanWork->m_maxHp = caravanWork->GetArtifactIncludeHpMax();

    }

    for (unsigned int i = 0; i < 4; i++)
    {
        int idx = g->m_gameWork.m_wmBackupParams[i];
        if (Game.m_caravanWorkArr[idx].m_shopState == 0)
        {
            g->m_gameWork.m_wmBackupParams[i] = -1;
        }
        if (Game.m_caravanWorkArr[idx].m_shopBusyFlag != 0)
        {
            g->m_gameWork.m_wmBackupParams[i] = -1;
        }
    }

    Game.LoadScript(reinterpret_cast<char*>(save + 0x62D0));
    GetCharaGlobal()->LoadFurTexBuffer(reinterpret_cast<unsigned short*>(save + 0x6AD0));

}

/*
 * --INFO--
 * PAL Address: 0x800C2D28
 * PAL Size: 148b
 * EN Address: 0x800DB7E0
 * EN Size: 144b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMemoryCardMan::CalcCrc(Mc::SaveDat* saveData)
{
    unsigned char* data = saveData == 0 ? reinterpret_cast<unsigned char*>(m_saveBuffer)
                                       : reinterpret_cast<unsigned char*>(saveData);
    unsigned int crc = 0xFFFFFFFF;
    Crc32(0x1C, data, &crc);
    Crc32(0x8BB0, data + 0x20, &crc);
    return ~crc;
}

/*
 * --INFO--
 * PAL Address: 0x800C2C70
 * PAL Size: 184b
 * EN Address: 0x800DB870
 * EN Size: 116b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMemoryCardMan::ChkCrc(Mc::SaveDat* saveData)
{
    if (saveData == 0) {
        saveData = GetSaveDat(m_saveBuffer);
    }
    if (CalcCrc(saveData) == saveData->m_crc) {
        return 1;
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800C2550
 * PAL Size: 1824b
 * EN Address: 0x800DB8E4
 * EN Size: 1064b
 * JP Address: TODO
 * JP Size: TODO
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
    while ((((u32)(-((unsigned int)m_opDoneFlag) | (int)m_opDoneFlag)) >> 31) != 1)
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

        while ((((u32)(-((unsigned int)m_opDoneFlag) | (int)m_opDoneFlag)) >> 31) != 1)
        {
        }

        if (m_result != 0)
        {
            if (static_cast<unsigned int>(System.m_execParam) >= 1)
            {
                // "%s(%d) McFormat(%d) error(%d)"
                System.Printf("McFormat(%d) error(%d)\n", 0, m_result);
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
        if (static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            // "%s(%d) McMount(%d) error(%d)"
            System.Printf("McMount(%d) error(%d)\n", 0, m_result);
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

        while ((((u32)(-((unsigned int)m_opDoneFlag) | (int)m_opDoneFlag)) >> 31) != 1)
        {
        }

        if (m_result != 0)
        {
            if (static_cast<unsigned int>(System.m_execParam) >= 1)
            {
                // "McCreate(%d) error(%d)"
                System.Printf("McCreate(%d) error(%d)\n", 0, m_result);
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
            if (static_cast<unsigned int>(System.m_execParam) >= 1)
            {
                // "McGetStat(%d) error(%d)"
                System.Printf("McGetStat(%d) error(%d)\n", 0, m_result);
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
            m_saveBuffer = new (m_stage, "memorycard.cpp", 0x2AB)
                char[kMemoryCardSaveBufferSize];

            if (m_saveBuffer == 0 && static_cast<unsigned int>(System.m_execParam) >= 1)
            {
                System.Printf("%s(%d): Error: memory allocation error\n", "memorycard.cpp", 0x2AD);
            }
        }

        memset(m_saveBuffer, 0, kMemoryCardSaveBufferSize);

        SetMcIconImage();

        McWrite(m_saveBuffer, 0x4000, 0);

        while ((((u32)(-((unsigned int)m_opDoneFlag) | (int)m_opDoneFlag)) >> 31) != 1)
        {
        }

        if (m_result != 0)
        {
            if (static_cast<unsigned int>(System.m_execParam) >= 1)
            {
                System.Printf("McWrite(%d) error(%d)\n", 0, m_result);
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
            if (static_cast<unsigned int>(System.m_execParam) >= 1)
            {
                System.Printf("McSetStat(%d) error(%d)\n", 0, m_result);
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
            m_saveBuffer = new (m_stage, "memorycard.cpp", 0x2AB)
                char[kMemoryCardSaveBufferSize];

            if (m_saveBuffer == 0 && static_cast<unsigned int>(System.m_execParam) >= 1)
            {
                System.Printf("%s(%d): Error: memory allocation error\n", "memorycard.cpp", 0x2AD);
            }
        }

        memset(m_saveBuffer, 0, kMemoryCardSaveBufferSize);
    }

    MakeSaveData();

    McWrite(m_saveBuffer, kMemoryCardSaveBufferSize, 0x4000);

    while ((((u32)(-((unsigned int)m_opDoneFlag) | (int)m_opDoneFlag)) >> 31) != 1)
    {
    }

    if (m_result != 0)
    {
        if (static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            System.Printf("McWrite(%d) error(%d)\n", 0, m_result);
        }

        if (m_fileInfo.chan < 0 || m_fileInfo.chan > 1)
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

    if (m_saveBuffer != 0)
    {
        delete[] m_saveBuffer;
        m_saveBuffer = 0;
    }

    if (m_fileInfo.chan < 0 || m_fileInfo.chan > 1)
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

/*
 * --INFO--
 * PAL Address: 0x800C21A0
 * PAL Size: 944b
 * EN Address: 0x800DBD0C
 * EN Size: 516b
 * JP Address: TODO
 * JP Size: TODO
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
    while ((((u32)(-((unsigned int)m_opDoneFlag) | (int)m_opDoneFlag)) >> 31) != 1)
    {
    }

    // If mount failed
    if (m_result != 0)
    {
        if (static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            // "McMount(%d) error(%d)"
            System.Printf("McMount(%d) error(%d)\n", 0, m_result);
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
        if (static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            // "McOpen(%d) error(%d)"
            System.Printf("McOpen(%d) error(%d)\n", 0, m_result);
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
        m_saveBuffer = new (m_stage, "memorycard.cpp", 0x2AB)
            char[kMemoryCardSaveBufferSize];

        if (m_saveBuffer == 0 && static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            System.Printf("%s(%d): Error: memory allocation error\n", "memorycard.cpp", 0x2AD);
        }
    }

    memset(m_saveBuffer, 0, kMemoryCardSaveBufferSize);
    McRead(m_saveBuffer, kMemoryCardSaveBufferSize, 0x4000);

    // Wait for read to finish
    while ((((u32)(-((unsigned int)m_opDoneFlag) | (int)m_opDoneFlag)) >> 31) != 1)
    {
    }

    if (m_result != 0)
    {
        if (static_cast<unsigned int>(System.m_execParam) >= 1)
        {
            // "McRead(%d) error(%d)"
            System.Printf("McRead(%d) error(%d)\n", 0, m_result);
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

    Game.LoadInit();
    SetLoadData();
    Game.LoadFinished();

    if (m_saveBuffer != 0)
    {
        delete[] m_saveBuffer;
        m_saveBuffer = 0;
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800C2140
 * PAL Size: 96b
 * EN Address: 0x800DBF10
 * EN Size: 128b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800C20BC
 * PAL Size: 132b
 * EN Address: 0x800DBF90
 * EN Size: 260b
 * JP Address: TODO
 * JP Size: TODO
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

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 72b
 * EN Address: 0x800DC094
 * EN Size: 92b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMemoryCardMan::Crc32(int count, unsigned char* data, unsigned int* crc)
{
    while (--count >= 0) {
        *crc = (*crc << 8) ^ s_CrcTable[(*crc >> 24) ^ *data++];
    }
}

/*
 * --INFO--
 * PAL Address: 0x800C1FF0
 * PAL Size: 204b
 * EN Address: 0x800DC0F0
 * EN Size: 148b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::EncodeData()
{
    Mc::SaveDat* const save = GetSaveDat(m_saveBuffer);
    const int rotAmount = save->m_rotateKey % 0x20;
    u32* ptr = GetSaveEncodedWords(save);

    const int wordCount = (kMemoryCardSaveBufferSize - offsetof(Mc::SaveDat, m_random)) / sizeof(u32);
    for (int count = 0; count < wordCount; count++)
    {
        u32 rotated = __rlwnm(*ptr, rotAmount, 0, 31);
        *ptr++ = LoadSwapped(&rotated);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800C1F20
 * PAL Size: 208b
 * EN Address: 0x800DC184
 * EN Size: 148b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::DecodeData()
{
    Mc::SaveDat* const save = GetSaveDat(m_saveBuffer);
    u32* ptr = GetSaveEncodedWords(save);
    const int rotAmount = 0x20 - (save->m_rotateKey % 0x20);

    const int wordCount = (kMemoryCardSaveBufferSize - offsetof(Mc::SaveDat, m_random)) / sizeof(u32);
    for (int count = 0; count < wordCount; count++)
    {
        u32 word = *ptr;
        *ptr++ = __rlwnm(LoadSwapped(&word), rotAmount, 0, 31);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800C18FC
 * PAL Size: 1572b
 * EN Address: 0x800DC218
 * EN Size: 1464b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::Odekake(int mode, Mc::SaveDat& srcSave, int srcChar, Mc::SaveDat& dstSave, int dstChar)
{
    if (static_cast<unsigned int>(System.m_execParam) >= 3)
    {
        System.Printf("CMemoryCardMan.Odekake: \203L\203\203\203\211\203o\203\223%d\202\251\202\347\203L\203\203\203\211\203o\203\223%d\202\311%s\202\265\202\334\202\267\201B\012", srcChar, dstChar, mode != 0 ? "\202\250\217o\202\251\202\257" : sMcOdekakeReturn);
    }

    Mc::CharaDat& srcCharacter = srcSave.m_characters[srcChar];
    Mc::CharaDat& dstCharacter = dstSave.m_characters[dstChar];
    u8* srcCharData = reinterpret_cast<u8*>(&srcCharacter);
    u8* dstCharData = reinterpret_cast<u8*>(&dstCharacter);

    if (mode != 0)
    {
        memset(&dstCharacter, 0, sizeof(dstCharacter));

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
        dstCharacter.m_tribeId = srcCharacter.m_tribeId;
        dstCharacter.m_genderFlag = srcCharacter.m_genderFlag;
        dstCharacter.m_appearanceVariant = srcCharacter.m_appearanceVariant;
        memcpy(dstCharData + 0x34, srcCharData + 0x34, 8);
        memcpy(dstCharData + 0xBC, srcCharData + 0xBC, 0x0C);
        *reinterpret_cast<u32*>(dstCharData + 0xE8) = *reinterpret_cast<u32*>(srcCharData + 0xE8);
        memcpy(dstCharData + 0xF0, srcCharData + 0xF0, 0x10);
        dstCharacter.m_exists = srcCharacter.m_exists;
        memcpy(dstCharData + 0x5B8, srcCharData + 0x5B8, 0x100);
        memcpy(dstCharData + 0x6B8, srcCharData + 0x6B8, 0x200);
        *reinterpret_cast<u32*>(dstCharData + 0x8B8) = *reinterpret_cast<u32*>(srcCharData + 0x8B8);
        *reinterpret_cast<u32*>(dstCharData + 0x8BC) = *reinterpret_cast<u32*>(srcCharData + 0x8BC);
        dstCharacter.m_hasCharacterId = srcCharacter.m_hasCharacterId;
        dstCharacter.m_characterId = srcCharacter.m_characterId;
        dstCharacter.m_originSerial = srcSave.m_mcSerial;
        dstCharacter.m_originRandom = srcSave.m_mcRandom;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                dstSave.m_linkTable[dstChar][i][dstChar][j] = (i == 0 && j == 0) ? 0x32 : 0;
            }
        }

        memset(dstCharData + 0xC8, 0xFF, 0x10);
        memset(dstCharData + 0xD8, 0, 0x10);
        *reinterpret_cast<u16*>(dstCharData + 0x28) = 0;
        memset(dstCharData + 0x3C, 0xFF, 0x80);

        int artifact = static_cast<int>(*reinterpret_cast<s16*>(dstCharData + 0x34));
        if (artifact >= 0 && artifact < 0x40)
        {
            artifact = artifact * 2 + 0x3C;
            *reinterpret_cast<u16*>(dstCharData + artifact) = *reinterpret_cast<s16*>(srcCharData + artifact);
            *reinterpret_cast<u16*>(dstCharData + 0x28) = *reinterpret_cast<u16*>(dstCharData + 0x28) + 1;
        }

        artifact = static_cast<int>(*reinterpret_cast<s16*>(dstCharData + 0x36));
        if (artifact >= 0 && artifact < 0x40)
        {
            artifact = artifact * 2 + 0x3C;
            *reinterpret_cast<u16*>(dstCharData + artifact) = *reinterpret_cast<s16*>(srcCharData + artifact);
            *reinterpret_cast<u16*>(dstCharData + 0x28) = *reinterpret_cast<u16*>(dstCharData + 0x28) + 1;
        }

        artifact = static_cast<int>(*reinterpret_cast<s16*>(dstCharData + 0x38));
        if (artifact >= 0 && artifact < 0x40)
        {
            artifact = artifact * 2 + 0x3C;
            *reinterpret_cast<u16*>(dstCharData + artifact) = *reinterpret_cast<s16*>(srcCharData + artifact);
            *reinterpret_cast<u16*>(dstCharData + 0x28) = *reinterpret_cast<u16*>(dstCharData + 0x28) + 1;
        }

        artifact = static_cast<int>(*reinterpret_cast<s16*>(dstCharData + 0x3A));
        if (artifact >= 0 && artifact < 0x40)
        {
            artifact = artifact * 2 + 0x3C;
            *reinterpret_cast<u16*>(dstCharData + artifact) = *reinterpret_cast<s16*>(srcCharData + artifact);
            *reinterpret_cast<u16*>(dstCharData + 0x28) = *reinterpret_cast<u16*>(dstCharData + 0x28) + 1;
        }

        srcCharacter.m_isAway = 1;
        dstCharacter.m_isGuest = 1;
        *reinterpret_cast<u16*>(dstCharData + 0x6C2) = 3;
    }
    else
    {
        memcpy(dstCharData + 0xBC, srcCharData + 0xBC, 0x0C);

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                srcSave.m_linkTable[srcChar][i][srcChar][j] = 0;
            }
        }

        dstCharacter.m_isAway = 0;
        srcCharacter.m_hasCharacterId = 0;
        memset(&srcCharacter, 0, sizeof(srcCharacter));
        *reinterpret_cast<u16*>(dstCharData + 0x6C2) = 0x0C;
    }

    srcSave.m_random = Math.Rand(0x7FFFFFFF);
    srcSave.m_crc = CalcCrc(&srcSave);

    dstSave.m_random = Math.Rand(0x7FFFFFFF);
    dstSave.m_crc = CalcCrc(&dstSave);
}

/*
 * --INFO--
 * PAL Address: 0x800C17B8
 * PAL Size: 324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemoryCardMan::CalcSaveDatHpMax(Mc::SaveDat* saveDat)
{
    u8* save = reinterpret_cast<u8*>(saveDat);
    int charSlot = 0;

    do
    {
        u8* charData = save + 0x14D0;
        if (*reinterpret_cast<int*>(charData + 0x5B4) != 0)
        {
            short equippedItems[4];

            for (int itemSlot = 0; itemSlot < 0x49; itemSlot++)
            {
                if (itemSlot >= 0x45)
                {
                    const int word = itemSlot >> 5;
                    const int bit = itemSlot % 32;
                    if ((*reinterpret_cast<u32*>(charData + 0xBC + word * 4) & (1 << bit)) != 0)
                    {
                        int equippedSlot = itemSlot - 0x45;
                        equippedItems[equippedSlot] = static_cast<short>(itemSlot + 0x9F);
                    }
                    else
                    {
                        int equippedSlot = itemSlot - 0x45;
                        equippedItems[equippedSlot] = -1;
                    }
                }

            }

            int itemData = Game.unkCFlatData0[2];
            int totalHpBonus = 0;

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

            int finalHpMax = 0x10;
            if (totalHpBonus + 8 < 0x10)
            {
                finalHpMax = totalHpBonus + 8;
            }

            *reinterpret_cast<short*>(charData + 0x06) = finalHpMax;
        }

        charSlot++;
        save += 0x9C0;
    }
    while (charSlot < 8);
}
