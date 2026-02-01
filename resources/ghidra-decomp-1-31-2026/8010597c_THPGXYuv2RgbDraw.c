// Function: THPGXYuv2RgbDraw
// Entry: 8010597c
// Size: 476 bytes

void THPGXYuv2RgbDraw(undefined4 param_1,undefined4 param_2,undefined4 param_3,short param_4,
                     short param_5,short param_6,short param_7,short param_8,short param_9)

{
  double dVar1;
  undefined auStack_88 [32];
  undefined auStack_68 [32];
  undefined auStack_48 [40];
  
  GXInitTexObj(auStack_48,param_1,param_6,param_7,1,0,0,0);
  dVar1 = (double)FLOAT_80331884;
  GXInitTexObjLOD(dVar1,dVar1,dVar1,auStack_48,0,0,0,0,0);
  GXLoadTexObj(auStack_48,0);
  GXInitTexObj(auStack_68,param_2,(int)param_6 >> 1 & 0xffff,(int)param_7 >> 1 & 0xffff,1,0,0,0);
  dVar1 = (double)FLOAT_80331884;
  GXInitTexObjLOD(dVar1,dVar1,dVar1,auStack_68,0,0,0,0,0);
  GXLoadTexObj(auStack_68,1);
  GXInitTexObj(auStack_88,param_3,(int)param_6 >> 1 & 0xffff,(int)param_7 >> 1 & 0xffff,1,0,0,0);
  dVar1 = (double)FLOAT_80331884;
  GXInitTexObjLOD(dVar1,dVar1,dVar1,auStack_88,0,0,0,0,0);
  GXLoadTexObj(auStack_88,2);
  GXBegin(0x80,7,4);
  DAT_cc008000._0_2_ = param_4;
  DAT_cc008000._0_2_ = param_5;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = param_4 + param_8;
  DAT_cc008000._0_2_ = param_5;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 1;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = param_4 + param_8;
  DAT_cc008000._0_2_ = param_5 + param_9;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 1;
  DAT_cc008000._0_2_ = 1;
  DAT_cc008000._0_2_ = param_4;
  DAT_cc008000._0_2_ = param_5 + param_9;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 1;
  return;
}

