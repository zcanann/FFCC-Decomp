// Function: GetRaceStr__8CMenuPcsFiPc
// Entry: 80145c84
// Size: 748 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void GetRaceStr__8CMenuPcsFiPc(CMenuPcs *menuPcs,int param_2,char *param_3)

{
  ushort uVar1;
  uint uVar2;
  undefined *puVar3;
  char *pcVar4;
  
  GetItemType__8CMenuPcsFii(menuPcs,param_2,1);
  uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + param_2 * 0x48 + 4);
  *param_3 = '\0';
  if ((uVar1 & 0xf) == 0xf) {
    puVar3 = PTR_s_Tutti_802143ec;
    if (Game.game.m_gameWork.m_languageId != '\x03') {
      if (Game.game.m_gameWork.m_languageId < 3) {
        if ((Game.game.m_gameWork.m_languageId != '\x01') &&
           (puVar3 = PTR_s_Alle_Rassen_8021430c, Game.game.m_gameWork.m_languageId != '\0'))
        goto LAB_80145d60;
      }
      else {
        puVar3 = PTR_s_Todos_802145ac;
        if ((Game.game.m_gameWork.m_languageId == '\x05') ||
           (puVar3 = PTR_DAT_802144cc, Game.game.m_gameWork.m_languageId < 5)) goto LAB_80145d60;
      }
      puVar3 = PTR_DAT_8021422c;
    }
LAB_80145d60:
    strcpy(param_3,puVar3);
    return;
  }
  uVar2 = 0;
  if (((((uVar1 & 1) == 0) && (uVar2 = 1, (uVar1 & 2) == 0)) && (uVar2 = 2, (uVar1 & 4) == 0)) &&
     (uVar2 = 3, (uVar1 & 8) == 0)) {
    uVar2 = 4;
  }
  if (uVar2 < 4) {
    if (Game.game.m_gameWork.m_languageId == '\x03') {
      puVar3 = (&PTR_s_Clavat_80214110)[uVar2];
    }
    else if (Game.game.m_gameWork.m_languageId < 3) {
      if ((Game.game.m_gameWork.m_languageId == '\x01') ||
         (Game.game.m_gameWork.m_languageId == '\0')) {
LAB_80145e44:
        puVar3 = (&PTR_s_Clavat_802140f0)[uVar2];
      }
      else {
        puVar3 = (&PTR_s_Clavat_80214100)[uVar2];
      }
    }
    else if (Game.game.m_gameWork.m_languageId == '\x05') {
      puVar3 = (&PTR_s_Clavate_80214130)[uVar2];
    }
    else {
      if (4 < Game.game.m_gameWork.m_languageId) goto LAB_80145e44;
      puVar3 = (&PTR_s_Clavat_80214120)[uVar2];
    }
    strcpy(param_3,puVar3);
    if (Game.game.m_gameWork.m_languageId == '\x02') {
      strcat(param_3,&DAT_80332958);
    }
  }
  if (((uVar1 & 0xf) != 0) && ((uVar1 & 0x30) != 0)) {
    strcpy(param_3,&DAT_8033295c);
  }
  if ((uVar1 & 0x30) == 0) {
    return;
  }
  uVar2 = (uVar1 & 0x30) >> 5;
  if (Game.game.m_gameWork.m_languageId == '\x03') {
    pcVar4 = (&PTR_s_Maschio_802143e4)[uVar2];
    goto LAB_80145f48;
  }
  if (Game.game.m_gameWork.m_languageId < 3) {
    if ((Game.game.m_gameWork.m_languageId != '\x01') && (Game.game.m_gameWork.m_languageId != '\0')
       ) {
      pcVar4 = (&PTR_DAT_80214304)[uVar2];
      goto LAB_80145f48;
    }
  }
  else {
    if (Game.game.m_gameWork.m_languageId == '\x05') {
      pcVar4 = (&PTR_s_Hombre_802145a4)[uVar2];
      goto LAB_80145f48;
    }
    if (Game.game.m_gameWork.m_languageId < 5) {
      pcVar4 = (&PTR_s_Masculin_802144c4)[uVar2];
      goto LAB_80145f48;
    }
  }
  pcVar4 = (&PTR_DAT_80214224)[uVar2];
LAB_80145f48:
  strcat(param_3,pcVar4);
  return;
}

