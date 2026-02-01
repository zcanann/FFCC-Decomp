// Function: setAttackAfter__8CGMonObjFi
// Entry: 80119930
// Size: 308 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void setAttackAfter__8CGMonObjFi(CGMonObj *gMonObj,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + param_2 * 0x48 + 10);
  if (uVar3 == 0xffff) {
    uVar3 = 0;
  }
  if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
    iVar1 = Game.game.m_gameWork.m_bossArtifactStageTable
            [Game.game.m_gameWork.m_bossArtifactStageIndex];
    iVar2 = 2;
    if (iVar1 < 2) {
      iVar2 = iVar1;
    }
  }
  else {
    iVar2 = 0;
  }
  if (0 < iVar2) {
    uVar3 = uVar3 - *(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + iVar2 * 2 + 0x58);
    uVar3 = uVar3 & ~((int)uVar3 >> 0x1f);
  }
  if (uVar3 == 0) {
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
  }
  else {
    iVar1 = (int)uVar3 / 5 + ((int)uVar3 >> 0x1f);
    iVar1 = iVar1 - (iVar1 >> 0x1f);
    iVar2 = 1;
    if (0 < iVar1) {
      iVar2 = iVar1;
    }
    iVar2 = Rand__5CMathFUl(&Math,iVar2);
    *(uint *)&gMonObj->field_0x6f0 = uVar3 + iVar2;
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x11,0,0);
  }
  return;
}

