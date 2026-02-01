// Function: PCAnimCtrl__8CMenuPcsFv
// Entry: 800f26f4
// Size: 1036 bytes

void PCAnimCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  int iVar2;
  CModel *pCVar3;
  int iVar4;
  CCharaPcsCHandle *pCVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  CMenuPcs *pCVar9;
  
  uVar7 = 0;
  iVar2 = *(int *)&menuPcs->field_0x828;
  if ((*(char *)(iVar2 + 0xd) != '\0') && (*(char *)(iVar2 + 10) != '\0')) {
    uVar7 = 1 << (int)*(short *)(iVar2 + 4);
  }
  if ((*(char *)(iVar2 + 0x1d) != '\0') && (*(char *)(iVar2 + 0x1a) != '\0')) {
    uVar7 = uVar7 | 1 << (int)*(short *)(iVar2 + 0x14);
  }
  if ((*(char *)(iVar2 + 0x2d) != '\0') && (*(char *)(iVar2 + 0x2a) != '\0')) {
    uVar7 = uVar7 | 1 << (int)*(short *)(iVar2 + 0x24);
  }
  if ((*(char *)(iVar2 + 0x3d) != '\0') && (*(char *)(iVar2 + 0x3a) != '\0')) {
    uVar7 = uVar7 | 1 << (int)*(short *)(iVar2 + 0x34);
  }
  piVar6 = *(int **)&menuPcs->field_0x844;
  iVar2 = 0;
  pCVar9 = menuPcs;
  do {
    pCVar5 = *(CCharaPcsCHandle **)&pCVar9->field_0x7f4;
    pCVar3 = pCVar5->m_model;
    iVar4 = -1 - (pCVar5->m_currentAnimIndex >> 0x1f);
    if (((pCVar3 != (CModel *)0x0) && (pCVar3->m_texSet != (CTextureSet *)0x0)) &&
       (pCVar5->m_charaKind != 3)) {
      piVar6[3] = (int)pCVar3->m_time;
      if (piVar6[1] < 0) {
        uVar8 = uVar7 & 1 << iVar2;
        if (((uVar8 == 0) && (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) != 8)) &&
           ((*piVar6 == 0 && (2999 < piVar6[2])))) {
          *piVar6 = 4;
          SetAnim__Q29CCharaPcs7CHandleFiiiii
                    (pCVar5,(*(uint *)(*(int *)&pCVar9->field_0x7f4 + 4) / 100 - 1) * 6 + *piVar6,
                     0xffffffff,0xffffffff,iVar4,0);
          piVar6[3] = (int)pCVar5->m_model->m_time;
          piVar6[4] = (int)pCVar5->m_model->m_animEnd;
          piVar6[2] = 0;
        }
        else if ((uVar8 == 0) || (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) == 8)) {
LAB_800f2a00:
          if ((float)piVar6[4] <= (float)piVar6[3]) {
            iVar1 = *piVar6;
            if (((iVar1 == 3) || (iVar1 == 4)) || (iVar1 == 5)) {
              *piVar6 = 0;
              SetAnim__Q29CCharaPcs7CHandleFiiiii
                        (pCVar5,(*(uint *)(*(int *)&pCVar9->field_0x7f4 + 4) / 100 - 1) * 6 +
                                *piVar6,0xffffffff,0xffffffff,iVar4,0);
              piVar6[3] = (int)pCVar5->m_model->m_time;
              piVar6[4] = (int)pCVar5->m_model->m_animEnd;
              if (uVar8 == 0) {
                piVar6[2] = 0;
              }
              else {
                piVar6[2] = 0x834;
              }
            }
            SetFrame__Q26CChara6CModelFf(FLOAT_803313dc,pCVar5->m_model);
            piVar6[2] = piVar6[2] + 1;
          }
          else {
            AddFrame__Q26CChara6CModelFf((double)FLOAT_80331698,pCVar5->m_model);
            piVar6[2] = piVar6[2] + 1;
          }
        }
        else {
          iVar1 = *piVar6;
          if ((iVar1 == 1) && (11999 < piVar6[2])) {
            *piVar6 = 0;
            piVar6[2] = 0;
          }
          else if ((iVar1 == 2) && (8999 < piVar6[2])) {
            *piVar6 = 1;
          }
          else if ((iVar1 == 1) && ((5999 < piVar6[2] && (piVar6[2] < 9000)))) {
            *piVar6 = 2;
          }
          else {
            if ((iVar1 != 0) || (piVar6[2] < 3000)) goto LAB_800f2a00;
            *piVar6 = 1;
          }
          SetAnim__Q29CCharaPcs7CHandleFiiiii
                    (pCVar5,(*(uint *)(*(int *)&pCVar9->field_0x7f4 + 4) / 100 - 1) * 6 + *piVar6,
                     0xffffffff,0xffffffff,iVar4,0);
          piVar6[3] = (int)pCVar5->m_model->m_time;
          piVar6[4] = (int)pCVar5->m_model->m_animEnd;
        }
      }
      else {
        *piVar6 = piVar6[1];
        piVar6[1] = -1;
        SetAnim__Q29CCharaPcs7CHandleFiiiii
                  (pCVar5,(*(uint *)(*(int *)&pCVar9->field_0x7f4 + 4) / 100 - 1) * 6 + *piVar6,
                   0xffffffff,0xffffffff,iVar4,0);
        piVar6[3] = (int)pCVar5->m_model->m_time;
        piVar6[4] = (int)pCVar5->m_model->m_animEnd;
        piVar6[2] = 0;
      }
    }
    iVar2 = iVar2 + 1;
    piVar6 = piVar6 + 5;
    pCVar9 = (CMenuPcs *)&pCVar9->field_0x4;
    if (7 < iVar2) {
      return;
    }
  } while( true );
}

