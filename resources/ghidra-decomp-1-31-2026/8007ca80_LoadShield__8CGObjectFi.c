// Function: LoadShield__8CGObjectFi
// Entry: 8007ca80
// Size: 232 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadShield__8CGObjectFi(CGObject *gObject,int param_2)

{
  CCharaPcsCHandle *handle;
  int16_t iVar1;
  undefined2 uVar2;
  
  if (gObject->m_shieldModelHandle != (CCharaPcsCHandle *)0x0) {
    __dt__Q29CCharaPcs7CHandleFv(gObject->m_shieldModelHandle,1);
    gObject->m_shieldModelHandle = (CCharaPcsCHandle *)0x0;
  }
  if (0 < param_2) {
    handle = (CCharaPcsCHandle *)
             __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci
                       (0x194,(CCharaPcsCHandle *)Game.game.m_mainStage,s_gobject_cpp_801d9bd0,0xa23
                       );
    if (handle != (CCharaPcsCHandle *)0x0) {
      handle = (CCharaPcsCHandle *)__ct__Q29CCharaPcs7CHandleFv(handle);
    }
    gObject->m_shieldModelHandle = handle;
    Add__Q29CCharaPcs7CHandleFv(gObject->m_shieldModelHandle);
    if (gObject->m_ownerType == '\0') {
      uVar2 = *(undefined2 *)((int)gObject->m_scriptHandle + 0x3e2);
    }
    else {
      uVar2 = 0;
    }
    LoadModel__Q29CCharaPcs7CHandleFiUlUlUliii
              (gObject->m_shieldModelHandle,4,param_2,0,uVar2,0xffffffff,0,1);
    iVar1 = SearchNode__Q26CChara6CModelFPc(gObject->m_charaModelHandle->m_model,&DAT_80330380);
    gObject->m_shieldAttachNodeIndex = iVar1;
  }
  return;
}

