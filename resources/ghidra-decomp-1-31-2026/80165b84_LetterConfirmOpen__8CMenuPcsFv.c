// Function: LetterConfirmOpen__8CMenuPcsFv
// Entry: 80165b84
// Size: 1544 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

bool LetterConfirmOpen__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  uint8_t uVar1;
  uint32_t uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  char *pcVar5;
  int32_t iVar6;
  undefined4 uVar7;
  int iVar8;
  short local_420;
  short local_41e;
  char acStack_41c [128];
  undefined auStack_39c [128];
  char acStack_31c [128];
  undefined auStack_29c [128];
  undefined auStack_21c [128];
  undefined auStack_19c [128];
  undefined auStack_11c [128];
  undefined auStack_9c [140];
  
  uVar2 = Game.game.m_scriptFoodBase[0];
  uVar1 = Game.game.m_gameWork.m_languageId;
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xc) != '\0') goto LAB_8016615c;
  memset(acStack_41c,0,0x400);
  if (uVar1 == '\x03') {
    uVar4 = *(undefined4 *)
             ((int)Game.game.m_cFlatDataArr[1].m_table[2].index +
             (*(uint *)(uVar2 + DAT_8032eee8 * 0xc + 0x3ec) >> 7 & 0x7fc));
    uVar3 = GetMenuStr__8CMenuPcsFi(menuPcs,0x26);
    sprintf(acStack_41c,&DAT_8033316c,uVar3,uVar4);
  }
  else if (uVar1 < 3) {
    if ((uVar1 == '\x01') || (uVar1 == '\0')) {
LAB_80165d58:
      uVar7 = *(undefined4 *)
               ((int)Game.game.m_cFlatDataArr[1].m_table[2].index +
               (*(uint *)(uVar2 + DAT_8032eee8 * 0xc + 0x3ec) >> 7 & 0x7fc));
      uVar3 = GetMenuStr__8CMenuPcsFi(menuPcs,0x26);
      uVar4 = GetMenuStr__8CMenuPcsFi(menuPcs,0x25);
      sprintf(acStack_41c,s__s__s_s_80333184,uVar4,uVar7,uVar3);
    }
    else {
      uVar4 = *(undefined4 *)
               ((int)Game.game.m_cFlatDataArr[1].m_table[2].index +
               (*(uint *)(uVar2 + DAT_8032eee8 * 0xc + 0x3ec) >> 7 & 0x7fc));
      uVar3 = GetMenuStr__8CMenuPcsFi(menuPcs,0x26);
      sprintf(acStack_41c,&DAT_8033316c,uVar4,uVar3);
    }
  }
  else if (uVar1 == '\x05') {
    uVar4 = *(undefined4 *)
             ((int)Game.game.m_cFlatDataArr[1].m_table[2].index +
             (*(uint *)(uVar2 + DAT_8032eee8 * 0xc + 0x3ec) >> 7 & 0x7fc));
    uVar3 = GetMenuStr__8CMenuPcsFi(menuPcs,0x26);
    sprintf(acStack_41c,s__s__s__8033317c,uVar3,uVar4);
  }
  else {
    if (4 < uVar1) goto LAB_80165d58;
    uVar7 = *(undefined4 *)
             ((int)Game.game.m_cFlatDataArr[1].m_table[2].index +
             (*(uint *)(uVar2 + DAT_8032eee8 * 0xc + 0x3ec) >> 7 & 0x7fc));
    uVar3 = GetMenuStr__8CMenuPcsFi(menuPcs,0x25);
    uVar4 = GetMenuStr__8CMenuPcsFi(menuPcs,0x26);
    sprintf(acStack_41c,&DAT_80333174,uVar4,uVar7,uVar3);
  }
  if (uVar1 == '\x03') {
    uVar3 = GetMenuStr__8CMenuPcsFi(menuPcs,0x24);
    uVar4 = GetMenuStr__8CMenuPcsFi(menuPcs,0x23);
    uVar7 = GetMenuStr__8CMenuPcsFi(menuPcs,0x25);
    sprintf(auStack_39c,s__s_s_s_s__801dee14,uVar7,uVar4,s_ReplyStr,uVar3);
  }
  else if (((uVar1 < 3) && (uVar1 != '\x01')) && (uVar1 != '\0')) {
    uVar3 = GetMenuStr__8CMenuPcsFi(menuPcs,0x27);
    uVar4 = GetMenuStr__8CMenuPcsFi(menuPcs,0x24);
    uVar7 = GetMenuStr__8CMenuPcsFi(menuPcs,0x23);
    sprintf(auStack_39c,s__s_s_s_s_801dee08,uVar7,s_ReplyStr,uVar4,uVar3);
  }
  else {
    uVar3 = GetMenuStr__8CMenuPcsFi(menuPcs,0x24);
    uVar4 = GetMenuStr__8CMenuPcsFi(menuPcs,0x23);
    sprintf(auStack_39c,&DAT_80333174,uVar4,s_ReplyStr,uVar3);
  }
  iVar8 = 2;
  if (DAT_8032eeed != '\x02') {
    if (uVar1 == '\x02') {
      if (DAT_8032eeed == '\0') {
        iVar6 = Game.game.m_cFlatDataArr[1].m_table[0].index[DAT_8032eef0 * 5 + 4];
        uVar3 = GetMenuStr__8CMenuPcsFi(menuPcs,0x24);
        uVar4 = GetMenuStr__8CMenuPcsFi(menuPcs,0x23);
        sprintf(acStack_31c,&DAT_80333174,uVar4,iVar6,uVar3);
      }
      else if (DAT_8032eeed == '\x01') {
        uVar3 = GetMenuStr__8CMenuPcsFi(menuPcs,4);
        sprintf(acStack_31c,s__d__s_8033318c,DAT_8032eef0,uVar3);
      }
      pcVar5 = (char *)GetMenuStr__8CMenuPcsFi(menuPcs,0x28);
      strcat(acStack_31c,pcVar5);
    }
    else {
      uVar3 = GetMenuStr__8CMenuPcsFi(menuPcs,0x28);
      strcpy(acStack_31c,uVar3);
      if (DAT_8032eeed == '\0') {
        strcat(acStack_31c,
               (char *)Game.game.m_cFlatDataArr[1].m_table[0].index[DAT_8032eef0 * 5 + 4]);
      }
      else if (DAT_8032eeed == '\x01') {
        iVar8 = strlen(acStack_31c);
        uVar3 = GetMenuStr__8CMenuPcsFi(menuPcs,4);
        sprintf(acStack_31c + iVar8,s__d__s_8033318c,DAT_8032eef0,uVar3);
      }
    }
    iVar8 = 3;
  }
  pcVar5 = (char *)GetMenuStr__8CMenuPcsFi(menuPcs,0x21);
  strcat(acStack_41c + iVar8 * 0x80,pcVar5);
  strcpy(acStack_41c + (iVar8 + 1) * 0x80,&DAT_80333194);
  pcVar5 = (char *)GetMenuStr__8CMenuPcsFi(menuPcs,1);
  strcat(acStack_41c + (iVar8 + 1) * 0x80,pcVar5);
  strcpy(acStack_41c + (iVar8 + 2) * 0x80,&DAT_80333194);
  pcVar5 = (char *)GetMenuStr__8CMenuPcsFi(menuPcs,2);
  strcat(acStack_41c + (iVar8 + 2) * 0x80,pcVar5);
  SetSingDynamicWinMessInfo__8CMenuPcsFiPcPcPcPcPcPcPcPc
            (menuPcs,iVar8 + 3,acStack_41c,auStack_39c,acStack_31c,auStack_29c,auStack_21c,
             auStack_19c,auStack_11c,auStack_9c);
  GetSingWinSize__8CMenuPcsFiPsPsi(menuPcs,0,&local_41e,&local_420,1);
  SetMcWinInfo__8CMenuPcsFii(menuPcs,(int)local_41e,(int)local_420);
  *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28) = 0;
  *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 0xff;
  *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 1;
LAB_8016615c:
  return *(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1;
}

