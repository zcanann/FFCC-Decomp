// Function: SetLightSource__7CMapMngFv
// Entry: 80032bf0
// Size: 812 bytes

void SetLightSource__7CMapMngFv(CMapMng *mapMng)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  CMapObj *pCVar7;
  int iVar8;
  undefined4 local_188;
  Vec local_184;
  Vec local_178;
  undefined4 local_16c;
  undefined4 local_160;
  int local_154;
  Vec local_150;
  float local_144;
  undefined local_13c;
  undefined local_13b;
  undefined local_13a;
  undefined local_138;
  undefined local_137;
  undefined local_136;
  undefined local_135;
  undefined local_134;
  undefined local_133;
  undefined local_132;
  undefined local_131;
  undefined4 local_120;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_bc;
  undefined4 local_b0;
  int local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  undefined local_8c;
  undefined local_8b;
  undefined local_8a;
  undefined local_88;
  undefined local_87;
  undefined local_86;
  undefined local_85;
  undefined local_84;
  undefined local_83;
  undefined local_82;
  undefined local_81;
  undefined4 local_70;
  
  iVar6 = 0;
  sVar1 = mapMng->field10_0xc;
  for (pCVar7 = mapMng->mapObjArr; fVar3 = FLOAT_8032f9a0, pCVar7 < mapMng->mapObjArr + sVar1;
      pCVar7 = pCVar7 + 1) {
    iVar8 = *(int *)&pCVar7->field_0xec;
    if (iVar8 != 0) {
      iVar4 = *(int *)(iVar8 + 4);
      if (iVar4 == 1) {
        if (*(int *)(iVar8 + 0x34) == 0) {
          __ct__Q29CLightPcs6CLightFv(&local_188);
          local_188 = 1;
          local_184.x = *(float *)&pCVar7->field_0xc4;
          local_184.y = *(float *)&pCVar7->field_0xd4;
          local_184.z = *(float *)&pCVar7->field_0xe4;
          local_150.x = FLOAT_8032f9a0;
          local_150.y = FLOAT_8032f9a0;
          local_150.z = FLOAT_8032f998;
          iVar4 = *(int *)(iVar8 + 0x10);
          local_178.x = *(float *)(iVar4 + 0xc4);
          local_178.y = *(float *)(iVar4 + 0xd4);
          local_178.z = *(float *)(iVar4 + 0xe4);
          PSVECSubtract(&local_178,&local_184,&local_150);
          PSVECNormalize(&local_150,&local_150);
          local_16c = *(undefined4 *)(iVar8 + 0x14);
          local_144 = FLOAT_8032f9dc * *(float *)(iVar8 + 0x18);
          local_160 = *(undefined4 *)(iVar8 + 0x1c);
          local_138 = *(undefined *)(iVar8 + 0xc);
          local_137 = *(undefined *)(iVar8 + 0xd);
          local_136 = *(undefined *)(iVar8 + 0xe);
          local_135 = *(undefined *)(iVar8 + 0xf);
          local_134 = *(undefined *)(iVar8 + 8);
          local_133 = *(undefined *)(iVar8 + 9);
          local_132 = *(undefined *)(iVar8 + 10);
          local_131 = *(undefined *)(iVar8 + 0xb);
          local_120 = 0;
          local_13c = *(undefined *)(iVar8 + 0x2c);
          if (*(char *)(iVar8 + 0x2d) == '\0') {
            local_13b = 4;
          }
          else {
            local_13b = 2;
          }
          local_13a = *(undefined *)(iVar8 + 0x30);
          local_154 = 1 << iVar6;
          Add__9CLightPcsFPQ29CLightPcs6CLight(&LightPcs,&local_188);
        }
        else {
          puVar5 = *(undefined4 **)(iVar8 + 0x38);
          *puVar5 = 1;
          fVar2 = FLOAT_8032f998;
          *(undefined *)(puVar5 + 0x15) = *(undefined *)(iVar8 + 8);
          *(undefined *)((int)puVar5 + 0x55) = *(undefined *)(iVar8 + 9);
          *(undefined *)((int)puVar5 + 0x56) = *(undefined *)(iVar8 + 10);
          *(undefined *)((int)puVar5 + 0x57) = *(undefined *)(iVar8 + 0xb);
          puVar5[1] = *(undefined4 *)&pCVar7->field_0xc4;
          puVar5[2] = *(undefined4 *)&pCVar7->field_0xd4;
          puVar5[3] = *(undefined4 *)&pCVar7->field_0xe4;
          puVar5[0xe] = fVar3;
          puVar5[0xf] = fVar3;
          puVar5[0x10] = fVar2;
          puVar5[4] = *(undefined4 *)(*(int *)(iVar8 + 0x10) + 0xc4);
          puVar5[5] = *(undefined4 *)(*(int *)(iVar8 + 0x10) + 0xd4);
          puVar5[6] = *(undefined4 *)(*(int *)(iVar8 + 0x10) + 0xe4);
          PSVECSubtract((Vec *)(puVar5 + 4),(Vec *)(puVar5 + 1),(Vec *)(puVar5 + 0xe));
          PSVECNormalize((Vec *)(puVar5 + 0xe),(Vec *)(puVar5 + 0xe));
        }
        iVar6 = iVar6 + 1;
      }
      else if ((iVar4 < 1) && (-1 < iVar4)) {
        __ct__Q29CLightPcs6CLightFv(&local_d8);
        local_d8 = 0;
        local_d4 = *(undefined4 *)&pCVar7->field_0xc4;
        local_a4 = 1 << iVar6;
        local_d0 = *(undefined4 *)&pCVar7->field_0xd4;
        local_cc = *(undefined4 *)&pCVar7->field_0xe4;
        local_a0 = FLOAT_8032f9a0;
        local_9c = FLOAT_8032f9a0;
        local_98 = FLOAT_8032f998;
        local_bc = *(undefined4 *)(iVar8 + 0x10);
        local_94 = FLOAT_8032f9d8;
        local_b0 = *(undefined4 *)(iVar8 + 0x14);
        local_88 = *(undefined *)(iVar8 + 0xc);
        local_87 = *(undefined *)(iVar8 + 0xd);
        local_86 = *(undefined *)(iVar8 + 0xe);
        local_85 = *(undefined *)(iVar8 + 0xf);
        local_84 = *(undefined *)(iVar8 + 8);
        local_83 = *(undefined *)(iVar8 + 9);
        local_82 = *(undefined *)(iVar8 + 10);
        local_81 = *(undefined *)(iVar8 + 0xb);
        local_70 = 0;
        local_8c = *(undefined *)(iVar8 + 0x1c);
        local_8b = 4;
        local_8a = *(undefined *)(iVar8 + 0x20);
        Add__9CLightPcsFPQ29CLightPcs6CLight(&LightPcs,&local_d8);
        iVar6 = iVar6 + 1;
      }
    }
  }
  return;
}

