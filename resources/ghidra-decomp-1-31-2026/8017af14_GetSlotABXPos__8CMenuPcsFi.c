// Function: GetSlotABXPos__8CMenuPcsFi
// Entry: 8017af14
// Size: 396 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int GetSlotABXPos__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  undefined *puVar1;
  CFont *font;
  int iVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  uVar3 = (uint)Game.game.m_gameWork.m_languageId;
  puVar1 = PTR_s__Slot_A_Slot_B_80215e08;
  if (uVar3 != 3) {
    if (uVar3 < 3) {
      if ((uVar3 != 1) && (puVar1 = PTR_s__Steckplatz_A_Steckplatz_B_80215d1c, uVar3 != 0))
      goto LAB_8017afb0;
    }
    else {
      puVar1 = PTR_s__Ranura_A_Ranura_B_80215fe0;
      if ((uVar3 == 5) || (puVar1 = PTR_s__Slot_A_Slot_B_80215ef4, uVar3 < 5)) goto LAB_8017afb0;
    }
    puVar1 = PTR_s__Slot_A_Slot_B_80215c30;
  }
LAB_8017afb0:
  font = *(CFont **)&menuPcs->field_0xf8;
  SetMargin__5CFontFf(FLOAT_803336cc,font);
  SetShadow__5CFontFi(font,0);
  SetScale__5CFontFf(FLOAT_803336cc,font);
  SetTlut__5CFontFi(font,0x23);
  dVar4 = (double)GetWidth__5CFontFPc(font,puVar1 + 1);
  iVar2 = (int)(((double)CONCAT44(0x43300000,
                                  (int)(*(short **)&menuPcs->field_0x848)[2] - (int)dVar4 ^
                                  0x80000000) - DOUBLE_803336d8) * DOUBLE_803336d0 +
               ((double)CONCAT44(0x43300000,(int)**(short **)&menuPcs->field_0x848 ^ 0x80000000) -
               DOUBLE_803336d8));
  if (param_2 != 0) {
    dVar5 = (double)GetWidth__5CFontFPc(font,(&PTR_DAT_8021673c)[uVar3]);
    iVar2 = iVar2 + ((int)dVar4 - (int)dVar5);
  }
  return iVar2 + -0x1e;
}

