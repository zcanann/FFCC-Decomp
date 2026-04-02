#include "ffcc/file.h"

#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/goout.h"
#include "ffcc/graphic.h"
#include "ffcc/render_buffers.h"
#include "ffcc/memory.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/util.h"

#include "PowerPC_EABI_Support/Runtime/MWCPlusLib.h"
#include <dolphin/gx.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/vi.h>

#include <string.h>

extern "C" void __dla__FPv(void*);
extern "C" void* CreateStage__7CMemoryFUlPci(void*, unsigned long, char*, int);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern char s_openWarnFmt[];

CFile File;

static char s_fileCpp[] = "file.cpp";
static char s_cFile[] = "CFile";
static char s_drawErrorFmt[] = "CFile::drawError %d";
static char s_queueWarnAnyFmt[] = "BackAllFilesToQueue: %s";
static char s_queueWarnTargetFmt[] = "BackAllFilesToQueue: %s (%s)";
static char s_closeWarnFmt[] = "Close: %s";
static char s_readWarnFmt[] = "Read: %s (%u)";

static const char* s_diskErrorText[4][6][3] = {
    {
        {"Disk read error.", "Please check the Game Disc.", ""},
        {"Erreur de lecture du disque.", "Veuillez verifier le disque.", ""},
        {"Lesefehler auf der Disk.", "Bitte uberprufen Sie die Disk.", ""},
        {"Errore di lettura disco.", "Controllare il disco di gioco.", ""},
        {"Error de lectura del disco.", "Comprueba el disco de juego.", ""},
        {"Disc read error.", "Please check the Game Disc.", ""},
    },
    {
        {"Wrong Game Disc.", "Please insert the correct disc.", ""},
        {"Mauvais disque.", "Inserez le disque correct.", ""},
        {"Falsche Disk.", "Bitte richtige Disk einlegen.", ""},
        {"Disco errato.", "Inserire il disco corretto.", ""},
        {"Disco incorrecto.", "Inserta el disco correcto.", ""},
        {"Wrong game disc.", "Please insert the correct disc.", ""},
    },
    {
        {"Disc cover is open.", "Please close the disc cover.", ""},
        {"Capot du disque ouvert.", "Fermez le capot du disque.", ""},
        {"Disc-Abdeckung ist offen.", "Bitte Abdeckung schliessen.", ""},
        {"Sportello disco aperto.", "Chiudere lo sportello disco.", ""},
        {"Tapa del disco abierta.", "Cierra la tapa del disco.", ""},
        {"Disc cover open.", "Please close the disc cover.", ""},
    },
    {
        {"A fatal error has occurred.", "Turn off the power and refer", "to the Nintendo GameCube manual."},
        {"Une erreur fatale est survenue.", "Eteignez la console et consultez", "le manuel Nintendo GameCube."},
        {"Ein schwerer Fehler ist aufgetreten.", "Konsole ausschalten und im", "Nintendo GameCube-Handbuch nachsehen."},
        {"Si e verificato un errore grave.", "Spegnere e consultare il", "manuale Nintendo GameCube."},
        {"Se ha producido un error grave.", "Apaga la consola y consulta", "el manual de Nintendo GameCube."},
        {"A fatal error has occurred.", "Turn off the power and refer", "to the Nintendo GameCube manual."},
    },
};

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::CHandle::Reset()
{
	m_completionStatus = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80013bb8
 * PAL Size: 408b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */

void CFile::Init()
{
    DVDInit();
    m_allocStage = CreateStage__7CMemoryFUlPci(&Memory, 0x10ac00, s_cFile, 0);
    m_fatalDiskErrorFlag = 0;
    m_isDiskError = 0;
    m_readBuffer = __nwa__FUlPQ27CMemory6CStagePci(0x100000, (CMemory::CStage*)m_allocStage, s_fileCpp, 0x2b);
    m_handlePoolHead.m_currentOffset = (u32)__construct_new_array(
        __nwa__FUlPQ27CMemory6CStagePci(sizeof(CHandle) * 0x80 + 0x10, (CMemory::CStage*)m_allocStage, s_fileCpp, 0x2e),
        0, 0, sizeof(CHandle), 0x80);
    m_fileHandle.m_next = &m_fileHandle;
    m_fileHandle.m_previous = &m_fileHandle;
    m_fileHandle.m_priority = PRI_SENTINEL;
    m_freeList = (CHandle*)m_handlePoolHead.m_currentOffset;

    unsigned int handleIndex = 0;
    int byteOffset = 0;
    for (int blockCount = 0x20; blockCount != 0; blockCount--) {
        CHandle* nextHandle;

        if (handleIndex == 0x7F) {
            nextHandle = (CHandle*)&m_freeListSentinelDummy;
        } else {
            nextHandle = (CHandle*)(m_handlePoolHead.m_currentOffset + (handleIndex + 1) * sizeof(CHandle));
        }
        *(CHandle**)(m_handlePoolHead.m_currentOffset + byteOffset + 0x4) = nextHandle;
        handleIndex++;

        if (handleIndex == 0x7F) {
            nextHandle = (CHandle*)&m_freeListSentinelDummy;
        } else {
            nextHandle = (CHandle*)(m_handlePoolHead.m_currentOffset + (handleIndex + 1) * sizeof(CHandle));
        }
        *(CHandle**)(m_handlePoolHead.m_currentOffset + byteOffset + 0xB0) = nextHandle;
        handleIndex++;

        if (handleIndex == 0x7F) {
            nextHandle = (CHandle*)&m_freeListSentinelDummy;
        } else {
            nextHandle = (CHandle*)(m_handlePoolHead.m_currentOffset + (handleIndex + 1) * sizeof(CHandle));
        }
        *(CHandle**)(m_handlePoolHead.m_currentOffset + byteOffset + 0x15C) = nextHandle;
        handleIndex++;

        if (handleIndex == 0x7F) {
            nextHandle = (CHandle*)&m_freeListSentinelDummy;
        } else {
            nextHandle = (CHandle*)(m_handlePoolHead.m_currentOffset + (handleIndex + 1) * sizeof(CHandle));
        }
        *(CHandle**)(m_handlePoolHead.m_currentOffset + byteOffset + 0x208) = nextHandle;
        handleIndex++;

        byteOffset += 0x2B0;
        handleIndex++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80013b48
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFile::Quit()
{
    if (m_readBuffer != 0) {
        delete[] m_readBuffer;
        m_readBuffer = 0;
    }

    u32 nextOffset = m_handlePoolHead.m_currentOffset;
    if (nextOffset != 0) {
        if (nextOffset != 0) {
            __dla__FPv((void*)(nextOffset - 0x10));
        }
        m_handlePoolHead.m_currentOffset = 0;
    }

    Memory.DestroyStage((CMemory::CStage*)m_allocStage);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::Frame()
{
	kick();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
DVDDiskID* CFile::GetCurrentDiskID()
{
	return DVDGetCurrentDiskID();
}

/*
 * --INFO--
 * PAL Address: 0x80013968
 * PAL Size: 416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */

CFile::CHandle* CFile::Open(char* path, unsigned long userParam, CFile::PRI pri)
{
    if (Game.m_gameWork.m_gamePaused != 0)
    {
        pri = CFile::PRI_CRITICAL;
    }

    CHandle* end = m_fileHandle.m_previous;
    CHandle* it = end;
    CHandle* handle = 0;
    DVDFileInfo fi;

    while (it != end) {
        if (pri < it->m_priority) {
            break;
        }
        it = it->m_previous;
    }

    it = it->m_next;

    s32 entry = DVDConvertPathToEntrynum(path);

    if (entry != -1)
	{
        u32 length;

        DVDFastOpen(entry, &fi);
        length = fi.length;
        handle = m_freeList;
        m_freeList = handle->m_previous;
        handle->m_previous = it;
        handle->m_next = it->m_next;
        it->m_next->m_previous = handle;
        it->m_next = handle;
        handle->m_priority = pri;
        handle->m_userParam = userParam;
        handle->m_length = length;
        handle->m_completionStatus = 0;
        handle->m_closedFlag = 0;
        handle->m_flags = 0;
        strcpy(handle->m_name, path);
        handle->m_chunkSize = length;
        handle->m_currentOffset = 0;
        handle->m_nextOffset = 0;
        fi.cb.userData = handle;
        handle->m_dvdFileInfo = fi;
	}

    if (handle == 0 && (unsigned int)System.m_execParam >= 1)
	{
        System.Printf(s_openWarnFmt, path);
    }

    return handle;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CFile::GetLength(CFile::CHandle* fileHandle)
{
	return fileHandle->m_length;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma dont_inline on
void CFile::BackAllFilesToQueue(CHandle* fileHandle)
{
    CHandle* inFlight;

    while (1)
    {
        inFlight = CheckQueue();
        if (inFlight == 0)
        {
            break;
        }

        SyncCompleted(inFlight);

        if (fileHandle != 0 && inFlight == fileHandle)
        {
            inFlight->m_completionStatus = 0;
            continue;
        }

        if (fileHandle != 0)
        {
            if ((unsigned int)System.m_execParam >= 2)
            {
                System.Printf(s_queueWarnTargetFmt, inFlight->m_name, fileHandle->m_name);
            }
        }
        else if ((unsigned int)System.m_execParam >= 3)
        {
            System.Printf(s_queueWarnAnyFmt, inFlight->m_name);
        }

        inFlight->m_completionStatus = 1;
    }
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x800137b0
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFile::Read(CFile::CHandle* fileHandle)
{
	BackAllFilesToQueue(fileHandle);
	fileHandle->m_completionStatus = 2;
	u32 readSize = (fileHandle->m_chunkSize + 0x1FU) & ~0x1FU;
	if (readSize > 0x100000U && (unsigned int)System.m_execParam >= 1)
	{
		System.Printf(s_readWarnFmt, fileHandle->m_name, readSize);
	}
	DVDReadAsyncPrio(&fileHandle->m_dvdFileInfo, m_readBuffer, readSize, fileHandle->m_currentOffset, 0, 2);
	fileHandle->m_nextOffset = fileHandle->m_currentOffset + readSize;
	SyncCompleted(fileHandle);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::LockBuffer()
{
	CFile::CHandle* fileHandle;

	while(true)
	{
		fileHandle = CheckQueue();

		if (fileHandle == 0)
		{
			break;
		}

		SyncCompleted(fileHandle);

		fileHandle->m_completionStatus = 1;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::UnlockBuffer()
{
	kick();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::ReadASync(CFile::CHandle* fileHandle)
{
	fileHandle->m_completionStatus = 1;
	kick();
}

/*
 * --INFO--
 * PAL Address: 0x8001366C
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFile::Close(CFile::CHandle* fileHandle)
{
	if ((fileHandle->m_completionStatus == 2) && (2 <= (unsigned int)System.m_execParam))
	{
		System.Printf(s_closeWarnFmt, fileHandle->m_name);
	}

	DVDClose(&fileHandle->m_dvdFileInfo);

	fileHandle->m_closedFlag = 1;
	fileHandle->m_next->m_previous = fileHandle->m_previous;
	fileHandle->m_previous->m_next = fileHandle->m_next;
	fileHandle->m_previous = m_freeList;
	m_freeList = fileHandle;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CFile::IsCompleted(CFile::CHandle* fileHandle)
{
	if (fileHandle->m_completionStatus == 3)
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
void CFile::SyncCompleted(CFile::CHandle* fileHandle)
{
	while (fileHandle->m_completionStatus != 3)
	{
		kick();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800134f4
 * PAL Size: 280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
void CFile::kick()
{
    CHandle* handle = CheckQueue();
    if (handle != 0)
    {
        return;
    }

    handle = m_fileHandle.m_previous;
    do
    {
        if ((Game.m_gameWork.m_gamePaused == 0 || handle->m_priority == PRI_CRITICAL)
            && (handle->m_completionStatus == 1 || handle->m_completionStatus == 4))
        {
            u32 readSize;

            handle->m_completionStatus = 2;
            readSize = (handle->m_chunkSize + 0x1F) & ~0x1F;

            if (readSize > 0x100000U && (unsigned int)System.m_execParam >= 1)
            {
                System.Printf(s_readWarnFmt, handle->m_name, readSize);
            }

            DVDReadAsyncPrio(&handle->m_dvdFileInfo, m_readBuffer, readSize, handle->m_currentOffset, 0, 2);
            handle->m_nextOffset = handle->m_currentOffset + readSize;
            if (handle->m_completionStatus != 3)
            {
                return;
            }

            kick();
            return;
        }

        handle = handle->m_previous;
    } while (handle != &m_fileHandle);
}
#pragma dont_inline reset

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFile::CHandle* CFile::CheckQueue()
{
    CHandle* sentinel = &m_fileHandle;
    CHandle* handle = sentinel->m_previous;

    while (handle != sentinel)
    {
        if (handle->m_completionStatus == 2)
        {
            int dvdStatus = DVDGetCommandBlockStatus(&handle->m_dvdFileInfo.cb);

            if (dvdStatus == 0x0B || ((u32)(dvdStatus - 4) <= 2U) || dvdStatus == -1)
            {
                DrawError(handle->m_dvdFileInfo, dvdStatus);
            }
            else if (dvdStatus == 0)
            {
                handle->m_completionStatus = 3;
                return CheckQueue();
            }
            else if (dvdStatus > 0)
            {
                return handle;
            }
            else
            {
                handle->m_completionStatus = 4;
            }
        }
        else if (handle->m_completionStatus == 3)
        {
            return handle;
        }

        handle = handle->m_previous;
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x80012bb8
 * PAL Size: 1696b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFile::DrawError(DVDFileInfo& info, int errorCode)
{
    _GXTexObj backupTexObj;
    m_isDiskError = 1;

    do
    {
        if (System.m_execParam != 0)
        {
            System.Printf(s_drawErrorFmt, errorCode);
        }

        CFont* font = MenuPcs.GetFont22();
        bool usingFallbackFont = (font == 0);
        if (usingFallbackFont)
        {
            font = *(CFont**)((char*)&FontMan + 8);
        }

        if (font == 0)
        {
            m_isDiskError = 0;
            return;
        }

        Graphic._WaitDrawDone(s_fileCpp, 0x2CC);

        bool compactLayout = (!usingFallbackFont && gRenderScratchTextureBuffer != 0);
        if (compactLayout)
        {
            Graphic.GetBackBufferRect2(gRenderScratchTextureBuffer, &backupTexObj, 0, 0, 0x280, 0x70, 0, GX_NEAR, GX_TF_RGBA8, 0);

            gUtil.RenderColorQuad(0.0f, 0.0f, 640.0f, 112.0f, CColor(0, 0, 0, 255).color);
            memcpy((void*)((char*)gRenderScratchTextureBuffer + 0x46000), (void*)((char*)gRenderEmbedFrameBuffer + 0x34800), 0x29400);
            DCFlushRange((void*)((char*)gRenderScratchTextureBuffer + 0x46000), 0x29400);
        }
        else
        {
            gUtil.RenderColorQuad(0.0f, 0.0f, 640.0f, 448.0f, CColor(0, 0, 0, 255).color);
        }

        font->SetScale(1.0f);
        font->SetShadow(1);
        font->SetMargin(0.0f);
        font->SetZMode(0, 0);
        font->SetColor(CColor(255, 255, 255, 255).color);
        font->SetTlut(usingFallbackFont ? -1 : 7);
        font->DrawInit();

        int msgIndex = 0;
        switch (errorCode)
        {
        case 4:
        case 6:
            msgIndex = 2;
            break;
        case 5:
            msgIndex = 1;
            break;
        case 0x0B:
            msgIndex = 0;
            break;
        case -1:
            msgIndex = 3;
            m_fatalDiskErrorFlag = 1;
            break;
        default:
            break;
        }

        unsigned int language = Game.m_gameWork.m_languageId;
        const char* const* lines = s_diskErrorText[msgIndex][language];
        unsigned int baseY = compactLayout ? 0x20 : 200;

        if (strlen(lines[2]) == 0)
        {
            font->SetPosX(64.0f);
            font->SetPosY((float)baseY);
            font->SetPosZ(0.0f);
            font->Draw((char*)lines[0]);
            font->SetPosX(64.0f);
            font->SetPosY((float)(baseY + 0x1C));
            font->SetPosZ(0.0f);
            font->Draw((char*)lines[1]);
        }
        else
        {
            font->SetPosX(64.0f);
            font->SetPosY((float)((int)baseY - 14));
            font->SetPosZ(0.0f);
            font->Draw((char*)lines[0]);
            font->SetPosX(64.0f);
            font->SetPosY((float)(baseY + 14));
            font->SetPosZ(0.0f);
            font->Draw((char*)lines[1]);
            font->SetPosX(64.0f);
            font->SetPosY((float)(baseY + 42));
            font->SetPosZ(0.0f);
            font->Draw((char*)lines[2]);
        }

        font->DrawQuit();

        if (compactLayout)
        {
            GXSetDispCopySrc(0, 0, 0x280, 0x70);
            GXSetDispCopyDst(0x280, 0x70);
            GXCopyDisp((void*)((char*)gRenderEmbedFrameBuffer + 0x34800), GX_FALSE);
        }
        else
        {
            GXSetDispCopySrc(0, 0, 0x280, 0x1C0);
            GXSetDispCopyDst(0x280, 0x1C0);
            GXCopyDisp(gRenderEmbedFrameBuffer, GX_FALSE);
        }

        Graphic._WaitDrawDone(s_fileCpp, 0x329);
        Graphic.SetStdDispCopySrc();
        Graphic.SetStdDispCopyDst();
        Graphic._WaitDrawDone(s_fileCpp, 0x32D);
        VIWaitForRetrace();
        Sound.PauseDiscError(1);
        VISetBlack(FALSE);
        VIFlush();

        while (DVDGetCommandBlockStatus(&info.cb) == errorCode)
        {
            VIWaitForRetrace();
        }

        if (compactLayout)
        {
            gUtil.RenderTextureQuad(0.0f, 0.0f, 640.0f, 112.0f, &backupTexObj, 0, 0, 0, GX_BL_SRCALPHA,
                                           GX_BL_INVSRCALPHA);
            memcpy((void*)((char*)gRenderEmbedFrameBuffer + 0x34800), (void*)((char*)gRenderScratchTextureBuffer + 0x46000), 0x29400);
            DCFlushRange((void*)((char*)gRenderEmbedFrameBuffer + 0x34800), 0x29400);
        }
        else
        {
            gUtil.RenderColorQuad(0.0f, 0.0f, 640.0f, 448.0f, CColor(0, 0, 0, 255).color);
            GXCopyDisp(gRenderEmbedFrameBuffer, GX_FALSE);
        }

        Graphic._WaitDrawDone(s_fileCpp, 0x35B);
        m_fatalDiskErrorFlag = 0;

        int status = DVDGetCommandBlockStatus(&info.cb);
        while (status == 1)
        {
            VIWaitForRetrace();
            status = DVDGetCommandBlockStatus(&info.cb);
        }
        errorCode = status;
    } while (errorCode == 0x0B || (errorCode >= 4 && errorCode <= 6) || errorCode == -1);

    Sound.PauseDiscError(0);
    m_isDiskError = 0;
}
