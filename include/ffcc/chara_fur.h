#ifndef _FFCC_CGCHARAOBJ_H_
#define _FFCC_CGCHARAOBJ_H_

class CGObject;
class CGPrgObj;
class CGPartyObj;
class CCombi2Set;
class CCombi2;
class PPPIFPARAM;
class CFont;
class CGObjWork;
class Vec;
class CFlatRuntime2;

void la(CGObject *);
void SAFE_CAST_WORK(CGObjWork *);

class CGCharaObj
{
	CGCharaObj();
	~CGCharaObj();

	void onCreate();
	void onDestroy();
	void ClearAllSta();
	void onChangeStat(int);
	void onCancelStat(int);
	void onFramePostCalc();
	void onFramePreCalc();
	void onAlphaUpdate();
	void endPSlotBit(int);
	void deletePSlotBit(int);
	void onFrameStat();
	void onAnimPoint(int, int);
	void resetIgnoreHit();
	void decIgnoreHit();
	void damageDelete();
	void onHit(int, CGObject *, int, Vec *);
	void onHitParticle(int, int, int, int, Vec *, PPPIFPARAM *);
	void getReplaceStat(int);
	void putHitParticleFromItem(CGPrgObj *, int);
	void setSta(int, int);
	void effective(int, int, CGPrgObj *, int &);
	void calcSta(int, int, CGObject *);
	void addHp(int, CGPrgObj *);
	void calcRegist(int, int, int &, int &, int &, int);
	void onDamage(CGPrgObj *, int, int, int, Vec *);
	void getItemPdt(int, int, int &, int &, int &);
	void putParticleFromItem(int, int, int, Vec *);
	void statShield();
	void statAttack();
	void statDie();
	void statMagic();
	void statKizetsu();
	void onStatMagic();
	void statDamage();
	void statButtobi();
	void onChangePrg(int);
	void calcCastTime(int);
	void onDrawDebug(CFont *, float, float &, float);
	void addSe(int);
	void seDamageDelete();
	void StaticFrame();
	void combi2();
	void sendCombiToScript(CGCharaObj *, int, int);
	void scCheckItem(CCombi2Set *, CGCharaObj *, int);
	void scCheckTime(CCombi2Set *, CGCharaObj *, CGCharaObj *, int);
	void searchCombi(int, CGPartyObj **, int &);
	void enableAttackCol(int, int, int);
	void onStatShield();
	void onStatAttack(int);
	void onStatDie();
	void GetCID();
	void enableDamageCol(int);
};

#endif // _FFCC_CGCHARAOBJ_H_
