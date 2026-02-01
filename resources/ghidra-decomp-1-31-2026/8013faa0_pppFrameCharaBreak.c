// Function: pppFrameCharaBreak
// Entry: 8013faa0
// Size: 1140 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameCharaBreak(pppCharaBreak *pppCharaBreak,UnkB *param_2,UnkC *param_3)

{
  float fVar1;
  CCharaPcsCHandle *handle;
  CModel *model;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  CMeshCRefData *pCVar8;
  int iVar9;
  CDisplayList *pCVar10;
  CMesh *mesh;
  void *pvVar11;
  int *piVar12;
  uint uVar13;
  
  if (DAT_8032ed70 == 0) {
    pvVar11 = (void *)((int)(&pppCharaBreak->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
    if (*(int *)((int)pvVar11 + 0x44) != 0) {
      handle = (CCharaPcsCHandle *)
               GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).x,0);
      model = (CModel *)GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
      *(CModel **)((int)pvVar11 + 0x40) = model;
      CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
                ((float)param_2->m_dataValIndex,&pppCharaBreak->field0_0x0,param_2->m_graphId,
                 (undefined *)((int)pvVar11 + 4),(undefined *)((int)pvVar11 + 8),
                 (undefined *)((int)pvVar11 + 0xc),&param_2->m_initWOrk,&param_2->m_stepValue);
      CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
                (*(float *)(param_2->m_payload + 0x14),&pppCharaBreak->field0_0x0,param_2->m_graphId
                 ,(undefined *)((int)pvVar11 + 0x10),(undefined *)((int)pvVar11 + 0x14),
                 (undefined *)((int)pvVar11 + 0x18),param_2->m_payload + 0x18,
                 param_2->m_payload + 0x1c);
      model->m_cbUser0 = pvVar11;
      model->m_cbUser1 = param_2;
      model->m_beforeMeshCallback = CharaBreak_BeforeMeshLockEnvCallback__FPQ26CChara6CModelPvPvi;
      model->m_afterMeshDrawCallback = CharaBreak_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
      model->m_afterMeshEnvCallback = CharaBreak_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f
      ;
      model->m_beforeCalcMatrixCallback =
           CharaBreak_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv;
      fVar1 = FLOAT_80332048;
      if (param_2->m_graphId == (pppCharaBreak->field0_0x0).m_graphId) {
        if (((FLOAT_80332048 == *(float *)(param_2->m_payload + 4)) &&
            (FLOAT_80332048 == *(float *)(param_2->m_payload + 8))) &&
           (FLOAT_80332048 == *(float *)(param_2->m_payload + 0xc))) {
          *(float *)(param_2->m_payload + 4) = FLOAT_8033204c;
          *(float *)(param_2->m_payload + 8) = fVar1;
          *(float *)(param_2->m_payload + 0xc) = fVar1;
        }
        else {
          PSVECNormalize((Vec *)(param_2->m_payload + 4),(Vec *)(param_2->m_payload + 4));
        }
      }
      mesh = model->m_meshes;
      if (*(int *)((int)pvVar11 + 0x1c) == 0) {
        *(float *)((int)pvVar11 + 0x3c) = FLOAT_80332050;
        uVar2 = pppMemFree__FPv(model->m_data->m_meshCount << 2,pppEnvStPtr->m_stagePtr,
                                s_pppCharaBreak_cpp_801dd690,0x3d0);
        *(undefined4 *)((int)pvVar11 + 0x1c) = uVar2;
        if (*(int *)((int)pvVar11 + 0x1c) == 0) {
LAB_8013fee0:
          *(undefined4 *)((int)pvVar11 + 0x44) = 0;
          model->m_cbUser0 = (void *)0x0;
          model->m_cbUser1 = (void *)0x0;
          model->m_beforeMeshCallback = (void *)0x0;
          model->m_afterMeshDrawCallback = (void *)0x0;
          model->m_afterMeshEnvCallback = (void *)0x0;
          model->m_beforeCalcMatrixCallback = (void *)0x0;
          return;
        }
        iVar5 = 0;
        for (uVar7 = 0; uVar7 < model->m_data->m_meshCount; uVar7 = uVar7 + 1) {
          *(undefined4 *)(*(int *)((int)pvVar11 + 0x1c) + iVar5) = 0;
          iVar5 = iVar5 + 4;
        }
        iVar5 = 0;
        for (uVar7 = 0; uVar7 < model->m_data->m_meshCount; uVar7 = uVar7 + 1) {
          pCVar8 = mesh->m_data;
          iVar3 = strcmp(pCVar8,&DAT_80332054);
          if (iVar3 == 0) {
            CalcBoundaryBoxQuantized__5CUtilFP3VecP3VecP6S16VecUlUl
                      ((CUtil *)&DAT_8032ec70,(undefined *)((int)pvVar11 + 0x20),
                       (undefined *)((int)pvVar11 + 0x30),mesh->m_workPositions,
                       pCVar8->m_vertexCount,model->m_data->m_posQuant);
          }
          uVar2 = pppMemFree__FPv(mesh->m_data->m_displayListCount << 2,pppEnvStPtr->m_stagePtr,
                                  s_pppCharaBreak_cpp_801dd690,0x3e9);
          *(undefined4 *)(*(int *)((int)pvVar11 + 0x1c) + iVar5) = uVar2;
          iVar3 = *(int *)(*(int *)((int)pvVar11 + 0x1c) + iVar5);
          if (iVar3 == 0) goto LAB_8013fee0;
          uVar4 = mesh->m_data->m_displayListCount;
          puVar6 = (undefined4 *)(iVar3 + (uVar4 - 1) * 4);
          if (-1 < (int)(uVar4 - 1)) {
            uVar13 = uVar4 >> 3;
            if (uVar13 != 0) {
              do {
                *puVar6 = 0;
                puVar6[-1] = 0;
                puVar6[-2] = 0;
                puVar6[-3] = 0;
                puVar6[-4] = 0;
                puVar6[-5] = 0;
                puVar6[-6] = 0;
                puVar6[-7] = 0;
                puVar6 = puVar6 + -8;
                uVar13 = uVar13 - 1;
              } while (uVar13 != 0);
              uVar4 = uVar4 & 7;
              if (uVar4 == 0) goto LAB_8013fd4c;
            }
            do {
              *puVar6 = 0;
              puVar6 = puVar6 + -1;
              uVar4 = uVar4 - 1;
            } while (uVar4 != 0);
          }
LAB_8013fd4c:
          pCVar10 = mesh->m_data->m_displayLists;
          iVar9 = mesh->m_data->m_displayListCount - 1;
          piVar12 = (int *)(iVar3 + iVar9 * 4);
          for (; -1 < iVar9; iVar9 = iVar9 + -1) {
            iVar3 = pppMemFree__FPv(0x10,pppEnvStPtr->m_stagePtr,s_pppCharaBreak_cpp_801dd690,0x3fc)
            ;
            *piVar12 = iVar3;
            if ((undefined4 *)*piVar12 == (undefined4 *)0x0) goto LAB_8013fee0;
            *(undefined4 *)*piVar12 = 0;
            *(undefined4 *)(*piVar12 + 4) = 0;
            *(undefined4 *)(*piVar12 + 0xc) = 0;
            *(uint32_t *)(*piVar12 + 4) = pCVar10->m_size;
            uVar2 = pppMemFree__FPv(pCVar10->m_size,pppEnvStPtr->m_stagePtr,
                                    s_pppCharaBreak_cpp_801dd690,0x40b);
            *(undefined4 *)*piVar12 = uVar2;
            if (*(void **)*piVar12 == (void *)0x0) goto LAB_8013fee0;
            memcpy(*(void **)*piVar12,pCVar10->m_data,pCVar10->m_size);
            ReWriteDisplayList__5CUtilFPvUlUl
                      ((CUtil *)&DAT_8032ec70,*(undefined4 *)*piVar12,pCVar10->m_size,1);
            iVar3 = GetNumPolygonFromDL__5CUtilFPvUl((CUtil *)&DAT_8032ec70,*(undefined4 *)*piVar12)
            ;
            uVar2 = pppMemFree__FPv(iVar3 * 0x34,pppEnvStPtr->m_stagePtr,
                                    s_pppCharaBreak_cpp_801dd690,0x423);
            *(undefined4 *)(*piVar12 + 0xc) = uVar2;
            if (*(int *)(*piVar12 + 0xc) == 0) goto LAB_8013fee0;
            *(short *)(*piVar12 + 8) = (short)iVar3;
            CreatePolygon__FP12POLYGON_DATAPvUlPQ26CChara6CModelPQ26CChara5CMesh
                      (*(undefined4 *)(*piVar12 + 0xc),pCVar10->m_data,pCVar10->m_size,model,mesh);
            InitPolygonParameter__FP11PCharaBreakP11VCharaBreakP12POLYGON_DATAUlPQ26CChara6CModelPQ26CChara5CMesh
                      (param_2,pvVar11,*(undefined4 *)(*piVar12 + 0xc),
                       (uint)*(ushort *)(*piVar12 + 8),model,mesh);
            piVar12 = piVar12 + -1;
            pCVar10 = pCVar10 + 1;
          }
          iVar5 = iVar5 + 4;
          mesh = mesh + 1;
        }
      }
      if (DAT_8032ed78 == '\0') {
        UpdatePolygonData__FP11PCharaBreakP11VCharaBreakPQ26CChara6CModel(param_2,pvVar11,model);
      }
    }
  }
  return;
}

