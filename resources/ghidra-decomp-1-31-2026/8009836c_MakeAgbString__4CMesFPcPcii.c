// Function: MakeAgbString__4CMesFPcPcii
// Entry: 8009836c
// Size: 2136 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void MakeAgbString__4CMesFPcPcii(char *param_1,char *param_2,int param_3,int param_4)

{
  uint uVar1;
  byte bVar2;
  char *pcVar3;
  char cVar5;
  int iVar4;
  int iVar6;
  int iVar7;
  char *pcVar8;
  
  if (DAT_8032edb4 == '\0') {
    DAT_8032edb0 = &DAT_80330888;
    DAT_8032edb4 = '\x01';
  }
  iVar6 = 0;
  iVar7 = 0;
  do {
    cVar5 = *param_2;
    if (cVar5 == '\0') {
      return;
    }
    if (cVar5 == -1) {
      pcVar3 = param_2 + 2;
      pcVar8 = param_2 + 1;
      uVar1 = (byte)param_2[1] - 0xa0 & 0xff;
      switch(uVar1) {
      case 0:
        if (param_4 == 0) {
          *param_1 = '\n';
          param_1 = param_1 + 1;
        }
        else if (param_1[-1] == '-') {
          param_1 = param_1 + -1;
          *param_1 = '\0';
        }
        break;
      case 2:
      case 3:
      case 7:
      case 10:
      case 0xb:
      case 0xd:
      case 0xf:
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x15:
      case 0x16:
      case 0x17:
      case 0x18:
      case 0x23:
      case 0x24:
      case 0x25:
      case 0x26:
      case 0x27:
      case 0x28:
      case 0x29:
      case 0x55:
        if (System.m_execParam != 0) {
          Printf__7CSystemFPce(&System,s_Not_corresponding_TAG_is_used____801d9e30,uVar1 + 0xa0);
        }
        break;
      case 4:
        *param_1 = '\x1d';
        param_1 = param_1 + 1;
        break;
      case 5:
        *param_1 = '\x1c';
        param_1 = param_1 + 1;
        break;
      case 6:
        *param_1 = '\x1e';
        param_1 = param_1 + 1;
        break;
      case 8:
        strcpy(param_1,*(int *)(m_tempVar__4CMes + (char)(param_2[4] << 4 | param_2[5] & 0xfU) * 4)
                       * 0xc30 + -0x7fddf986);
        iVar4 = strlen(param_1);
        param_1 = param_1 + iVar4;
        pcVar8 = param_2 + 5;
        break;
      case 9:
      case 0x1d:
      case 0x37:
      case 0x39:
      case 0x3b:
      case 0x3d:
      case 0x3f:
        iVar4 = *(int *)(m_tempVar__4CMes +
                        (char)((byte)(((byte)param_2[4] & 0xf) << 4) | param_2[5] & 0xfU) * 4);
        if (uVar1 == 0x39) {
          strcpy(param_1,Game.game.m_cFlatDataArr[1].m_table[0].index[iVar4 * 5 + 3]);
        }
        else if (uVar1 < 0x39) {
          if (uVar1 == 0x1d) {
            strcpy(param_1,Game.game.m_cFlatDataArr[1].m_table[0].index[iVar4 * 5]);
          }
          else if (uVar1 < 0x1d) {
            if (uVar1 == 9) {
LAB_80098544:
              strcpy(param_1,Game.game.m_cFlatDataArr[1].m_table[0].index[iVar4 * 5 + 1]);
            }
          }
          else if (uVar1 == 0x37) goto LAB_80098544;
        }
        else if (uVar1 == 0x3d) {
          MakeArtItemName__5CGameFPcii
                    (&Game.game,param_1,iVar4,
                     *(uint *)(m_tempVar__4CMes + (char)(param_2[6] << 4 | param_2[7] & 0xfU) * 4) &
                     0xffff);
        }
        else if (uVar1 < 0x3d) {
          if (uVar1 == 0x3b) {
            MakeArtItemName__5CGameFPcii(&Game.game,param_1,iVar4,1);
          }
        }
        else if (uVar1 == 0x3f) {
          MakeNumItemName__5CGameFPcii
                    (&Game.game,param_1,iVar4,
                     *(uint *)(m_tempVar__4CMes + (char)(param_2[6] << 4 | param_2[7] & 0xfU) * 4) &
                     0xffff);
        }
        if (iVar6 != 0) {
          if (iVar6 == 1) {
            if (*param_1 != '\0') {
              toupper(param_1);
            }
          }
          else if (iVar6 == 2) {
            if (*param_1 != '\0') {
              cVar5 = _toupperLatin1();
              *param_1 = cVar5;
            }
          }
          else if (*param_1 != '\0') {
            tolower(param_1);
          }
          iVar6 = 0;
        }
        iVar4 = strlen(param_1);
        param_1 = param_1 + iVar4;
        pcVar8 = param_2 + 5;
        break;
      case 0xc:
      case 0xe:
      case 0x13:
      case 0x14:
        if (1 < (uint)System.m_execParam) {
          Printf__7CSystemFPce(&System,s_This_TAG_is_not_created___02x__801d9e10,uVar1 + 0xa0);
        }
        break;
      case 0x1e:
      case 0x2a:
      case 0x38:
      case 0x3a:
      case 0x3c:
      case 0x3e:
      case 0x40:
        iVar4 = *(int *)(m_tempVar__4CMes + (char)(param_2[4] << 4 | param_2[5] & 0xfU) * 4);
        switch(uVar1) {
        case 0x1e:
          strcpy(param_1,Game.game.m_cFlatDataArr[1].m_table[1].index[iVar4 * 5]);
          break;
        case 0x2a:
        case 0x38:
          strcpy(param_1,Game.game.m_cFlatDataArr[1].m_table[1].index[iVar4 * 5 + 1]);
          break;
        case 0x3a:
          strcpy(param_1,Game.game.m_cFlatDataArr[1].m_table[1].index[iVar4 * 5 + 3]);
          break;
        case 0x3c:
          MakeArtMonName__5CGameFPcii(&Game.game,param_1,iVar4,1);
          break;
        case 0x3e:
          MakeArtMonName__5CGameFPcii
                    (&Game.game,param_1,iVar4,
                     *(uint *)(m_tempVar__4CMes + (char)(param_2[6] << 4 | param_2[7] & 0xfU) * 4) &
                     0xffff);
          break;
        case 0x40:
          MakeNumMonName__5CGameFPcii
                    (&Game.game,param_1,iVar4,
                     *(uint *)(m_tempVar__4CMes + (char)(param_2[6] << 4 | param_2[7] & 0xfU) * 4) &
                     0xffff);
        }
        if (iVar6 != 0) {
          if (iVar6 == 1) {
            if (*param_1 != '\0') {
              toupper(param_1);
            }
          }
          else if (iVar6 == 2) {
            if (*param_1 != '\0') {
              cVar5 = _toupperLatin1();
              *param_1 = cVar5;
            }
          }
          else if (*param_1 != '\0') {
            tolower(param_1);
          }
          iVar6 = 0;
        }
        iVar4 = strlen(param_1);
        param_1 = param_1 + iVar4;
        pcVar8 = param_2 + 5;
        break;
      case 0x2b:
        strcpy(param_1,Game.game.m_cFlatDataArr[1].m_table[2].index
                       [*(int *)(m_tempVar__4CMes + (char)(param_2[4] << 4 | param_2[5] & 0xfU) * 4)
                       ]);
        iVar4 = strlen(param_1);
        param_1 = param_1 + iVar4;
        pcVar8 = param_2 + 5;
        break;
      case 0x2c:
        strcpy(param_1,Game.game.m_cFlatDataArr[1].m_table[3].index
                       [*(int *)(m_tempVar__4CMes + (char)(param_2[4] << 4 | param_2[5] & 0xfU) * 4)
                       ]);
        iVar4 = strlen(param_1);
        param_1 = param_1 + iVar4;
        pcVar8 = param_2 + 5;
        break;
      case 0x2d:
        strcpy(param_1,Game.game.m_cFlatDataArr[1].m_table[3].index
                       [*(int *)(m_tempVar__4CMes + (char)(param_2[4] << 4 | param_2[5] & 0xfU) * 4)
                        + 0x3c]);
        iVar4 = strlen(param_1);
        param_1 = param_1 + iVar4;
        pcVar8 = param_2 + 5;
        break;
      case 0x2e:
        strcpy(param_1,Game.game.m_cFlatDataArr[1].m_table[5].index
                       [*(int *)(m_tempVar__4CMes + (char)(*pcVar3 << 4 | param_2[3] & 0xfU) * 4)]);
        iVar4 = strlen(param_1);
        param_1 = param_1 + iVar4;
        pcVar8 = param_2 + 3;
        break;
      case 0x2f:
        strcpy(param_1,0x8021ff68);
        iVar4 = strlen(param_1);
        param_1 = param_1 + iVar4;
        break;
      case 0x30:
        sprintf(param_1,&DAT_8033088c,
                *(undefined4 *)(m_tempVar__4CMes + (char)(*pcVar3 << 4 | param_2[3] & 0xfU) * 4));
        iVar4 = strlen(param_1);
        param_1 = param_1 + iVar4;
        pcVar8 = param_2 + 3;
        break;
      case 0x41:
        bVar2 = *pcVar3 << 4 | param_2[3] & 0xfU;
        if (bVar2 == 1) {
          iVar6 = 1;
        }
        else {
          iVar6 = 2;
          if (bVar2 == 0) {
            iVar6 = 3;
          }
        }
        break;
      case 0x42:
        iVar7 = 2;
        if (*(int *)(m_tempVar__4CMes + (char)(*pcVar3 << 4 | param_2[3] & 0xfU) * 4) == 1) {
          iVar7 = 1;
        }
        break;
      case 0x44:
        iVar7 = 2;
        if (param_3 == 0) {
          iVar7 = 1;
        }
        break;
      case 0x45:
        iVar7 = 2;
        if (Game.game.m_caravanWorkArr
            [*(int *)(m_tempVar__4CMes + (char)(*pcVar3 << 4 | param_2[3] & 0xfU) * 4)].m_genderFlag
            == 0) {
          iVar7 = 1;
        }
        break;
      case 0x46:
        if (iVar7 == 1) {
          iVar7 = 2;
        }
        else if (iVar7 == 2) {
          iVar7 = 1;
        }
        break;
      case 0x47:
        iVar7 = 0;
        break;
      case 0x54:
        strcpy(param_1,DAT_8032edb0);
        iVar4 = strlen(param_1);
        param_1 = param_1 + iVar4;
      }
    }
    else {
      pcVar8 = param_2;
      if (iVar7 != 2) {
        *param_1 = cVar5;
        param_1 = param_1 + 1;
      }
    }
    param_2 = pcVar8 + 1;
  } while( true );
}

