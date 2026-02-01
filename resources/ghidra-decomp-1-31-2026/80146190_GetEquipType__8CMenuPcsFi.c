// Function: GetEquipType__8CMenuPcsFi
// Entry: 80146190
// Size: 188 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 GetEquipType__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  ushort uVar1;
  undefined4 unaff_r31;
  
  uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + param_2 * 0x48 + 4);
  if ((uVar1 & 0x100) == 0) {
    if ((uVar1 & 0x400) == 0) {
      if ((uVar1 & 0xa00) == 0) {
        if ((uVar1 & 0x3000) == 0) {
          if (System.m_execParam != 0) {
            Printf__7CSystemFPce
                      (&System,s__s__d___item____d_m_equip____08x_801de8b0,s_singmenu_cpp_801de8d4,
                       0xd3d,param_2);
          }
        }
        else {
          unaff_r31 = 3;
        }
      }
      else {
        unaff_r31 = 2;
      }
    }
    else {
      unaff_r31 = 1;
    }
  }
  else {
    unaff_r31 = 0;
  }
  return unaff_r31;
}

