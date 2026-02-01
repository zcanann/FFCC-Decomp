// Function: CalcPolygonHeight__FP7PYmMeltP11VERTEX_DATAP8_GXColorf
// Entry: 800a5d5c
// Size: 624 bytes

/* WARNING: Removing unreachable block (ram,0x800a5fb0) */
/* WARNING: Removing unreachable block (ram,0x800a5fa8) */
/* WARNING: Removing unreachable block (ram,0x800a5fa0) */
/* WARNING: Removing unreachable block (ram,0x800a5f98) */
/* WARNING: Removing unreachable block (ram,0x800a5f90) */
/* WARNING: Removing unreachable block (ram,0x800a5f88) */
/* WARNING: Removing unreachable block (ram,0x800a5d94) */
/* WARNING: Removing unreachable block (ram,0x800a5d8c) */
/* WARNING: Removing unreachable block (ram,0x800a5d84) */
/* WARNING: Removing unreachable block (ram,0x800a5d7c) */
/* WARNING: Removing unreachable block (ram,0x800a5d74) */
/* WARNING: Removing unreachable block (ram,0x800a5d6c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcPolygonHeight__FP7PYmMeltP11VERTEX_DATAP8_GXColorf
               (double param_1,int param_2,undefined4 *param_3,undefined *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  float local_f8;
  float local_f4;
  float local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  
  iVar1 = *(ushort *)(param_2 + 10) + 1;
  iVar1 = iVar1 * iVar1;
  dVar5 = (double)(pppMngStPtr->m_savedPosition).y;
  dVar6 = (double)FLOAT_80330af0;
  dVar7 = (double)FLOAT_80330b10;
  dVar8 = (double)FLOAT_80330b14;
  dVar9 = (double)FLOAT_80330b18;
  puVar4 = param_3;
  for (iVar3 = 0; iVar3 < iVar1; iVar3 = iVar3 + 1) {
    *(undefined *)(puVar4 + 3) = *param_4;
    *(undefined *)((int)puVar4 + 0xd) = param_4[1];
    *(undefined *)((int)puVar4 + 0xe) = param_4[2];
    *(undefined *)((int)puVar4 + 0xf) = param_4[3];
    local_f8 = (pppMngStPtr->m_matrix).value[0][3];
    local_f4 = (pppMngStPtr->m_matrix).value[1][3] + *(float *)(param_2 + 0x24);
    local_f0 = (pppMngStPtr->m_matrix).value[2][3];
    local_d4 = (float)dVar6;
    local_d0 = (float)dVar7;
    local_cc = (float)dVar6;
    local_ec = *puVar4;
    local_e8 = puVar4[1];
    local_e4 = puVar4[2];
    local_e0 = local_f8;
    local_dc = local_f4;
    local_d8 = local_f0;
    pppAddVector__FR3Vec3Vec3Vec(puVar4,&local_ec,&local_f8);
    local_98 = (float)dVar8;
    local_9c = (float)dVar8;
    local_a0 = (float)dVar8;
    local_8c = (float)dVar9;
    local_90 = (float)dVar9;
    local_94 = (float)dVar9;
    local_c8 = *puVar4;
    local_c4 = puVar4[1];
    local_c0 = puVar4[2];
    local_b0 = local_d4;
    local_ac = local_d0;
    local_a8 = local_cc;
    local_a4 = (float)dVar6;
    iVar2 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                      (&MapMng,&local_c8,&local_d4,0xffffffff);
    if (iVar2 == 0) {
      puVar4[1] = (float)dVar5;
      if (*(char *)(param_2 + 0x2e) != '\0') {
        *(undefined *)(puVar4 + 3) = 0;
        *(undefined *)((int)puVar4 + 0xd) = 0;
        *(undefined *)((int)puVar4 + 0xe) = 0;
        *(undefined *)((int)puVar4 + 0xf) = 0;
      }
    }
    else {
      CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,puVar4);
      if (((float)puVar4[1] < (float)(dVar5 - (double)*(float *)(param_2 + 0x28))) &&
         (puVar4[1] = (float)dVar5, *(char *)(param_2 + 0x2e) != '\0')) {
        *(undefined *)(puVar4 + 3) = 0;
        *(undefined *)((int)puVar4 + 0xd) = 0;
        *(undefined *)((int)puVar4 + 0xe) = 0;
        *(undefined *)((int)puVar4 + 0xf) = 0;
      }
    }
    puVar4[1] = (float)puVar4[1] + *(float *)(param_2 + 0x20);
    puVar4[1] = (float)((double)(float)puVar4[1] - param_1);
    puVar4 = puVar4 + 4;
  }
  DCFlushRange(param_3,iVar1 * 0x10);
  return;
}

