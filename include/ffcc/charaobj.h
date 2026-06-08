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

extern int gCGCharaObjCreateSerial;
extern char gCGCharaObjCreateSerialInit;

class CGCharaObj : public CGPrgObj
{
public:
	struct IgnoreHitSlot
	{
		union
		{
			unsigned char m_flag;
			struct
			{
				unsigned char m_flag_80 : 1;
				unsigned char m_flag_lo : 7;
			} m_flagBits;
		};
		unsigned char m_pad;
		signed short m_timer;
		CGObject* m_source;
	};

	CGCharaObj() {}
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
	int onHit(int, CGObject*, int, Vec*);
	void onHitParticle(int, int, int, int, Vec*, PPPIFPARAM*);
	int getReplaceStat(int);
	virtual void onStatDie();
	virtual void onDamage(CGPrgObj*, int, int, int, Vec*);
	virtual void onStatMagic();
	virtual void onStatAttack(int);
	virtual void onStatShield();
	virtual void enableAttackCol(int, int, int);
	virtual void enableDamageCol(int);
	void putHitParticleFromItem(CGPrgObj*, int);
	void setSta(int, int);
	void effective(int, int, CGPrgObj*, int&);
	int calcSta(int, int, CGObject*);
	void addHp(int, CGPrgObj*);
	void calcRegist(int, int, int&, int&, int&, int);
	int getItemPdt(int, int, int&, int&, int&);
	void putParticleFromItem(int, int, int, Vec*);
	void statShield();
	void statAttack();
	void statDie();
	void statMagic();
	void statKizetsu();
	void statDamage();
	void statButtobi();
	void onChangePrg(int);
	int calcCastTime(int);
	void onDrawDebug(CFont*, float, float&, float);
	void addSe(int);
	void seDamageDelete();
	void StaticFrame();
	static void combi2();
	void sendCombiToScript(CGCharaObj*, int, int);
	void scCheckItem(CCombi2Set*, CGCharaObj*, int);
	void scCheckTime(CCombi2Set*, CGCharaObj*, CGCharaObj*, int);
	static int searchCombi(int, CGPartyObj **, int&);
	int GetCID();

	int m_attackAnimId;
	int m_unk554;
	int m_unk558;
	int m_unk55C;
	int m_itemId;
	int m_particleSlots[0x16];
	float m_targetDist;
	Vec m_targetDelta;
	union {
		unsigned char m_unk5CC[4];
		float m_targetAngle;
	};
	float m_partyDistance[4];
	Vec m_partyDelta[4];
	float m_partyAngle[4];
	int m_partyRank[4];
	int m_castFrameStart;
	int m_castFrameEnd;
	int m_castFrameCurrent;
	struct Unk63CBits {
		signed char m_bit80 : 1;
		signed char m_bit40 : 1;
		signed char m_bit20 : 1;
		signed char m_bit10 : 1;
		signed char m_bit08 : 1;
		signed char m_bit04 : 1;
		signed char m_bit02 : 1;
		signed char m_bit01 : 1;
	};
	union {
		int m_unk63C;
		Unk63CBits m_unk63CBits;
	};
	IgnoreHitSlot m_ignoreHit[4];
	int m_comboFrame;
	int m_comboFramePrev;
	int m_comboState;
	Vec m_comboCenter;
	Vec m_comboTarget;
	union {
		int m_damageParticle;
		int m_comboItemState;
	};
	int m_unk688;
	int m_unk68C;
	float m_pushScale;
	float m_alpha;
	union {
		int m_stateResetCounter;
		int m_comboScriptArg;
	};
	union {
		int m_stateResetLimit;
		unsigned int m_comboScriptMode;
	};
	int m_stateTick;
	short m_aStarGroupId;
	short m_unk6A6;
	union {
		int m_castTimeTick;
		int m_comboLinkCount;
	};
	union {
		unsigned char m_unk6AC[0xC];
		CGPrgObj* m_comboLinks[3];
	};
};

STATIC_ASSERT(offsetof(CGCharaObj, m_targetAngle) == 0x5CC);
STATIC_ASSERT(offsetof(CGCharaObj, m_comboCenter) == 0x66C);
STATIC_ASSERT(offsetof(CGCharaObj, m_comboTarget) == 0x678);
STATIC_ASSERT(offsetof(CGCharaObj, m_comboItemState) == 0x684);
STATIC_ASSERT(offsetof(CGCharaObj, m_comboScriptArg) == 0x698);
STATIC_ASSERT(offsetof(CGCharaObj, m_comboScriptMode) == 0x69C);
STATIC_ASSERT(offsetof(CGCharaObj, m_comboLinkCount) == 0x6A8);
STATIC_ASSERT(offsetof(CGCharaObj, m_comboLinks) == 0x6AC);
STATIC_ASSERT(sizeof(CGCharaObj) == 0x6B8);

#endif // _FFCC_CGCHARAOBJ_H_
