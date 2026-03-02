#include "ffcc/monobj_boss.h"
#include "ffcc/prgobj.h"
#include "ffcc/charaobj.h"
#include "ffcc/math.h"
#include "ffcc/p_game.h"

#include <math.h>

extern CMath Math;
extern "C" int Rand__5CMathFUl(CMath*, unsigned long);
extern "C" void setAttackAfter__8CGMonObjFi(CGMonObj*, int);
extern "C" void reqAnim__8CGPrgObjFiii(void*, int, int, int);
extern "C" void putParticle__8CGPrgObjFiiP8CGObjectfi(void*, int, int, void*, float, int);
extern "C" void playSe3D__8CGPrgObjFiiiiP3Vec(void*, int, int, int, int, Vec*);
extern "C" int isLoopAnim__8CGPrgObjFv(void*);
extern "C" void changeStat__8CGPrgObjFiii(void*, int, int, int);
extern "C" void Move__8CGObjectFP3Vecfiiiii(void*, Vec*, float, int, int, int, int, int);
extern "C" void moveVectorHRot__8CGObjectFfffi(void*, float, float, float, int);
extern "C" void ResetParticleWork__13CFlatRuntime2Fii(void*, int, int);
extern "C" void SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject(void*, void*);
extern "C" void SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject(void*, void*);
extern "C" void PutParticleWork__13CFlatRuntime2Fv(void*);
extern float FLOAT_80331dd0;
extern float FLOAT_80331cf8;
extern float FLOAT_80331dcc;
extern float FLOAT_80331dc8;
extern float FLOAT_80331d18;
extern float FLOAT_80331d1c;
extern float FLOAT_80331d20;
extern float FLOAT_80331dd4;
extern float FLOAT_80331d24;
extern float FLOAT_80331d2c;
extern float FLOAT_80331dd8;
extern float FLOAT_80331d60;
extern float FLOAT_80331db8;
extern float DAT_8032ec20;
extern double DOUBLE_80331d00;
extern double DOUBLE_80331d08;
extern double DOUBLE_80331d10;
extern double DOUBLE_80331dc0;
extern unsigned char CFlat[];
extern char SoundBuffer[];

/*
 * --INFO--
 * PAL Address: 0x80132f68
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncGiantCrab()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80132f68_damagedFuncGiantCrab__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80132e80
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::logicFuncGiantCrab()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80132e80_logicFuncGiantCrab__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80132e78
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::calcBranchFuncGiantCrab(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80132e78_calcBranchFuncGiantCrab__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x801329e8
 * PAL Size: 1168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncGiantCrab()
{
	u8* self = (u8*)this;
	int state = *(int*)(self + 0x520);

	if (state == 100) {
		if (*(int*)(self + 0x528) == 0) {
			int soundStep = *(int*)(SoundBuffer + 0x4f0);
			if (soundStep == 2) {
				*(float*)(SoundBuffer + 0x4f4) = FLOAT_80331dd0;
				*(float*)(SoundBuffer + 0x4f8) = FLOAT_80331cf8;
				*(float*)(SoundBuffer + 0x4fc) = FLOAT_80331dcc;
			} else if (soundStep < 2) {
				if (soundStep == 0) {
					*(float*)(SoundBuffer + 0x4f4) = FLOAT_80331dc8;
					*(float*)(SoundBuffer + 0x4f8) = FLOAT_80331cf8;
					*(float*)(SoundBuffer + 0x4fc) = FLOAT_80331dcc;
				} else if (soundStep > -1) {
					*(float*)(SoundBuffer + 0x4f4) = FLOAT_80331dc8;
					*(float*)(SoundBuffer + 0x4f8) = FLOAT_80331cf8;
					*(float*)(SoundBuffer + 0x4fc) = FLOAT_80331dc8;
				}
			} else if (soundStep < 4) {
				*(float*)(SoundBuffer + 0x4f4) = FLOAT_80331dd0;
				*(float*)(SoundBuffer + 0x4f8) = FLOAT_80331cf8;
				*(float*)(SoundBuffer + 0x4fc) = FLOAT_80331dc8;
			}

			*(int*)(SoundBuffer + 0x4f0) = (soundStep + 1) & 3;
			reqAnim__8CGPrgObjFiii(self, 0xc, 0, 0);

			int pdtIndex = -1;
			u8* charaModelHandle = *(u8**)(self + 0xf8);
			if (charaModelHandle != 0) {
				u8* pdtLoadRef = *(u8**)(charaModelHandle + 0x178);
				if (pdtLoadRef != 0) {
					pdtIndex = *(int*)(pdtLoadRef + 0x14);
				}
			}
			putParticle__8CGPrgObjFiiP8CGObjectfi(self, (pdtIndex << 8) | 6, 0, self, FLOAT_80331d18, 0);
			putParticle__8CGPrgObjFiiP8CGObjectfi(self, (pdtIndex << 8) | 7, 0, self, FLOAT_80331d18, 0);
		}

		int frame = *(int*)(self + 0x528);
		if (frame > 0x20) {
			if (frame == 0x21) {
				playSe3D__8CGPrgObjFiiiiP3Vec(self, 0x4e30, 0x32, 0x1c2, 0, 0);
			} else if (frame == 0x32) {
				playSe3D__8CGPrgObjFiiiiP3Vec(self, 0x4e35, 0x32, 0x1c2, 0, 0);
			}

			*(u32*)(self + 0x1c0) &= 0xfff7fffd;
			float moveScale = PSVECDistance((Vec*)(SoundBuffer + 0x4f4), (Vec*)(self + 0x15c)) * FLOAT_80331dd4;
			Vec moveDir = { 0.0f, 0.0f, 0.0f };
			Move__8CGObjectFP3Vecfiiiii(self, &moveDir, moveScale, 0x10, 1, 0, 0, 0);

			int targetIdx = *(int*)(self + 0x6c4);
			if (targetIdx > -1) {
				u8* target = (u8*)Game.game.m_partyObjArr[targetIdx];
				if (target != 0) {
					*(float*)(self + 0x1b4) = (float)atan2(
					    (double)(*(float*)(target + 0x15c) - *(float*)(self + 0x15c)),
					    (double)(*(float*)(target + 0x164) - *(float*)(self + 0x164)));
				}
			}
		}

		if (isLoopAnim__8CGPrgObjFv(self) != 0) {
			changeStat__8CGPrgObjFiii(self, 0, 0, 0);
			*(u32*)(self + 0x1c0) |= 0x80002;
		}
	} else if (state > 99 && state < 0x69) {
		if (*(int*)(self + 0x528) == 0) {
			float turnOffset = FLOAT_80331d2c;
			int animId = 1;
			if (state == 0x67) {
				turnOffset = FLOAT_80331d24;
				animId = 0x12;
			} else if (state >= 0x68) {
				turnOffset = FLOAT_80331dd8;
				animId = 0x13;
			}

			reqAnim__8CGPrgObjFiii(self, animId, 0, 0);
			u16 scriptScale = *(u16*)(*(u8**)(self + 0x7c) + 0xd4);
			float moveMagnitude =
			    *(float*)(self + 0x690) *
			    (FLOAT_80331d60 * (float)((double)scriptScale - DOUBLE_80331dc0) + FLOAT_80331db8);
			moveVectorHRot__8CGObjectFfffi(self, *(float*)(self + 0x1b4) + turnOffset, FLOAT_80331cf8, moveMagnitude, 0x1e);

			int targetIdx = *(int*)(self + 0x6c4);
			if (targetIdx > -1) {
				u8* target = (u8*)Game.game.m_partyObjArr[targetIdx];
				if (target != 0) {
					*(float*)(self + 0x1b4) = (float)atan2(
					    (double)(*(float*)(target + 0x15c) - *(float*)(self + 0x15c)),
					    (double)(*(float*)(target + 0x164) - *(float*)(self + 0x164)));
				}
			}

			u32 action = (u32) * (void**)(self + 0x68);
			if (action == 0x63) {
				playSe3D__8CGPrgObjFiiiiP3Vec(self, 0x8cab, 0x32, 0x1c2, 0, 0);
			} else if (action < 99) {
				if (action == 0x5b) {
					playSe3D__8CGPrgObjFiiiiP3Vec(self, 0x4e2a, 0x32, 0x1c2, 0, 0);
				}
			} else if (action == 0x6b) {
				playSe3D__8CGPrgObjFiiiiP3Vec(self, 0xfdf3, 0x32, 0x1c2, 0, 0);
			}
		}

		if (*(int*)(self + 0x528) == 0x19) {
			changeStat__8CGPrgObjFiii(self, 0, 0, 0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x801329b4
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncGolem()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/801329b4_damagedFuncGolem__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8013296c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncGolem(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8013296c_changeStatFuncGolem__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x8013292c
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::calcBranchFuncGolem(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8013292c_calcBranchFuncGolem__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x80132670
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncGolem()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80132670_frameStatFuncGolem__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80132640
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncArmstrong(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80132640_changeStatFuncArmstrong__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x80132600
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncArmstrong()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80132600_cancelStatFuncArmstrong__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8013256c
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncArmstrong()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8013256c_frameStatFuncArmstrong__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80132538
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncOrcKing()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80132538_cancelStatFuncOrcKing__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x801322dc
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncOrcKing()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/801322dc_frameStatFuncOrcKing__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80132160
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::alwaysFuncOrcKing()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80132160_alwaysFuncOrcKing__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8013215c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncOrcKing()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8013215c_moveFrameFuncOrcKing__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80132158
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncOrcKing()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80132158_moveCancelFuncOrcKing__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80132100
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::calcBranchFuncOrcKing(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80132100_calcBranchFuncOrcKing__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x801320cc
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncGoblinKing()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/801320cc_cancelStatFuncGoblinKing__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8013204c
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncGoblinKing()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8013204c_frameStatFuncGoblinKing__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8013203c
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::calcBranchFuncGoblinKing(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8013203c_calcBranchFuncGoblinKing__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x80132008
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncSaw()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80132008_cancelStatFuncSaw__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80131dd8
 * PAL Size: 560b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncSaw()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80131dd8_frameStatFuncSaw__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80131d04
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::logicFuncSaw()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80131d04_logicFuncSaw__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80131c24
 * PAL Size: 224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncSaw()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80131c24_moveFrameFuncSaw__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80131bd8
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::attackedFuncSaw()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80131bd8_attackedFuncSaw__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8013197c
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncLKShooter()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8013197c_frameStatFuncLKShooter__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80131828
 * PAL Size: 340b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::attackCheckFuncLKShooter(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80131828_attackCheckFuncLKShooter__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x801317f8
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncDragonZombie(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/801317f8_changeStatFuncDragonZombie__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x801316f8
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncDragonZombie()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/801316f8_cancelStatFuncDragonZombie__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8013164c
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncDragonZombie()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8013164c_frameStatFuncDragonZombie__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80131638
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::calcBranchFuncDragonZombie(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80131638_calcBranchFuncDragonZombie__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x80131608
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncCaveWorm(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80131608_changeStatFuncCaveWorm__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x801315d4
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncCaveWorm()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/801315d4_cancelStatFuncCaveWorm__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8013159c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncCaveWorm()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8013159c_frameStatFuncCaveWorm__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80131554
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncLich(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80131554_changeStatFuncLich__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x80131520
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncLich()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80131520_cancelStatFuncLich__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80131294
 * PAL Size: 652b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncLich()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80131294_frameStatFuncLich__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8013127c
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::calcBranchFuncLich(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8013127c_calcBranchFuncLich__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x801311fc
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncTetsukyojin(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/801311fc_changeStatFuncTetsukyojin__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x801311a0
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncTetsukyojin()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/801311a0_cancelStatFuncTetsukyojin__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80130d00
 * PAL Size: 1184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncTetsukyojin()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80130d00_frameStatFuncTetsukyojin__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80130ce4
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::calcBranchFuncTetsukyojin(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80130ce4_calcBranchFuncTetsukyojin__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x80130c88
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncGigasLoad()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80130c88_damagedFuncGigasLoad__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80130c40
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::tgtFuncGigasLoad(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80130c40_tgtFuncGigasLoad__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x80130bf4
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::calcBranchFuncGigasLoad(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80130bf4_calcBranchFuncGigasLoad__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x80130ac8
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncWifeLamia()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80130ac8_frameStatFuncWifeLamia__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80130a64
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncWifeLamia()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80130a64_damagedFuncWifeLamia__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80130a1c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncMolbol(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80130a1c_changeStatFuncMolbol__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x801309e8
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncMolbol()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/801309e8_cancelStatFuncMolbol__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80130898
 * PAL Size: 336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncMolbol()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80130898_frameStatFuncMolbol__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x801307d4
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::initFinishedFuncMeteoParasiteC()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/801307d4_initFinishedFuncMeteoParasiteC__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x801306b8
 * PAL Size: 284b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncMeteoParasiteC()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/801306b8_damagedFuncMeteoParasiteC__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x801302c8
 * PAL Size: 1008b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncMeteoParasiteC()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/801302c8_frameStatFuncMeteoParasiteC__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x801302b8
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::calcBranchFuncMeteoParasiteC(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/801302b8_calcBranchFuncMeteoParasiteC__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x80130224
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::logicFuncMeteoParasiteC()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80130224_logicFuncMeteoParasiteC__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x80130208
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::attackCheckFuncMeteoParasiteC(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/80130208_attackCheckFuncMeteoParasiteC__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x8013004c
 * PAL Size: 444b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::initFinishedFuncMeteoParasite()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8013004c_initFinishedFuncMeteoParasite__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8012ffe4
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncMeteoParasite(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012ffe4_changeStatFuncMeteoParasite__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x8012fcc8
 * PAL Size: 796b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::alwaysFuncMeteoParasite()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012fcc8_alwaysFuncMeteoParasite__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8012fad0
 * PAL Size: 504b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncMeteoParasite()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012fad0_frameStatFuncMeteoParasite__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8012fa20
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::logicFuncMeteoParasite()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012fa20_logicFuncMeteoParasite__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8012f984
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::attackCheckFuncMeteoParasite(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012f984_attackCheckFuncMeteoParasite__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x8012f8bc
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::aiAddDuct(int&)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012f8bc_aiAddDuct__8CGMonObjFRi.c
}

/*
 * --INFO--
 * PAL Address: 0x8012f870
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::initFinishedFuncDuct()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012f870_initFinishedFuncDuct__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8012f7ac
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncDuct()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012f7ac_damagedFuncDuct__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8012f678
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::logicFuncRamoe()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012f678_logicFuncRamoe__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8012f648
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncRamoe(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012f648_changeStatFuncRamoe__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x8012f644
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncRamoe()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012f644_cancelStatFuncRamoe__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8012f598
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncRamoe()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012f598_frameStatFuncRamoe__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8012f534
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::initFinishedFuncLastBoss()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012f534_initFinishedFuncLastBoss__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8012f4b0
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncLastBoss()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012f4b0_damagedFuncLastBoss__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8012f480
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncLastBoss(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012f480_changeStatFuncLastBoss__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x8012f3e8
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncLastBoss()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012f3e8_cancelStatFuncLastBoss__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8012efa8
 * PAL Size: 1088b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncLastBoss()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	const int state = prgObj->m_lastStateId;
	const int stateFrame = prgObj->m_stateFrame;

	if (state == 0x65) {
		if (stateFrame == 0) {
			object->m_bgColMask &= 0xFFF7FFFF;
			prgObj->reqAnim(0x19, 0, 0);

			int pdtNo = -1;
			if (object->m_charaModelHandle != 0 && object->m_charaModelHandle->m_pdtLoadRef != 0) {
				pdtNo = reinterpret_cast<int*>(object->m_charaModelHandle->m_pdtLoadRef)[2];
			}

			prgObj->putParticle((pdtNo << 8) | 0x11, 0, object, 1.0f, 0);
			prgObj->putParticle((pdtNo << 8) | 0x12, 0, object, 1.0f, 0);
			prgObj->playSe3D(0x12913, 0x32, 0x96, 0, 0);
		} else if (stateFrame == 0x29) {
			object->m_bodyEllipsoidRadius = 7.0f;
		} else if (prgObj->isLoopAnim() != 0) {
			object->m_bgColMask |= 0x80000;
			prgObj->changeStat(0, 0, 0);
			object->SetAnimSlot(0x13, 0);
			object->SetAnimSlot(0x15, 1);
			object->SetAnimSlot(0x17, 4);
			mon[0x6B4] = 0;
		}
	} else if (state < 0x65) {
		if (99 < state) {
			if (stateFrame == 0) {
				reinterpret_cast<CGCharaObj*>(this)->damageDelete();
				object->m_bgColMask &= 0xFFF7FFFF;
				prgObj->reqAnim(0x18, 0, 0);

				int pdtNo = -1;
				if (object->m_charaModelHandle != 0 && object->m_charaModelHandle->m_pdtLoadRef != 0) {
					pdtNo = reinterpret_cast<int*>(object->m_charaModelHandle->m_pdtLoadRef)[2];
				}

				prgObj->putParticle((pdtNo << 8) | 0x10, 0, object, 1.0f, 0);
				prgObj->playSe3D(0x12912, 0x32, 0x96, 0, 0);
			} else if (stateFrame == 0x7D) {
				object->m_bodyEllipsoidRadius = 2.0f;
			} else if (prgObj->isLoopAnim() != 0) {
				object->m_bgColMask |= 0x80000;
				object->SetAnimSlot(0x12, 0);
				object->SetAnimSlot(0x14, 1);
				object->SetAnimSlot(0x16, 4);
				prgObj->changeStat(0, 0, 0);
				mon[0x6B4] = 2;
			}
		}
	} else if (state < 0x67) {
		if (stateFrame == 0) {
			int pdtNo = -1;
			if (object->m_charaModelHandle != 0 && object->m_charaModelHandle->m_pdtLoadRef != 0) {
				pdtNo = reinterpret_cast<int*>(object->m_charaModelHandle->m_pdtLoadRef)[2];
			}
			prgObj->putParticle((pdtNo << 8) | 5, *reinterpret_cast<int*>(mon + 0x58C), object, 1.0f, 0x12902);
		} else if (stateFrame == 0x4B) {
			for (int i = 0; i < 4; i++) {
				CGPartyObj* party = Game.game.m_partyObjArr[i];
				if (party != 0) {
					CGPrgObj* partyPrg = reinterpret_cast<CGPrgObj*>(party);
					if (partyPrg->m_lastStateId == 0x24) {
						if (fabs(prgObj->getTargetRot(partyPrg)) < 0.5235987755982988) {
							partyPrg->changeStat(0x25, 0, 0);
						}
					}
				}
			}
		} else if (stateFrame == 200) {
			for (int i = 0; i < 4; i++) {
				CGPartyObj* party = Game.game.m_partyObjArr[i];
				if (party != 0) {
					CGPrgObj* partyPrg = reinterpret_cast<CGPrgObj*>(party);
					if (partyPrg->m_lastStateId == 0x25) {
						partyPrg->changeStat(0x24, 0, 0);
					}
				}
			}
			reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x400);
		}

		reinterpret_cast<CGCharaObj*>(this)->statAttack();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012ef94
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::calcBranchFuncLastBoss(int)
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012ef94_calcBranchFuncLastBoss__8CGMonObjFi.c
}

/*
 * --INFO--
 * PAL Address: 0x8012ef0c
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::logicFuncLastBoss()
{
	// Ghidra reference: resources/ghidra-decomp-1-31-2026/8012ef0c_logicFuncLastBoss__8CGMonObjFv.c
}

/*
 * --INFO--
 * PAL Address: 0x8012e9bc
 * PAL Size: 1360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::teleport(
	int mode, int animId, int startFrame, int blendEndFrame, int seStart, int seEnd, int particleStart, int particleBlend, int particleEnd,
	Vec* teleportPoints, int& teleportIndex, Vec& startPos
)
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	int pdtNo = -1;

	if (object->m_charaModelHandle != 0 && object->m_charaModelHandle->m_pdtLoadRef != 0) {
		pdtNo = reinterpret_cast<int*>(object->m_charaModelHandle->m_pdtLoadRef)[2];
	}

	if (prgObj->m_stateFrame == 0) {
		object->m_bgColMask &= 0xFFF3FFFC;
		*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags) &= 0xEF;
		object->m_groundHitOffset.x = 0.0f;
		object->m_groundHitOffset.y = 0.0f;
		object->m_groundHitOffset.z = 0.0f;

		prgObj->reqAnim(animId, 0, 0);
		prgObj->playSe3D(seStart, 0x32, 0x1C2, 0, 0);
		prgObj->putParticle(particleStart | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), object, 1.0f, 0);

		if (mode == 0) {
			prgObj->putParticle(particleBlend | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), &object->m_worldPosition, 1.0f, 0);
		} else {
			prgObj->putParticle(particleBlend | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), object, 1.0f, 0);
		}
	}

	const int stateFrame = prgObj->m_stateFrame;
	const int blendStartFrame = startFrame + 8;

	if (blendStartFrame < stateFrame) {
		if (stateFrame < blendEndFrame) {
			if (stateFrame <= blendEndFrame + 8) {
				if (stateFrame == blendEndFrame + 1) {
					if (mode == 0) {
						prgObj->putParticle(particleEnd | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), &object->m_worldPosition, 1.0f, 0);
						prgObj->playSe3D(seEnd, 0x32, 0x1C2, 0, 0);
					}

					object->m_bgColMask |= 3;
					*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags) =
						(*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags) & 0xEF) | 0x10;
					object->m_groundHitOffset.x = 0.0f;
					object->m_groundHitOffset.y = 0.0f;
					object->m_groundHitOffset.z = 0.0f;

					if (mode == 1) {
						object->m_displayFlags |= 1;
					}
				}

				const float angle = 3.1415927f * (1.0f - static_cast<float>(stateFrame - blendEndFrame) * 0.125f);
				const float wave = static_cast<float>(cos(angle));
				object->m_rotationX = wave;
				object->m_rotationZ = wave;
				object->m_rotationY = 1.0f + static_cast<float>(sin(angle));

				if (stateFrame == blendEndFrame + 8) {
					object->m_bgColMask |= 0xC0000;
					setAttackAfter__8CGMonObjFi(this, *reinterpret_cast<int*>(mon + 0x560));
				}
			}
		} else {
			if (stateFrame == startFrame + 9) {
				int nextIndex;
				do {
					nextIndex = Rand__5CMathFUl(&Math, 4);
				} while (nextIndex == teleportIndex);

				teleportIndex = nextIndex;
				startPos = object->m_worldPosition;

				if (mode == 1) {
					object->m_displayFlags &= 0xFFFFFFFE;
				}
			}

			const float ratio = static_cast<float>(stateFrame - blendStartFrame) / static_cast<float>(blendEndFrame - blendStartFrame);
			const float blend = 0.5f * (1.0f + static_cast<float>(cos(3.1415927f * ratio)));
			Vec fromPoint;
			Vec fromCurrent;
			Vec blended;

			PSVECScale(&teleportPoints[teleportIndex], &fromPoint, 1.0f - blend);
			PSVECScale(&object->m_worldPosition, &fromCurrent, blend);
			PSVECAdd(&fromCurrent, &fromPoint, &blended);
			object->m_worldPosition = blended;

			if (mode == 1 && stateFrame == blendEndFrame - 0x2A) {
				prgObj->putParticle(particleEnd | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), &teleportPoints[teleportIndex], 1.0f, 0);
				prgObj->playSe3D(seEnd, 0x32, 0x1C2, 0, 0);
			}
		}
	} else if (startFrame <= stateFrame) {
		const float angle = 3.1415927f * static_cast<float>(stateFrame - startFrame) * 0.125f;
		const float wave = static_cast<float>(cos(angle));
		object->m_rotationX = wave;
		object->m_rotationZ = wave;
		object->m_rotationY = 1.0f + static_cast<float>(sin(angle));
	}
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::suikomiSub(CGObject*, float)
{
	// Ghidra reference: not found in resources/ghidra-decomp-1-31-2026
}

/*
 * --INFO--
 * PAL Address: 0x8012e5dc
 * PAL Size: 992b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::suikomi(int endFrame, float zOffset)
{
	CGCharaObj* chara = reinterpret_cast<CGCharaObj*>(this);
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	unsigned char* self = reinterpret_cast<unsigned char*>(this);

	if (prgObj->m_stateFrame == 0) {
		playSe3D__8CGPrgObjFiiiiP3Vec(prgObj, 0xdec0, 0x32, 0x1c2, 0, 0);
		for (int i = 0; i < 4; i++) {
			CGPartyObj* party = Game.game.m_partyObjArr[i];
			if (party != 0) {
				ResetParticleWork__13CFlatRuntime2Fii(CFlat, 0x26, *(int*)(self + 0x58c));
				SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject(CFlat, this);
				SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject(CFlat, party);
				PutParticleWork__13CFlatRuntime2Fv(CFlat);
			}
		}
	}

	if (prgObj->m_stateFrame <= endFrame) {
		for (int i = 0; i < 4; i++) {
			CGPartyObj* party = Game.game.m_partyObjArr[i];
			if (party != 0) {
				float dx = *(float*)(self + 0x15c) - *(float*)((unsigned char*)party + 0x15c);
				float dz =
				    zOffset + (*(float*)(self + 0x164) - *(float*)((unsigned char*)party + 0x164));
				float distSq = dx * dx + dz * dz;
				double dist = (double)distSq;

				if (dist <= (double)FLOAT_80331cf8) {
					if (DOUBLE_80331d10 <= dist) {
						unsigned int exp = (unsigned int)distSq & 0x7f800000;
						int fpClass;
						if (exp == 0x7f800000) {
							fpClass = (((unsigned int)distSq & 0x7fffff) == 0) ? 2 : 1;
						} else if ((exp < 0x7f800000) && (exp == 0)) {
							fpClass = (((unsigned int)distSq & 0x7fffff) == 0) ? 3 : 5;
						} else {
							fpClass = 4;
						}
						if (fpClass == 1) {
							dist = (double)DAT_8032ec20;
						}
					} else {
						dist = (double)DAT_8032ec20;
					}
				} else {
					double inv = 1.0 / sqrt(dist);
					inv = DOUBLE_80331d00 * inv * -(dist * inv * inv - DOUBLE_80331d08);
					inv = DOUBLE_80331d00 * inv * -(dist * inv * inv - DOUBLE_80331d08);
					dist = (double)(float)(dist * DOUBLE_80331d00 * inv *
					                       -(dist * inv * inv - DOUBLE_80331d08));
				}

				if ((double)FLOAT_80331cf8 < dist) {
					float accel = (float)((double)FLOAT_80331d18 / dist) * FLOAT_80331d1c *
					              (float)(dist / (double)FLOAT_80331d20);
					*(float*)((unsigned char*)party + 0x104) += dx * accel;
					*(float*)((unsigned char*)party + 0x10c) += dz * accel;
				}
			}
		}

		if ((Game.game.unk_flat3_0xc7d0 != 0) && (*(int*)(Game.game.unk_flat3_0xc7d0 + 0x550) == 0)) {
			unsigned int target = Game.game.unk_flat3_0xc7d0;
			float dx = *(float*)(self + 0x15c) - *(float*)(target + 0x15c);
			float dz = zOffset + (*(float*)(self + 0x164) - *(float*)(target + 0x164));
			float distSq = dx * dx + dz * dz;
			double dist = (double)distSq;

			if (dist <= (double)FLOAT_80331cf8) {
				if (DOUBLE_80331d10 <= dist) {
					unsigned int exp = (unsigned int)distSq & 0x7f800000;
					int fpClass;
					if (exp == 0x7f800000) {
						fpClass = (((unsigned int)distSq & 0x7fffff) == 0) ? 2 : 1;
					} else if ((exp < 0x7f800000) && (exp == 0)) {
						fpClass = (((unsigned int)distSq & 0x7fffff) == 0) ? 3 : 5;
					} else {
						fpClass = 4;
					}
					if (fpClass == 1) {
						dist = (double)DAT_8032ec20;
					}
				} else {
					dist = (double)DAT_8032ec20;
				}
			} else {
				double inv = 1.0 / sqrt(dist);
				inv = DOUBLE_80331d00 * inv * -(dist * inv * inv - DOUBLE_80331d08);
				inv = DOUBLE_80331d00 * inv * -(dist * inv * inv - DOUBLE_80331d08);
				dist = (double)(float)(dist * DOUBLE_80331d00 * inv *
				                       -(dist * inv * inv - DOUBLE_80331d08));
			}

			if ((double)FLOAT_80331cf8 < dist) {
				float accel = (float)((double)FLOAT_80331d18 / dist) * FLOAT_80331d1c *
				              (float)(dist / (double)FLOAT_80331d20);
				*(float*)(target + 0x104) += dx * accel;
				*(float*)(target + 0x10c) += dz * accel;
			}
		}

		if (prgObj->m_stateFrame == endFrame) {
			chara->endPSlotBit(0x400);
		}
	}

	chara->statAttack();
}


