// Function: LetterReplyWinOpen__8CMenuPcsFv
// Entry: 80166194
// Size: 764 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

bool LetterReplyWinOpen__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  uint8_t uVar1;
  uint32_t uVar2;
  void *ptr;
  undefined *ptr_00;
  undefined *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined *puVar7;
  char *pcVar8;
  short local_430;
  short local_42e;
  char acStack_42c [128];
  undefined auStack_3ac [128];
  undefined auStack_32c [128];
  undefined auStack_2ac [128];
  undefined auStack_22c [128];
  undefined auStack_1ac [128];
  undefined auStack_12c [128];
  undefined auStack_ac [136];
  
  uVar2 = Game.game.m_scriptFoodBase[0];
  uVar1 = Game.game.m_gameWork.m_languageId;
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xc) == '\0') {
    memset(acStack_42c,0,0x400);
    uVar4 = MenuPcs._236_4_;
    if (Game.game.m_gameWork.m_menuStageMode != '\0') {
      uVar4 = MenuPcs._244_4_;
    }
    ptr = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x400,uVar4,s_menu_letter_cpp_801dedf8,0x323);
    uVar4 = MenuPcs._236_4_;
    if (Game.game.m_gameWork.m_menuStageMode != '\0') {
      uVar4 = MenuPcs._244_4_;
    }
    ptr_00 = (undefined *)
             __nwa__FUlPQ27CMemory6CStagePci(0x400,uVar4,s_menu_letter_cpp_801dedf8,0x325);
    memset(ptr,0,0x400);
    memset(ptr_00,0,0x400);
    strcpy(ptr,*(undefined4 *)
                ((int)Game.game.m_cFlatDataArr[1].m_mesPtr +
                (*(ushort *)(uVar2 + DAT_8032eee8 * 0xc + 0x3ec) & 0x7fc) * 2 + 0x44));
    MakeAgbString__4CMesFPcPcii(ptr_00,ptr,*(undefined2 *)(uVar2 + 0x3e2),0);
    DAT_8032eeeb = '\0';
    pcVar8 = acStack_42c;
    iVar6 = 0;
    puVar7 = ptr_00;
    do {
      puVar3 = (undefined *)strchr(puVar7,10);
      if (puVar3 != (undefined *)0x0) {
        *puVar3 = 0;
      }
      if (uVar1 == '\x02') {
        uVar4 = GetMenuStr__8CMenuPcsFi(menuPcs,0x24);
        uVar5 = GetMenuStr__8CMenuPcsFi(menuPcs,0x23);
        sprintf(pcVar8,&DAT_80333174,uVar5,puVar7,uVar4);
      }
      else {
        uVar4 = GetMenuStr__8CMenuPcsFi(menuPcs,0x24);
        uVar5 = GetMenuStr__8CMenuPcsFi(menuPcs,0x23);
        sprintf(pcVar8,&DAT_80333174,uVar5,puVar7,uVar4);
      }
      DAT_8032eeeb = DAT_8032eeeb + '\x01';
      if (puVar3 == (undefined *)0x0) break;
      iVar6 = iVar6 + 1;
      puVar7 = puVar3 + 1;
      pcVar8 = pcVar8 + 0x80;
    } while (iVar6 < 7);
    __dla__FPv(ptr);
    __dla__FPv(ptr_00);
    pcVar8 = (char *)GetMenuStr__8CMenuPcsFi(menuPcs,3);
    iVar6 = (int)DAT_8032eeeb;
    DAT_8032eeeb = DAT_8032eeeb + '\x01';
    strcat(acStack_42c + iVar6 * 0x80,pcVar8);
    SetSingDynamicWinMessInfo__8CMenuPcsFiPcPcPcPcPcPcPcPc
              (menuPcs,(int)DAT_8032eeeb,acStack_42c,auStack_3ac,auStack_32c,auStack_2ac,auStack_22c
               ,auStack_1ac,auStack_12c,auStack_ac);
    GetSingWinSize__8CMenuPcsFiPsPsi(menuPcs,0,&local_42e,&local_430,1);
    SetMcWinInfo__8CMenuPcsFii(menuPcs,(int)local_42e,(int)local_430);
    *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 0xff;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 1;
  }
  return *(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1;
}

