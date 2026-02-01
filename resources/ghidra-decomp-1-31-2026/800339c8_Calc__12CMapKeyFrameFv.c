// Function: Calc__12CMapKeyFrameFv
// Entry: 800339c8
// Size: 88 bytes

void Calc__12CMapKeyFrameFv(CMapKeyFrame *param_1)

{
  int iVar1;
  
  param_1->field5_0x8 = param_1->field5_0x8 + 1;
  iVar1 = param_1->field7_0x10;
  if (param_1->field5_0x8 <= iVar1) {
    return;
  }
  if (param_1->field6_0xc == iVar1) {
    *(undefined *)&param_1->isRun = 0;
    return;
  }
  if (param_1->field_0x3 != '\0') {
    param_1->field5_0x8 = param_1->field6_0xc;
    return;
  }
  param_1->field5_0x8 = iVar1;
  *(undefined *)&param_1->isRun = 0;
  return;
}

