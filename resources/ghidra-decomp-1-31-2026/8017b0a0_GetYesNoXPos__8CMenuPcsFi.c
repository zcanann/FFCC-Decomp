// Function: GetYesNoXPos__8CMenuPcsFi
// Entry: 8017b0a0
// Size: 384 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int GetYesNoXPos__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  undefined *puVar1;
  CFont *font;
  int iVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  uVar3 = (uint)Game.game.m_gameWork.m_languageId;
  puVar1 = PTR_DAT_80215e34;
  if (uVar3 != 3) {
    if (uVar3 < 3) {
      if ((uVar3 != 1) && (puVar1 = PTR_s__Ja_Nein_80215d48, uVar3 != 0)) goto LAB_8017b13c;
    }
    else {
      puVar1 = PTR_DAT_8021600c;
      if ((uVar3 == 5) || (puVar1 = PTR_s__Oui_Non_80215f20, uVar3 < 5)) goto LAB_8017b13c;
    }
    puVar1 = PTR_s__Yes_No_80215c5c;
  }
LAB_8017b13c:
  font = *(CFont **)&menuPcs->field_0xf8;
  SetMargin__5CFontFf(FLOAT_803336cc,font);
  SetShadow__5CFontFi(font,0);
  SetScale__5CFontFf(FLOAT_803336cc,font);
  dVar4 = (double)GetWidth__5CFontFPc(font,puVar1 + 1);
  iVar2 = (int)(((double)CONCAT44(0x43300000,
                                  (int)(*(short **)&menuPcs->field_0x848)[2] - (int)dVar4 ^
                                  0x80000000) - DOUBLE_803336d8) * DOUBLE_803336d0 +
               ((double)CONCAT44(0x43300000,(int)**(short **)&menuPcs->field_0x848 ^ 0x80000000) -
               DOUBLE_803336d8));
  if (param_2 != 0) {
    dVar5 = (double)GetWidth__5CFontFPc(font,*(undefined4 *)(&DAT_80216728 + uVar3 * 4));
    iVar2 = iVar2 + ((int)dVar4 - (int)dVar5);
  }
  return iVar2 + -0x1e;
}

