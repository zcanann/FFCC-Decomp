// Function: putGil__10CGPartyObjFi
// Entry: 8011cbdc
// Size: 308 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 putGil__10CGPartyObjFi(CGPrgObj *param_1,undefined4 param_2)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((int)((uint)*(byte *)&(param_1->object).m_weaponNodeFlags << 0x18) < 0) {
    if (((((int)((uint)*(byte *)((int)&(param_1->object).m_weaponNodeFlags + 1) << 0x18) < 0) &&
         ((int)((uint)*(byte *)&param_1[1].object.m_shieldAttachNodeIndex << 0x18) < 0)) &&
        (*(short *)((param_1->object).m_scriptHandle + 7) != 0)) &&
       (param_1[1].object.m_moveBaseSpeed == 0.0)) {
      if ((Game.game.m_gameWork.m_menuStageMode == '\0') ||
         (iVar2 = CanCreateFromScript__9CGItemObjFv(), iVar2 != 0)) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      goto LAB_8011cc84;
    }
  }
  bVar1 = false;
LAB_8011cc84:
  if ((bVar1) &&
     (iVar2 = CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS
                        ((double)FLOAT_80331a78,2,1,param_2,param_1,0), iVar2 != 0)) {
    *(undefined2 *)(iVar2 + 0x560) = 1;
    *(short *)(iVar2 + 0x562) = (short)(param_1->object).m_scriptHandle[0xed];
    if (Game.game.m_gameWork.m_menuStageMode == '\0') {
      changeStat__8CGPrgObjFiii(param_1,0x1b,0,0);
    }
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

