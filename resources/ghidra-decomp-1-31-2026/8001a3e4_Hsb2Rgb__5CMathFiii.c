// Function: Hsb2Rgb__5CMathFiii
// Entry: 8001a3e4
// Size: 412 bytes

undefined4 Hsb2Rgb__5CMathFiii(undefined4 param_1,int param_2,int param_3,int param_4)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  char cVar7;
  undefined4 local_18;
  
  iVar2 = (param_3 * 0xff) / 100 + (param_3 * 0xff >> 0x1f);
  uVar5 = iVar2 - (iVar2 >> 0x1f);
  iVar2 = (param_4 * 0xff) / 100 + (param_4 * 0xff >> 0x1f);
  uVar3 = iVar2 - (iVar2 >> 0x1f);
  cVar4 = (char)uVar3;
  if (FLOAT_8032f740 == (float)((double)CONCAT44(0x43300000,uVar5 ^ 0x80000000) - DOUBLE_8032f750))
  {
    local_18 = (uint)CONCAT21(CONCAT11(cVar4,cVar4),cVar4) << 8;
  }
  else {
    iVar2 = (0xff - uVar5) * uVar3;
    iVar6 = iVar2 / 0xff + (iVar2 >> 0x1f);
    iVar2 = param_2 / 0x3c + (param_2 >> 0x1f);
    iVar6 = iVar6 - (iVar6 >> 0x1f);
    iVar2 = (param_2 + (iVar2 - (iVar2 >> 0x1f)) * -0x3c) * (uVar3 - iVar6);
    iVar2 = iVar2 / 0x3c + (iVar2 >> 0x1f);
    cVar1 = (char)iVar2 - (char)(iVar2 >> 0x1f);
    cVar7 = (char)iVar6;
    if (param_2 < 0x3c) {
      local_18 = (uint)CONCAT12(cVar4,CONCAT11(cVar7 + cVar1,cVar7)) << 8;
    }
    else if (param_2 < 0x78) {
      local_18._1_3_ = CONCAT21((short)uVar3,cVar7) << 8;
      local_18 = CONCAT13(cVar4 - cVar1,local_18._1_3_);
    }
    else if (param_2 < 0xb4) {
      local_18 = (uVar3 & 0xff) << 0x10;
      local_18 = CONCAT13(cVar7,local_18._1_3_);
      local_18 = (uint)CONCAT21(local_18._0_2_,cVar7 + cVar1) << 8;
    }
    else if (param_2 < 0xf0) {
      local_18 = (uVar3 & 0xff) << 8;
      local_18._1_3_ = CONCAT12(cVar4 - cVar1,local_18._2_2_);
      local_18 = CONCAT13(cVar7,local_18._1_3_);
    }
    else if (param_2 < 300) {
      local_18 = (uVar3 & 0xff) << 8;
      local_18._1_3_ = CONCAT12(cVar7,local_18._2_2_);
      local_18 = CONCAT13(cVar7 + cVar1,local_18._1_3_);
    }
    else if (param_2 < 0x168) {
      local_18 = (uint)CONCAT21(CONCAT11(cVar4,cVar7),cVar4 - cVar1) << 8;
    }
    else {
      local_18 = 0;
    }
  }
  local_18 = CONCAT31(local_18._0_3_,0xff);
  return local_18;
}

