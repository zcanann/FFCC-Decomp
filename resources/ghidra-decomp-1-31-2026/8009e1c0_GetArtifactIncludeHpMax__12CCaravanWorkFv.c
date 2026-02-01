// Function: GetArtifactIncludeHpMax__12CCaravanWorkFv
// Entry: 8009e1c0
// Size: 316 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int GetArtifactIncludeHpMax__12CCaravanWorkFv(CCaravanWork *caravanWork)

{
  ushort uVar1;
  CGObjWork *pCVar2;
  ushort *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  pCVar2 = &caravanWork->gObjWork;
  iVar5 = 0;
  iVar4 = 0;
  iVar6 = 0x32;
  do {
    if ((iVar4 < 0x60) && (0 < (short)caravanWork->m_artifacts[0])) {
      puVar3 = (ushort *)(Game.game.unkCFlatData0[2] + (short)caravanWork->m_artifacts[0] * 0x48);
      uVar1 = *puVar3;
      if ((uVar1 != 0xdb) && ((0xda < uVar1 && (uVar1 == 0xe4)))) {
        iVar5 = iVar5 + (uint)puVar3[3];
      }
    }
    if ((iVar4 + 1 < 0x60) && (0 < (short)caravanWork->m_artifacts[1])) {
      puVar3 = (ushort *)(Game.game.unkCFlatData0[2] + (short)caravanWork->m_artifacts[1] * 0x48);
      uVar1 = *puVar3;
      if ((uVar1 != 0xdb) && ((0xda < uVar1 && (uVar1 == 0xe4)))) {
        iVar5 = iVar5 + (uint)puVar3[3];
      }
    }
    caravanWork = (CCaravanWork *)&(caravanWork->gObjWork).m_objType;
    iVar4 = iVar4 + 2;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  iVar5 = iVar5 + (uint)*(ushort *)
                         (Game.game.unkCFlatData0[0] + pCVar2->m_baseDataIndex * 0x1d0 + 6);
  if (0xf < iVar5) {
    return 0x10;
  }
  return iVar5;
}

