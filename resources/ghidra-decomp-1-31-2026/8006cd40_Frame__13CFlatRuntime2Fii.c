// Function: Frame__13CFlatRuntime2Fii
// Entry: 8006cd40
// Size: 2652 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 Frame__13CFlatRuntime2Fii(CFlatRuntime *flatRuntime2,undefined4 param_2,int param_3)

{
  byte bVar1;
  uint uVar2;
  CGBaseObj *pCVar3;
  CGObject *pCVar4;
  int iVar5;
  double dVar6;
  undefined auStack_48 [60];
  
  DumpMapFile__7CSystemFPv((CSystem *)auStack_48);
  if (param_3 == 0) {
    StaticFrame__10CGCharaObjFv();
    CheckGameOver__10CGPartyObjFv();
    Frame__12CFlatRuntimeFii(flatRuntime2,param_2);
    for (pCVar3 = *(CGBaseObj **)(CFlat._2288_4_ + 0x24); pCVar3 != (CGBaseObj *)&CFlat.field_0x8cc;
        pCVar3 = (CGBaseObj *)(pCVar3->object).m_next) {
      if (-1 < (pCVar3->object).m_classIndex) {
        bVar1 = (pCVar3->object).m_flags;
        if (((-1 < (int)((uint)bVar1 << 0x18)) &&
            (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
           (uVar2 = (**(code **)((int)(pCVar3->object).m_vtable + 0xc))(pCVar3), (uVar2 & 5) == 5))
        goto LAB_8006ce8c;
      }
    }
    pCVar3 = (CGBaseObj *)0x0;
LAB_8006ce8c:
    if (pCVar3 != (CGBaseObj *)0x0) {
      Frame__9CGBaseObjFv(pCVar3);
      for (pCVar3 = (CGBaseObj *)(pCVar3->object).m_next; pCVar3 != (CGBaseObj *)&CFlat.field_0x8cc;
          pCVar3 = (CGBaseObj *)(pCVar3->object).m_next) {
        if (-1 < (pCVar3->object).m_classIndex) {
          bVar1 = (pCVar3->object).m_flags;
          if (((-1 < (int)((uint)bVar1 << 0x18)) &&
              (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
             (uVar2 = (**(code **)((int)(pCVar3->object).m_vtable + 0xc))(pCVar3), (uVar2 & 5) == 5)
             ) goto LAB_8006ce8c;
        }
      }
      pCVar3 = (CGBaseObj *)0x0;
      goto LAB_8006ce8c;
    }
  }
  else if (param_3 == 1) {
    Reset__10CStopWatchFv(auStack_48);
    Start__10CStopWatchFv(auStack_48);
    for (pCVar4 = *(CGObject **)(CFlat._2288_4_ + 0x24); pCVar4 != (CGObject *)&CFlat.field_0x8cc;
        pCVar4 = (CGObject *)(pCVar4->base_object).object.m_next) {
      if (-1 < (pCVar4->base_object).object.m_classIndex) {
        bVar1 = (pCVar4->base_object).object.m_flags;
        if (((-1 < (int)((uint)bVar1 << 0x18)) &&
            (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
           (uVar2 = (**(code **)((int)(pCVar4->base_object).object.m_vtable + 0xc))(pCVar4),
           (uVar2 & 5) == 5)) goto LAB_8006cfac;
      }
    }
    pCVar4 = (CGObject *)0x0;
LAB_8006cfac:
    if (pCVar4 != (CGObject *)0x0) {
      move__8CGObjectFv(pCVar4);
      for (pCVar4 = (CGObject *)(pCVar4->base_object).object.m_next;
          pCVar4 != (CGObject *)&CFlat.field_0x8cc;
          pCVar4 = (CGObject *)(pCVar4->base_object).object.m_next) {
        if (-1 < (pCVar4->base_object).object.m_classIndex) {
          bVar1 = (pCVar4->base_object).object.m_flags;
          if (((-1 < (int)((uint)bVar1 << 0x18)) &&
              (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
             (uVar2 = (**(code **)((int)(pCVar4->base_object).object.m_vtable + 0xc))(pCVar4),
             (uVar2 & 5) == 5)) goto LAB_8006cfac;
        }
      }
      pCVar4 = (CGObject *)0x0;
      goto LAB_8006cfac;
    }
    Stop__10CStopWatchFv(auStack_48);
    dVar6 = (double)Get__10CStopWatchFv(auStack_48);
    CFlat._4920_4_ = (undefined4)((double)(float)CFlat._4920_4_ + dVar6);
    Reset__10CStopWatchFv(auStack_48);
    Start__10CStopWatchFv(auStack_48);
    for (iVar5 = *(int *)(CFlat._2288_4_ + 0x24); iVar5 != -0x7fd657d4;
        iVar5 = *(int *)(iVar5 + 0x24)) {
      if (-1 < *(short *)(iVar5 + 0x14)) {
        bVar1 = *(byte *)(iVar5 + 0x38);
        if (((-1 < (int)((uint)bVar1 << 0x18)) &&
            (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
           (uVar2 = (**(code **)(*(int *)(iVar5 + 0x48) + 0xc))(iVar5), (uVar2 & 5) == 5))
        goto LAB_8006d0d8;
      }
    }
    iVar5 = 0;
LAB_8006d0d8:
    if (iVar5 != 0) {
      objectCollision__8CGObjectFv(iVar5);
      for (iVar5 = *(int *)(iVar5 + 0x24); iVar5 != -0x7fd657d4; iVar5 = *(int *)(iVar5 + 0x24)) {
        if (-1 < *(short *)(iVar5 + 0x14)) {
          bVar1 = *(byte *)(iVar5 + 0x38);
          if (((-1 < (int)((uint)bVar1 << 0x18)) &&
              (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
             (uVar2 = (**(code **)(*(int *)(iVar5 + 0x48) + 0xc))(iVar5), (uVar2 & 5) == 5))
          goto LAB_8006d0d8;
        }
      }
      iVar5 = 0;
      goto LAB_8006d0d8;
    }
    Stop__10CStopWatchFv(auStack_48);
    dVar6 = (double)Get__10CStopWatchFv(auStack_48);
    CFlat._4928_4_ = (undefined4)((double)(float)CFlat._4928_4_ + dVar6);
    Reset__10CStopWatchFv(auStack_48);
    Start__10CStopWatchFv(auStack_48);
    for (iVar5 = *(int *)(CFlat._2288_4_ + 0x24); iVar5 != -0x7fd657d4;
        iVar5 = *(int *)(iVar5 + 0x24)) {
      if (-1 < *(short *)(iVar5 + 0x14)) {
        bVar1 = *(byte *)(iVar5 + 0x38);
        if (((-1 < (int)((uint)bVar1 << 0x18)) &&
            (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
           (uVar2 = (**(code **)(*(int *)(iVar5 + 0x48) + 0xc))(iVar5), (uVar2 & 5) == 5))
        goto LAB_8006d204;
      }
    }
    iVar5 = 0;
LAB_8006d204:
    if (iVar5 != 0) {
      bgCollision__8CGObjectFv(iVar5);
      for (iVar5 = *(int *)(iVar5 + 0x24); iVar5 != -0x7fd657d4; iVar5 = *(int *)(iVar5 + 0x24)) {
        if (-1 < *(short *)(iVar5 + 0x14)) {
          bVar1 = *(byte *)(iVar5 + 0x38);
          if (((-1 < (int)((uint)bVar1 << 0x18)) &&
              (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
             (uVar2 = (**(code **)(*(int *)(iVar5 + 0x48) + 0xc))(iVar5), (uVar2 & 5) == 5))
          goto LAB_8006d204;
        }
      }
      iVar5 = 0;
      goto LAB_8006d204;
    }
    Stop__10CStopWatchFv(auStack_48);
    dVar6 = (double)Get__10CStopWatchFv(auStack_48);
    CFlat._4924_4_ = (undefined4)((double)(float)CFlat._4924_4_ + dVar6);
    Reset__10CStopWatchFv(auStack_48);
    Start__10CStopWatchFv(auStack_48);
    for (iVar5 = *(int *)(CFlat._2288_4_ + 0x24); iVar5 != -0x7fd657d4;
        iVar5 = *(int *)(iVar5 + 0x24)) {
      if (-1 < *(short *)(iVar5 + 0x14)) {
        bVar1 = *(byte *)(iVar5 + 0x38);
        if (((-1 < (int)((uint)bVar1 << 0x18)) &&
            (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
           (uVar2 = (**(code **)(*(int *)(iVar5 + 0x48) + 0xc))(iVar5), (uVar2 & 5) == 5))
        goto LAB_8006d330;
      }
    }
    iVar5 = 0;
LAB_8006d330:
    if (iVar5 != 0) {
      update__8CGObjectFv(iVar5);
      for (iVar5 = *(int *)(iVar5 + 0x24); iVar5 != -0x7fd657d4; iVar5 = *(int *)(iVar5 + 0x24)) {
        if (-1 < *(short *)(iVar5 + 0x14)) {
          bVar1 = *(byte *)(iVar5 + 0x38);
          if (((-1 < (int)((uint)bVar1 << 0x18)) &&
              (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
             (uVar2 = (**(code **)(*(int *)(iVar5 + 0x48) + 0xc))(iVar5), (uVar2 & 5) == 5))
          goto LAB_8006d330;
        }
      }
      iVar5 = 0;
      goto LAB_8006d330;
    }
    Stop__10CStopWatchFv(auStack_48);
    dVar6 = (double)Get__10CStopWatchFv(auStack_48);
    CFlat._4932_4_ = (undefined4)((double)(float)CFlat._4932_4_ + dVar6);
    Reset__10CStopWatchFv(auStack_48);
    Start__10CStopWatchFv(auStack_48);
    for (iVar5 = *(int *)(CFlat._2288_4_ + 0x24); iVar5 != -0x7fd657d4;
        iVar5 = *(int *)(iVar5 + 0x24)) {
      if (-1 < *(short *)(iVar5 + 0x14)) {
        bVar1 = *(byte *)(iVar5 + 0x38);
        if (((-1 < (int)((uint)bVar1 << 0x18)) &&
            (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
           (uVar2 = (**(code **)(*(int *)(iVar5 + 0x48) + 0xc))(iVar5), (uVar2 & 5) == 5))
        goto LAB_8006d45c;
      }
    }
    iVar5 = 0;
LAB_8006d45c:
    if (iVar5 != 0) {
      hit__8CGObjectFv(iVar5);
      for (iVar5 = *(int *)(iVar5 + 0x24); iVar5 != -0x7fd657d4; iVar5 = *(int *)(iVar5 + 0x24)) {
        if (-1 < *(short *)(iVar5 + 0x14)) {
          bVar1 = *(byte *)(iVar5 + 0x38);
          if (((-1 < (int)((uint)bVar1 << 0x18)) &&
              (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
             (uVar2 = (**(code **)(*(int *)(iVar5 + 0x48) + 0xc))(iVar5), (uVar2 & 5) == 5))
          goto LAB_8006d45c;
        }
      }
      iVar5 = 0;
      goto LAB_8006d45c;
    }
    Stop__10CStopWatchFv(auStack_48);
    dVar6 = (double)Get__10CStopWatchFv(auStack_48);
    CFlat._4936_4_ = (undefined4)((double)(float)CFlat._4936_4_ + dVar6);
    for (pCVar4 = *(CGObject **)(CFlat._2288_4_ + 0x24); pCVar4 != (CGObject *)&CFlat.field_0x8cc;
        pCVar4 = (CGObject *)(pCVar4->base_object).object.m_next) {
      if (-1 < (pCVar4->base_object).object.m_classIndex) {
        bVar1 = (pCVar4->base_object).object.m_flags;
        if (((-1 < (int)((uint)bVar1 << 0x18)) &&
            (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
           (uVar2 = (**(code **)((int)(pCVar4->base_object).object.m_vtable + 0xc))(pCVar4),
           (uVar2 & 5) == 5)) goto LAB_8006d578;
      }
    }
    pCVar4 = (CGObject *)0x0;
LAB_8006d578:
    if (pCVar4 != (CGObject *)0x0) {
      copy__8CGObjectFv(pCVar4);
      for (pCVar4 = (CGObject *)(pCVar4->base_object).object.m_next;
          pCVar4 != (CGObject *)&CFlat.field_0x8cc;
          pCVar4 = (CGObject *)(pCVar4->base_object).object.m_next) {
        if (-1 < (pCVar4->base_object).object.m_classIndex) {
          bVar1 = (pCVar4->base_object).object.m_flags;
          if (((-1 < (int)((uint)bVar1 << 0x18)) &&
              (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
             (uVar2 = (**(code **)((int)(pCVar4->base_object).object.m_vtable + 0xc))(pCVar4),
             (uVar2 & 5) == 5)) goto LAB_8006d578;
        }
      }
      pCVar4 = (CGObject *)0x0;
      goto LAB_8006d578;
    }
  }
  else {
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    GXSetZCompLoc(0);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
    GXSetZMode(1,3,1);
    GXSetCullMode(1);
    GXSetNumTevStages(1);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
    GXSetNumChans(1);
    GXSetChanCtrl(0,0,0,0,0,2,1);
    GXSetChanCtrl(2,0,0,0,0,2,2);
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    drawAStar__6CAStarFv((CAStar *)&DbgMenuPcs.field_0x2a5c);
    for (pCVar3 = *(CGBaseObj **)(CFlat._2288_4_ + 0x24); pCVar3 != (CGBaseObj *)&CFlat.field_0x8cc;
        pCVar3 = (CGBaseObj *)(pCVar3->object).m_next) {
      if (-1 < (pCVar3->object).m_classIndex) {
        bVar1 = (pCVar3->object).m_flags;
        if (((-1 < (int)((uint)bVar1 << 0x18)) &&
            (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
           (uVar2 = (**(code **)((int)(pCVar3->object).m_vtable + 0xc))(pCVar3), (uVar2 & 1) == 1))
        goto LAB_8006d768;
      }
    }
    pCVar3 = (CGBaseObj *)0x0;
LAB_8006d768:
    if (pCVar3 != (CGBaseObj *)0x0) {
      Draw__9CGBaseObjFv(pCVar3);
      for (pCVar3 = (CGBaseObj *)(pCVar3->object).m_next; pCVar3 != (CGBaseObj *)&CFlat.field_0x8cc;
          pCVar3 = (CGBaseObj *)(pCVar3->object).m_next) {
        if (-1 < (pCVar3->object).m_classIndex) {
          bVar1 = (pCVar3->object).m_flags;
          if (((-1 < (int)((uint)bVar1 << 0x18)) &&
              (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
             (uVar2 = (**(code **)((int)(pCVar3->object).m_vtable + 0xc))(pCVar3), (uVar2 & 1) == 1)
             ) goto LAB_8006d768;
        }
      }
      pCVar3 = (CGBaseObj *)0x0;
      goto LAB_8006d768;
    }
  }
  __ct__10CStopWatchFPc(auStack_48,0xffffffff);
  return 1;
}

