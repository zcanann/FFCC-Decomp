// Function: onScriptChanging__9CCharaPcsFPc
// Entry: 8007999c
// Size: 420 bytes

/* WARNING: Removing unreachable block (ram,0x80079b24) */
/* WARNING: Removing unreachable block (ram,0x80079b1c) */
/* WARNING: Removing unreachable block (ram,0x80079b14) */
/* WARNING: Removing unreachable block (ram,0x800799bc) */
/* WARNING: Removing unreachable block (ram,0x800799b4) */
/* WARNING: Removing unreachable block (ram,0x800799ac) */

void onScriptChanging__9CCharaPcsFPc(CCharaPcs *charaPcs)

{
  int iVar1;
  float fVar2;
  byte *pbVar3;
  uint uVar4;
  CCharaPcs *pCVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  undefined local_a8;
  undefined local_a7;
  undefined local_a6;
  undefined local_a5;
  undefined auStack_a4 [4];
  undefined local_a0;
  undefined local_9f;
  undefined local_9e;
  undefined local_9d;
  undefined4 local_98;
  uint uStack_94;
  undefined4 local_90;
  uint uStack_8c;
  longlong local_88;
  undefined4 local_80;
  uint uStack_7c;
  longlong local_78;
  undefined4 local_70;
  uint uStack_6c;
  longlong local_68;
  undefined4 local_60;
  uint uStack_5c;
  longlong local_58;
  
  dVar6 = (double)FLOAT_80330308;
  uVar4 = 0;
  pCVar5 = charaPcs;
  dVar7 = DOUBLE_803302b0;
  dVar8 = DOUBLE_803302b8;
  do {
    pbVar3 = (byte *)__ct__6CColorFUcUcUcUc(auStack_a4,0xff,0xff,0xff,0xff);
    __ct__6CColorFv(&local_a8);
    uStack_8c = uVar4 ^ 0x80000000;
    uStack_94 = (uint)*pbVar3;
    local_90 = 0x43300000;
    local_98 = 0x43300000;
    fVar2 = (float)((double)(float)((double)CONCAT44(0x43300000,uStack_8c) - dVar8) * dVar6);
    local_80 = 0x43300000;
    local_70 = 0x43300000;
    local_60 = 0x43300000;
    iVar1 = (int)((float)((double)CONCAT44(0x43300000,uStack_94) - dVar7) * fVar2);
    local_88 = (longlong)iVar1;
    local_a8 = (undefined)iVar1;
    uStack_7c = (uint)pbVar3[1];
    iVar1 = (int)((float)((double)CONCAT44(0x43300000,uStack_7c) - dVar7) * fVar2);
    local_78 = (longlong)iVar1;
    local_a7 = (undefined)iVar1;
    uStack_6c = (uint)pbVar3[2];
    iVar1 = (int)((float)((double)CONCAT44(0x43300000,uStack_6c) - dVar7) * fVar2);
    local_68 = (longlong)iVar1;
    local_a6 = (undefined)iVar1;
    uStack_5c = (uint)pbVar3[3];
    iVar1 = (int)((float)((double)CONCAT44(0x43300000,uStack_5c) - dVar7) * fVar2);
    local_58 = (longlong)iVar1;
    local_a5 = (undefined)iVar1;
    __ct__6CColorFR6CColor(&local_a0,&local_a8);
    uVar4 = uVar4 + 1;
    pCVar5->field_0x12c = local_a0;
    pCVar5->field_0x12d = local_9f;
    pCVar5->field_0x12e = local_9e;
    pCVar5->field_0x12f = local_9d;
    pCVar5 = (CCharaPcs *)&pCVar5->field_0x4;
  } while ((int)uVar4 < 5);
  *(undefined4 *)&charaPcs->field_0x24 = 0;
  *(undefined4 *)&charaPcs->field_0xe4 = 0;
  *(undefined4 *)&charaPcs->field_0x44 = 0x80;
  *(undefined4 *)&charaPcs->field_0x48 = 100;
  return;
}

