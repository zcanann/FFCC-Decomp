// Function: pppRenderBreathModel
// Entry: 800db204
// Size: 1244 bytes

/* WARNING: Removing unreachable block (ram,0x800db6c4) */
/* WARNING: Removing unreachable block (ram,0x800db214) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderBreathModel(pppBreathModel *pppBreathModel,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  pppModelSt *pppModelSt;
  int *piVar13;
  float *pfVar14;
  int iVar15;
  float *a;
  double dVar16;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_174;
  Vec local_170;
  Vec local_164;
  Mtx MStack_158;
  Mtx MStack_128;
  Mtx MStack_f8;
  Mtx local_c8;
  Mtx MStack_98;
  undefined8 local_68;
  longlong local_60;
  longlong local_58;
  longlong local_50;
  
  iVar8 = *param_3->m_serializedDataOffsets;
  iVar7 = param_3->m_serializedDataOffsets[1];
  a = *(float **)(&pppBreathModel->field_0xb0 + iVar8);
  iVar15 = *(int *)(&pppBreathModel->field_0xb4 + iVar8);
  pfVar14 = *(float **)(&pppBreathModel->field_0xb8 + iVar8);
  piVar13 = *(int **)(&pppBreathModel->field_0xbc + iVar8);
  iVar12 = *(int *)(&pppBreathModel->field_0xc0 + iVar8);
  if (param_2->m_stepValue != 9.18341e-41) {
    pppModelSt = (pppModelSt *)pppEnvStPtr->m_mapMeshPtr[(int)param_2->m_stepValue];
    pppInitBlendMode__Fv();
    pppSetBlendMode__FUc(param_2->m_payload[4]);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (*(float *)(param_2->m_payload + 0xb0),(pppCVector *)0x0,(pppFMATRIX *)0x0,
               param_2->m_payload[0xb6],param_2->m_payload[0xb5],param_2->m_payload[4],
               param_2->m_payload[0xb7],param_2->m_payload[0xb8],1,param_2->m_payload[0xb9]);
    bVar2 = (&pppBreathModel->field_0x88)[iVar7];
    bVar3 = (&pppBreathModel->field_0x89)[iVar7];
    bVar4 = (&pppBreathModel->field_0x8a)[iVar7];
    bVar5 = (&pppBreathModel->field_0x8b)[iVar7];
    for (iVar7 = 0; iVar7 < iVar12; iVar7 = iVar7 + 1) {
      if (0 < *(short *)*(float (*) [4])(a + 0x14)) {
        PSMTXScale((pppMngStPtr->m_scale).x * a[0x19],(pppMngStPtr->m_scale).y * a[0x1a],
                   (pppMngStPtr->m_scale).z * a[0x1b],&MStack_128);
        PSMTXConcat((Mtx *)a,&MStack_128,&MStack_158);
        PSMTXConcat(&ppvCameraMatrix0,&MStack_158,&MStack_158);
        PSMTXConcat(&ppvCameraMatrix0,(Mtx *)a,&MStack_f8);
        PSMTXMultVec(&MStack_f8,(Vec *)(a + 0xc),&local_170);
        MStack_158.value[0][3] = local_170.x;
        MStack_158.value[1][3] = local_170.y;
        MStack_158.value[2][3] = local_170.z;
        GXLoadPosMtxImm(&MStack_158,0);
        local_68 = (double)CONCAT44(0x43300000,bVar5 ^ 0x80000000);
        iVar11 = (int)((float)(local_68 - DOUBLE_80330f78) - a[0x22]);
        uVar6 = (uint)bVar2;
        uVar9 = (uint)bVar3;
        uVar10 = (uint)bVar4;
        iVar1 = iVar11;
        if (pfVar14 != (float *)0x0) {
          iVar1 = (int)*pfVar14;
          local_68 = (double)(longlong)(int)pfVar14[1];
          local_58 = (longlong)(int)pfVar14[2];
          local_50 = (longlong)(int)pfVar14[3];
          uVar6 = (uint)bVar2 + iVar1;
          uVar9 = (uint)bVar3 + (int)pfVar14[1];
          uVar10 = (uint)bVar4 + (int)pfVar14[2];
          iVar11 = iVar11 + (int)pfVar14[3];
        }
        local_60 = (longlong)iVar1;
        if ((int)uVar6 < 0) {
          uVar6 = 0;
        }
        else if (0xff < (int)uVar6) {
          uVar6 = 0xff;
        }
        if ((int)uVar9 < 0) {
          uVar9 = 0;
        }
        else if (0xff < (int)uVar9) {
          uVar9 = 0xff;
        }
        if ((int)uVar10 < 0) {
          uVar10 = 0;
        }
        else if (0xff < (int)uVar10) {
          uVar10 = 0xff;
        }
        if (iVar11 < 0) {
          iVar11 = 0;
        }
        else if (0x7f < iVar11) {
          iVar11 = 0x7f;
        }
        local_17c = CONCAT31(CONCAT21(CONCAT11((char)uVar6,(char)uVar9),(char)uVar10),(char)iVar11);
        local_174 = local_17c;
        GXSetChanAmbColor(4,&local_17c);
        pppDrawMesh__FP10pppModelStP3Veci(pppModelSt,*(Vec **)&pppBreathModel->field_0x70,1);
      }
      if (iVar15 != 0) {
        iVar15 = iVar15 + 0x30;
      }
      if (pfVar14 != (float *)0x0) {
        pfVar14 = pfVar14 + 8;
      }
      a = a + 0x26;
    }
    if ((CFlat._4764_4_ & 0x200000) != 0) {
      for (iVar7 = 0; iVar7 < (int)(uint)*(ushort *)((int)&param_2->m_arg3 + 2); iVar7 = iVar7 + 1)
      {
        if (*piVar13 == 1) {
          if (iVar7 == 2) {
            local_178 = 0x800000ff;
          }
          else if (iVar7 < 2) {
            if (iVar7 == 0) {
              local_178 = 0x800000ff;
            }
            else {
              if (iVar7 < 0) goto LAB_800db5ac;
              local_178 = 0x8080ffff;
            }
          }
          else if (iVar7 < 4) {
            local_178 = 0x808080ff;
          }
          else {
LAB_800db5ac:
            local_178 = 0x6080ff;
          }
          iVar15 = -1;
          dVar16 = (double)(float)piVar13[10];
          iVar12 = 0;
          for (uVar6 = (uint)*(ushort *)&param_2->m_arg3; uVar6 != 0; uVar6 = uVar6 - 1) {
            if (*(char *)(piVar13[2] + iVar12) != -1) {
              iVar15 = (int)*(char *)(piVar13[1] + iVar12);
              break;
            }
            iVar12 = iVar12 + 1;
          }
          PSMTXIdentity(&local_c8);
          local_c8.value[0][0] = (float)dVar16;
          local_c8.value[1][1] = (float)dVar16;
          local_c8.value[2][2] = (float)dVar16;
          PSMTXConcat((Mtx *)(*(int *)(&pppBreathModel->field_0xb4 + iVar8) + iVar15 * 0x30),
                      &(pppBreathModel->field0_0x0).m_localMatrix,&MStack_98);
          PSMTXConcat(&ppvCameraMatrix0,&MStack_98,&MStack_98);
          PSMTXMultVec(&MStack_98,(Vec *)(piVar13 + 3),&local_164);
          local_c8.value[0][3] = local_164.x;
          local_c8.value[1][3] = local_164.y;
          local_c8.value[2][3] = local_164.z;
          pppSetBlendMode__FUc(1);
          local_180 = local_178;
          DrawSphere__8CGraphicFPA4_f8_GXColor(&Graphic,&local_c8,&local_180);
        }
        piVar13 = piVar13 + 0x17;
      }
      pppInitBlendMode__Fv();
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,2);
    }
  }
  return;
}

