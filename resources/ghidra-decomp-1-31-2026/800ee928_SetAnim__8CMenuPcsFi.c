// Function: SetAnim__8CMenuPcsFi
// Entry: 800ee928
// Size: 500 bytes

void SetAnim__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  uint uVar1;
  CCharaPcsCHandle *handle;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  handle = *(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + param_2 * 4);
  if (handle->m_charaKind != 3) {
    uVar1 = (uint)handle->m_charaNo / 100;
    iVar4 = uVar1 * 100;
    iVar3 = (uVar1 - 1) * 6;
    LoadAnim__Q29CCharaPcs7CHandleFPciiiiii(handle,s_stand_80331638,iVar3,1,0,iVar4,0xffffffff,0);
    LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
              (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + param_2 * 4),&DAT_80331640,iVar3 + 1,1
               ,0,iVar4,0xffffffff,0);
    LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
              (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + param_2 * 4),&DAT_80331648,iVar3 + 2,1
               ,0,iVar4,0xffffffff,0);
    LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
              (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + param_2 * 4),&DAT_8033164c,iVar3 + 3,3
               ,0,iVar4,0xffffffff,0);
    LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
              (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + param_2 * 4),&DAT_80331654,iVar3 + 4,1
               ,0,iVar4,0xffffffff,0);
    LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
              (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + param_2 * 4),&DAT_8033165c,iVar3 + 5,1
               ,0,iVar4,0xffffffff,0);
    iVar5 = param_2 * 0x14;
    *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar5) = 0;
    *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar5 + 4) = 0xffffffff;
    iVar2 = rand();
    iVar4 = iVar2 / 0xfa + (iVar2 >> 0x1f);
    *(int *)(*(int *)&menuPcs->field_0x844 + iVar5 + 8) = iVar2 + (iVar4 - (iVar4 >> 0x1f)) * -0xfa;
    SetAnim__Q29CCharaPcs7CHandleFiiiii
              (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + param_2 * 4),iVar3,0xffffffff,
               0xffffffff,
               -1 - ((*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + param_2 * 4))->
                     m_currentAnimIndex >> 0x1f),1);
    *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar5 + 0xc) =
         *(undefined4 *)(*(int *)(*(int *)(&menuPcs->field_0x7f4 + param_2 * 4) + 0x168) + 0xb4);
    *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar5 + 0x10) =
         *(undefined4 *)(*(int *)(*(int *)(&menuPcs->field_0x7f4 + param_2 * 4) + 0x168) + 0xc0);
  }
  return;
}

