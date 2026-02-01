// Function: LoadWeapon__8CGObjectFii
// Entry: 8007cb68
// Size: 244 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadWeapon__8CGObjectFii(CGObject *gObject,int param_2,int param_3)

{
  CCharaPcsCHandle *handle;
  int16_t iVar1;
  undefined2 uVar2;
  
  if (gObject->m_weaponModelHandle != (CCharaPcsCHandle *)0x0) {
    __dt__Q29CCharaPcs7CHandleFv(gObject->m_weaponModelHandle,1);
    gObject->m_weaponModelHandle = (CCharaPcsCHandle *)0x0;
  }
  if (0 < param_2) {
    handle = (CCharaPcsCHandle *)
             __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci
                       (0x194,(CCharaPcsCHandle *)Game.game.m_mainStage,s_gobject_cpp_801d9bd0,0xa11
                       );
    if (handle != (CCharaPcsCHandle *)0x0) {
      handle = (CCharaPcsCHandle *)__ct__Q29CCharaPcs7CHandleFv(handle);
    }
    gObject->m_weaponModelHandle = handle;
    Add__Q29CCharaPcs7CHandleFv(gObject->m_weaponModelHandle);
    if (gObject->m_ownerType == '\0') {
      uVar2 = *(undefined2 *)((int)gObject->m_scriptHandle + 0x3e2);
    }
    else {
      uVar2 = 0;
    }
    LoadModel__Q29CCharaPcs7CHandleFiUlUlUliii
              (gObject->m_weaponModelHandle,4,param_2,param_3,uVar2,0xffffffff,0,1);
    iVar1 = SearchNode__Q26CChara6CModelFPc(gObject->m_charaModelHandle->m_model,s_r_item_80330388);
    gObject->m_weaponAttachNode = iVar1;
  }
  return;
}

