// Function: pppInitDrawEnv__FUc
// Entry: 80054070
// Size: 152 bytes

void pppInitDrawEnv__FUc(char param_1)

{
  InitVtxFmt__12CMaterialManFi11_GXCompTypei11_GXCompTypei11_GXCompTypei
            (&MaterialMan,0xffffffff,4,0,3,0xe,3,10);
  DAT_8032ed84 = 0xff;
  DAT_8032ed85 = 0xff;
  DAT_8032ed86 = 0xff;
  DAT_8032ed88 = 0xff;
  DAT_8032ed89 = 0xff;
  DAT_8032ed8a = 0xff;
  DAT_8032ed8b = 0xff;
  FLOAT_8032ed8c = FLOAT_8032fde8;
  if (param_1 != '\0') {
    FLOAT_8032ed8c = FLOAT_8032fddc;
  }
  SetNumDiffuse__9CLightPcsFUl(&LightPcs,0);
  return;
}

