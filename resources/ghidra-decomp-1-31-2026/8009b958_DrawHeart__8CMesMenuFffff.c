// Function: DrawHeart__8CMesMenuFffff
// Entry: 8009b958
// Size: 916 bytes

/* WARNING: Removing unreachable block (ram,0x8009bcd0) */
/* WARNING: Removing unreachable block (ram,0x8009bcc8) */
/* WARNING: Removing unreachable block (ram,0x8009bcc0) */
/* WARNING: Removing unreachable block (ram,0x8009bcb8) */
/* WARNING: Removing unreachable block (ram,0x8009bcb0) */
/* WARNING: Removing unreachable block (ram,0x8009bca8) */
/* WARNING: Removing unreachable block (ram,0x8009bca0) */
/* WARNING: Removing unreachable block (ram,0x8009bc98) */
/* WARNING: Removing unreachable block (ram,0x8009bc90) */
/* WARNING: Removing unreachable block (ram,0x8009bc88) */
/* WARNING: Removing unreachable block (ram,0x8009bc80) */
/* WARNING: Removing unreachable block (ram,0x8009bc78) */
/* WARNING: Removing unreachable block (ram,0x8009b9c0) */
/* WARNING: Removing unreachable block (ram,0x8009b9b8) */
/* WARNING: Removing unreachable block (ram,0x8009b9b0) */
/* WARNING: Removing unreachable block (ram,0x8009b9a8) */
/* WARNING: Removing unreachable block (ram,0x8009b9a0) */
/* WARNING: Removing unreachable block (ram,0x8009b998) */
/* WARNING: Removing unreachable block (ram,0x8009b990) */
/* WARNING: Removing unreachable block (ram,0x8009b988) */
/* WARNING: Removing unreachable block (ram,0x8009b980) */
/* WARNING: Removing unreachable block (ram,0x8009b978) */
/* WARNING: Removing unreachable block (ram,0x8009b970) */
/* WARNING: Removing unreachable block (ram,0x8009b968) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawHeart__8CMesMenuFffff
               (double param_1,double param_2,undefined8 param_3,double param_4,int param_5)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint32_t uVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  undefined auStack_100 [8];
  double local_f8;
  undefined4 local_f0;
  uint uStack_ec;
  undefined4 local_e8;
  uint uStack_e4;
  
  uVar7 = Game.game.m_scriptFoodBase[*(int *)(param_5 + 0x18)];
  if ((uVar7 != 0) && ((double)FLOAT_803308d8 < param_4)) {
    local_f8 = (double)(longlong)(int)((double)FLOAT_80330908 * param_4);
    uVar3 = __ct__6CColorFUcUcUcUc
                      (auStack_100,0xff,0xff,0xff,(int)((double)FLOAT_80330908 * param_4));
    SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar3);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x17);
    uVar4 = 0x4c;
    if ((*(uint *)(param_5 + 0x18) & 1) != 0) {
      uVar4 = 0x30;
    }
    dVar18 = (double)(float)((double)FLOAT_8033090c + param_2);
    dVar20 = (double)FLOAT_80330910;
    iVar9 = 0;
    dVar13 = (double)FLOAT_80330918;
    dVar14 = (double)FLOAT_80330914;
    param_1 = param_1 + (double)(float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) -
                                       DOUBLE_80330900);
    dVar15 = (double)FLOAT_8033091c;
    dVar16 = (double)FLOAT_80330920;
    dVar17 = (double)FLOAT_803308d8;
    iVar8 = param_5;
    dVar19 = DOUBLE_80330900;
    for (iVar6 = 0; param_1 = (double)(float)param_1,
        iVar6 < (int)(uint)(*(ushort *)(uVar7 + 0x1a) >> 1); iVar6 = iVar6 + 1) {
      uStack_ec = *(uint *)(iVar8 + 0x3db0) ^ 0x80000000;
      local_f0 = 0x43300000;
      iVar5 = *(int *)(param_5 + 0x3da8) - iVar9;
      dVar10 = (double)sin((double)(float)(dVar20 * -(double)(float)((double)(float)((double)
                                                  CONCAT44(0x43300000,uStack_ec) - dVar19) * dVar13
                                                  - dVar14)));
      uVar4 = *(uint *)(iVar8 + 0x3dd0);
      dVar10 = (double)(float)((double)(float)(dVar15 * (double)(float)dVar10 + dVar14) * dVar16);
      if (uVar4 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = ((int)uVar4 >> 2) * *(int *)(&DAT_8020f998 + ((uVar4 + 1) * 4 & 0xc));
      }
      local_f8 = (double)(CONCAT44(0x43300000,iVar2) ^ 0x80000000);
      if (uVar4 == 0) {
        uStack_e4 = 0;
      }
      else {
        uStack_e4 = ((int)uVar4 >> 2) * *(int *)(&DAT_8020f998 + (uVar4 & 3) * 4);
      }
      uStack_e4 = uStack_e4 ^ 0x80000000;
      dVar11 = (double)(float)(param_1 + (double)(float)(local_f8 - dVar19));
      local_e8 = 0x43300000;
      dVar12 = (double)(float)(dVar18 + (double)(float)((double)CONCAT44(0x43300000,uStack_e4) -
                                                       dVar19));
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar11,dVar12,(double)FLOAT_803308dc,(double)FLOAT_803308dc,dVar17,dVar17,dVar10,
                 dVar10,&MenuPcs,3);
      if (0 < iVar5) {
        iVar2 = 0xb;
        if (iVar5 < 0xb) {
          iVar2 = iVar5;
        }
        local_e8 = 0x43300000;
        local_f0 = 0x43300000;
        uStack_e4 = ~((int)(-(uint)*(ushort *)(uVar7 + 0x42) | (uint)*(ushort *)(uVar7 + 0x42)) >>
                     0x1f) & 0x18U ^ 0x80000000;
        uStack_ec = (0xc - iVar2) * 0x18 ^ 0x80000000;
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar11,dVar12,(double)FLOAT_803308dc,(double)FLOAT_803308dc,
                   (double)(float)((double)CONCAT44(0x43300000,uStack_e4) - DOUBLE_80330900),
                   (double)(float)((double)CONCAT44(0x43300000,uStack_ec) - DOUBLE_80330900),dVar10,
                   dVar10,&MenuPcs,3);
      }
      fVar1 = FLOAT_80330928;
      if ((*(uint *)(param_5 + 0x18) & 1) != 0) {
        fVar1 = FLOAT_80330924;
      }
      param_1 = param_1 + (double)fVar1;
      iVar9 = iVar9 + 0xc;
      iVar8 = iVar8 + 4;
    }
  }
  return;
}

