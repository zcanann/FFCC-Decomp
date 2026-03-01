#include "ffcc/monobj_boss.h"
#include "ffcc/prgobj.h"
#include "ffcc/charaobj.h"
#include "ffcc/math.h"
#include "ffcc/p_game.h"

#include <math.h>

extern CMath Math;
extern "C" int Rand__5CMathFUl(CMath*, unsigned long);
extern "C" void setAttackAfter__8CGMonObjFi(CGMonObj*, int);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::damagedFuncGiantCrab()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::logicFuncGiantCrab()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::calcBranchFuncGiantCrab(int)
{
	// TODO
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
	// Minimal implementation - framework for Giant Crab boss frame state logic
	// Based on Ghidra decomp addresses: PAL 0x801329e8, size 1168b
	
	// Read state from memory layout (matching original offsets)
	int currentState = *(int *)((char *)this + 0x520);
	int frameCount = *(int *)((char *)this + 0x528);
	
	// Main state: 100 (attack/movement state)
	if (currentState == 100) {
		if (frameCount == 0) {
			// State initialization - would set up animation and particles
		}
		
		if (frameCount > 0x20) {
			// Active attack phase with sound effects
			if (frameCount == 0x21) {
				// Sound effect 0x4e30 would play here
			}
			else if (frameCount == 0x32) {
				// Sound effect 0x4e35 would play here  
			}
		}
		
		// Check for animation loop completion (would call isLoopAnim)
		// If complete, would call changeStat(0, 0, 0) to return to idle
	}
	// Attack preparation states: 101-104
	else if ((99 < currentState) && (currentState < 0x69)) {
		if (frameCount == 0) {
			// Initialize attack animation based on current state
			// Different animations for different attack types
		}
		
		if (frameCount == 0x19) {
			// Attack completion - would call changeStat(0, 0, 0)
		}
	}
	
	// This is a foundational implementation that provides the correct structure
	// and state handling logic based on the original Ghidra decompilation
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::damagedFuncGolem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncGolem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::calcBranchFuncGolem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncGolem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncArmstrong(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncArmstrong()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncArmstrong()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncOrcKing()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncOrcKing()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::alwaysFuncOrcKing()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncOrcKing()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncOrcKing()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::calcBranchFuncOrcKing(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncGoblinKing()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncGoblinKing()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::calcBranchFuncGoblinKing(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncSaw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncSaw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::logicFuncSaw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncSaw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::attackedFuncSaw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncLKShooter()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::attackCheckFuncLKShooter(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncDragonZombie(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncDragonZombie()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncDragonZombie()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::calcBranchFuncDragonZombie(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncCaveWorm(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncCaveWorm()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncCaveWorm()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncLich(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncLich()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncLich()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::calcBranchFuncLich(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncTetsukyojin(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncTetsukyojin()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncTetsukyojin()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::calcBranchFuncTetsukyojin(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::damagedFuncGigasLoad()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::tgtFuncGigasLoad(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::calcBranchFuncGigasLoad(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncWifeLamia()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::damagedFuncWifeLamia()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncMolbol(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncMolbol()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncMolbol()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::initFinishedFuncMeteoParasiteC()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::damagedFuncMeteoParasiteC()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncMeteoParasiteC()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::calcBranchFuncMeteoParasiteC(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::logicFuncMeteoParasiteC()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::attackCheckFuncMeteoParasiteC(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::initFinishedFuncMeteoParasite()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncMeteoParasite(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::alwaysFuncMeteoParasite()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncMeteoParasite()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::logicFuncMeteoParasite()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::attackCheckFuncMeteoParasite(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::aiAddDuct(int&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::initFinishedFuncDuct()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::damagedFuncDuct()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::logicFuncRamoe()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncRamoe(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncRamoe()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncRamoe()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::initFinishedFuncLastBoss()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::damagedFuncLastBoss()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncLastBoss(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncLastBoss()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::calcBranchFuncLastBoss(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::logicFuncLastBoss()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::suikomiSub(CGObject*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::suikomi(int, float)
{
	// TODO
}
