// Function: pppConstructBlurChara
// Entry: 800de22c
// Size: 112 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructBlurChara(pppBlurChara *pppBlurChara,UnkC *param_2)

{
  CGObject *gObject;
  CCharaPcsCHandle *handle;
  int iVar1;
  undefined4 *puVar2;
  
  gObject = (CGObject *)(pppMngStPtr->m_velocity).y;
  puVar2 = (undefined4 *)
           ((int)(&pppBlurChara->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  puVar2[1] = gObject;
  handle = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl(gObject,0);
  iVar1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
  *(code **)(iVar1 + 0x108) = BlurChara_AfterDrawModelCallback__FPQ26CChara6CModelPvPv;
  *puVar2 = 0;
  puVar2[2] = 0;
  puVar2[3] = *(undefined4 *)(iVar1 + 0x9c);
  return;
}

