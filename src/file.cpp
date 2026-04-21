#include "ffcc/file.h"

#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/goout.h"
#include "ffcc/graphic.h"
#include "ffcc/memory.h"
#include "ffcc/p_game.h"
#include "ffcc/p_menu.h"
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

CFile File;

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
static const char s_diskReadErrorIt2[] = "per ulteriori indicazioni.";
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
static const char s_wrongDiscDe1[] = "Crystal Chronicles-Disc ein.";
static const char s_wrongDiscIt0[] = "Inserisci il disco di gioco ";
static const char s_wrongDiscIt1[] = "FINAL FANTASY Crystal Chronicles.";
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

static const char s_cFile[] = "CFile";
static const char s_drawErrorFmt[] = "CFile::drawError: %d\n";
static const char s_fileCpp[] = "file.cpp";
static const char s_readWarnFmt[] = {0x43, 0x46, 0x69, 0x6C, 0x65, 0x2E, 0x6B, 0x69, 0x63, 0x6B, 0x3A, 0x20, 0x83, 0x54, 0x83, 0x43, 0x83, 0x59, 0x82, 0xAA, 0x83, 0x6F, 0x83, 0x62, 0x83, 0x74, 0x83, 0x40, 0x82, 0xF0, 0x89, 0x7A, 0x82, 0xA6, 0x82, 0xDC, 0x82, 0xB5, 0x82, 0xBD, 0x81, 0x42, 0x25, 0x73, 0x28, 0x25, 0x64, 0x62, 0x79, 0x74, 0x65, 0x29, 0x0A, 0x00};
static const char s_closeWarnFmt[] = {0x93, 0xC7, 0x82, 0xDD, 0x8D, 0x9E, 0x82, 0xDD, 0x93, 0x72, 0x92, 0x86, 0x82, 0xC5, 0x63, 0x6C, 0x6F, 0x73, 0x65, 0x82, 0xB5, 0x82, 0xDC, 0x82, 0xB5, 0x82, 0xBD, 0x81, 0x42, 0x25, 0x73, 0x0A, 0x00};
static const char s_queueWarnTargetFmt[] = {0x1B, 0x5B, 0x37, 0x3B, 0x33, 0x31, 0x6D, 0x93, 0xC7, 0x82, 0xDD, 0x8D, 0x9E, 0x82, 0xDD, 0x92, 0x86, 0x82, 0xA9, 0x81, 0x41, 0x93, 0xC7, 0x82, 0xDD, 0x8D, 0x9E, 0x82, 0xDD, 0x8C, 0xE3, 0x83, 0x4E, 0x83, 0x8D, 0x81, 0x5B, 0x83, 0x59, 0x82, 0xB3, 0x82, 0xEA, 0x82, 0xC4, 0x82, 0xA2, 0x82, 0xC8, 0x82, 0xA2, 0x83, 0x74, 0x83, 0x40, 0x83, 0x43, 0x83, 0x8B, 0x41, 0x82, 0xC6, 0x81, 0x41, 0x93, 0xAF, 0x8A, 0xFA, 0x93, 0xC7, 0x82, 0xDD, 0x8D, 0x9E, 0x82, 0xDD, 0x42, 0x82, 0xAA, 0x8D, 0xAC, 0x8D, 0xDD, 0x82, 0xB5, 0x82, 0xDC, 0x82, 0xB5, 0x82, 0xBD, 0x81, 0x42, 0x0A, 0x83, 0x76, 0x83, 0x8D, 0x83, 0x4F, 0x83, 0x89, 0x83, 0x80, 0x82, 0xA9, 0x83, 0x58, 0x83, 0x4E, 0x83, 0x8A, 0x83, 0x76, 0x83, 0x67, 0x82, 0xC9, 0x96, 0xE2, 0x91, 0xE8, 0x82, 0xAA, 0x82, 0xA0, 0x82, 0xE8, 0x82, 0xDC, 0x82, 0xB7, 0x81, 0x42, 0x0A, 0x41, 0x82, 0xF0, 0x83, 0x6F, 0x83, 0x62, 0x83, 0x74, 0x83, 0x40, 0x82, 0xA9, 0x82, 0xE7, 0x8D, 0xED, 0x8F, 0x9C, 0x82, 0xB5, 0x8D, 0xC4, 0x93, 0x78, 0x83, 0x4C, 0x83, 0x85, 0x81, 0x5B, 0x83, 0x43, 0x83, 0x93, 0x83, 0x4F, 0x82, 0xB5, 0x82, 0xC4, 0x81, 0x41, 0x42, 0x82, 0xF0, 0x93, 0xC7, 0x82, 0xDD, 0x8D, 0x9E, 0x82, 0xDD, 0x82, 0xDC, 0x82, 0xB7, 0x81, 0x42, 0x0A, 0x41, 0x3D, 0x25, 0x73, 0x0A, 0x42, 0x3D, 0x25, 0x73, 0x1B, 0x5B, 0x30, 0x6D, 0x0A, 0x00};
static const char s_queueWarnAnyFmt[] = {0x93, 0xC7, 0x82, 0xDD, 0x8D, 0x9E, 0x82, 0xDD, 0x92, 0x86, 0x82, 0xA9, 0x81, 0x41, 0x93, 0xC7, 0x82, 0xDD, 0x8D, 0x9E, 0x82, 0xDD, 0x8C, 0xE3, 0x83, 0x4E, 0x83, 0x8D, 0x81, 0x5B, 0x83, 0x59, 0x82, 0xB3, 0x82, 0xEA, 0x82, 0xC4, 0x82, 0xA2, 0x82, 0xC8, 0x82, 0xA2, 0x83, 0x74, 0x83, 0x40, 0x83, 0x43, 0x83, 0x8B, 0x82, 0xAA, 0x82, 0xA0, 0x82, 0xE8, 0x82, 0xDC, 0x82, 0xB5, 0x82, 0xBD, 0x81, 0x42, 0x0A, 0x88, 0xD3, 0x90, 0x7D, 0x93, 0x49, 0x82, 0xC8, 0x83, 0x75, 0x83, 0x8D, 0x83, 0x62, 0x83, 0x4E, 0x82, 0xC8, 0x82, 0xCC, 0x82, 0xC5, 0x81, 0x41, 0x96, 0xE2, 0x91, 0xE8, 0x82, 0xCD, 0x82, 0xA0, 0x82, 0xE8, 0x82, 0xDC, 0x82, 0xB9, 0x82, 0xF1, 0x81, 0x42, 0x0A, 0x83, 0x6F, 0x83, 0x62, 0x83, 0x74, 0x83, 0x40, 0x82, 0xA9, 0x82, 0xE7, 0x8D, 0xED, 0x8F, 0x9C, 0x82, 0xB5, 0x8D, 0xC4, 0x93, 0x78, 0x83, 0x4C, 0x83, 0x85, 0x81, 0x5B, 0x83, 0x43, 0x83, 0x93, 0x83, 0x4F, 0x82, 0xB5, 0x82, 0xDC, 0x82, 0xB7, 0x81, 0x42, 0x0A, 0x25, 0x73, 0x0A, 0x00};
static const char s_openWarnFmt[] = {0x43, 0x46, 0x69, 0x6C, 0x65, 0x3A, 0x3A, 0x52, 0x65, 0x61, 0x64, 0x20, 0x83, 0x49, 0x81, 0x5B, 0x83, 0x76, 0x83, 0x93, 0x82, 0xC5, 0x82, 0xAB, 0x82, 0xDC, 0x82, 0xB9, 0x82, 0xF1, 0x81, 0x42, 0x25, 0x73, 0x0A, 0x00};

static const char s_emptyErrorText[] = "";

static const char* l_tError[72] = {
    s_discCoverOpenJp0, s_discCoverOpenJp1, s_emptyErrorText,
    s_discCoverOpenEn0, s_discCoverOpenEn1, s_discCoverOpenEn2,
    s_discCoverOpenDe0, s_discCoverOpenDe1, s_discCoverOpenDe2,
    s_discCoverOpenIt0, s_discCoverOpenIt1, s_discCoverOpenIt2,
    s_discCoverOpenFr0, s_discCoverOpenFr1, s_discCoverOpenFr2,
    s_discCoverOpenEs0, s_discCoverOpenEs1, s_discCoverOpenEs2,

    s_wrongDiscJp0, s_wrongDiscJp1, s_emptyErrorText,
    s_wrongDiscEn0, s_wrongDiscEn1, s_emptyErrorText,
    s_wrongDiscDe0, s_wrongDiscDe1, s_emptyErrorText,
    s_wrongDiscIt0, s_wrongDiscIt1, s_emptyErrorText,
    s_wrongDiscFr0, s_emptyErrorText, s_emptyErrorText,
    s_wrongDiscEs0, s_emptyErrorText, s_emptyErrorText,

    s_diskReadErrorJp0, s_diskReadErrorJp1, s_emptyErrorText,
    s_diskReadErrorEn0, s_diskReadErrorEn1, s_diskReadErrorEn2,
    s_diskReadErrorDe0, s_diskReadErrorDe1, s_diskReadErrorDe2,
    s_diskReadErrorIt0, s_diskReadErrorIt1, s_diskReadErrorIt2,
    s_diskReadErrorFr0, s_diskReadErrorFr1, s_diskReadErrorFr2,
    s_diskReadErrorEs0, s_diskReadErrorEs1, s_diskReadErrorEs2,

    s_fatalErrorJp0, s_fatalErrorJp1, s_fatalErrorJp2,
    s_fatalErrorEn0, s_fatalErrorEn1, s_fatalErrorEn2,
    s_fatalErrorDe0, s_fatalErrorDe1, s_fatalErrorDe2,
    s_fatalErrorIt0, s_fatalErrorIt1, s_fatalErrorIt2,
    s_fatalErrorFr0, s_fatalErrorFr1, s_emptyErrorText,
    s_fatalErrorEs0, s_fatalErrorEs1, s_fatalErrorEs2,
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
    m_allocStage = CreateStage__7CMemoryFUlPci(&Memory, 0x10ac00, const_cast<char*>(s_cFile), 0);
    m_fatalDiskErrorFlag = 0;
    m_isDiskError = 0;
    m_readBuffer =
        __nwa__FUlPQ27CMemory6CStagePci(0x100000, (CMemory::CStage*)m_allocStage, const_cast<char*>(s_fileCpp), 0x2b);
    m_handlePoolHead.m_currentOffset = (u32)__construct_new_array(
        __nwa__FUlPQ27CMemory6CStagePci(
            sizeof(CHandle) * 0x80 + 0x10, (CMemory::CStage*)m_allocStage, const_cast<char*>(s_fileCpp), 0x2e),
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
        System.Printf(const_cast<char*>(s_openWarnFmt), path);
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
                System.Printf(const_cast<char*>(s_queueWarnTargetFmt), inFlight->m_name, fileHandle->m_name);
            }
        }
        else if ((unsigned int)System.m_execParam >= 3)
        {
            System.Printf(const_cast<char*>(s_queueWarnAnyFmt), inFlight->m_name);
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
		System.Printf(const_cast<char*>(s_readWarnFmt), fileHandle->m_name, readSize);
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
		System.Printf(const_cast<char*>(s_closeWarnFmt), fileHandle->m_name);
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
                System.Printf(const_cast<char*>(s_readWarnFmt), handle->m_name, readSize);
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
                continue;
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
                completionStatus = 4;
                handle->m_completionStatus = completionStatus;
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
            handle = handle->m_previous;
        }
    } while (handle != &m_fileHandle);

    return result;
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
        if ((unsigned int)System.m_execParam >= 1)
        {
            System.Printf(const_cast<char*>(s_drawErrorFmt), errorCode);
        }

        CFont* font = MenuPcs.m_fonts[0];
        int usingFallbackFont = 0;
        if (font == 0)
        {
            usingFallbackFont = 1;
            font = FontMan.m_font;
        }

        if (font == 0)
        {
            m_isDiskError = 0;
            return;
        }

        Graphic._WaitDrawDone(const_cast<char*>(s_fileCpp), 0x2CC);

        int compactLayout = 0;
        if (usingFallbackFont == 0 && Graphic.m_scratchTextureBuffer != 0)
        {
            compactLayout = 1;
        }

        if (compactLayout != 0)
        {
            Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backupTexObj, 0, 0, 0x280, 0x70, 0, GX_NEAR, GX_TF_RGBA8, 0);

            gUtil.RenderColorQuad(0.0f, 0.0f, 640.0f, 112.0f, CColor(0, 0, 0, 255).color);
            memcpy((void*)((char*)Graphic.m_scratchTextureBuffer + 0x46000), (void*)((char*)Graphic.m_frameBuffer + 0x34800), 0x29400);
            DCFlushRange((void*)((char*)Graphic.m_scratchTextureBuffer + 0x46000), 0x29400);
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
        font->SetTlut(usingFallbackFont != 0 ? -1 : 7);
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
        const char* const* lines = &l_tError[msgIndex * 18 + language * 3];
        unsigned int baseY = 200;
        if (compactLayout != 0)
        {
            baseY = 0x20;
        }

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

        if (compactLayout != 0)
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

        Graphic._WaitDrawDone(const_cast<char*>(s_fileCpp), 0x329);
        Graphic.SetStdDispCopySrc();
        Graphic.SetStdDispCopyDst();
        Graphic._WaitDrawDone(const_cast<char*>(s_fileCpp), 0x32D);
        VIWaitForRetrace();
        Sound.PauseDiscError(1);
        VISetBlack(FALSE);
        VIFlush();

        while (DVDGetCommandBlockStatus(&info.cb) == errorCode)
        {
            VIWaitForRetrace();
        }

        if (compactLayout != 0)
        {
            gUtil.RenderTextureQuad(0.0f, 0.0f, 640.0f, 112.0f, &backupTexObj, 0, 0, 0, GX_BL_SRCALPHA,
                                           GX_BL_INVSRCALPHA);
            memcpy((void*)((char*)Graphic.m_frameBuffer + 0x34800), (void*)((char*)Graphic.m_scratchTextureBuffer + 0x46000), 0x29400);
            DCFlushRange((void*)((char*)Graphic.m_frameBuffer + 0x34800), 0x29400);
        }
        else
        {
            gUtil.RenderColorQuad(0.0f, 0.0f, 640.0f, 448.0f, CColor(0, 0, 0, 255).color);
            GXCopyDisp(Graphic.m_frameBuffer, GX_FALSE);
        }

        Graphic._WaitDrawDone(const_cast<char*>(s_fileCpp), 0x35B);
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
