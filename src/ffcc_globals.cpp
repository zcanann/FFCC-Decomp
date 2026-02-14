// Central definitions for global manager singletons.
//
// Many FFCC headers declare these as `extern`.
// This file provides the single definition to avoid ODR violations.

#include "ffcc/file.h"
#include "ffcc/gbaque.h"
#include "ffcc/graphic.h"
#include "ffcc/joybus.h"
#include "ffcc/map.h"
#include "ffcc/memory.h"
#include "ffcc/memorycard.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_chara.h"
#include "ffcc/p_game.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/usb.h"

CFile File;
GbaQueue GbaQue;
CGraphic Graphic;
JoyBus Joybus;
CMapMng MapMng;
CMemory Memory;
CMemoryCardMan MemoryCardMan;
CCameraPcs CameraPcs;
CCharaPcs CharaPcs;
CGamePcs Game;
CPad Pad;
CSound Sound;
CUSB USB;
