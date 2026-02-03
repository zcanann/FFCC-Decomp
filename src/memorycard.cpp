#include "ffcc/memorycard.h"
#include "ffcc/file.h"
#include "ffcc/system.h"

#include "dolphin/card.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"
#include "string.h"

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
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::Init()
{
    CARDInit();

    m_result = 0;
    m_opDoneFlag = 0;
    m_currentSlot = -1;
    m_state = 0;
    m_saveBuffer = (char*)nullptr;

    // m_stage = Memory.CreateStage(0x16000, s_CMemoryCardMan_801dae0c, 0);
    // m_mountWorkArea = __nwa__(0xA000,  mStage, s_memorycard_cpp_801daea8, 0x88);

    m_currentSlot = -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::Quit()
{ 
  m_currentSlot = -1;
  
  if (m_mountWorkArea != (void*)nullptr)
  {
    delete[] m_mountWorkArea;
    m_mountWorkArea = (void*)nullptr;
  }
  
  // DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,mStage);
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
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::MakeSaveData()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::SetLoadData()
{
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
    unsigned char* data = (unsigned char*)saveData;
    if (data == nullptr) {
        data = (unsigned char*)m_saveBuffer;
    }
    
    unsigned int crc = 0xFFFFFFFF;
    
    // Process first 0x1c (28) bytes
    for (int i = 0; i < 0x1c; i++) {
        unsigned char byte = data[i];
        crc = (crc << 8) ^ crcTable[(crc >> 24) ^ byte];
    }
    
    // Skip 4 bytes (CRC location at 0x1c), continue from 0x20
    data += 0x20;
    
    // Process remaining 0x8bb0 (35760) bytes
    for (int i = 0; i < 0x8bb0; i++) {
        unsigned char byte = data[i];
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
    unsigned char* data = (unsigned char*)saveData;
    if (data == nullptr) {
        data = (unsigned char*)m_saveBuffer;
    }
    if (data == nullptr) {
        data = (unsigned char*)m_saveBuffer;
    }
    
    unsigned int crc = 0xFFFFFFFF;
    
    // Process first 0x1c (28) bytes
    for (int i = 0; i < 0x1c; i++) {
        unsigned char byte = data[i];
        crc = (crc << 8) ^ crcTable[(crc >> 24) ^ byte];
    }
    
    // Skip 4 bytes (CRC location at 0x1c), continue from 0x20
    unsigned char* dataPtr = data + 0x20;
    
    // Process remaining 0x8bb0 (35760) bytes
    for (int i = 0; i < 0x8bb0; i++) {
        unsigned char byte = dataPtr[i];
        crc = (crc << 8) ^ crcTable[(crc >> 24) ^ byte];
    }
    
    // Get stored CRC from offset 0x1c
    unsigned int storedCrc = *(unsigned int*)(data + 0x1c);
    
    // Compare calculated CRC with stored CRC
    // Return 1 if they match, 0 if they don't
    return (~crc == storedCrc) ? 1 : 0;
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
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::EncodeData()
{
    const u8  key = m_saveBuffer[0x11];
    const u32 rotAmount = key & 0x1F;

    u32* ptr = reinterpret_cast<u32*>(m_saveBuffer + 0x18);

    for (int i = 0; i < 0x5B6; i++)
    {
        for (int w = 0; w < 7; w++)
        {
            u32 v = ptr[w];
            v = (v << rotAmount) | (v >> (32 - rotAmount));
            ptr[w] = v;
        }

        ptr += 7;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::DecodeData()
{
    u32 shift = (m_saveBuffer[0x11] & 0x1F);
    u32 rshift = (32 - shift) & 31; 
    u32* ptr = reinterpret_cast<u32*>(m_saveBuffer + 0x18);

    for (int i = 0; i < 0x5B6; i++)
    {
        for (int w = 0; w < 7; w++)
        {
            u32 v = ptr[w];
            v = (v >> shift) | (v << rshift);
            ptr[w] = v;
        }

        ptr += 7;
    }
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
            
            if (equippedItems[0] >= 0) {
                // TODO: Access Game.game.unkCFlatData0[2] + itemID * 0x48 + 6
                totalHpBonus += 0; // Placeholder
            }
            if (equippedItems[1] >= 0) {
                totalHpBonus += 0; // Placeholder
            }
            if (equippedItems[2] >= 0) {
                totalHpBonus += 0; // Placeholder
            }
            if (equippedItems[3] >= 0) {
                totalHpBonus += 0; // Placeholder
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
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::Odekake(int, Mc::SaveDat&, int, Mc::SaveDat&, int)
{
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
