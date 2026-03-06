#ifndef _FFCC_CGCHARAOBJ_H_
#define _FFCC_CGCHARAOBJ_H_

#include "ffcc/prgobj.h"

class CGObject;
class CGPrgObj;
class CGCharaObj;
class CCombi2Set;
class CGPartyObj;
class CFont;
struct Vec;
class PPPIFPARAM;
class CGObjWork;
class CFlatRuntime2;
class CVector;

void la(CGObject*);
void SAFE_CAST_WORK(CGObjWork*);

class CGCharaObj : public CGPrgObj
{
public:
	struct IgnoreHitSlot
	{
		unsigned char m_flag;
		unsigned char m_pad;
		unsigned short m_timer;
		CGObject* m_source;
	};

	CGCharaObj();
	~CGCharaObj();
	
	void onCreate();
	void onDestroy();
	void ClearAllSta();
	void onChangeStat(int);
	void onCancelStat(int);
	void onFramePostCalc();
	void onFramePreCalc();
	float onAlphaUpdate();
	void endPSlotBit(int);
	void deletePSlotBit(int);
	void onFrameStat();
	void onAnimPoint(int, int);
	void resetIgnoreHit();
	void decIgnoreHit();
	void damageDelete();
	void onHit(int, CGObject*, int, Vec*);
	void onHitParticle(int, int, int, int, Vec*, PPPIFPARAM*);
	int getReplaceStat(int);
	void putHitParticleFromItem(CGPrgObj*, int);
	void setSta(int, int);
	void effective(int, int, CGPrgObj*, int&);
	void calcSta(int, int, CGObject*);
	void addHp(int, CGPrgObj*);
	void calcRegist(int, int, int&, int&, int&, int);
	void onDamage(CGPrgObj*, int, int, int, Vec*);
	void getItemPdt(int, int, int&, int&, int&);
	void putParticleFromItem(int, int, int, Vec*);
	void statShield();
	void statAttack();
	void statDie();
	void statMagic();
	void statKizetsu();
	void onStatMagic();
	void onStatShield();
	void onStatAttack(int);
	void onStatDie();
	void statDamage();
	void statButtobi();
	void onChangePrg(int);
	void calcCastTime(int);
	void onDrawDebug(CFont*, float, float&, float);
	void addSe(int);
	void seDamageDelete();
	void StaticFrame();
	void combi2();
	void sendCombiToScript(CGCharaObj*, int, int);
	void scCheckItem(CCombi2Set*, CGCharaObj*, int);
	void scCheckTime(CCombi2Set*, CGCharaObj*, CGCharaObj*, int);
	int searchCombi(int, CGPartyObj **, int&);
	void enableAttackCol(int, int, int);
	int GetCID();
	void enableDamageCol(int);

	int m_attackAnimId;
	int m_itemId;
	int m_particleSlots[0x16];
	float m_targetDist;
	Vec m_targetDelta;
	unsigned char m_unk5CC[4];
	float m_partyDistance[4];
	Vec m_partyDelta[4];
	float m_partyAngle[4];
	int m_partyRank[4];
	int m_castFrameStart;
	int m_castFrameEnd;
	int m_castFrameCurrent;
	IgnoreHitSlot m_ignoreHit[4];
	unsigned char m_unk65C[4];
	int m_comboFrame;
	int m_comboFramePrev;
	int m_comboState;
	unsigned char m_unk66C[0x18];
	int m_damageParticle;
	int m_unk688;
	float m_pushScale;
	float m_alpha;
	int m_stateResetCounter;
	int m_stateResetLimit;
	int m_stateTick;
	short m_lastBgGroupCopy;
	short m_aStarGroupId;
	int m_castTimeTick;
	unsigned char m_unk6AC[0xC];
};

#endif // _FFCC_CGCHARAOBJ_H_
