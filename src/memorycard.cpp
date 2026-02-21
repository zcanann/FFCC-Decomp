#include "ffcc/memorycard.h"
#include "ffcc/file.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"

#include "dolphin/card.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"
#include "string.h"

extern unsigned char Game[];
extern CMath Math;
CMemoryCardMan MemoryCardMan;

// CRC32 lookup table
static const unsigned int crcTable[256] = {
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
    0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
    0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
    0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
    0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
    0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
    0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
    0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
    0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
    0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
    0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
    0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
    0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
    0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
    0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
    0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
    0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
    0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
    0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
    0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
    0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
    0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
    0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
    0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
    0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
    0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
    0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
    0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
    0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
    0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
    0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
    0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
    0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
    0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
    0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
    0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
    0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
    0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
    0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

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
    m_stage = reinterpret_cast<CStage*>(Memory.CreateStage(0x16000, (char*)"CMemoryCardMan", 0));
    m_mountWorkArea = new (reinterpret_cast<CMemory::CStage*>(m_stage), (char*)"memorycard.cpp", 0x88) char[0xA000];

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
                System.Printf("%s", (char*)nullptr /* DAT_801db044 */);

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
        System.Printf("%s", (char*)nullptr /* DAT_801db07c */);
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
	m_result = CARDOpen(chan, (const char*)nullptr /* PTR_DAT_8032e854 */, &m_fileInfo);
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
        (const char*)nullptr, // PTR_DAT_8032e854, // file name string
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
        m_saveBuffer = (char*)nullptr; // (char*)__nwa__(0xA000, mStage, s_memorycard_cpp_801daea8, 0x2AB);

        if (m_saveBuffer == 0 && System.m_execParam != 0)
        {
            System.Printf("%s(%d): Error: memory allocation", "memorycard.cpp", 0x2AD);
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
        m_saveBuffer = (char*)nullptr; // (char*)__nwa__(0xA000, mStage, s_memorycard_cpp_801daea8, 0x2AB);

        if (m_saveBuffer == (char*)nullptr && System.m_execParam != 0)
        {
            System.Printf("%s(%d): Error: memory allocation", "" /* s_memorycard_cpp_801daea8 */, 0x2AD);
        }

        memset(m_saveBuffer, 0, 0xA000);
    }
	
    char path[136];

    const char* lang = (const char*) nullptr; // Game.game.GetLangString();
    sprintf(path, "dvd/%smenu/%s", lang, "" /*PTR_s_icon_dat_8032e850*/);
    CFile::CHandle* h = File.Open(path, 0, CFile::PRI_LOW);

    if (h == nullptr && System.m_execParam != 0)
    {
        System.Printf("%s(%d): Error: %s open error", "" /* s_memorycard_cpp_801daea8 */, 0x2EF, path);
    }

    File.Read(h);
    File.SyncCompleted(h);

    int len = File.GetLength(h);

    if (len != 0x2A00 && System.m_execParam != 0)
    {
        System.Printf("%s(%d): Error: [%s] data error", "" /* s_memorycard_cpp_801daea8 */, 0x2F6, path);
    }

    memcpy(m_saveBuffer + 0x40, File.m_readBuffer, len);

    File.Close(h);

    m_cardStat.commentAddr = 0;
    m_cardStat.iconAddr    = 0x40;

    m_cardStat.bannerFormat = (m_cardStat.bannerFormat & ~0x03) | 0x02; // lower 2 bits = 2
    m_cardStat.bannerFormat &= ~0x04;  // clear bit 2

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

    m_cardStat.offsetIconTlut = 0x2840;
    m_cardStat.offsetIconTlut = 0x2A40;

    size_t titleLen = strlen("" /* PTR_s_FF_Crystal_Chronicles_8032e858 */);
    memcpy(m_saveBuffer, "" /*PTR_s_FF_Crystal_Chronicles_8032e858*/, titleLen);
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
        "FFCC", // PTR_DAT_8032e854, // file name
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
    static const char s_magic0[] = "FFCC";
    static const char s_magic1[] = "GCCP";
    static const char s_magic2[] = "SAVE";
    static const char s_magic3[] = "DATA";

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
    u8* game = Game + 0x10;
    u8* gameWork = game + 0x08;

    const u64 now = OSGetTime();
    memcpy(save + 0x8AD0, &now, sizeof(now));

    memcpy(save + 0x00, s_magic0, strlen(s_magic0));
    memcpy(save + 0x04, s_magic1, strlen(s_magic1));
    memcpy(save + 0x08, s_magic2, strlen(s_magic2));
    memcpy(save + 0x0C, s_magic3, strlen(s_magic3));
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
    static const char s_magic0[] = "FFCC";
    static const char s_magic1[] = "GCCP";
    static const char s_magic2[] = "SAVE";
    static const char s_magic3[] = "DATA";

    if (m_saveBuffer == (char*)nullptr)
    {
        return;
    }

    u8* save = reinterpret_cast<u8*>(m_saveBuffer);
    u8* game = Game + 0x10;
    u8* gameWork = game + 0x08;

    if (save[0x00] != s_magic0[0] || save[0x01] != s_magic0[1] || save[0x02] != s_magic0[2] || save[0x03] != s_magic0[3])
    {
        return;
    }
    if (save[0x04] != s_magic1[0] || save[0x05] != s_magic1[1] || save[0x06] != s_magic1[2] || save[0x07] != s_magic1[3])
    {
        return;
    }
    if (save[0x08] != s_magic2[0] || save[0x09] != s_magic2[1] || save[0x0A] != s_magic2[2] || save[0x0B] != s_magic2[3])
    {
        return;
    }
    if (save[0x0C] != s_magic3[0] || save[0x0D] != s_magic3[1] || save[0x0E] != s_magic3[2] || save[0x0F] != s_magic3[3])
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
        *reinterpret_cast<int*>(cv + 0xC28) = *reinterpret_cast<int*>(src + 0x1D98);
        *reinterpret_cast<int*>(cv + 0xC2C) = *reinterpret_cast<int*>(src + 0x1D9C);
        *reinterpret_cast<int*>(cv + 0x10) = *reinterpret_cast<int*>(src + 0x1DA4);

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
    unsigned char byte;
    int i;
    unsigned char* ptr;
    unsigned int crc;
    unsigned char* data = (unsigned char*)saveData;

    if (data == nullptr)
    {
        data = (unsigned char*)m_saveBuffer;
    }

    crc = 0xFFFFFFFF;
    i = 0x1C;
    ptr = data;
    while (true)
    {
        i--;
        if (i < 0)
        {
            break;
        }

        byte = *ptr;
        ptr++;
        crc = (crc << 8) ^ crcTable[(crc >> 24) ^ byte];
    }

    ptr = data + 0x20;
    i = 0x8BB0;
    while (true)
    {
        i--;
        if (i < 0)
        {
            break;
        }

        byte = *ptr;
        ptr++;
        crc = (crc << 8) ^ crcTable[(crc >> 24) ^ byte];
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
    int i;
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
    i = 0x1C;
    while (i = i - 1, -1 < i)
    {
        byte = *ptr;
        ptr++;
        crc = (crc << 8) ^ crcTable[(crc >> 24) ^ byte];
    }

    ptr += 0x20 - 0x1C;
    i = 0x8BB0;
    while (i = i - 1, -1 < i)
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
                System.Printf("%s", /* s_McFormat(%d)_error(%d)_801daef8 */ 0);
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
            System.Printf("%s", /* s_McMount(%d)_error(%d)_801dae78 */ 0);
        }

        result = CARDUnmount(0);
        m_result = result;
        m_opDoneFlag = 1;
        m_state = 2;
        m_currentSlot = 0xFF;

        return m_result;
    }

    result = CARDOpen(0, /* PTR_DAT_8032e854 */ (const char*)0, &m_fileInfo);
    m_result = result;
    m_opDoneFlag = 1;
    m_state = 3;

    if (m_result == -4)
    {
        m_opDoneFlag = 0;
        m_state = 5;

        result = CARDCreateAsync(
            0,
            /* PTR_DAT_8032e854 */ (const char*)0,
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
                System.Printf("%s", /* s_McCreate(%d)_error(%d)_801daf10 */ 0);
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
                System.Printf("%s", /* s_McGetStat(%d)_error(%d)_801daf28 */ 0);
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
                System.Printf("%s", /* s_%s(%d):_Error:_memory_allocation_801daeb8 */ 0);
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
                System.Printf("%s", /* s_McWrite(%d)_error(%d)_801daf44 */ 0);
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
                System.Printf("%s", /* s_McSetStat(%d)_error(%d)_801daf5c */ 0);
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
                System.Printf("%s", /* s_%s(%d):_Error:_memory_allocation_801daeb8 */ 0);
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
        System.Printf("%s", /* s_McWrite(%d)_error(%d)_801daf44 */ 0);
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
            System.Printf("%s", /* s_McMount(%d)_error(%d)_801dae78 */ 0);
        }

        result = CARDUnmount(0);
        m_result = result;
        m_opDoneFlag = 1;
        m_state = 2;
        m_currentSlot = 0xFF;

        return m_result;
    }

    result = CARDOpen(0, /* PTR_DAT_8032e854 */ (const char*)0, &m_fileInfo);
    m_result = result;
    m_opDoneFlag = 1;
    m_state = 3;

    if (m_result != 0)
    {
        // Open failed
        if (System.m_execParam != 0)
        {
            // "McOpen(%d) error(%d)"
            System.Printf("%s", /* s_McOpen(%d)_error(%d)_801dae90 */ 0);
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
            System.Printf("%s", /* s_%s(%d):_Error:_memory_allocation_801daeb8 */ 0);
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
        System.Printf("%s", /* s_McRead(%d)_error(%d)_801daee0 */ 0);
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
    const u32 rotAmount = m_saveBuffer[0x11] & 0x1F;
    u32* ptr = reinterpret_cast<u32*>(m_saveBuffer + 0x18);
    int count = 0x5B6;

    do
    {
        ptr[0] = (ptr[0] << rotAmount) | (ptr[0] >> (0x20 - rotAmount));
        ptr[1] = (ptr[1] << rotAmount) | (ptr[1] >> (0x20 - rotAmount));
        ptr[2] = (ptr[2] << rotAmount) | (ptr[2] >> (0x20 - rotAmount));
        ptr[3] = (ptr[3] << rotAmount) | (ptr[3] >> (0x20 - rotAmount));
        ptr[4] = (ptr[4] << rotAmount) | (ptr[4] >> (0x20 - rotAmount));
        ptr[5] = (ptr[5] << rotAmount) | (ptr[5] >> (0x20 - rotAmount));
        ptr[6] = (ptr[6] << rotAmount) | (ptr[6] >> (0x20 - rotAmount));
        ptr += 7;
        count--;
    }
    while (count != 0);
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
    const u32 rotAmount = 0x20 - (m_saveBuffer[0x11] & 0x1F);
    u32* ptr = reinterpret_cast<u32*>(m_saveBuffer + 0x18);
    int count = 0x5B6;

    do
    {
        ptr[0] = (ptr[0] << (rotAmount & 0x1F)) | (ptr[0] >> (0x20 - (rotAmount & 0x1F)));
        ptr[1] = (ptr[1] << (rotAmount & 0x1F)) | (ptr[1] >> (0x20 - (rotAmount & 0x1F)));
        ptr[2] = (ptr[2] << (rotAmount & 0x1F)) | (ptr[2] >> (0x20 - (rotAmount & 0x1F)));
        ptr[3] = (ptr[3] << (rotAmount & 0x1F)) | (ptr[3] >> (0x20 - (rotAmount & 0x1F)));
        ptr[4] = (ptr[4] << (rotAmount & 0x1F)) | (ptr[4] >> (0x20 - (rotAmount & 0x1F)));
        ptr[5] = (ptr[5] << (rotAmount & 0x1F)) | (ptr[5] >> (0x20 - (rotAmount & 0x1F)));
        ptr[6] = (ptr[6] << (rotAmount & 0x1F)) | (ptr[6] >> (0x20 - (rotAmount & 0x1F)));
        ptr += 7;
        count--;
    }
    while (count != 0);
}

void CMemoryCardMan::CalcSaveDatHpMax(Mc::SaveDat* saveDat)
{
    int charSlot = 0;
    
    do {
        char* charData = (char*)saveDat + charSlot * 0x9c0;
        
        // Check if character slot is active
        if (*(int*)(charData + 0x1a84) != 0)
        {
            short equippedItems[4];
            int itemSlot = 0x45;
            int accessoryCount = 0x49;
            
            // Process equipped accessory slots (items 0x45-0x48)
            do {
                if (itemSlot > 0x44) {
                    int bitShift = itemSlot >> 0x1f;
                    unsigned int bitMask = 1 << ((bitShift * 0x20 | (unsigned int)(itemSlot * 0x8000000 + bitShift) >> 0x1b) - bitShift);
                    
                    if ((*(unsigned int*)(charData + (itemSlot >> 5) * 4 + 0x158c) & bitMask) == 0) {
                        equippedItems[itemSlot - 0x45] = -1;
                    } else {
                        equippedItems[itemSlot - 0x45] = itemSlot + 0x9f;
                    }
                }
                itemSlot++;
                accessoryCount--;
            } while (accessoryCount != 0);
            
            // Calculate total HP bonus from equipped accessories
            unsigned int totalHpBonus = 0;
            unsigned int itemData = *(unsigned int*)(Game + 0xC5B8);
            
            if (equippedItems[0] >= 0) {
                totalHpBonus = (unsigned int)*(unsigned short*)(itemData + equippedItems[0] * 0x48 + 6);
            }
            if (equippedItems[1] >= 0) {
                totalHpBonus += *(unsigned short*)(itemData + equippedItems[1] * 0x48 + 6);
            }
            if (equippedItems[2] >= 0) {
                totalHpBonus += *(unsigned short*)(itemData + equippedItems[2] * 0x48 + 6);
            }
            if (equippedItems[3] >= 0) {
                totalHpBonus += *(unsigned short*)(itemData + equippedItems[3] * 0x48 + 6);
            }
            
            // Calculate final HP max (base 8 + bonuses, capped at 16)
            unsigned short finalHpMax = 16;
            if (totalHpBonus + 8 < 16) {
                finalHpMax = totalHpBonus + 8;
            }
            
            // Store calculated HP max in save data
            *(unsigned short*)(charData + 0x14d6) = finalHpMax;
        }
        charSlot++;
    } while (charSlot < 8);
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
    MemoryCardMan.m_opDoneFlag = 1;

    if (MemoryCardMan.m_state == 1)
    {
        if (result == 0)
        {
            MemoryCardMan.m_currentSlot = currentSlot;
        }
    }
}
