// Function: pppRenderRain
// Entry: 800dd424
// Size: 548 bytes

/* WARNING: Removing unreachable block (ram,0x800dd62c) */
/* WARNING: Removing unreachable block (ram,0x800dd624) */
/* WARNING: Removing unreachable block (ram,0x800dd61c) */
/* WARNING: Removing unreachable block (ram,0x800dd614) */
/* WARNING: Removing unreachable block (ram,0x800dd60c) */
/* WARNING: Removing unreachable block (ram,0x800dd604) */
/* WARNING: Removing unreachable block (ram,0x800dd5fc) */
/* WARNING: Removing unreachable block (ram,0x800dd5f4) */
/* WARNING: Removing unreachable block (ram,0x800dd46c) */
/* WARNING: Removing unreachable block (ram,0x800dd464) */
/* WARNING: Removing unreachable block (ram,0x800dd45c) */
/* WARNING: Removing unreachable block (ram,0x800dd454) */
/* WARNING: Removing unreachable block (ram,0x800dd44c) */
/* WARNING: Removing unreachable block (ram,0x800dd444) */
/* WARNING: Removing unreachable block (ram,0x800dd43c) */
/* WARNING: Removing unreachable block (ram,0x800dd434) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderRain(pppRain *pppRain,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  Vec local_b0 [2];
  
  iVar1 = param_3->m_serializedDataOffsets[1];
  iVar2 = param_3->m_serializedDataOffsets[2];
  pppSetBlendMode__FUc(param_2->m_payload[0x48]);
  pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
            (FLOAT_80331018,(pppCVector *)(&pppRain->field_0x88 + iVar1),&ppvCameraMatrix0,
             param_2->m_payload[0x4a],param_2->m_payload[0x49],param_2->m_payload[0x48],0,1,1,0);
  GXSetNumChans(1);
  GXSetNumTevStages(1);
  GXSetTevDirect(0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0xff,4);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
  GXSetLineWidth(param_2->m_payload[0x3c],0);
  SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
  pfVar3 = *(float **)((int)(&pppRain->field0_0x0 + 2) + iVar2);
  dVar9 = (double)(pppMngStPtr->m_matrix).value[0][3];
  dVar8 = (double)(pppMngStPtr->m_matrix).value[1][3];
  dVar7 = (double)(pppMngStPtr->m_matrix).value[2][3];
  GXBegin(0xa8,7,(*(ushort *)&param_2->m_dataValIndex & 0x7fff) << 1);
  dVar10 = (double)FLOAT_80331018;
  dVar11 = (double)FLOAT_8033101c;
  iVar2 = 0;
  while (iVar2 < (int)(uint)*(ushort *)&param_2->m_dataValIndex) {
    dVar6 = (double)(float)(dVar9 + (double)*pfVar3);
    dVar5 = (double)(float)(dVar8 + (double)pfVar3[1]);
    dVar4 = (double)(float)(dVar7 + (double)pfVar3[2]);
    PSVECScale(pfVar3[6],(Vec *)(pfVar3 + 3),local_b0);
    DAT_cc008000 = (float)dVar6;
    pfVar3 = pfVar3 + 8;
    iVar2 = iVar2 + 1;
    DAT_cc008000 = (float)dVar5;
    DAT_cc008000 = (float)dVar4;
    DAT_cc008000 = *(undefined4 *)(&pppRain->field_0x88 + iVar1);
    DAT_cc008000 = (float)dVar10;
    DAT_cc008000 = (float)dVar10;
    DAT_cc008000 = (float)(dVar6 + (double)local_b0[0].x);
    DAT_cc008000 = (float)(dVar5 + (double)local_b0[0].y);
    DAT_cc008000 = (float)(dVar4 + (double)local_b0[0].z);
    DAT_cc008000 = *(undefined4 *)(&pppRain->field_0x88 + iVar1);
    DAT_cc008000 = (float)dVar11;
    DAT_cc008000 = (float)dVar11;
  }
  GXSetLineWidth(8,0);
  return;
}

