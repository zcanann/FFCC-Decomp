// Function: pppConstructEmission
// Entry: 800e6554
// Size: 160 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructEmission(pppEmission *pppEmission,UnkC *param_2)

{
  float fVar1;
  CCharaPcsCHandle *handle;
  int iVar2;
  undefined4 *puVar3;
  
  fVar1 = FLOAT_803311f8;
  puVar3 = (undefined4 *)((int)(&pppEmission->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2])
  ;
  puVar3[1] = 0;
  *(undefined *)(puVar3 + 2) = 0x80;
  *(undefined *)((int)puVar3 + 9) = 0x80;
  *(undefined *)((int)puVar3 + 10) = 0x80;
  *(undefined *)((int)puVar3 + 0xb) = 0x80;
  puVar3[5] = fVar1;
  puVar3[4] = fVar1;
  puVar3[3] = fVar1;
  handle = (CCharaPcsCHandle *)
           GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).x,0);
  iVar2 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
  *(code **)(iVar2 + 0xfc) = Emission_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
  *(code **)(iVar2 + 0x104) = Emission_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f;
  *puVar3 = 0;
  puVar3[6] = *(undefined4 *)(iVar2 + 0x9c);
  *(undefined *)(puVar3 + 7) = 0;
  return;
}

