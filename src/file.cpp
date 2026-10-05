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
static const char s_diskReadErrorJp0[] = {0x83, 0x66, 0x83, 0x42, 0x83, 0x58, 0x83, 0x4E, 0x82, 0xF0, 0x93, 0xC7, 0x82, 0xDF, 0x82, 0xDC, 0x82, 0xB9, 0x82, 0xF1, 0x82, 0xC5, 0x82, 0xB5, 0x82, 0xBD, 0x81, 0x42, 0x00};
static const char s_diskReadErrorJp1[] = {0x82, 0xAD, 0x82, 0xED, 0x82, 0xB5, 0x82, 0xAD, 0x82, 0xCD, 0x81, 0x41, 0x96, 0x7B, 0x91, 0xCC, 0x82, 0xCC, 0x8E, 0xE6, 0x88, 0xB5, 0x90, 0xE0, 0x96, 0xBE, 0x8F, 0x91, 0x82, 0xF0, 0x82, 0xA8, 0x93, 0xC7, 0x82, 0xDD, 0x82, 0xAD, 0x82, 0xBE, 0x82, 0xB3, 0x82, 0xA2, 0x81, 0x42, 0x00};
static const char s_diskReadErrorEn0[] = "The Game Disc could not be read.";
static const char s_diskReadErrorEn1[] = "Please read the Nintendo GameCube Instruction";
static const char s_diskReadErrorEn2[] = "Booklet for more information.";
static const char s_diskReadErrorDe0[] = "Diese Game Disc kann nicht gelesen werden.";
static const char s_diskReadErrorDe1[] = "Bitte lesen Sie die Bedienungsanleitung des";
static const char s_diskReadErrorDe2[] = "Nintendo GameCube, um weitere Informationen zu erhalten.";
static const char s_diskReadErrorIt0[] = "Impossibile leggere il disco di gioco.";
static const char s_diskReadErrorIt1[] = "Consulta il manuale di istruzioni del Nintendo GameCube";
#ifdef VERSION_GCCE01
static const char s_diskReadErrorIt2[] = " per ulteriori indicazioni.";
#else
static const char s_diskReadErrorIt2[] = "per ulteriori indicazioni.";
#endif
static const char s_diskReadErrorFr0[] = {0x4C, 0x61, 0x20, 0x6C, 0x65, 0x63, 0x74, 0x75, 0x72, 0x65, 0x20, 0x64, 0x75, 0x20, 0x64, 0x69, 0x73, 0x71, 0x75, 0x65, 0x20, 0x61, 0x20, 0xE9, 0x63, 0x68, 0x6F, 0x75, 0xE9, 0x2E, 0x00};
static const char s_diskReadErrorFr1[] = {0x56, 0x65, 0x75, 0x69, 0x6C, 0x6C, 0x65, 0x7A, 0x20, 0x76, 0x6F, 0x75, 0x73, 0x20, 0x72, 0xE9, 0x66, 0xE9, 0x72, 0x65, 0x72, 0x20, 0x61, 0x75, 0x20, 0x6D, 0x61, 0x6E, 0x75, 0x65, 0x6C, 0x20, 0x64, 0x27, 0x69, 0x6E, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x73, 0x00};
static const char s_diskReadErrorFr2[] = "Nintendo GameCube pour de plus amples informations.";
static const char s_diskReadErrorEs0[] = "No se puede leer el disco.";
static const char s_diskReadErrorEs1[] = "Consulta el manual de instrucciones de";
static const char s_diskReadErrorEs2[] = {0x4E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x20, 0x47, 0x61, 0x6D, 0x65, 0x43, 0x75, 0x62, 0x65, 0x20, 0x70, 0x61, 0x72, 0x61, 0x20, 0x6F, 0x62, 0x74, 0x65, 0x6E, 0x65, 0x72, 0x20, 0x6D, 0xE1, 0x73, 0x20, 0x69, 0x6E, 0x66, 0x6F, 0x72, 0x6D, 0x61, 0x63, 0x69, 0xF3, 0x6E, 0x2E, 0x00};

static const char s_discCoverOpenJp0[] = {0x83, 0x66, 0x83, 0x42, 0x83, 0x58, 0x83, 0x4E, 0x83, 0x4A, 0x83, 0x6F, 0x81, 0x5B, 0x82, 0xAA, 0x8A, 0x4A, 0x82, 0xA2, 0x82, 0xC4, 0x82, 0xA2, 0x82, 0xDC, 0x82, 0xB7, 0x81, 0x42, 0x00};
static const char s_discCoverOpenJp1[] = {0x83, 0x51, 0x81, 0x5B, 0x83, 0x80, 0x82, 0xF0, 0x91, 0xB1, 0x82, 0xAF, 0x82, 0xE9, 0x8F, 0xEA, 0x8D, 0x87, 0x82, 0xCD, 0x81, 0x41, 0x83, 0x66, 0x83, 0x42, 0x83, 0x58, 0x83, 0x4E, 0x83, 0x4A, 0x83, 0x6F, 0x81, 0x5B, 0x82, 0xF0, 0x95, 0xC2, 0x82, 0xDF, 0x82, 0xC4, 0x82, 0xAD, 0x82, 0xBE, 0x82, 0xB3, 0x82, 0xA2, 0x81, 0x42, 0x00};
static const char s_discCoverOpenEn0[] = "The Disc Cover is open.";
static const char s_discCoverOpenEn1[] = "If you want to continue the game,";
static const char s_discCoverOpenEn2[] = "please close the Disc Cover.";
static const char s_discCoverOpenDe0[] = {0x44, 0x65, 0x72, 0x20, 0x44, 0x69, 0x73, 0x63, 0x2D, 0x44, 0x65, 0x63, 0x6B, 0x65, 0x6C, 0x20, 0x69, 0x73, 0x74, 0x20, 0x67, 0x65, 0xF6, 0x66, 0x66, 0x6E, 0x65, 0x74, 0x2E, 0x00};
static const char s_discCoverOpenDe1[] = {0x42, 0x69, 0x74, 0x74, 0x65, 0x20, 0x64, 0x65, 0x6E, 0x20, 0x44, 0x69, 0x73, 0x63, 0x2D, 0x44, 0x65, 0x63, 0x6B, 0x65, 0x6C, 0x20, 0x73, 0x63, 0x68, 0x6C, 0x69, 0x65, 0xDF, 0x65, 0x6E, 0x2C, 0x00};
static const char s_discCoverOpenDe2[] = "um mit dem Spiel fortzufahren.";
static const char s_discCoverOpenIt0[] = {0x49, 0x6C, 0x20, 0x63, 0x6F, 0x70, 0x65, 0x72, 0x63, 0x68, 0x69, 0x6F, 0x20, 0x64, 0x65, 0x6C, 0x20, 0x64, 0x69, 0x73, 0x63, 0x6F, 0x20, 0xE8, 0x20, 0x61, 0x70, 0x65, 0x72, 0x74, 0x6F, 0x2E, 0x00};
static const char s_discCoverOpenIt1[] = "Se vuoi proseguire nel gioco,";
static const char s_discCoverOpenIt2[] = "chiudi il coperchio del disco.";
static const char s_discCoverOpenFr0[] = "Le couvercle est ouvert.";
static const char s_discCoverOpenFr1[] = {0x50, 0x6F, 0x75, 0x72, 0x20, 0x63, 0x6F, 0x6E, 0x74, 0x69, 0x6E, 0x75, 0x65, 0x72, 0x20, 0xE0, 0x20, 0x6A, 0x6F, 0x75, 0x65, 0x72, 0x2C, 0x00};
static const char s_discCoverOpenFr2[] = "veuillez fermer le couvercle.";
static const char s_discCoverOpenEs0[] = {0x4C, 0x61, 0x20, 0x74, 0x61, 0x70, 0x61, 0x20, 0x65, 0x73, 0x74, 0xE1, 0x20, 0x61, 0x62, 0x69, 0x65, 0x72, 0x74, 0x61, 0x2E, 0x20, 0x00};
static const char s_discCoverOpenEs1[] = "Si quieres seguir jugando,";
static const char s_discCoverOpenEs2[] = "debes cerrar la tapa.";

static const char s_wrongDiscJp0[] = {0x83, 0x74, 0x83, 0x40, 0x83, 0x43, 0x83, 0x69, 0x83, 0x8B, 0x83, 0x74, 0x83, 0x40, 0x83, 0x93, 0x83, 0x5E, 0x83, 0x57, 0x81, 0x5B, 0x81, 0x45, 0x83, 0x4E, 0x83, 0x8A, 0x83, 0x58, 0x83, 0x5E, 0x83, 0x8B, 0x83, 0x4E, 0x83, 0x8D, 0x83, 0x6A, 0x83, 0x4E, 0x83, 0x8B, 0x82, 0xCC, 0x83, 0x66, 0x83, 0x42, 0x83, 0x58, 0x83, 0x4E, 0x82, 0xF0, 0x00};
static const char s_wrongDiscJp1[] = {0x83, 0x5A, 0x83, 0x62, 0x83, 0x67, 0x82, 0xB5, 0x82, 0xC4, 0x82, 0xAD, 0x82, 0xBE, 0x82, 0xB3, 0x82, 0xA2, 0x81, 0x42, 0x00};
static const char s_wrongDiscEn0[] = "Please insert the FINAL FANTASY";
static const char s_wrongDiscEn1[] = "Crystal Chronicles Game Disc.";
static const char s_wrongDiscDe0[] = "Bitte legen Sie die FINAL FANTASY";
#ifdef VERSION_GCCE01
static const char s_wrongDiscDe1[] = "Crystal Chronicles Disc ein.";
#else
static const char s_wrongDiscDe1[] = "Crystal Chronicles-Disc ein.";
#endif
static const char s_wrongDiscIt0[] = "Inserisci il disco di gioco ";
#ifdef VERSION_GCCE01
static const char s_wrongDiscIt1[] = "FINAL FANTASY Crystal Chronicles";
#else
static const char s_wrongDiscIt1[] = "FINAL FANTASY Crystal Chronicles.";
#endif
static const char s_wrongDiscFr0[] = {0x56, 0x65, 0x75, 0x69, 0x6C, 0x6C, 0x65, 0x7A, 0x20, 0x69, 0x6E, 0x73, 0xE9, 0x72, 0x65, 0x72, 0x20, 0x6C, 0x65, 0x20, 0x64, 0x69, 0x73, 0x71, 0x75, 0x65, 0x00};
static const char s_wrongDiscEs0[] = "Coloca el disco de";

static const char s_fatalErrorJp0[] = {0x83, 0x47, 0x83, 0x89, 0x81, 0x5B, 0x82, 0xAA, 0x94, 0xAD, 0x90, 0xB6, 0x82, 0xB5, 0x82, 0xDC, 0x82, 0xB5, 0x82, 0xBD, 0x81, 0x42, 0x00};
static const char s_fatalErrorJp1[] = {0x96, 0x7B, 0x91, 0xCC, 0x82, 0xCC, 0x83, 0x70, 0x83, 0x8F, 0x81, 0x5B, 0x83, 0x7B, 0x83, 0x5E, 0x83, 0x93, 0x82, 0xF0, 0x89, 0x9F, 0x82, 0xB5, 0x82, 0xC4, 0x81, 0x41, 0x93, 0x64, 0x8C, 0xB9, 0x82, 0xF0, 0x82, 0x6E, 0x82, 0x65, 0x82, 0x65, 0x82, 0xC9, 0x82, 0xB5, 0x81, 0x41, 0x00};
static const char s_fatalErrorJp2[] = {0x96, 0x7B, 0x91, 0xCC, 0x82, 0xCC, 0x8E, 0xE6, 0x88, 0xB5, 0x90, 0xE0, 0x96, 0xBE, 0x8F, 0x91, 0x82, 0xCC, 0x8E, 0x77, 0x8E, 0xA6, 0x82, 0xC9, 0x8F, 0x5D, 0x82, 0xC1, 0x82, 0xC4, 0x89, 0xBA, 0x82, 0xB3, 0x82, 0xA2, 0x81, 0x42, 0x00};
static const char s_fatalErrorEn0[] = "An error has occurred.";
static const char s_fatalErrorEn1[] = "Turn the power off and refer to the Nintendo GameCube";
static const char s_fatalErrorEn2[] = "Instruction Booklet for further instructions.";
static const char s_fatalErrorDe0[] = "Ein Fehler ist aufgetreten.";
static const char s_fatalErrorDe1[] = "Bitte schalten Sie den Nintendo GameCube aus und lesen Sie die";
static const char s_fatalErrorDe2[] = " Bedienungsanleitung,um weitere Informationen zu erhalten.";
static const char s_fatalErrorIt0[] = {0x53, 0x69, 0x20, 0xE8, 0x20, 0x76, 0x65, 0x72, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x6F, 0x20, 0x75, 0x6E, 0x20, 0x65, 0x72, 0x72, 0x6F, 0x72, 0x65, 0x2E, 0x00};
static const char s_fatalErrorIt1[] = "Spegni e consulta il manuale di istruzioni del";
static const char s_fatalErrorIt2[] = "Nintendo GameCube per ulteriori indicazioni.";
static const char s_fatalErrorFr0[] = "Une erreur est survenue.";
static const char s_fatalErrorFr1[] = {0x45, 0x74, 0x65, 0x69, 0x67, 0x6E, 0x65, 0x7A, 0x20, 0x6C, 0x61, 0x20, 0x63, 0x6F, 0x6E, 0x73, 0x6F, 0x6C, 0x65, 0x20, 0x65, 0x74, 0x20, 0x72, 0xE9, 0x66, 0xE9, 0x72, 0x65, 0x7A, 0x2D, 0x76, 0x6F, 0x75, 0x73, 0x20, 0x61, 0x75, 0x20, 0x6D, 0x61, 0x6E, 0x75, 0x65, 0x6C, 0x20, 0x64, 0x27, 0x69, 0x6E, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x73, 0x00};
static const char s_fatalErrorEs0[] = "Se ha producido un error.";
static const char s_fatalErrorEs1[] = "Apaga la consola y consulta el manual de instrucciones ";
static const char s_fatalErrorEs2[] = {0x64, 0x65, 0x20, 0x4E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x20, 0x47, 0x61, 0x6D, 0x65, 0x43, 0x75, 0x62, 0x65, 0x20, 0x70, 0x61, 0x72, 0x61, 0x20, 0x6F, 0x62, 0x74, 0x65, 0x6E, 0x65, 0x72, 0x20, 0x6D, 0xE1, 0x73, 0x20, 0x69, 0x6E, 0x66, 0x6F, 0x72, 0x6D, 0x61, 0x63, 0x69, 0xF3, 0x6E, 0x2E, 0x00};

extern const char s_emptyErrorText[] = "";


static const char* l_tError[4][6][3] = {
    {
        {s_diskReadErrorJp0, s_diskReadErrorJp1, s_emptyErrorText},
        {s_diskReadErrorEn0, s_diskReadErrorEn1, s_diskReadErrorEn2},
        {s_diskReadErrorDe0, s_diskReadErrorDe1, s_diskReadErrorDe2},
        {s_diskReadErrorIt0, s_diskReadErrorIt1, s_diskReadErrorIt2},
        {s_diskReadErrorFr0, s_diskReadErrorFr1, s_diskReadErrorFr2},
        {s_diskReadErrorEs0, s_diskReadErrorEs1, s_diskReadErrorEs2},
    },
    {
        {s_discCoverOpenJp0, s_discCoverOpenJp1, s_emptyErrorText},
        {s_discCoverOpenEn0, s_discCoverOpenEn1, s_discCoverOpenEn2},
        {s_discCoverOpenDe0, s_discCoverOpenDe1, s_discCoverOpenDe2},
        {s_discCoverOpenIt0, s_discCoverOpenIt1, s_discCoverOpenIt2},
        {s_discCoverOpenFr0, s_discCoverOpenFr1, s_discCoverOpenFr2},
        {s_discCoverOpenEs0, s_discCoverOpenEs1, s_discCoverOpenEs2},
    },
    {
        {s_wrongDiscJp0, s_wrongDiscJp1, s_emptyErrorText},
        {s_wrongDiscEn0, s_wrongDiscEn1, s_emptyErrorText},
        {s_wrongDiscDe0, s_wrongDiscDe1, s_emptyErrorText},
        {s_wrongDiscIt0, s_wrongDiscIt1, s_emptyErrorText},
        {s_wrongDiscFr0, s_wrongDiscIt1, s_emptyErrorText},
        {s_wrongDiscEs0, s_wrongDiscIt1, s_emptyErrorText},
    },
    {
        {s_fatalErrorJp0, s_fatalErrorJp1, s_fatalErrorJp2},
        {s_fatalErrorEn0, s_fatalErrorEn1, s_fatalErrorEn2},
        {s_fatalErrorDe0, s_fatalErrorDe1, s_fatalErrorDe2},
        {s_fatalErrorIt0, s_fatalErrorIt1, s_fatalErrorIt2},
        {s_fatalErrorFr0, s_fatalErrorFr1, s_diskReadErrorFr2},
        {s_fatalErrorEs0, s_fatalErrorEs1, s_fatalErrorEs2},
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
                System.Printf("CFile.kick: \203T\203C\203Y\202\252\203o\203b\203t\203@\202\360\211z\202\246\202\334\202\265\202\275\201B%s(%dbyte)\n", handle->m_name, readSize);
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
        CFont* font = MenuPcs.m_fonts[0];
        if (MenuPcs.m_fonts[0] == 0)
        {
            font = FontMan.m_font;
            usingFallbackFont = 1;
        }

        if (font == 0)
        {
            m_isDiskError = 0;
            return;
        }

        Graphic._WaitDrawDone("file.cpp", FileErrorDrawBeginLine);

        int hasScratchTexture = (int)Graphic.m_scratchTextureBuffer;
        hasScratchTexture = hasScratchTexture != 0;
        int compactLayout = (bool)(hasScratchTexture && usingFallbackFont == 0);

        if (compactLayout)
        {
            Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backupTexObj, 0, 0, 0x280, 0x70, 0, GX_NEAR, GX_TF_RGBA8, 0);

            gUtil.RenderColorQuad(0.0f, 0.0f, 640.0f, 112.0f, CColor(0, 0, 0, 255).color);
            memcpy((void*)((char*)Graphic.m_scratchTextureBuffer + 0x46000), (void*)((char*)Graphic.m_frameBuffer + 0x34800), FileErrorCopySize);
            DCFlushRange((void*)((char*)Graphic.m_scratchTextureBuffer + 0x46000), FileErrorCopySize);
        }
        else
        {
            gUtil.RenderColorQuad(0.0f, 0.0f, 640.0f, 448.0f, CColor(0, 0, 0, 255).color);
        }

        font->SetScale(0.8f);
        font->SetShadow(1);
        font->SetMargin(0.0f);
        font->SetZMode(0, 0);
        font->SetColor(CColor(255, 255, 255, 255).color);
        font->SetTlut(usingFallbackFont ? -1 : 7);
        font->DrawInit();

        int baseY = 200;
        if (compactLayout)
        {
            baseY = 0x20;
        }

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

        unsigned int language = Game.m_gameWork.m_languageId;
        const char* const* lines = l_tError[msgIndex][language];

        if (strlen(lines[2]) == 0)
        {
            font->SetPosX(32.0f);
            font->SetPosY((float)baseY);
            font->SetPosZ(0.0f);
            font->Draw((char*)lines[0]);
            font->SetPosX(32.0f);
            font->SetPosY((float)(baseY + 0x1C));
            font->SetPosZ(0.0f);
            font->Draw((char*)lines[1]);
        }
        else
        {
            font->SetPosX(32.0f);
            font->SetPosY((float)((int)baseY - 14));
            font->SetPosZ(0.0f);
            font->Draw((char*)lines[0]);
            font->SetPosX(32.0f);
            font->SetPosY((float)(baseY + 14));
            font->SetPosZ(0.0f);
            font->Draw((char*)lines[1]);
            font->SetPosX(32.0f);
            font->SetPosY((float)(baseY + 42));
            font->SetPosZ(0.0f);
            font->Draw((char*)lines[2]);
        }

        font->DrawQuit();

        if (compactLayout)
        {
            GXSetDispCopySrc(0, 0, 0x280, 0x70);
            GXSetDispCopyDst(0x280, 0x70);
            GXCopyDisp((void*)((char*)Graphic.m_frameBuffer + 0x34800), GX_FALSE);
        }
        else
        {
            GXSetDispCopySrc(0, 0, 0x280, 0x1C0);
            GXSetDispCopyDst(0x280, 0x1C0);
            GXCopyDisp(Graphic.m_frameBuffer, GX_FALSE);
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
            gUtil.RenderTextureQuad(0.0f, 0.0f, 640.0f, 112.0f, &backupTexObj, 0, 0, 0, GX_BL_SRCALPHA,
                                           GX_BL_INVSRCALPHA);
            memcpy((void*)((char*)Graphic.m_frameBuffer + 0x34800), (void*)((char*)Graphic.m_scratchTextureBuffer + 0x46000), FileErrorCopySize);
            DCFlushRange((void*)((char*)Graphic.m_frameBuffer + 0x34800), FileErrorCopySize);
        }
        else
        {
            gUtil.RenderColorQuad(0.0f, 0.0f, 640.0f, 448.0f, CColor(0, 0, 0, 255).color);
            GXCopyDisp(Graphic.m_frameBuffer, GX_FALSE);
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
