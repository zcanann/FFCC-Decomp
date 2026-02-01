// Function: create__9CCharaPcsFv
// Entry: 8007a100
// Size: 812 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void create__9CCharaPcsFv(int param_1)

{
  float fVar1;
  float fVar2;
  CStage *pCVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 local_148;
  Vec local_144;
  Vec local_138 [2];
  float local_11c;
  float local_118;
  Vec aVStack_110 [4];
  undefined local_e0;
  undefined local_df;
  undefined local_de;
  undefined local_dd;
  
  *(undefined4 *)(param_1 + 0x718) = 0;
  pCVar3 = CreateStage__7CMemoryFUlPci(&Memory,0x177000,s_CCharaPcs_LoadModel_801d9998,0);
  *(CStage **)(param_1 + 0xcc) = pCVar3;
  pCVar3 = CreateStage__7CMemoryFUlPci(&Memory,0x130000,s_CCharaPcs_LoadTex_801d99ac,0);
  *(CStage **)(param_1 + 0xd0) = pCVar3;
  pCVar3 = CreateStage__7CMemoryFUlPci(&Memory,0x8400,s_CCharaPcs_LoadWepTex_801d99c0,0);
  *(CStage **)(param_1 + 0xd8) = pCVar3;
  pCVar3 = CreateStage__7CMemoryFUlPci(&Memory,0x18000,s_CCharaPcs_LoadWepModel_801d99d8,0);
  *(CStage **)(param_1 + 0xdc) = pCVar3;
  pCVar3 = CreateStage__7CMemoryFUlPci(&Memory,0x10000,s_CCharaPcs_LoadFaModel_801d99f0,0);
  *(CStage **)(param_1 + 0xe0) = pCVar3;
  uVar5 = 0x1e0000;
  if (Game.game.m_currentSceneId == 4) {
    uVar5 = 0x190000;
  }
  pCVar3 = CreateStage__7CMemoryFUlPci(&Memory,uVar5,s_CCharaPcs_LoadAnim_801d9a08,0);
  *(CStage **)(param_1 + 0xd4) = pCVar3;
  iVar4 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                    (&Memory,0x194,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0xdb,0);
  if (iVar4 != 0) {
    *(undefined4 *)(iVar4 + 0x15c) = 0;
    *(undefined4 *)(iVar4 + 0x160) = 0;
    *(undefined4 *)(iVar4 + 0x168) = 0;
    *(undefined4 *)(iVar4 + 0x16c) = 0;
    *(undefined4 *)(iVar4 + 0x170) = 0;
    *(undefined4 *)(iVar4 + 0x174) = 0;
    iVar7 = 2;
    iVar6 = iVar4;
    do {
      *(undefined4 *)(iVar6 + 0x10) = 0;
      *(undefined4 *)(iVar6 + 0x14) = 0;
      *(undefined4 *)(iVar6 + 0x18) = 0;
      *(undefined4 *)(iVar6 + 0x1c) = 0;
      *(undefined4 *)(iVar6 + 0x20) = 0;
      *(undefined4 *)(iVar6 + 0x24) = 0;
      *(undefined4 *)(iVar6 + 0x28) = 0;
      *(undefined4 *)(iVar6 + 0x2c) = 0;
      *(undefined4 *)(iVar6 + 0x30) = 0;
      *(undefined4 *)(iVar6 + 0x34) = 0;
      *(undefined4 *)(iVar6 + 0x38) = 0;
      *(undefined4 *)(iVar6 + 0x3c) = 0;
      *(undefined4 *)(iVar6 + 0x40) = 0;
      *(undefined4 *)(iVar6 + 0x44) = 0;
      *(undefined4 *)(iVar6 + 0x48) = 0;
      *(undefined4 *)(iVar6 + 0x4c) = 0;
      *(undefined4 *)(iVar6 + 0x50) = 0;
      *(undefined4 *)(iVar6 + 0x54) = 0;
      *(undefined4 *)(iVar6 + 0x58) = 0;
      *(undefined4 *)(iVar6 + 0x5c) = 0;
      *(undefined4 *)(iVar6 + 0x60) = 0;
      *(undefined4 *)(iVar6 + 100) = 0;
      *(undefined4 *)(iVar6 + 0x68) = 0;
      *(undefined4 *)(iVar6 + 0x6c) = 0;
      *(undefined4 *)(iVar6 + 0x70) = 0;
      *(undefined4 *)(iVar6 + 0x74) = 0;
      *(undefined4 *)(iVar6 + 0x78) = 0;
      *(undefined4 *)(iVar6 + 0x7c) = 0;
      *(undefined4 *)(iVar6 + 0x80) = 0;
      *(undefined4 *)(iVar6 + 0x84) = 0;
      *(undefined4 *)(iVar6 + 0x88) = 0;
      *(undefined4 *)(iVar6 + 0x8c) = 0;
      iVar6 = iVar6 + 0x80;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    *(undefined4 *)(iVar4 + 0x178) = 0;
    fVar2 = FLOAT_8033028c;
    *(undefined4 *)(iVar4 + 0x110) = 0xffffffff;
    fVar1 = FLOAT_80330288;
    *(undefined4 *)(iVar4 + 8) = 0;
    *(float *)(iVar4 + 0x11c) = fVar2;
    *(float *)(iVar4 + 0xc) = fVar1;
    *(undefined4 *)(iVar4 + 0x120) = 0;
    *(undefined4 *)(iVar4 + 0x188) = 0;
    *(undefined4 *)(iVar4 + 0x18c) = 0;
    *(float *)(iVar4 + 0x154) = fVar1;
    *(undefined4 *)(iVar4 + 0x158) = 0;
    *(byte *)(iVar4 + 400) = *(byte *)(iVar4 + 400) & 0x7f | 0x80;
  }
  *(int *)(param_1 + 0x4c) = iVar4;
  *(int *)(*(int *)(param_1 + 0x4c) + 0x15c) = *(int *)(param_1 + 0x4c);
  *(int *)(*(int *)(param_1 + 0x4c) + 0x160) = *(int *)(param_1 + 0x4c);
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  __ct__Q29CLightPcs10CBumpLightFv(&local_148);
  local_148 = 1;
  local_144.x = FLOAT_8033030c;
  local_144.y = FLOAT_80330310;
  local_144.z = FLOAT_80330314;
  local_138[0].x = FLOAT_80330318;
  local_138[0].y = FLOAT_8033031c;
  local_138[0].z = FLOAT_80330320;
  PSVECSubtract(local_138,&local_144,aVStack_110);
  PSVECNormalize(aVStack_110,aVStack_110);
  local_de = 0;
  local_e0 = 0x80;
  local_df = 0x80;
  local_dd = 0xff;
  local_11c = FLOAT_80330288;
  local_118 = FLOAT_80330288;
  DAT_8032edc0 = AddBump__9CLightPcsFPQ29CLightPcs6CLightQ29CLightPcs6TARGETPQ27CMemory6CStagei
                           (&LightPcs,&local_148,0,(CStage *)Chara._8280_4_,4);
  Create__6CCharaFv(&Chara);
  return;
}

