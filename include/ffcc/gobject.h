#ifndef _FFCC_CGOBJECT_H_
#define _FFCC_CGOBJECT_H_

#include "ffcc/baseobj.h"

struct Vec;
class Vec2d;
class CFont;
class PPPIFPARAM;
class CCameraPcs;
class CMapPcs;
class CGObject;
class CGBaseObj;

class CGObject : public CGBaseObj
{
public:
    virtual void onCreate();
    virtual void onDestroy();
    virtual void onDraw();
    virtual int GetCID();
    void move();
    void objectCollision();
    void bgCollision();
    void bgNormalCollision();
    void bgWorldCollision();
    void bgAttribCollision();
    void bgShadeCollision();
    void hit();
    void update();
    void copy();
    void CancelMove(int);
    void Move(Vec *, float, int, int, int, int, int);
    void MoveVector(Vec *, float, int, int, int, int);
    void moveVector(Vec *, float, int);
    void moveVectorH(Vec *, float, int);
    void moveVectorRot(float, float, float, int);
    void moveVectorHRot(float, float, float, int);
    void CCClass(int, int, float, Vec *, float);
    void CCClassRot(int, int, float, float, float, float);
    void Attach(CGObject *, char *, Vec *);
    void Detach();
    void DispCharaParts(int);
    void SetAttackCol(int, char *, float, Vec *);
    void SetDamageCol(int, char *, float, float, Vec *);
    void boundCheck();
    void Turn(float, int);
    void HitParticle(int, int, int, int, Vec *, PPPIFPARAM *);
    void SetClassWork(int, int);
    void SetTexAnim(char *);
    void LookAt(CGObject *, char *);
    void InitWork(int);
    void LoadModel(int, unsigned long, unsigned long, int);
    void LoadWeapon(int, int);
    void LoadShield(int);
    void LoadAnim(char *, int, int, int, unsigned long);
    void FreeAnim(int);
    void IsLoopAnim(int);
    void IsAnimFinished(int);
    void CancelAnim(int);
    void PlayAnim(int, int, int, int, int, char *);
    void SetDispItemName(int);
    void DrawDebug(CFont *);
    void SetPosBG(Vec *, int);
    void ResetDynamics();
    void CalcSphereNearPos(float, float, Vec &);
    void ResetAnimPoint(int);
    void AddAnimPoint(int, int, int);
    void SetAnimSlot(int, int);
    void CalcSafePos(int, CGObject *, Vec *);
    void PutDropItem();
    void IsDispRader();
    void IsHChara();
    void onHit(int, CGObject *, int, Vec *);
    void IsHShield();
    void IsHWeapon();
    void onAnimPoint(int, int);
    void onAlphaUpdate();
    void onHitParticle(int, int, int, int, Vec *, PPPIFPARAM *);
    void onDrawDebug(CFont *, float, float &, float);
};

#endif // _FFCC_CGOBJECT_H_
