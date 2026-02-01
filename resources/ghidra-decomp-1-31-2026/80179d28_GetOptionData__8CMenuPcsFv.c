// Function: GetOptionData__8CMenuPcsFv
// Entry: 80179d28
// Size: 256 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void GetOptionData__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar1 = countLeadingZeros((uint)Game.game.m_gameWork.m_gameInitFlag);
  menuPcs->field_0x8f = (char)(uVar1 >> 5);
  uVar3 = GetSoundMode__9CRedSoundFv(0x802f26dc);
  uVar1 = countLeadingZeros(uVar3);
  uVar1 = countLeadingZeros(uVar1 >> 5);
  menuPcs->field_0x90 = (char)(uVar1 >> 5);
  iVar2 = (int)Sound._8880_4_ / 10 + ((int)Sound._8880_4_ >> 0x1f);
  menuPcs->field_0x91 = (char)iVar2 - (char)(iVar2 >> 0x1f);
  iVar2 = (int)Sound._8884_4_ / 10 + ((int)Sound._8884_4_ >> 0x1f);
  menuPcs->field_0x92 = (char)iVar2 - (char)(iVar2 >> 0x1f);
  menuPcs->field_0xb5 = (byte)(-(uint)Game.game.m_gameWork.m_spModeFlags[0] >> 0x1f);
  menuPcs->field_0xb6 = (byte)(-(uint)Game.game.m_gameWork.m_spModeFlags[1] >> 0x1f);
  menuPcs->field_0xb7 = (byte)(-(uint)Game.game.m_gameWork.m_spModeFlags[2] >> 0x1f);
  menuPcs->field_0xb8 = (byte)(-(uint)Game.game.m_gameWork.m_spModeFlags[3] >> 0x1f);
  return;
}

