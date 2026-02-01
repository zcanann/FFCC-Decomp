// Function: onFrameAlways__9CGItemObjFv
// Entry: 801254cc
// Size: 384 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFrameAlways__9CGItemObjFv(CGPrgObj *param_1)

{
  double dVar1;
  uint32_t uVar2;
  uint uVar3;
  bool bVar4;
  
  dVar1 = DOUBLE_80331b70;
  uVar2 = param_1[1].object.base_object.object.m_codePos;
  if (uVar2 != 0) {
    uVar3 = uVar2 - 1;
    param_1[1].object.base_object.object.m_codePos = uVar3 & ~((int)uVar3 >> 0x1f);
    (param_1->object).m_bodyEllipsoidRadius =
         (float)param_1[1].object.base_object.object.m_engineObject *
         (float)((double)CONCAT44(0x43300000,
                                  8 - param_1[1].object.base_object.object.m_codePos ^ 0x80000000) -
                dVar1) * FLOAT_80331b68;
  }
  if ((param_1->object).m_worldParamA == 1.4013e-44) {
    if (((((Game.game.m_gameWork.m_gameInitFlag == '\0') ||
          (-1 < (int)((uint)(byte)CFlat._4836_1_ << 0x1c | (uint)((byte)CFlat._4836_1_ >> 4)))) ||
         (-1 < (int)((uint)(byte)CFlat._4836_1_ << 0x1d | (uint)((byte)CFlat._4836_1_ >> 3)))) ||
        ((-1 < (int)((uint)*(byte *)&(param_1->object).m_weaponNodeFlags << 0x18) ||
         (CFlat._4780_4_ != 0)))) || (param_1[1].object.base_object.object.m_id != 0)) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
    if ((bVar4) && (CFlat._66604_4_ == 0)) {
      CFlat._66604_4_ = GetFreeParticleSlot__13CFlatRuntime2Fv();
      putParticleTrace__8CGPrgObjFiiP8CGObjectfi
                (SUB84((double)FLOAT_80331b18,0),param_1,0x141,CFlat._66604_4_,&param_1->object,0);
    }
    else if ((!bVar4) && (CFlat._66604_4_ != 0)) {
      EndParticleSlot__13CFlatRuntime2Fii((CFlatRuntime2 *)&CFlat,CFlat._66604_4_);
      CFlat._66604_4_ = 0;
    }
    return;
  }
  return;
}

