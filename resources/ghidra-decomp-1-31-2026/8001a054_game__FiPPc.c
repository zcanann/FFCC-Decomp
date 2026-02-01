// Function: game__FiPPc
// Entry: 8001a054
// Size: 476 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void game__FiPPc(int param_1,int param_2)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  
  Init__5CGameFv(&Game.game);
  strcpy(0x8022b7b4,&DAT_8032f718);
  if (param_1 != 0) {
    puVar5 = (undefined4 *)(param_2 + 4);
    bVar2 = false;
    bVar3 = false;
    for (iVar6 = 1; iVar6 < param_1; iVar6 = iVar6 + 1) {
      if (bVar2) {
        strcpy(0x8022b7b4,*puVar5);
        bVar2 = false;
      }
      else if (bVar3) {
        iVar4 = strcmp(*puVar5,&DAT_8032f720);
        if (iVar4 == 0) {
          Game.game.m_gameWork.m_languageId = '\x01';
        }
        else {
          iVar4 = strcmp(*puVar5,&DAT_8032f724);
          if (iVar4 == 0) {
            Game.game.m_gameWork.m_languageId = '\x01';
          }
          else {
            iVar4 = strcmp(*puVar5,&DAT_8032f728);
            if (iVar4 == 0) {
              Game.game.m_gameWork.m_languageId = '\x02';
            }
            else {
              iVar4 = strcmp(*puVar5,&DAT_8032f72c);
              if (iVar4 == 0) {
                Game.game.m_gameWork.m_languageId = '\x03';
              }
              else {
                iVar4 = strcmp(*puVar5,&DAT_8032f730);
                if (iVar4 == 0) {
                  Game.game.m_gameWork.m_languageId = '\x04';
                }
                else {
                  iVar4 = strcmp(*puVar5,&DAT_8032f734);
                  if (iVar4 == 0) {
                    Game.game.m_gameWork.m_languageId = '\x05';
                  }
                  else {
                    Game.game.m_gameWork.m_languageId = '\0';
                  }
                }
              }
            }
          }
        }
        bVar3 = false;
      }
      else {
        cVar1 = *(char *)*puVar5;
        if ((cVar1 == '-') || (cVar1 == '/')) {
          cVar1 = ((char *)*puVar5)[1];
          if (cVar1 == 'l') {
            bVar3 = true;
          }
          else if ((cVar1 < 'l') && (cVar1 == 'f')) {
            bVar2 = true;
          }
        }
      }
      puVar5 = puVar5 + 1;
    }
  }
  Exec__5CGameFv(&Game.game);
  Quit__5CGameFv(&Game.game);
  return;
}

