// Function: SetAnim__Q29CCharaPcs7CHandleFiiiii
// Entry: 80075400
// Size: 232 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
SetAnim__Q29CCharaPcs7CHandleFiiiii
          (CCharaPcsCHandle *param_1,int param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5,int param_6)

{
  undefined4 uVar1;
  CChara *chara;
  
  if (param_1->m_model == (CModel *)0x0) {
    uVar1 = 0;
  }
  else if ((param_1->m_currentAnimIndex == param_2) && (param_6 == 0)) {
    uVar1 = 0;
  }
  else {
    if (param_2 == -1) {
      chara = (CChara *)0x0;
    }
    else if (param_1->m_animSlot[param_2] == (CRef *)0x0) {
      chara = (CChara *)0x0;
    }
    else {
      chara = (CChara *)param_1->m_animSlot[param_2][5].vtable;
    }
    if (chara == (CChara *)0x0) {
      if ((param_1->m_charaKind != 3) && (1 < (uint)System.m_execParam)) {
        Printf__7CSystemFPce(&System,&DAT_801d91f8,param_1->m_charaKind,param_1->m_charaNo,param_2);
      }
      uVar1 = 0;
    }
    else {
      AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii
                (param_1->m_model,chara,param_3,param_4,param_5);
      param_1->m_currentAnimIndex = param_2;
      uVar1 = 1;
    }
  }
  return uVar1;
}

