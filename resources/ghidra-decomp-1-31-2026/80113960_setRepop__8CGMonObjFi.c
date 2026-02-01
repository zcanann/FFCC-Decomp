// Function: setRepop__8CGMonObjFi
// Entry: 80113960
// Size: 1436 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void setRepop__8CGMonObjFi(CGMonObj *gMonObj,int param_2)

{
  float fVar1;
  ushort uVar2;
  int iVar3;
  CRef *pCVar4;
  void **ppvVar5;
  int iVar6;
  int iVar7;
  void *pvVar8;
  undefined8 uVar9;
  
  ppvVar5 = (gMonObj->gObject).m_scriptHandle;
  pvVar8 = ppvVar5[4];
  if (((param_2 == 0) || (iVar6 = (int)(short)Game.game.m_gameWork.m_optionValue, 8 < iVar6)) ||
     (uVar9 = __shl2i(0,1,ppvVar5[2]), iVar6 = iVar6 * 8,
     (*(uint *)(&CFlat.field_0x12f4 + iVar6) & (uint)uVar9) == 0 &&
     (*(uint *)(&CFlat.field_0x12f0 + iVar6) & (uint)((ulonglong)uVar9 >> 0x20)) == 0)) {
    if (param_2 == 0) {
      *(float *)&gMonObj->field_0x6f8 = (gMonObj->gObject).unk_0x168;
      *(float *)&gMonObj->field_0x6fc = (gMonObj->gObject).unk_0x16C;
      *(float *)&gMonObj->field_0x700 = (gMonObj->gObject).unk_0x170;
      (gMonObj->gObject).m_worldPosition.x = *(float *)&gMonObj->field_0x6f8;
      (gMonObj->gObject).m_worldPosition.y = *(float *)&gMonObj->field_0x6fc;
      (gMonObj->gObject).m_worldPosition.z = *(float *)&gMonObj->field_0x700;
      fVar1 = (float)(gMonObj->gObject).m_bgFlags;
      (gMonObj->gObject).m_rotBaseY = fVar1;
      (gMonObj->gObject).m_rotTargetY = fVar1;
      ppvVar5 = (gMonObj->gObject).m_scriptHandle;
      *(undefined2 *)(ppvVar5 + 7) = *(undefined2 *)((int)ppvVar5 + 0x1a);
      *(undefined4 *)&gMonObj->field_0x6c4 = 0xffffffff;
      *(undefined2 *)&gMonObj->field_0x6e4 = 0;
      *(undefined2 *)&gMonObj->field_0x6e6 = 0;
      *(undefined4 *)&gMonObj->field_0x6c8 = 0;
      *(undefined4 *)&gMonObj->field_0x6cc = 0;
      gMonObj->_bossBranchRelated = 0;
      gMonObj->field_0x6b8 = 0;
      gMonObj->field_0x6b9 = 0;
      gMonObj->field_0x6ba = 0;
      gMonObj->field_0x6bc = 0;
      gMonObj->field_0x6bd = 0;
      gMonObj->field_0x6be = 0;
      *(undefined4 *)&gMonObj->field_0x6f0 = 0;
      *(undefined4 *)&gMonObj->field_0x6f4 = 0;
      gMonObj->field_0x6bf = 0;
      gMonObj->field_0x6c0 = 0;
      gMonObj->field_0x6c2 = 0;
      gMonObj->field_0x6c3 = 0;
      *(undefined4 *)&gMonObj->field_0x6d8 = 0;
      *(undefined4 *)&gMonObj->field_0x6dc = 0;
      gMonObj->field_0x6bb = 0;
      *(undefined4 *)&gMonObj->field_0x704 = 0;
      memset(&gMonObj->field_0x70c,0,0x34);
    }
    (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x90))(gMonObj,0,0,0);
    (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x94))(gMonObj,1);
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
    uVar2 = *(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xfe);
    if (((uVar2 & 0x80) == 0) && ((uVar2 & 0x20) == 0)) {
      if (((uVar2 & 0x40) != 0) || (pvVar8 == (void *)0x39)) {
        *(undefined4 *)&gMonObj->field_0x6d8 = 4;
        *(undefined4 *)&gMonObj->field_0x6dc = 0;
        gMonObj->field_0x6bb = 1;
        (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x94))(gMonObj,0);
        if ((uVar2 & 0x40) != 0) {
          SetAnimSlot__8CGObjectFii(&gMonObj->gObject,10,0);
        }
      }
      if ((uVar2 & 0x200) != 0) {
        changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x36,0,0);
      }
      if (param_2 == 0) {
        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x18,0x32,0x96,0,0);
        putParticle__8CGPrgObjFiiP3Vecfi
                  ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,300,0,
                   &(gMonObj->gObject).m_worldPosition,0);
        fVar1 = FLOAT_803319c0;
        (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0x90002;
        *(float *)&gMonObj->field_0x694 = fVar1;
      }
    }
    else {
      if (param_2 == 0) {
        (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0x10002;
      }
      *(undefined4 *)&gMonObj->field_0x6d8 = 4;
      *(undefined4 *)&gMonObj->field_0x6dc = 0;
      gMonObj->field_0x6bb = 1;
      (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x94))(gMonObj,0);
    }
    if (pvVar8 == (void *)0x55) {
      *(undefined4 *)&gMonObj->field_0x6d8 = 4;
      *(undefined4 *)&gMonObj->field_0x6dc = 0;
      gMonObj->field_0x6bb = 1;
    }
    uVar2 = *(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1a8);
    for (iVar6 = 0; iVar6 < (int)(uint)uVar2; iVar6 = iVar6 + 1) {
      iVar7 = 0;
      if ((int)pvVar8 < 0xa7) {
        if (pvVar8 == (void *)0x9c) {
          iVar7 = 1;
        }
      }
      else if (pvVar8 == (void *)0xa9) {
        iVar7 = 0;
      }
      else if ((int)pvVar8 < 0xa9) {
        iVar7 = 2;
      }
      pCVar4 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar4 == (CRef *)0x0) {
        iVar3 = -1;
      }
      else {
        iVar3 = pCVar4[2].refCount;
      }
      putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,iVar6 + iVar7 + 0x50U | iVar3 << 8,
                 *(int *)&gMonObj->field_0x5a4,&gMonObj->gObject,0);
    }
    endPSlotBit__10CGCharaObjFi(gMonObj,0x20000);
    uVar2 = *(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1aa);
    for (iVar6 = 0; iVar6 < (int)(uint)uVar2; iVar6 = iVar6 + 1) {
      pCVar4 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar4 == (CRef *)0x0) {
        iVar7 = -1;
      }
      else {
        iVar7 = pCVar4[2].refCount;
      }
      putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,iVar6 + 0x5aU | iVar7 << 8,
                 *(int *)&gMonObj->field_0x5a8,&gMonObj->gObject,0);
    }
    if ((*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xfe) & 1) != 0) {
      *(float *)&gMonObj->field_0x694 = FLOAT_803319e8;
      ppvVar5 = (gMonObj->gObject).m_scriptHandle;
      pvVar8 = ppvVar5[4];
      iVar6 = (int)((uint)*(byte *)&(gMonObj->gObject).m_weaponNodeFlags << 0x18) >> 0x1f;
      if (*(short *)((int)ppvVar5[9] + 0xfc) != 0xb) {
        iVar6 = 1;
      }
      endPSlotBit__10CGCharaObjFi(gMonObj,0x1000);
      if (iVar6 == 0) {
        uVar2 = *(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1ae);
      }
      else {
        uVar2 = *(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1ac);
      }
      iVar7 = 0x3c;
      if (iVar6 != 0) {
        iVar7 = 0x46;
      }
      for (iVar6 = 0; iVar6 < (int)(uint)uVar2; iVar6 = iVar6 + 1) {
        pCVar4 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
        if (pCVar4 == (CRef *)0x0) {
          iVar3 = -1;
        }
        else {
          iVar3 = pCVar4[2].refCount;
        }
        putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
                  ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,iVar7 + iVar6 | iVar3 << 8,
                   *(int *)&gMonObj->field_0x594,&gMonObj->gObject,0);
      }
      if (*(short *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xfc) == 0xb) {
        SetTexAnim__8CGObjectFPc(&gMonObj->gObject,&DAT_803319ec);
      }
      if ((int)((uint)*(byte *)&(gMonObj->gObject).m_weaponNodeFlags << 0x18) < 0) {
        if (pvVar8 == (void *)0x83) {
          playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x987a,0x32,0x96,0,0);
        }
        else if (pvVar8 == (void *)0x7f) {
          playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x11585,0x32,0x96,0,0);
        }
      }
      gMonObj->field_0x6ba = 0;
    }
  }
  else {
    *(undefined2 *)(ppvVar5 + 7) = 0;
    (gMonObj->gObject).m_bgColMask = 0;
    (gMonObj->gObject).m_displayFlags = 0;
    *(byte *)&(gMonObj->gObject).m_weaponNodeFlags =
         *(byte *)&(gMonObj->gObject).m_weaponNodeFlags & 0xef;
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x28,0,0);
  }
  return;
}

