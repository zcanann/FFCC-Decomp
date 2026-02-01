// Function: pppRyjMegaBirthModel
// Entry: 80087ce8
// Size: 520 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRyjMegaBirthModel
               (pppRyjMegaBirthModel *pppRyjMegaBirthModel,PRyjMegaBirthModel *pRyjMegaBirthModel,
               UnkC *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  int iVar5;
  void *pvVar6;
  PARTICLE_WMAT *pPVar7;
  _PARTICLE_COLOR *p_Var8;
  VRyjMegaBirthModel *vRyjMegaBirthModel;
  
  iVar5 = param_3->m_serializedDataOffsets[1];
  vRyjMegaBirthModel =
       (VRyjMegaBirthModel *)
       ((int)(&pppRyjMegaBirthModel->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
  if (vRyjMegaBirthModel->field12_0xc == (void *)0x0) {
    vRyjMegaBirthModel->field15_0x18 = (uint)*(ushort *)(pRyjMegaBirthModel->m_matrix).value[2];
    pvVar6 = (void *)pppMemAlloc__FUlPQ27CMemory6CStagePci
                               (vRyjMegaBirthModel->field15_0x18 * 0xa0,pppEnvStPtr->m_stagePtr,
                                s_pppRyjMegaBirthModel_cpp_801d9c18,0x8d);
    vRyjMegaBirthModel->field12_0xc = pvVar6;
    if (vRyjMegaBirthModel->field12_0xc != (void *)0x0) {
      memset(vRyjMegaBirthModel->field12_0xc,0,vRyjMegaBirthModel->field15_0x18 * 0xa0);
    }
    if (pRyjMegaBirthModel->m_useWorldMatrix != '\0') {
      pPVar7 = (PARTICLE_WMAT *)
               pppMemAlloc__FUlPQ27CMemory6CStagePci
                         (vRyjMegaBirthModel->field15_0x18 * 0x30,pppEnvStPtr->m_stagePtr,
                          s_pppRyjMegaBirthModel_cpp_801d9c18,0x97);
      vRyjMegaBirthModel->field13_0x10 = pPVar7;
      if (vRyjMegaBirthModel->field13_0x10 != (PARTICLE_WMAT *)0x0) {
        memset(vRyjMegaBirthModel->field13_0x10,0,vRyjMegaBirthModel->field15_0x18 * 0x30);
      }
    }
    if (pRyjMegaBirthModel->field_0x131 != '\0') {
      p_Var8 = (_PARTICLE_COLOR *)
               pppMemAlloc__FUlPQ27CMemory6CStagePci
                         (vRyjMegaBirthModel->field15_0x18 << 5,pppEnvStPtr->m_stagePtr,
                          s_pppRyjMegaBirthModel_cpp_801d9c18,0xa2);
      vRyjMegaBirthModel->field14_0x14 = p_Var8;
      if (vRyjMegaBirthModel->field14_0x14 != (_PARTICLE_COLOR *)0x0) {
        memset(vRyjMegaBirthModel->field14_0x14,0,vRyjMegaBirthModel->field15_0x18 << 5);
      }
    }
    *(undefined4 *)vRyjMegaBirthModel = *(undefined4 *)&pRyjMegaBirthModel->field_0xf8;
    *(undefined4 *)&vRyjMegaBirthModel->field_0x4 = *(undefined4 *)&pRyjMegaBirthModel->field_0xfc;
    *(undefined4 *)&vRyjMegaBirthModel->field_0x8 = *(undefined4 *)&pRyjMegaBirthModel->field_0x100;
    PSVECNormalize((Vec *)vRyjMegaBirthModel,(Vec *)vRyjMegaBirthModel);
    fVar1 = (pppRyjMegaBirthModel->field0_0x0).m_localMatrix.value[0][3];
    fVar2 = (pppRyjMegaBirthModel->field0_0x0).m_localMatrix.value[1][3];
    fVar3 = (pppRyjMegaBirthModel->field0_0x0).m_localMatrix.value[2][3];
    (vRyjMegaBirthModel->field18_0x20).x = fVar1;
    (vRyjMegaBirthModel->field18_0x20).y = fVar2;
    (vRyjMegaBirthModel->field18_0x20).z = fVar3;
    (vRyjMegaBirthModel->field19_0x2c).x = fVar1;
    (vRyjMegaBirthModel->field19_0x2c).y = fVar2;
    (vRyjMegaBirthModel->field19_0x2c).z = fVar3;
  }
  if (vRyjMegaBirthModel->field12_0xc == (void *)0x0) {
    bVar4 = false;
  }
  else if ((pRyjMegaBirthModel->m_useWorldMatrix == '\0') ||
          (vRyjMegaBirthModel->field13_0x10 != (PARTICLE_WMAT *)0x0)) {
    if ((pRyjMegaBirthModel->field_0x131 == '\0') ||
       (vRyjMegaBirthModel->field14_0x14 != (_PARTICLE_COLOR *)0x0)) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
  }
  else {
    bVar4 = false;
  }
  if (bVar4) {
    calc_particle__FP11_pppPObjectP18VRyjMegaBirthModelP18PRyjMegaBirthModelP6VColor
              (&pppRyjMegaBirthModel->field0_0x0,vRyjMegaBirthModel,pRyjMegaBirthModel,
               (VColor *)((int)(&pppRyjMegaBirthModel->field0_0x0 + 2) + iVar5));
  }
  return;
}

