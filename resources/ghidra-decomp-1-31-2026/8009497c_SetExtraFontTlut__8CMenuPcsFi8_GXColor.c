// Function: SetExtraFontTlut__8CMenuPcsFi8_GXColor
// Entry: 8009497c
// Size: 368 bytes

void SetExtraFontTlut__8CMenuPcsFi8_GXColor(CMenuPcs *menuPcs,int param_2,byte *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  undefined uVar6;
  int iVar7;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  longlong local_48;
  undefined4 local_40;
  uint uStack_3c;
  longlong local_38;
  undefined4 local_30;
  uint uStack_2c;
  longlong local_28;
  
  iVar4 = param_2 * 4;
  iVar7 = 0;
  do {
    uVar6 = GetTlutColor__8CTextureFi
                      (*(CTexture **)(*(int *)(&menuPcs->field_0x100 + iVar4) + 0x34),iVar7);
    if (iVar7 < 9) {
      local_60._2_2_ = CONCAT11(param_3[2],uVar6);
      local_60 = CONCAT22(*(undefined2 *)param_3,local_60._2_2_);
    }
    else {
      uStack_54 = iVar7 - 9U ^ 0x80000000;
      local_58 = 0x43300000;
      uStack_4c = 0xf5 - *param_3 ^ 0x80000000;
      uStack_3c = 0xf5 - param_3[1] ^ 0x80000000;
      uStack_2c = 0xf5 - param_3[2] ^ 0x80000000;
      local_50 = 0x43300000;
      local_40 = 0x43300000;
      fVar5 = FLOAT_80330808 -
              (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80330838) / FLOAT_80330858;
      local_30 = 0x43300000;
      iVar1 = (int)-((float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80330838) * fVar5 -
                    FLOAT_8033085c);
      local_48 = (longlong)iVar1;
      iVar2 = (int)-((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80330838) * fVar5 -
                    FLOAT_8033085c);
      local_38 = (longlong)iVar2;
      iVar3 = (int)-((float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80330838) * fVar5 -
                    FLOAT_8033085c);
      local_28 = (longlong)iVar3;
      local_60._2_2_ = CONCAT11((char)iVar3,uVar6);
      local_60 = CONCAT22(CONCAT11((char)iVar1,(char)iVar2),local_60._2_2_);
    }
    local_64 = local_60;
    SetTlutColor__8CTextureFi8_GXColor
              (*(CTexture **)(*(int *)(&menuPcs->field_0x100 + iVar4) + 0x34),iVar7,&local_64);
    iVar7 = iVar7 + 1;
  } while (iVar7 < 0x10);
  FlushTlut__8CTextureFv(*(CTexture **)(*(int *)(&menuPcs->field_0x100 + iVar4) + 0x34));
  return;
}

