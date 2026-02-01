// Function: LetterSetAttachItem__8CMenuPcsFUii
// Entry: 8016394c
// Size: 64 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LetterSetAttachItem__8CMenuPcsFUii(CMenuPcs *menuPcs,int param_2,undefined4 param_3)

{
  DAT_8032eef0 = param_2;
  if (DAT_8032eeed == '\0') {
    DAT_8032eeee = (undefined)param_2;
    DAT_8032eef0 = (int)*(short *)(Game.game.m_scriptFoodBase[0] + param_2 * 2 + 0xb6);
  }
  DAT_8032eef4 = param_3;
  return;
}

