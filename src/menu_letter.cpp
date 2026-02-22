#include "ffcc/menu_letter.h"
#include "ffcc/p_game.h"

namespace {
unsigned int DAT_8032eef0 = 0;
unsigned char DAT_8032eeee = 0;
unsigned char DAT_8032eeed = 0;
int DAT_8032eef4 = 0;
} // namespace

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit0()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit2()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit3()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit4()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterCtrl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterLstOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterLstClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterMessOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterMessClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterItemWinOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterItemWinClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterReplyWinOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterReplyWinClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterAttachWinOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterAttachWinClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterConfirmOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterConfirmClose()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 80165b4c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::LetterDraw()
{
	if (*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x30) == 0) {
		LetterListDraw();
	} else {
		LetterMessDraw();
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterListDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterMessDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterCtrlCur()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterLstBaseDraw(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterDrawPageMark(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 8016394c
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::LetterSetAttachItem(unsigned int itemIndex, int flag)
{
	DAT_8032eef0 = itemIndex;
	if (DAT_8032eeed == 0) {
		DAT_8032eeee = static_cast<unsigned char>(itemIndex);
		DAT_8032eef0 = static_cast<unsigned int>(*reinterpret_cast<short*>(Game.game.m_scriptFoodBase[0] + itemIndex * 2 + 0xB6));
	}
	DAT_8032eef4 = flag;
}
