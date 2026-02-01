// Function: onFramePostCalc__10CGCharaObjFv
// Entry: 80112618
// Size: 952 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFramePostCalc__10CGCharaObjFv(CGCharaObj *param_1)

{
  bool bVar1;
  ushort uVar2;
  uint uVar3;
  short sVar4;
  ushort uVar5;
  int iVar6;
  void **ppvVar7;
  int iVar8;
  int iVar9;
  
  ppvVar7 = (param_1->gPrgObj).object.m_scriptHandle;
  if (*(short *)((int)ppvVar7 + 0x42) != 0) {
    iVar6 = *(int *)&param_1->field_0x6a0;
    if ((iVar6 != 0) &&
       (iVar6 == (iVar6 / (int)(uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x3a)) *
                 (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x3a))) {
      if ((1 < *(ushort *)(ppvVar7 + 7)) &&
         (-1 < (int)((uint)(byte)CFlat._4836_1_ << 0x1a | (uint)((byte)CFlat._4836_1_ >> 6)))) {
        playSe3D__8CGPrgObjFiiiiP3Vec(&param_1->gPrgObj,0x19,0x32,0x96,0,0);
        addHp__10CGCharaObjFiP8CGPrgObj(param_1,0xffffffff,(CGPrgObj *)0x0);
      }
    }
  }
  iVar6 = 0;
  iVar9 = 0;
  do {
    iVar8 = *(ushort *)((int)(param_1->gPrgObj).object.m_scriptHandle + iVar9 + 0x3e) - 1;
    if ((iVar8 != 0) && (iVar6 == 2)) {
      *(int *)&param_1->field_0x6a0 = *(int *)&param_1->field_0x6a0 + 1;
    }
    uVar3 = (**(code **)((int)(param_1->gPrgObj).object.base_object.object.m_vtable + 0xc))(param_1)
    ;
    if (((uVar3 & 0x6d) == 0x6d) &&
       (((((iVar6 == 0 || (iVar6 == 4)) || (iVar6 == 9)) || (iVar6 == 3)) && (0 < iVar8)))) {
      bVar1 = false;
      uVar3 = (uint)(char)(param_1->gPrgObj).object.m_animStateMisc;
      if (Pad._452_4_ == 0) {
        if (uVar3 == 0) {
          if (Pad._448_4_ != -1) goto LAB_80112780;
        }
      }
      else {
LAB_80112780:
        bVar1 = true;
      }
      if (bVar1) {
        uVar5 = 0;
      }
      else {
        uVar5 = *(ushort *)
                 (&Pad.field_0x8 +
                 (uVar3 & ~((int)~(Pad._448_4_ - uVar3 | uVar3 - Pad._448_4_) >> 0x1f)) * 0x54);
      }
      if ((MiniGamePcs._25732_4_ & 0x100) != 0) {
        bVar1 = false;
        if (Pad._452_4_ == 0) {
          if (uVar3 == 0) {
            if (Pad._448_4_ != -1) goto LAB_801127f0;
          }
        }
        else {
LAB_801127f0:
          bVar1 = true;
        }
        if (bVar1) {
          uVar2 = 0;
        }
        else {
          uVar2 = *(ushort *)
                   (&Pad.field_0x10 +
                   (uVar3 & ~((int)~(Pad._448_4_ - uVar3 | uVar3 - Pad._448_4_) >> 0x1f)) * 0x54);
        }
        uVar5 = uVar5 | uVar2;
      }
      if ((uVar5 & 0xf) != 0) {
        iVar8 = iVar8 - (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x3c);
        Printf__7CSystemFPce(&System,&DAT_801dc940);
      }
    }
    setSta__10CGCharaObjFii(param_1,iVar6,iVar8);
    iVar6 = iVar6 + 1;
    iVar9 = iVar9 + 2;
    if (0x26 < iVar6) {
      ppvVar7 = (param_1->gPrgObj).object.m_scriptHandle;
      if (((*(short *)((int)ppvVar7 + 0x3e) == 0) && (*(short *)(ppvVar7 + 0x14) == 0)) &&
         (*(short *)(ppvVar7 + 0x11) == 0)) {
        (param_1->gPrgObj).object.m_displayFlags = (param_1->gPrgObj).object.m_displayFlags | 2;
      }
      else {
        (param_1->gPrgObj).object.m_displayFlags =
             (param_1->gPrgObj).object.m_displayFlags & 0xfffffffd;
        param_1->field_0x63c = param_1->field_0x63c & 0x7f;
      }
      *(int *)&(param_1->gPrgObj).m_flags = *(int *)&(param_1->gPrgObj).m_flags + 1;
      if ((char)param_1->field_0x640 < '\0') {
        if (*(short *)&param_1->field_0x642 != 0) {
          sVar4 = *(short *)&param_1->field_0x642 + -1;
          *(short *)&param_1->field_0x642 = sVar4;
          if (sVar4 == 0) {
            param_1->field_0x640 = param_1->field_0x640 & 0x7f;
          }
        }
      }
      if ((char)param_1->field_0x648 < '\0') {
        if (*(short *)&param_1->field_0x64a != 0) {
          sVar4 = *(short *)&param_1->field_0x64a + -1;
          *(short *)&param_1->field_0x64a = sVar4;
          if (sVar4 == 0) {
            param_1->field_0x648 = param_1->field_0x648 & 0x7f;
          }
        }
      }
      if ((char)param_1->field_0x650 < '\0') {
        if (*(short *)&param_1->field_0x652 != 0) {
          sVar4 = *(short *)&param_1->field_0x652 + -1;
          *(short *)&param_1->field_0x652 = sVar4;
          if (sVar4 == 0) {
            param_1->field_0x650 = param_1->field_0x650 & 0x7f;
          }
        }
      }
      if ((char)param_1->field_0x658 < '\0') {
        if (*(short *)&param_1->field_0x65a != 0) {
          sVar4 = *(short *)&param_1->field_0x65a + -1;
          *(short *)&param_1->field_0x65a = sVar4;
          if (sVar4 == 0) {
            param_1->field_0x658 = param_1->field_0x658 & 0x7f;
          }
        }
      }
      return;
    }
  } while( true );
}

