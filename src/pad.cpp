#include "ffcc/pad.h"

CPad Pad;

/*
 * --INFO--
 * PAL Address: 0x800211a8
 * PAL Size: 44b
 */
extern "C" void __sinit_pad_cpp()
{
	// Static initialization - setup vtable and clear member variables
	Pad._448_4_ = 0;
	Pad._452_4_ = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CPad::CPad()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 416b
 */
void CPad::Init()
{
	_4_2_ = 0;
	_8_2_ = 0;
	_448_4_ = 0;
	_452_4_ = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPad::Quit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 2844b
 */
void CPad::Frame()
{
	// Frame update for controller input
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPad::SaveReplayData()
{
	// TODO
}
