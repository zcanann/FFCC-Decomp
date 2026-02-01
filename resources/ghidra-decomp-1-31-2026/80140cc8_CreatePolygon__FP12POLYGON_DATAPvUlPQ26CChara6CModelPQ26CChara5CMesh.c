// Function: CreatePolygon__FP12POLYGON_DATAPvUlPQ26CChara6CModelPQ26CChara5CMesh
// Entry: 80140cc8
// Size: 592 bytes

void CreatePolygon__FP12POLYGON_DATAPvUlPQ26CChara6CModelPQ26CChara5CMesh
               (int param_1,ushort *param_2,undefined4 param_3,CModel *model,CMesh *mesh)

{
  bool bVar1;
  byte bVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  bool bVar6;
  bool bVar7;
  ushort *puVar8;
  short sVar10;
  uint uVar9;
  int iVar11;
  int iVar12;
  S16Vec *pSVar13;
  ushort *puVar14;
  S16Vec *pSVar15;
  byte bVar16;
  S16Vec local_98;
  float local_90;
  float local_8c;
  float local_88;
  Vec local_84;
  Mtx MStack_78;
  
  bVar1 = mesh->m_data->m_skinCount != 0;
  if (!bVar1) {
    PSMTXConcat(&model->m_localMtx,&model->m_nodes[mesh->m_data->m_nodeIndex].m_mtx,&MStack_78);
  }
  pSVar15 = mesh->m_workPositions;
  bVar7 = true;
  while (bVar7) {
    bVar2 = *(byte *)param_2;
    uVar3 = *(ushort *)((int)param_2 + 1);
    param_2 = (ushort *)((int)param_2 + 3);
    bVar16 = bVar2 & 0xf8;
    iVar11 = IsHasDrawFmtDL__5CUtilFUc((CUtil *)&DAT_8032ec70,(uint)bVar2);
    if (iVar11 == 0) {
      bVar7 = false;
    }
    else {
      sVar10 = uVar3 - 2;
      bVar6 = true;
      iVar11 = 0;
      puVar8 = (ushort *)0x0;
      if (bVar16 == 0x90) {
        sVar10 = (short)((ulonglong)((longlong)(int)(uint)uVar3 * 0x55555556) >> 0x20);
      }
      while (puVar14 = puVar8, bVar6) {
        uVar3 = *param_2;
        uVar4 = param_2[1];
        uVar5 = param_2[3];
        puVar8 = param_2 + 4;
        if ((bVar2 & 7) == 2) {
          puVar8 = param_2 + 5;
        }
        param_2 = puVar8;
        if (bVar1) {
          pSVar13 = pSVar15 + uVar3;
          iVar12 = param_1 + iVar11 * 6;
          *(short *)(iVar12 + 0x10) = pSVar13->x;
          *(short *)(iVar12 + 0x12) = pSVar13->y;
          *(short *)(iVar12 + 0x14) = pSVar13->z;
        }
        else {
          pSVar13 = pSVar15 + uVar3;
          local_98.x = pSVar13->x;
          local_98.y = pSVar13->y;
          local_98.z = pSVar13->z;
          ConvI2FVector__5CUtilFR3Vec6S16Vecl
                    ((CUtil *)&DAT_8032ec70,&local_84,&local_98,model->m_data->m_posQuant);
          PSMTXMultVec(&MStack_78,&local_84,&local_84);
          local_90 = local_84.x;
          local_8c = local_84.y;
          local_88 = local_84.z;
          ConvF2IVector__5CUtilFR6S16Vec3Vecl
                    ((CUtil *)&DAT_8032ec70,(S16Vec *)(param_1 + iVar11 * 6 + 0x10),&local_90,
                     model->m_data->m_posQuant);
        }
        iVar12 = param_1 + iVar11 * 2;
        iVar11 = iVar11 + 1;
        *(ushort *)(iVar12 + 0x22) = uVar3;
        *(ushort *)(iVar12 + 0x2e) = uVar5;
        *(ushort *)(iVar12 + 0x28) = uVar4;
        puVar8 = puVar14;
        if (bVar16 == 0x90) {
          if (iVar11 == 3) {
            sVar10 = sVar10 + -1;
            if (sVar10 < 1) {
              bVar6 = false;
            }
            iVar11 = 0;
            param_1 = param_1 + 0x34;
          }
        }
        else if (((bVar16 == 0x98) && (puVar8 = param_2, iVar11 != 1)) &&
                (puVar8 = puVar14, iVar11 == 3)) {
          sVar10 = sVar10 + -1;
          if (sVar10 < 1) {
            bVar6 = false;
          }
          uVar9 = countLeadingZeros((int)sVar10);
          if (((1 << (uVar9 & 0x1f) | 1U >> 0x20 - (uVar9 & 0x1f)) & 1) == 0) {
            param_2 = puVar14;
          }
          iVar11 = 0;
          param_1 = param_1 + 0x34;
        }
      }
    }
  }
  return;
}

