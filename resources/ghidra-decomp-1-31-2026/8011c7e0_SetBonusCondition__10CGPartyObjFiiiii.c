// Function: SetBonusCondition__10CGPartyObjFiiiii
// Entry: 8011c7e0
// Size: 488 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetBonusCondition__10CGPartyObjFiiiii
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  undefined4 unaff_r31;
  undefined4 uVar11;
  int iVar12;
  int local_58 [5];
  
  uVar9 = 0x10;
  if (Game.game.m_gameWork.m_radarType != '\0') {
    uVar9 = 4;
  }
  Printf__7CSystemFPce(&System,&DAT_801dcb5c,uVar9);
  iVar10 = -0x7fde1140;
  iVar7 = 0;
  iVar4 = 0;
  iVar6 = 0;
  iVar8 = Game.game.m_bossArtifactBase + Game.game.m_gameWork.m_bossArtifactStageIndex * 0x168;
  do {
    iVar5 = *(int *)(iVar10 + 0xc5b0);
    uVar11 = unaff_r31;
    if (iVar5 != 0) {
      if (param_1 == 0) {
        uVar11 = param_4;
        if (iVar6 != 2) {
          if (iVar6 < 2) {
            uVar11 = param_2;
            if ((iVar6 != 0) && (uVar11 = param_3, iVar6 < 0)) {
              uVar11 = unaff_r31;
            }
          }
          else {
            uVar11 = unaff_r31;
            if (iVar6 < 4) {
              uVar11 = param_5;
            }
          }
        }
        SetBonusCondition__12CCaravanWorkFi(*(CCaravanWork **)(iVar5 + 0x58),uVar11);
        if (2 < (uint)System.m_execParam) {
          Printf__7CSystemFPce(&System,&DAT_801dcb9c,iVar6,uVar11);
        }
      }
      else {
        do {
          iVar1 = Rand__5CMathFUl(&Math,uVar9);
          piVar3 = local_58;
          iVar2 = 0;
          iVar12 = iVar7;
          if (0 < iVar7) {
            do {
              if (iVar1 == *piVar3) break;
              piVar3 = piVar3 + 1;
              iVar2 = iVar2 + 1;
              iVar12 = iVar12 + -1;
            } while (iVar12 != 0);
          }
        } while (iVar2 != iVar7);
        *(int *)((int)local_58 + iVar4) = iVar1;
        iVar7 = iVar7 + 1;
        iVar4 = iVar4 + 4;
        SetBonusCondition__12CCaravanWorkFi
                  (*(CCaravanWork **)(iVar5 + 0x58),(uint)*(ushort *)(iVar8 + iVar1 * 2));
        if (2 < (uint)System.m_execParam) {
          Printf__7CSystemFPce(&System,&DAT_801dcb7c,iVar6,iVar1,*(undefined2 *)(iVar8 + iVar1 * 2))
          ;
        }
      }
      CalcStatus__12CCaravanWorkFv(*(undefined4 *)(iVar5 + 0x58));
    }
    iVar6 = iVar6 + 1;
    iVar10 = iVar10 + 4;
    unaff_r31 = uVar11;
    if (3 < iVar6) {
      return;
    }
  } while( true );
}

