// Function: RenderQuadTex2__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
// Entry: 800244a8
// Size: 352 bytes

/* WARNING: Removing unreachable block (ram,0x800245e4) */
/* WARNING: Removing unreachable block (ram,0x800245dc) */
/* WARNING: Removing unreachable block (ram,0x800245d4) */
/* WARNING: Removing unreachable block (ram,0x800245cc) */
/* WARNING: Removing unreachable block (ram,0x800244d0) */
/* WARNING: Removing unreachable block (ram,0x800244c8) */
/* WARNING: Removing unreachable block (ram,0x800244c0) */
/* WARNING: Removing unreachable block (ram,0x800244b8) */

void RenderQuadTex2__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
               (undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
               float *param_5,float *param_6)

{
  undefined4 uVar1;
  undefined4 uVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  if ((param_5 == (float *)0x0) || (param_6 == (float *)0x0)) {
    dVar5 = (double)FLOAT_8032f888;
    dVar3 = (double)FLOAT_8032f88c;
    dVar4 = dVar3;
    dVar6 = dVar5;
  }
  else {
    dVar6 = (double)*param_5;
    dVar5 = (double)param_5[1];
    dVar4 = (double)*param_6;
    dVar3 = (double)param_6[1];
  }
  GXBegin(0x80,7,4);
  DAT_cc008000 = *param_2;
  uVar1 = param_2[2];
  DAT_cc008000 = param_2[1];
  uVar2 = *param_4;
  DAT_cc008000 = uVar1;
  DAT_cc008000 = uVar2;
  DAT_cc008000 = (float)dVar6;
  DAT_cc008000 = (float)dVar5;
  DAT_cc008000 = (float)dVar6;
  DAT_cc008000 = (float)dVar5;
  DAT_cc008000 = *param_3;
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = uVar1;
  DAT_cc008000 = uVar2;
  DAT_cc008000 = (float)dVar4;
  DAT_cc008000 = (float)dVar5;
  DAT_cc008000 = (float)dVar4;
  DAT_cc008000 = (float)dVar5;
  DAT_cc008000 = *param_3;
  DAT_cc008000 = param_3[1];
  DAT_cc008000 = uVar1;
  DAT_cc008000 = uVar2;
  DAT_cc008000 = (float)dVar4;
  DAT_cc008000 = (float)dVar3;
  DAT_cc008000 = (float)dVar4;
  DAT_cc008000 = (float)dVar3;
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_3[1];
  DAT_cc008000 = uVar1;
  DAT_cc008000 = uVar2;
  DAT_cc008000 = (float)dVar6;
  DAT_cc008000 = (float)dVar3;
  DAT_cc008000 = (float)dVar6;
  DAT_cc008000 = (float)dVar3;
  return;
}

