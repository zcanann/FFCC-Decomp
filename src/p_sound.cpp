#include "ffcc/p_sound.h"
#include "ffcc/sound.h"

extern u32 CFlatFlags;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CSoundPcs::CSoundPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	800d8808
 * Size:	4
 */
void CSoundPcs::Init()
{
	return;
}

/*
 * --INFO--
 * Address:	800d8804
 * Size:	4
 */
void CSoundPcs::Quit()
{
	return;
}

/*
 * --INFO--
 * Address:	800d87f0
 * Size:	20
 */
void CSoundPcs::GetTable(unsigned long param)
{
	// TODO: Ghidra shows this returns param * 0x15c + -0x7fdefa50
	// but header shows void return type - needs investigation
}

/*
 * --INFO--
 * Address:	800d87ec
 * Size:	4
 */
void CSoundPcs::create()
{
	return;
}

/*
 * --INFO--
 * Address:	800d87c4
 * Size:	40
 */
void CSoundPcs::createLoad()
{
	Sound.LoadBlock();
}

/*
 * --INFO--
 * Address:	800d8774
 * Size:	80
 */
void CSoundPcs::destroy()
{
	Sound.CancelLoadWaveASync();
	Sound.StopStream();
	Sound.StopAndFreeAllSe(1);
	Sound.FreeBlock();
}

/*
 * --INFO--
 * Address:	800d874c
 * Size:	40
 */
void CSoundPcs::calc()
{
	Sound.Frame();
}

/*
 * --INFO--
 * Address:	800d8710
 * Size:	60
 */
void CSoundPcs::draw()
{
	if ((CFlatFlags & 0x400000) != 0) {
		Sound.Draw();
	}
}

/*
 * --INFO--
 * Address:	800d880c
 * Size:	188
 */
// TODO: Implement __sinit_p_sound_cpp with proper symbol declarations
// void __sinit_p_sound_cpp()
// {
// 	SoundPcs = &PTR_PTR_s_CSoundPcs_8021072c;
// 	DAT_802105b4 = DAT_80210580;
// 	DAT_802105b8 = DAT_80210584;
// 	DAT_802105bc = PTR_create__9CSoundPcsFv_80210588;
// 	DAT_802105c0 = DAT_8021058c;
// 	DAT_802105c4 = DAT_80210590;
// 	DAT_802105c8 = PTR_destroy__9CSoundPcsFv_80210594;
// 	DAT_802105cc = DAT_80210598;
// 	DAT_802105d0 = DAT_8021059c;
// 	DAT_802105d4 = PTR_calc__9CSoundPcsFv_802105a0;
// 	DAT_802105e0 = DAT_802105a4;
// 	DAT_802105e4 = DAT_802105a8;
// 	DAT_802105e8 = PTR_draw__9CSoundPcsFv_802105ac;
// }
