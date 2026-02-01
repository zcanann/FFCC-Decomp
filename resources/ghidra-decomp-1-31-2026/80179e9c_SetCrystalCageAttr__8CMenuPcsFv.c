// Function: SetCrystalCageAttr__8CMenuPcsFv
// Entry: 80179e9c
// Size: 244 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetCrystalCageAttr__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  undefined2 uVar1;
  
  if (*(short *)&menuPcs->field_0x88 != -1) {
    pppDeletePart__8CPartMngFi(&PartMng,(int)*(short *)&menuPcs->field_0x88);
  }
  if ((Game.game.m_gameWork.m_chaliceElement & 1U) == 0) {
    if ((Game.game.m_gameWork.m_chaliceElement & 2U) == 0) {
      if ((Game.game.m_gameWork.m_chaliceElement & 4U) == 0) {
        if ((Game.game.m_gameWork.m_chaliceElement & 8U) == 0) {
          if ((Game.game.m_gameWork.m_chaliceElement & 0x10U) != 0) {
            *(undefined2 *)&menuPcs->field_0x8a = 0x12;
            *(undefined4 *)&menuPcs->field_0x84 = 0x10;
          }
        }
        else {
          *(undefined2 *)&menuPcs->field_0x8a = 0x11;
          *(undefined4 *)&menuPcs->field_0x84 = 8;
        }
      }
      else {
        *(undefined2 *)&menuPcs->field_0x8a = 0x10;
        *(undefined4 *)&menuPcs->field_0x84 = 4;
      }
    }
    else {
      *(undefined2 *)&menuPcs->field_0x8a = 0xf;
      *(undefined4 *)&menuPcs->field_0x84 = 2;
    }
  }
  else {
    *(undefined2 *)&menuPcs->field_0x8a = 0xe;
    *(undefined4 *)&menuPcs->field_0x84 = 1;
  }
  uVar1 = BindEffect__8CMenuPcsFiii(menuPcs,5,(int)*(short *)&menuPcs->field_0x8a,0xffffffff);
  *(undefined2 *)&menuPcs->field_0x88 = uVar1;
  menuPcs->field_0x80 = 0;
  return;
}

