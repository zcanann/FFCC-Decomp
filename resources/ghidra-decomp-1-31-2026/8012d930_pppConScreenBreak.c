// Function: pppConScreenBreak
// Entry: 8012d930
// Size: 208 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConScreenBreak(pppScreenBreak *pppScreenBreak,UnkC *param_2)

{
  float fVar1;
  CCharaPcsCHandle *handle;
  int iVar2;
  CGObject *gObject;
  float *pfVar3;
  
  gObject = (CGObject *)(pppMngStPtr->m_velocity).x;
  pfVar3 = (float *)((int)(&pppScreenBreak->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  handle = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl(gObject,0);
  iVar2 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
  gObject->m_displayFlags = gObject->m_displayFlags | 0x40;
  *(code **)(iVar2 + 0xf0) = SB_BeforeDrawCallback__FPQ26CChara6CModelPvPvPA4_fi;
  fVar1 = FLOAT_80331cc4;
  *(code **)(iVar2 + 0xfc) = SB_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
  *(code **)(iVar2 + 0xf4) = SB_BeforeMeshLockEnvCallback__FPQ26CChara6CModelPvPvi;
  *(code **)(iVar2 + 0xec) = SB_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv;
  pfVar3[3] = 0.0;
  pfVar3[4] = 0.0;
  pfVar3[8] = fVar1;
  pfVar3[7] = fVar1;
  pfVar3[6] = fVar1;
  pfVar3[2] = fVar1;
  pfVar3[1] = fVar1;
  *pfVar3 = fVar1;
  *(undefined *)(pfVar3 + 9) = 0;
  *(undefined *)(pfVar3 + 10) = 0xff;
  *(undefined *)((int)pfVar3 + 0x29) = 0xff;
  *(undefined *)((int)pfVar3 + 0x2a) = 0xff;
  *(undefined *)((int)pfVar3 + 0x2b) = 0xff;
  return;
}

