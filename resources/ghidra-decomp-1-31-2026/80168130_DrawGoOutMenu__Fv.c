// Function: DrawGoOutMenu__Fv
// Entry: 80168130
// Size: 676 bytes

/* WARNING: Removing unreachable block (ram,0x801683b4) */
/* WARNING: Removing unreachable block (ram,0x80168140) */

void DrawGoOutMenu__Fv(void)

{
  uint uVar1;
  double dVar2;
  double local_38;
  undefined8 local_30;
  
  DAT_8032ef08 = &g_GoOutMenu;
  if (g_GoOutMenu._44_1_ == '\x03') {
    DrawInit__8CMenuPcsFv(&MenuPcs);
    DrawCMakeMenu__8CMenuPcsFv(&MenuPcs);
    if ((g_GoOutMenu._36_1_ == '\x01') && (*(short *)(MenuPcs._2092_4_ + 0x20) != 0)) {
      *(undefined2 *)(MenuPcs._2092_4_ + 0x1c) = 8;
      SetMainMode__10CGoOutMenuFUc(&g_GoOutMenu,1);
      *(undefined2 *)(MenuPcs._2092_4_ + 0x20) = 0;
    }
  }
  else if (((char)g_GoOutMenu._44_1_ < '\x03') && ('\x01' < (char)g_GoOutMenu._44_1_)) {
    if (g_GoOutMenu._29_1_ != '\0') {
      DrawInit__8CMenuPcsFv(&MenuPcs);
      DrawCMakeMenu__8CMenuPcsFv(&MenuPcs);
    }
    if (((g_GoOutMenu._24_1_ != '\x0f') && ((char)g_GoOutMenu._24_1_ < '\x0f')) &&
       ('\r' < (char)g_GoOutMenu._24_1_)) {
      DrawLoadMenu__8CMenuPcsFv(&MenuPcs);
    }
    if ((g_GoOutMenu._24_1_ == '\x01') && (*(short *)(MenuPcs._2092_4_ + 0x20) != 0)) {
      *(undefined2 *)(MenuPcs._2092_4_ + 0x1c) = 8;
      SetMainMode__10CGoOutMenuFUc(&g_GoOutMenu,1);
      *(undefined2 *)(MenuPcs._2092_4_ + 0x20) = 0;
    }
  }
  if ((g_GoOutMenu._54_2_ != -1) &&
     (DrawMcWin__8CMenuPcsFss(&MenuPcs,0xffff,0), *(short *)(MenuPcs._2120_4_ + 10) == 1)) {
    uVar1 = (uint)(short)g_GoOutMenu._54_2_;
    DrawMcWinMess__8CMenuPcsFii(&MenuPcs,uVar1,~-((uint)(uVar1 < 0x1e) - ((int)uVar1 >> 0x1f)) & 2);
  }
  if ((*(short *)(MenuPcs._2120_4_ + 10) == 1) && (g_GoOutMenu._71_1_ != '\0')) {
    local_38 = (double)(CONCAT44(0x43300000,
                                 (int)*(short *)(MenuPcs._2120_4_ + 2) +
                                 *(short *)(MenuPcs._2120_4_ + 6) + -0x3e) ^ 0x80000000);
    dVar2 = (double)(float)(local_38 - DOUBLE_803331d0);
    local_30 = (double)CONCAT44(0x43300000,(int)*(short *)MenuPcs._2120_4_ + 0x20U ^ 0x80000000);
    if (g_GoOutMenu._73_1_ == '\0') {
      uVar1 = GetYesNoXPos__8CMenuPcsFi(&MenuPcs,(uint)(byte)g_GoOutMenu._70_1_);
      local_30 = (double)CONCAT44(0x43300000,uVar1 ^ 0x80000000);
      DrawCursor__8CMenuPcsFiif
                ((double)FLOAT_803331c8,&MenuPcs,(int)(local_30 - DOUBLE_803331d0),(int)dVar2);
    }
    else {
      DrawCursor__8CMenuPcsFiif
                ((double)FLOAT_803331c8,&MenuPcs,(int)(local_30 - DOUBLE_803331d0),
                 (int)(short)g_GoOutMenu._76_2_ + (uint)(byte)g_GoOutMenu._70_1_ * 0x1e);
    }
  }
  return;
}

