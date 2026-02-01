// Function: loadModel__9CGItemObjFv
// Entry: 80124fe0
// Size: 700 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void loadModel__9CGItemObjFv(CGPrgObj *param_1)

{
  ushort uVar1;
  bool bVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  double dVar9;
  
  uVar5 = 0xffffffff;
  iVar6 = 0;
  uVar7 = 0;
  bVar2 = true;
  fVar3 = (param_1->object).m_worldParamA;
  if ((int)fVar3 < 0x18) {
    if (fVar3 == 1.82169e-44) {
      uVar5 = 0x33;
      bVar2 = false;
      goto LAB_80125108;
    }
    if ((int)fVar3 < 0xd) {
      if (fVar3 != 1.54143e-44) {
        if ((int)fVar3 < 0xb) {
          if (9 < (int)fVar3) {
            uVar5 = 8;
            bVar2 = false;
          }
        }
        else {
          uVar5 = 0x27;
          bVar2 = false;
        }
      }
      goto LAB_80125108;
    }
    if ((int)fVar3 < 0x12) {
      if ((int)fVar3 < 0xf) {
        uVar5 = 0x33;
        iVar6 = 1;
        bVar2 = false;
      }
      goto LAB_80125108;
    }
  }
  else if ((fVar3 != 5.04467e-44) &&
          (((0x23 < (int)fVar3 || (0x21 < (int)fVar3)) || ((int)fVar3 < 0x1f)))) goto LAB_80125108;
  uVar7 = 1;
  uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + (int)(param_1->object).m_worldParamB * 0x48 + 2);
  (param_1->object).m_ownerSlot = '\x01';
  uVar5 = uVar1 & 0xfff;
  iVar6 = (int)(uint)uVar1 >> 0xc;
  (param_1->object).m_stateFlags0 = (param_1->object).m_stateFlags0 & 0xf7 | 8;
  (param_1->object).m_moveAnimState = '\0';
  (param_1->object).m_moveAnimSubState = '\0';
  (param_1->object).m_randSeedLo = '\x11';
  (param_1->object).m_randSeedHi = 0x94;
LAB_80125108:
  if (-1 < (int)uVar5) {
    LoadModel__8CGObjectFiUlUli(&param_1->object,3,uVar5,iVar6,uVar7);
    LoadAnim__8CGObjectFPciiiUl(&param_1->object);
    SetAnimSlot__8CGObjectFii(&param_1->object,0,0);
    PlayAnim__8CGObjectFiiiiiPSc(&param_1->object,0,1,0,0xffff,0xffff,0);
  }
  if ((param_1->object).m_worldParamA == 2.52234e-44) {
    DispCharaParts__8CGObjectFi(&param_1->object,0);
    (param_1->object).m_stateFlags0 = (param_1->object).m_stateFlags0 & 0xef | 0x10;
  }
  if (bVar2) {
    iVar6 = 0;
    iVar8 = 0;
    do {
      if ((iVar6 != 0) || (*(short *)&param_1[1].object.base_object.object.m_thisBase != 1)) {
        iVar4 = Game.game.unkCFlatData0[2] + (int)(param_1->object).m_worldParamB * 0x48;
        uVar5 = (uint)*(ushort *)(iVar4 + iVar8 + 0x14);
        if (uVar5 != 0xffff) {
          putParticle__8CGPrgObjFiiP8CGObjectfi
                    ((double)(FLOAT_80331b50 *
                              (float)((double)CONCAT44(0x43300000,(uint)*(ushort *)(iVar4 + 0x10)) -
                                     DOUBLE_80331b60) + FLOAT_80331b4c),param_1,uVar5 | 0x100,
                     (int)param_1[1].object.base_object.object.m_localBase,&param_1->object,0);
        }
      }
      iVar6 = iVar6 + 1;
      iVar8 = iVar8 + 2;
    } while (iVar6 < 3);
  }
  if ((param_1->object).m_worldParamA == 2.84464e-43) {
    dVar9 = (double)RandF__5CMathFf((double)FLOAT_80331b58,&Math);
    (param_1->object).m_moveTimer = (int32_t)(float)((double)FLOAT_80331b54 - dVar9);
    *(byte *)&(param_1->object).m_weaponNodeFlags =
         *(byte *)&(param_1->object).m_weaponNodeFlags & 0xfb;
  }
  param_1->m_flags = param_1->m_flags & 0x7f | 0x80;
  return;
}

