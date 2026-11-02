#include "ffcc/file.h"

#ifdef VERSION_GCCJGC
#include "ffcc/joybusconst.h"
#include "ffcc/cardconst.h"
#endif

#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"
#include "ffcc/graphic.h"
#include "ffcc/memory.h"
#include "ffcc/p_menu.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/util.h"

#include <PowerPC_EABI_Support/Runtime/New.h>
#include <dolphin/gx.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/vi.h>

#include <string.h>

#ifndef VERSION_GCCJGC
static const char* l_tError[4][6][3] = {
    {
        {"\203f\203B\203X\203N\202\360\223\307\202\337\202\334\202\271\202\361\202\305\202\265\202\275\201B", "\202\255\202\355\202\265\202\255\202\315\201A\226{\221\314\202\314\216\346\210\265\220\340\226\276\217\221\202\360\202\250\223\307\202\335\202\255\202\276\202\263\202\242\201B", ""},
        {"The Game Disc could not be read.", "Please read the Nintendo GameCube Instruction", "Booklet for more information."},
        {"Diese Game Disc kann nicht gelesen werden.", "Bitte lesen Sie die Bedienungsanleitung des", "Nintendo GameCube, um weitere Informationen zu erhalten."},
        {"Impossibile leggere il disco di gioco.", "Consulta il manuale di istruzioni del Nintendo GameCube",
#ifdef VERSION_GCCE01
         " per ulteriori indicazioni."},
#else
         "per ulteriori indicazioni."},
#endif
        {"La lecture du disque a \351chou\351.", "Veuillez vous r\351f\351rer au manuel d'instructions", "Nintendo GameCube pour de plus amples informations."},
        {"No se puede leer el disco.", "Consulta el manual de instrucciones de", "Nintendo GameCube para obtener m\341s informaci\363n."},
    },
    {
        {"\203f\203B\203X\203N\203J\203o\201[\202\252\212J\202\242\202\304\202\242\202\334\202\267\201B", "\203Q\201[\203\200\202\360\221\261\202\257\202\351\217\352\215\207\202\315\201A\203f\203B\203X\203N\203J\203o\201[\202\360\225\302\202\337\202\304\202\255\202\276\202\263\202\242\201B", ""},
        {"The Disc Cover is open.", "If you want to continue the game,", "please close the Disc Cover."},
        {"Der Disc-Deckel ist ge\366ffnet.", "Bitte den Disc-Deckel schlie\337en,", "um mit dem Spiel fortzufahren."},
        {"Il coperchio del disco \350 aperto.", "Se vuoi proseguire nel gioco,", "chiudi il coperchio del disco."},
        {"Le couvercle est ouvert.", "Pour continuer \340 jouer,", "veuillez fermer le couvercle."},
        {"La tapa est\341 abierta. ", "Si quieres seguir jugando,", "debes cerrar la tapa."},
    },
    {
        {"\203t\203@\203C\203i\203\213\203t\203@\203\223\203^\203W\201[\201E\203N\203\212\203X\203^\203\213\203N\203\215\203j\203N\203\213\202\314\203f\203B\203X\203N\202\360", "\203Z\203b\203g\202\265\202\304\202\255\202\276\202\263\202\242\201B", ""},
        {"Please insert the FINAL FANTASY", "Crystal Chronicles Game Disc.", ""},
        {"Bitte legen Sie die FINAL FANTASY",
#ifdef VERSION_GCCE01
         "Crystal Chronicles Disc ein.",
#else
         "Crystal Chronicles-Disc ein.",
#endif
         ""},
        {"Inserisci il disco di gioco ",
#ifdef VERSION_GCCE01
         "FINAL FANTASY Crystal Chronicles",
#else
         "FINAL FANTASY Crystal Chronicles.",
#endif
         ""},
        {"Veuillez ins\351rer le disque",
#ifdef VERSION_GCCE01
         "FINAL FANTASY Crystal Chronicles",
#else
         "FINAL FANTASY Crystal Chronicles.",
#endif
         ""},
        {"Coloca el disco de",
#ifdef VERSION_GCCE01
         "FINAL FANTASY Crystal Chronicles",
#else
         "FINAL FANTASY Crystal Chronicles.",
#endif
         ""},
    },
    {
        {"\203G\203\211\201[\202\252\224\255\220\266\202\265\202\334\202\265\202\275\201B", "\226{\221\314\202\314\203p\203\217\201[\203{\203^\203\223\202\360\211\237\202\265\202\304\201A\223d\214\271\202\360\202n\202e\202e\202\311\202\265\201A", "\226{\221\314\202\314\216\346\210\265\220\340\226\276\217\221\202\314\216w\216\246\202\311\217]\202\301\202\304\211\272\202\263\202\242\201B"},
        {"An error has occurred.", "Turn the power off and refer to the Nintendo GameCube", "Instruction Booklet for further instructions."},
        {"Ein Fehler ist aufgetreten.", "Bitte schalten Sie den Nintendo GameCube aus und lesen Sie die", " Bedienungsanleitung,um weitere Informationen zu erhalten."},
        {"Si \350 verificato un errore.", "Spegni e consulta il manuale di istruzioni del", "Nintendo GameCube per ulteriori indicazioni."},
        {"Une erreur est survenue.", "Eteignez la console et r\351f\351rez-vous au manuel d'instructions", "Nintendo GameCube pour de plus amples informations."},
        {"Se ha producido un error.", "Apaga la consola y consulta el manual de instrucciones ", "de Nintendo GameCube para obtener m\341s informaci\363n."},
    },
};

#endif

enum {
#ifdef VERSION_GCCJGC
    FileReadBufferAllocationLine = 0x29,
    FileHandlePoolAllocationLine = 0x2C
#else
    FileReadBufferAllocationLine = 0x2B,
    FileHandlePoolAllocationLine = 0x2E
#endif
};

enum {
#ifdef VERSION_GCCJGC
    FileErrorCopySize = 0x23000,
    FileErrorDrawBeginLine = 0x2BA,
    FileErrorCopyLine = 0x311,
    FileErrorDisplayLine = 0x315,
    FileErrorDrawEndLine = 0x340
#elif defined(VERSION_GCCE01)
    FileErrorCopySize = 0x23000,
    FileErrorDrawBeginLine = 0x2C4,
    FileErrorCopyLine = 0x321,
    FileErrorDisplayLine = 0x325,
    FileErrorDrawEndLine = 0x353
#else
    FileErrorCopySize = 0x29400,
    FileErrorDrawBeginLine = 0x2CC,
    FileErrorCopyLine = 0x329,
    FileErrorDisplayLine = 0x32D,
    FileErrorDrawEndLine = 0x35B
#endif
};

CFile File;

/*
 * --INFO--
 * PAL Address: 0x80013bb8
 * PAL Size: 408b
 * EN Address: 0x80013B98
 * EN Size: 408b
 * JP Address: 0x80013BE8
 * JP Size: 404b
 */
void CFile::Init()
{
    DVDInit();
    m_allocStage = Memory.CreateStage(0x10ac00, "CFile", 0);
    m_fatalDiskErrorFlag = 0;
#ifndef VERSION_GCCJGC
    m_isDiskError = 0;
#endif
    m_readBuffer = new (m_allocStage, "file.cpp", FileReadBufferAllocationLine) unsigned char[0x100000];
    m_handlePool = new (m_allocStage, "file.cpp", FileHandlePoolAllocationLine) CHandle[0x80];
    m_fileHandle.m_next = &m_fileHandle;
    m_fileHandle.m_previous = &m_fileHandle;
    m_fileHandle.m_priority = PRI_SENTINEL;
    m_freeHandle.m_previous = m_handlePool;

    for (unsigned int i = 0; i < 0x80; i++) {
        CHandle* nextHandle;
        if (i == 0x7F) {
            nextHandle = &m_freeHandle;
        } else {
            nextHandle = &m_handlePool[i + 1];
        }

        m_handlePool[i].m_previous = nextHandle;
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

    if (m_handlePool != 0) {
        delete[] m_handlePool;
        m_handlePool = 0;
    }

    Memory.DestroyStage(m_allocStage);
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
        handle = m_freeHandle.m_previous;
        m_freeHandle.m_previous = handle->m_previous;
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
        System.Printf("CFile::Read \203I\201[\203v\203\223\202\305\202\253\202\334\202\271\202\361\201B%s\n", path);
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
                System.Printf("\033[7;31m\223\307\202\335\215\236\202\335\222\206\202\251\201A\223\307\202\335\215\236\202\335\214\343\203N\203\215\201[\203Y\202\263\202\352\202\304\202\242\202\310\202\242\203t\203@\203C\203\213A\202\306\201A\223\257\212\372\223\307\202\335\215\236\202\335B\202\252\215\254\215\335\202\265\202\334\202\265\202\275\201B\n\203v\203\215\203O\203\211\203\200\202\251\203X\203N\203\212\203v\203g\202\311\226\342\221\350\202\252\202\240\202\350\202\334\202\267\201B\nA\202\360\203o\203b\203t\203@\202\251\202\347\215\355\217\234\202\265\215\304\223x\203L\203\205\201[\203C\203\223\203O\202\265\202\304\201AB\202\360\223\307\202\335\215\236\202\335\202\334\202\267\201B\nA=%s\nB=%s\033[0m\n", inFlight->m_name, fileHandle->m_name);
            }
        }
        else if ((unsigned int)System.m_execParam >= 3)
        {
            System.Printf("\223\307\202\335\215\236\202\335\222\206\202\251\201A\223\307\202\335\215\236\202\335\214\343\203N\203\215\201[\203Y\202\263\202\352\202\304\202\242\202\310\202\242\203t\203@\203C\203\213\202\252\202\240\202\350\202\334\202\265\202\275\201B\n\210\323\220}\223I\202\310\203u\203\215\203b\203N\202\310\202\314\202\305\201A\226\342\221\350\202\315\202\240\202\350\202\334\202\271\202\361\201B\n\203o\203b\203t\203@\202\251\202\347\215\355\217\234\202\265\215\304\223x\203L\203\205\201[\203C\203\223\203O\202\265\202\334\202\267\201B\n%s\n", inFlight->m_name);
        }

        inFlight->m_completionStatus = 1;
    }
}

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
		System.Printf("CFile.kick: \203T\203C\203Y\202\252\203o\203b\203t\203@\202\360\211z\202\246\202\334\202\265\202\275\201B%s(%dbyte)\n", fileHandle->m_name, readSize);
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
 * PAL Address: UNUSED
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFile::Write(CFile::CHandle* fileHandle, void* buffer, unsigned long size)
{
	if (2 <= (unsigned int)System.m_execParam)
	{
		System.Printf("CFile.Write: USB\203\202\201[\203h\202\305\202\315\202\240\202\350\202\334\202\271\202\361\201B\n");
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFile::Write(char* path, void* buffer, unsigned long size)
{
	if (2 <= (unsigned int)System.m_execParam)
	{
		System.Printf("CFile.Write: USB\203\202\201[\203h\202\305\202\315\202\240\202\350\202\334\202\271\202\361\201B\n");
	}
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
		System.Printf("\223\307\202\335\215\236\202\335\223r\222\206\202\305close\202\265\202\334\202\265\202\275\201B%s\n", fileHandle->m_name);
	}

	DVDClose(&fileHandle->m_dvdFileInfo);

	fileHandle->m_closedFlag = 1;
	fileHandle->m_next->m_previous = fileHandle->m_previous;
	fileHandle->m_previous->m_next = fileHandle->m_next;
	fileHandle->m_previous = m_freeHandle.m_previous;
	m_freeHandle.m_previous = fileHandle;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CFile::IsCompleted(CFile::CHandle* fileHandle)
{
	unsigned char completed = fileHandle->m_completionStatus == 3;
	return completed;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::SyncCompleted(CFile::CHandle* fileHandle)
{
	while (!IsCompleted(fileHandle))
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
            readASync(handle);
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

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 216b
 * EN Address: 0x8001A058
 * EN Size: 236b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CFile::readASync(CFile::CHandle* handle)
{
    u32 readSize;

    handle->m_completionStatus = 2;
    readSize = (handle->m_chunkSize + 0x1F) & ~0x1F;

    if (readSize > 0x100000U && (unsigned int)System.m_execParam >= 1)
    {
        System.Printf("CFile.kick: \203T\203C\203Y\202\252\203o\203b\203t\203@\202\360\211z\202\246\202\334\202\265\202\275\201B%s(%dbyte)\n", handle->m_name, readSize);
    }

    DVDReadAsyncPrio(&handle->m_dvdFileInfo, m_readBuffer, readSize, handle->m_currentOffset, 0, 2);
    handle->m_nextOffset = handle->m_currentOffset + readSize;
}

/*
 * --INFO--
 * PAL Address: 0x80013258
 * PAL Size: 668b
 * EN Address: 0x80013238
 * EN Size: 668b
 * JP Address: 0x80013288
 * JP Size: 668b
 */
CFile::CHandle* CFile::CheckQueue()
{
    CHandle* result = 0;
    CHandle* handle = m_fileHandle.m_previous;

    do
    {
        int completionStatus = handle->m_completionStatus;
        if (completionStatus == 2)
        {
            int dvdStatus = DVDGetCommandBlockStatus(&handle->m_dvdFileInfo.cb);

            if (dvdStatus == 0x0B || ((u32)(dvdStatus - 4) <= 2U) || dvdStatus == -1)
            {
                DrawError(handle->m_dvdFileInfo, dvdStatus);
#ifdef VERSION_GCCJGC
                goto next;
#else
                continue;
#endif
            }
            else if (dvdStatus == 0)
            {
                completionStatus = 3;
                handle->m_completionStatus = completionStatus;
                result = CheckQueue();
                break;
            }
            else if (dvdStatus < 0)
            {
                handle->m_completionStatus = 4;
                goto next;
            }
            else
            {
                result = handle;
                break;
            }
        }

        if (completionStatus == 3)
        {
            result = handle;
            break;
        }
        else
        {
next:
            handle = handle->m_previous;
        }
    } while (handle != &m_fileHandle);

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x80012bb8
 * PAL Size: 1696b
 * EN Address: 0x80012B98
 * EN Size: 1696b
 * JP Address: 0x80012B58
 * JP Size: 1840b
 */
#ifdef VERSION_GCCJGC
#include "src/file_jp.inc"
#else
void CFile::DrawError(DVDFileInfo& info, int errorCode)
{
    _GXTexObj backupTexObj;
    m_isDiskError = 1;

    while (true)
    {
retry:
        if ((unsigned int)System.m_execParam >= 1)
        {
            System.Printf("CFile::drawError: %d\n", errorCode);
        }

        int usingFallbackFont = 0;
        CFont* font = MenuPcs.GetFont22();
        if (font == 0)
        {
            font = FontMan.GetInternal22();
            usingFallbackFont = 1;
        }

        if (font == 0)
        {
            m_isDiskError = 0;
            return;
        }

        Graphic._WaitDrawDone("file.cpp", FileErrorDrawBeginLine);

        int hasScratchTexture = Graphic.IsAvailableTempBuffer();
        bool useScratch = false;
        if (hasScratchTexture)
        {
            if (usingFallbackFont == 0)
            {
                useScratch = true;
            }
        }
        int compactLayout = useScratch;

        if (compactLayout)
        {
            Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backupTexObj, 0, 0, 0x280, 0x70, 0, GX_NEAR, GX_TF_RGBA8, 0);

            Util.RenderColorQuad(0.0f, 0.0f, 640.0f, 112.0f, CColor(0, 0, 0, 255));
            memcpy((void*)((char*)Graphic.m_scratchTextureBuffer + 0x46000), (void*)((char*)Graphic.GetFrameBuffer() + 0x34800), FileErrorCopySize);
            DCFlushRange((void*)((char*)Graphic.m_scratchTextureBuffer + 0x46000), FileErrorCopySize);
        }
        else
        {
            Util.RenderColorQuad(0.0f, 0.0f, 640.0f, 448.0f, CColor(0, 0, 0, 255));
        }

        font->SetScale(0.8f);
        font->SetShadow(1);
        font->SetMargin(0.0f);
        font->SetZMode(0, 0);
        font->SetColor(CColor(255, 255, 255, 255));
        font->SetTlut(usingFallbackFont ? -1 : 7);
        font->DrawInit();

        int baseY = compactLayout ? 0x20 : 200;

        int msgIndex = 0;
        switch (errorCode)
        {
        case 0x0B:
            msgIndex = 0;
            break;
        case 5:
            msgIndex = 1;
            break;
        case 4:
        case 6:
            msgIndex = 2;
            break;
        case -1:
            msgIndex = 3;
            m_fatalDiskErrorFlag = 1;
            break;
        default:
            break;
        }

        unsigned int language = Game.m_gameWork.GetLanguage();
        const char* const* lines = l_tError[msgIndex][language];

        if (strlen(lines[2]) == 0)
        {
            font->SetPos(32.0f, (float)baseY, 0.0f);
            font->Draw((char*)lines[0]);
            font->SetPos(32.0f, (float)(baseY + 0x1C), 0.0f);
            font->Draw((char*)lines[1]);
        }
        else
        {
            font->SetPos(32.0f, (float)((int)baseY - 14), 0.0f);
            font->Draw((char*)lines[0]);
            font->SetPos(32.0f, (float)(baseY + 14), 0.0f);
            font->Draw((char*)lines[1]);
            font->SetPos(32.0f, (float)(baseY + 42), 0.0f);
            font->Draw((char*)lines[2]);
        }

        font->DrawQuit();

        if (compactLayout)
        {
            GXSetDispCopySrc(0, 0, 0x280, 0x70);
            GXSetDispCopyDst(0x280, 0x70);
            GXCopyDisp((void*)((char*)Graphic.GetFrameBuffer() + 0x34800), GX_FALSE);
        }
        else
        {
            GXSetDispCopySrc(0, 0, 0x280, 0x1C0);
            GXSetDispCopyDst(0x280, 0x1C0);
            GXCopyDisp(Graphic.GetFrameBuffer(), GX_FALSE);
        }

        Graphic._WaitDrawDone("file.cpp", FileErrorCopyLine);
        Graphic.SetStdDispCopySrc();
        Graphic.SetStdDispCopyDst();
        Graphic._WaitDrawDone("file.cpp", FileErrorDisplayLine);
        VIWaitForRetrace();
        Sound.PauseDiscError(1);
        VISetBlack(FALSE);
        VIFlush();

        int status;
        while (true)
        {
            status = DVDGetCommandBlockStatus(&info.cb);
            if (status != errorCode)
            {
                break;
            }
            VIWaitForRetrace();
        }

        if (compactLayout)
        {
            Util.RenderTextureQuad(0.0f, 0.0f, 640.0f, 112.0f, &backupTexObj, 0, 0, 0, GX_BL_SRCALPHA,
                                           GX_BL_INVSRCALPHA);
            memcpy((void*)((char*)Graphic.GetFrameBuffer() + 0x34800), (void*)((char*)Graphic.m_scratchTextureBuffer + 0x46000), FileErrorCopySize);
            DCFlushRange((void*)((char*)Graphic.GetFrameBuffer() + 0x34800), FileErrorCopySize);
        }
        else
        {
            Util.RenderColorQuad(0.0f, 0.0f, 640.0f, 448.0f, CColor(0, 0, 0, 255));
            GXCopyDisp(Graphic.GetFrameBuffer(), GX_FALSE);
        }

        Graphic._WaitDrawDone("file.cpp", FileErrorDrawEndLine);
        m_fatalDiskErrorFlag = 0;

        while (true)
        {
            if (status != 1)
            {
                if (status == 0x0B || ((u32)(status - 4) <= 2U) || status == -1)
                {
                    errorCode = status;
                    goto retry;
                }

                break;
            }

            VIWaitForRetrace();
            status = DVDGetCommandBlockStatus(&info.cb);
        }

        break;
    }

    Sound.PauseDiscError(0);
    m_isDiskError = 0;
}

#endif

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::CHandle::Reset()
{
	m_completionStatus = 0;
}
