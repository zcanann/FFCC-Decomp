// Function: LoadModel__8CGObjectFiUlUli
// Entry: 8007cc5c
// Size: 184 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadModel__8CGObjectFiUlUli
               (CGObject *gObject,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  CCharaPcsCHandle *handle;
  
  if (gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0) {
    __dt__Q29CCharaPcs7CHandleFv(gObject->m_charaModelHandle,1);
    gObject->m_charaModelHandle = (CCharaPcsCHandle *)0x0;
  }
  handle = (CCharaPcsCHandle *)
           __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci
                     (0x194,(CCharaPcsCHandle *)Game.game.m_mainStage,s_gobject_cpp_801d9bd0,0xa01);
  if (handle != (CCharaPcsCHandle *)0x0) {
    handle = (CCharaPcsCHandle *)__ct__Q29CCharaPcs7CHandleFv(handle);
  }
  gObject->m_charaModelHandle = handle;
  Add__Q29CCharaPcs7CHandleFv(gObject->m_charaModelHandle);
  LoadModel__Q29CCharaPcs7CHandleFiUlUlUliii
            (gObject->m_charaModelHandle,param_2,param_3,param_4,0,0xffffffff,0,param_5);
  return;
}

