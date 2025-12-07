#ifndef _FFCC_CGOBJECT_H_
#define _FFCC_CGOBJECT_H_

#include "ffcc/baseobj.h"
#include "ffcc/p_chara.h"

#include <dolphin/types.h>
#include <dolphin/mtx.h>

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
    virtual int GetCID();     // vtable entry 0x10
	virtual void onCreate();  // vtable entry 0x1c
	virtual void onDestroy(); // vtable entry 0x20
    virtual void onDraw();    // vtable entry 0x28

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
    void Move(Vec*, float, int, int, int, int, int);
    void MoveVector(Vec*, float, int, int, int, int);
    void moveVector(Vec*, float, int);
    void moveVectorH(Vec*, float, int);
    void moveVectorRot(float, float, float, int);
    void moveVectorHRot(float, float, float, int);
    void CCClass(int, int, float, Vec*, float);
    void CCClassRot(int, int, float, float, float, float);
    void Attach(CGObject*, char*, Vec*);
    void Detach();
    void DispCharaParts(int);
    void SetAttackCol(int, char*, float, Vec*);
    void SetDamageCol(int, char*, float, float, Vec*);
    void boundCheck();
    void Turn(float, int);
    void HitParticle(int, int, int, int, Vec*, PPPIFPARAM*);
    void SetClassWork(int, int);
    void SetTexAnim(char*);
    void LookAt(CGObject*, char*);
    void InitWork(int);
    void LoadModel(int, unsigned long, unsigned long, int);
    void LoadWeapon(int, int);
    void LoadShield(int);
    void LoadAnim(char*, int, int, int, unsigned long);
    void FreeAnim(int);
    bool IsLoopAnim(int mode);
    void IsAnimFinished(int);
    void CancelAnim(int);
    void PlayAnim(int, int, int, int, int, char*);
    void SetDispItemName(int);
    void DrawDebug(CFont*);
    void SetPosBG(Vec*, int);
    void ResetDynamics();
    void CalcSphereNearPos(float, float, Vec&);
    void ResetAnimPoint(int);
    void AddAnimPoint(int, int, int);
    void SetAnimSlot(int, int);
    void CalcSafePos(int, CGObject*, Vec*);
    void PutDropItem();
    bool IsDispRader();
    void onHit(int, CGObject*, int, Vec*);
    void onAnimPoint(int, int);
    void onAlphaUpdate();
    void onHitParticle(int, int, int, int, Vec*, PPPIFPARAM*);
    void onDrawDebug(CFont*, float, float&, float);

    struct AttackCol
    {
        Vec m_localStart;       // 0x00-0x0C
        Vec m_localEnd;         // 0x0C-0x18
        Vec m_worldPosition;    // 0x18-0x24
        float m_radius;         // 0x24
        float m_radius2;        // 0x28
        unsigned int m_hitMask; // 0x2C
    };

    struct DamageCol
    {
        Vec m_localPosition;    // 0x00-0x0C
        Vec m_worldPosition;    // 0x0C-0x18
        float m_innerRadius;    // 0x18
        float m_outerRadius;    // 0x1C
        unsigned int m_hitMask; // 0x20
        int m_active;           // 0x24
    };

    unsigned char m_stateFlags0;      // 0x50
    char m_ownerType;                 // 0x51
    unsigned char m_classWorkIndex;   // 0x52
    unsigned char m_ownerSlot;        // 0x53
    unsigned char m_moveMode;         // 0x54
    unsigned char m_moveModePrevious; // 0x55
    void** m_scriptHandle;            // 0x58
    unsigned int m_objectFlags;       // 0x5C
    unsigned int m_displayFlags;      // 0x60
    Qtrn m_projection;                // 0x64
    float m_screenDepth;              // 0x74
    float m_bounceFactor;             // 0x78
    float m_jumpLandingDampening;     // 0x7C
    float m_gravityY;                 // 0x80
    Qtrn m_bgCollisionQtrn;           // 0x84
    unsigned char m_moveAnimState;    // 0x94
    unsigned char m_moveAnimSubState; // 0x95
    unsigned char m_randSeedLo;       // 0x96
    unsigned char m_randSeedHi;       // 0x97
    unsigned char m_lastMapIdHit;     // 0x98
    unsigned char m_lastMapIdExtra;   // 0x99
    unsigned short m_weaponNodeFlags; // 0x9A
    unsigned short m_shieldNodeFlags; // 0x9C
    unsigned short m_animStartFrame;  // 0x9E
    unsigned short m_animEndFrame;    // 0xA0
    unsigned short m_pushTimer;       // 0xA2
    unsigned short m_lookAtNodeIndex; // 0xA4
    unsigned short unk_0xA6;          // 0xA6
    CCharaPcs::CHandle* m_modelHandle;  // 0xA8
    CCharaPcs::CHandle* m_weaponHandle; // 0xAC
    CCharaPcs::CHandle* m_shieldHandle; // 0xB0
    Vec m_velocity;                   // 0xB4
    Vec m_acceleration;               // 0xC0
    Vec m_jumpVelocity;               // 0xCC
    float m_stepHeight;               // 0xD8
    unsigned char m_animQueueFlags;   // 0xDC
    unsigned char m_animQueuePos;     // 0xDD
    char m_animQueue[4];              // 0xDE
    unsigned char m_animStateMisc;    // 0xE2
    char m_currentAnimSlot;           // 0xE3
    char m_animSlotSel;               // 0xE4
    unsigned char m_dispItemTimer;    // 0xE5
    unsigned char m_pushParamA;       // 0xE6
    unsigned char m_pushParamB;       // 0xE7
    short m_lastBgGroup;              // 0xE8
    short m_weaponAttachNode;         // 0xEA
    short m_shieldAttachNodeIndex;    // 0xEC
    short m_animExtraIndex;           // 0xEE
    short m_collisionPushTimer;       // 0xF0
    short m_collisionPushTimerMax;    // 0xF2
    short m_lookAtTargetNodeIndex;    // 0xF4
    short m_lookAtReserved;           // 0xF6
    CCharaPcs::CHandle* m_charaModelHandle;  // 0xF8
    CCharaPcs::CHandle* m_weaponModelHandle; // 0xFC
    CCharaPcs::CHandle* m_shieldModelHandle; // 0x100
    Vec  m_groundHitOffset;           // 0x104
    Vec  m_bodyOffset;                // 0x110
    Vec  m_jumpOffset;                // 0x11C
    Vec  m_moveOffset;                // 0x128
    float m_capsuleHalfHeight;        // 0x134
    Vec  m_extraMoveVec;              // 0x138
    float m_bodyEllipsoidRadius;      // 0x144
    float m_bodyEllipsoidOffset;      // 0x148
    float m_bodyEllipsoidAspect;      // 0x14C
    float m_bodyColRadius;            // 0x150
    float m_attackColRadius;          // 0x154
    float m_nearColRadius;            // 0x158
    Vec  m_worldPosition;             // 0x15C
    float unk_0x168;                  // 0x168
    float unk_0x16C;                  // 0x16C
    float unk_0x170;                  // 0x170
    float m_rotationX;                // 0x174
    float m_rotationY;                // 0x178
    float m_rotationZ;                // 0x17C
    unsigned int m_attrFlags;         // 0x180
    float unk_0x184;                  // 0x184
    float unk_0x188;                  // 0x188
    CGObject* m_attachOwner;          // 0x18C
    int m_attachNode;                 // 0x190
    Vec  m_attachLocal;               // 0x194
    float m_moveBaseSpeed;            // 0x1A0
    float m_rotBaseX;                 // 0x1A4
    float m_rotBaseY;                 // 0x1A8
    float m_rotBaseZ;                 // 0x1AC
    float m_rotTargetX;               // 0x1B0
    float m_rotTargetY;               // 0x1B4
    float m_rotTargetZ;               // 0x1B8
    unsigned int m_bgFlags;           // 0x1BC
    unsigned int m_bgColMask;         // 0x1C0
    Vec m_moveVec;                    // 0x1C4
    float m_moveSpeed;                // 0x1D0
    int m_moveTimer;                  // 0x1D4
    unsigned int m_turnFrames;        // 0x1D8
    AttackCol m_attackColliders[8];   // 0x1DC
    DamageCol m_damageColliders[8];   // 0x35C
    float m_animPhase;                // 0x49C
    float m_turnSpeed;                // 0x4A0
    float m_turnBaseSpeed;            // 0x4A4
    float m_frontHitAngle;            // 0x4A8
    CGObject* m_lookAtTarget;         // 0x4AC
    float m_lookAtTimer;              // 0x4B0
    float m_stepSlopeLimit;           // 0x4B4
    float m_bgDownDist;               // 0x4B8
    float m_bgCharmFactor;            // 0x4BC
    float m_bgAttrValue;              // 0x4C0
    float m_animBlend;                // 0x4C4
    unsigned char m_lastBgAttr[4];    // 0x4C8
    Vec m_radiusCtrl;                 // 0x4CC
    Vec m_radiusCtrlVel;              // 0x4D8
    float m_groundFriction;           // 0x4E4
    Vec m_hitNormal;                  // 0x4E8
    float m_groundSlide;              // 0x4F4
    float m_worldParam;               // 0x4F8
    unsigned char m_worldMode[4];     // 0x4FC
    float m_worldParamA;              // 0x500
    float m_worldParamB;              // 0x504
    float m_lookAtAccumYaw;           // 0x508
    float m_lookAtAccumPitch;         // 0x50C
    unsigned short m_dropItemCodes[4]; // 0x510
};

#endif // _FFCC_CGOBJECT_H_
