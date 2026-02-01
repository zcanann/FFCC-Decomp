// Function: InitPolygonParameter__FP11PCharaBreakP11VCharaBreakP12POLYGON_DATAUlPQ26CChara6CModelPQ26CChara5CMesh
// Entry: 8014099c
// Size: 812 bytes

/* WARNING: Removing unreachable block (ram,0x80140cac) */
/* WARNING: Removing unreachable block (ram,0x801409ac) */

void InitPolygonParameter__FP11PCharaBreakP11VCharaBreakP12POLYGON_DATAUlPQ26CChara6CModelPQ26CChara5CMesh
               (int param_1,undefined4 param_2,undefined *param_3,uint param_4,CModel *model,
               CMesh *mesh)

{
  float fVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  S16Vec *pSVar6;
  uint uVar7;
  S16Vec *pSVar8;
  double dVar9;
  double dVar10;
  S16Vec local_78;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  Vec local_58;
  Vec local_4c;
  Vec local_40;
  
  pSVar8 = mesh->m_workNormals;
  dVar10 = (double)FLOAT_80332048;
  for (uVar7 = 0; uVar7 < param_4; uVar7 = uVar7 + 1) {
    local_4c.x = DAT_801dd678;
    local_4c.y = DAT_801dd67c;
    local_4c.z = DAT_801dd680;
    iVar3 = rand();
    iVar3 = (uint)*(byte *)(param_1 + 0x34) +
            (iVar3 - (iVar3 / (int)(uint)*(byte *)(param_1 + 0x35)) *
                     (uint)*(byte *)(param_1 + 0x35));
    if (0xff < iVar3) {
      iVar3 = 0xff;
    }
    param_3[1] = (char)iVar3;
    *param_3 = 0;
    *(undefined2 *)(param_3 + 2) = 0;
    if (*(char *)(param_1 + 0x41) == '\x02') {
      *param_3 = 1;
    }
    if (mesh->m_data->m_skinCount == 0) {
      dVar9 = (double)RandF__5CMathFf((double)FLOAT_8033204c,&Math);
      local_40.x = (float)dVar9;
      dVar9 = (double)RandF__5CMathFf((double)FLOAT_8033204c,&Math);
      local_40.y = (float)dVar9;
      dVar9 = (double)RandF__5CMathFf((double)FLOAT_8033204c,&Math);
      local_40.z = (float)dVar9;
      uVar4 = rand();
      fVar1 = FLOAT_80332078;
      if ((uVar4 & 1 ^ uVar4 >> 0x1f) != uVar4 >> 0x1f) {
        fVar1 = FLOAT_8033204c;
      }
      local_40.x = local_40.x * fVar1;
      uVar4 = rand();
      fVar1 = FLOAT_80332078;
      if ((uVar4 & 1 ^ uVar4 >> 0x1f) != uVar4 >> 0x1f) {
        fVar1 = FLOAT_8033204c;
      }
      local_40.y = local_40.y * fVar1;
      uVar4 = rand();
      fVar1 = FLOAT_80332078;
      if ((uVar4 & 1 ^ uVar4 >> 0x1f) != uVar4 >> 0x1f) {
        fVar1 = FLOAT_8033204c;
      }
      local_40.z = local_40.z * fVar1;
      PSVECNormalize(&local_40,&local_40);
      local_64 = local_40.x;
      local_60 = local_40.y;
      local_5c = local_40.z;
      ConvF2IVector__5CUtilFR6S16Vec3Vecl
                ((CUtil *)&DAT_8032ec70,(S16Vec *)(param_3 + 4),&local_64,model->m_data->m_normQuant
                );
    }
    else {
      pSVar6 = pSVar8 + *(ushort *)(param_3 + 0x28);
      *(short *)(param_3 + 4) = pSVar6->x;
      *(short *)(param_3 + 6) = pSVar6->y;
      *(short *)(param_3 + 8) = pSVar6->z;
      pSVar6 = pSVar8 + *(ushort *)(param_3 + 0x28);
      local_78.x = pSVar6->x;
      local_78.y = pSVar6->y;
      local_78.z = pSVar6->z;
      ConvI2FVector__5CUtilFR3Vec6S16Vecl
                ((CUtil *)&DAT_8032ec70,&local_40,&local_78,model->m_data->m_normQuant);
    }
    PSVECCrossProduct(&local_4c,&local_40,&local_58);
    dVar9 = (double)PSVECMag(&local_58);
    if (dVar10 == dVar9) {
      local_58.x = (float)dVar10;
      local_58.y = (float)dVar10;
      local_58.z = (float)dVar10;
    }
    else {
      PSVECScale((float)((double)FLOAT_8033204c / dVar9),&local_58,&local_58);
    }
    if (((dVar10 == (double)local_58.x) && (dVar10 == (double)local_58.y)) &&
       (dVar10 == (double)local_58.z)) {
      local_58.y = (float)dVar10;
      local_58.x = FLOAT_8033204c;
      local_58.z = (float)dVar10;
    }
    if ((*(char *)(param_1 + 0x40) != '\0') && (*(char *)(param_1 + 0x40) == '\x01')) {
      *(undefined2 *)(param_3 + 8) = 0;
      *(undefined2 *)(param_3 + 6) = 0;
      *(undefined2 *)(param_3 + 4) = 0;
      uVar5 = rand();
      sVar2 = (short)((int)uVar5 >> 0x1f);
      *(ushort *)(param_3 + 6) = ((ushort)uVar5 & 1 ^ -sVar2) + sVar2;
    }
    local_70 = local_58.x;
    local_6c = local_58.y;
    local_68 = local_58.z;
    ConvF2IVector__5CUtilFR6S16Vec3Vecl
              ((CUtil *)&DAT_8032ec70,(S16Vec *)(param_3 + 10),&local_70,model->m_data->m_normQuant)
    ;
    param_3 = param_3 + 0x34;
  }
  return;
}

