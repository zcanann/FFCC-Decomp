// Function: pppConstructEraseCharaParts
// Entry: 80103fa8
// Size: 100 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructEraseCharaParts(pppEraseCharaParts *pppEraseCharaParts,UnkC *param_2)

{
  CCharaPcsCHandle *handle;
  int iVar1;
  undefined *puVar2;
  CGObject *gObject;
  
  gObject = (CGObject *)(pppMngStPtr->m_velocity).x;
  puVar2 = (undefined *)
           ((int)(&pppEraseCharaParts->field0_0x0 + 2) + param_2->m_serializedDataOffsets[1]);
  *puVar2 = 0x80;
  puVar2[1] = 0x80;
  puVar2[2] = 0x80;
  puVar2[3] = 0x80;
  handle = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl(gObject,0);
  iVar1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
  *(code **)(iVar1 + 0xfc) = EraseCharaParts_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
  return;
}

