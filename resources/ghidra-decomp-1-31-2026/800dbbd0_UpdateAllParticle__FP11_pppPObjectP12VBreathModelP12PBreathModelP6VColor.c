// Function: UpdateAllParticle__FP11_pppPObjectP12VBreathModelP12PBreathModelP6VColor
// Entry: 800dbbd0
// Size: 1028 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void UpdateAllParticle__FP11_pppPObjectP12VBreathModelP12PBreathModelP6VColor
               (_pppPObject *pppPObject,int param_2,int param_3,VColor *vColor)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  short sVar8;
  int *piVar7;
  short sVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  _PARTICLE_COLOR *particleColor;
  PARTICLE_WMAT *pPVar15;
  int iVar16;
  Vec local_58;
  Vec VStack_4c;
  float local_40;
  float local_3c;
  float local_38;
  
  iVar12 = 0;
  iVar16 = *(int *)(param_2 + 0x30);
  pPVar15 = *(PARTICLE_WMAT **)(param_2 + 0x34);
  particleColor = *(_PARTICLE_COLOR **)(param_2 + 0x38);
  piVar14 = *(int **)(param_2 + 0x3c);
  iVar13 = *(int *)(param_2 + 0x40);
  if ((DAT_8032ed70 == 0) && (*(int *)(param_3 + 0xc) != 0xffff)) {
    *(short *)(param_2 + 0x44) = *(short *)(param_2 + 0x44) + 1;
    for (iVar11 = 0; iVar11 < iVar13; iVar11 = iVar11 + 1) {
      if (*(short *)(iVar16 + 0x50) < 1) {
        iVar10 = *(int *)(param_2 + 0x3c);
        for (sVar9 = 0; (int)sVar9 < (int)(uint)*(ushort *)(param_3 + 0x12); sVar9 = sVar9 + 1) {
          for (sVar8 = 0; (int)sVar8 < (int)(uint)*(ushort *)(param_3 + 0x10); sVar8 = sVar8 + 1) {
            if ((int)(short)iVar11 == (int)*(char *)(*(int *)(iVar10 + 4) + (int)sVar8)) {
              bVar1 = true;
              goto LAB_800dbcd8;
            }
          }
          iVar10 = iVar10 + 0x5c;
        }
        bVar1 = false;
        sVar8 = -1;
        sVar9 = -1;
LAB_800dbcd8:
        if (bVar1) {
          *(undefined *)(piVar14[sVar9 * 0x17 + 1] + (int)sVar8) = 0xff;
        }
        fVar2 = FLOAT_80330f70;
        iVar10 = (int)sVar9;
        if (iVar10 != -1) {
          iVar5 = 0;
          iVar6 = *(int *)(param_2 + 0x3c) + iVar10 * 0x5c;
          for (uVar4 = (uint)*(ushort *)(param_3 + 0x10); uVar4 != 0; uVar4 = uVar4 - 1) {
            if ((*(char *)(*(int *)(iVar6 + 4) + iVar5) != -1) ||
               (*(char *)(*(int *)(iVar6 + 8) + iVar5) != '\x01')) {
              bVar1 = false;
              goto LAB_800dbd64;
            }
            iVar5 = iVar5 + 1;
          }
          bVar1 = true;
LAB_800dbd64:
          if (bVar1) {
            piVar7 = piVar14 + iVar10 * 0x17;
            for (iVar10 = 0; iVar10 < (int)(uint)*(ushort *)(param_3 + 0x10); iVar10 = iVar10 + 1) {
              *(undefined *)(piVar7[2] + iVar10) = 0xff;
              piVar7[5] = (int)fVar2;
              piVar7[4] = (int)fVar2;
              piVar7[3] = (int)fVar2;
              piVar7[8] = (int)fVar2;
              piVar7[7] = (int)fVar2;
              piVar7[6] = (int)fVar2;
              piVar7[9] = (int)fVar2;
            }
            *piVar7 = 0;
          }
        }
        if ((*(ushort *)(param_3 + 0x1e) <= *(ushort *)(param_2 + 0x44)) &&
           (iVar12 < (int)(uint)*(ushort *)(param_3 + 0x1c))) {
          BirthParticle__FP11_pppPObjectP12VBreathModelP12PBreathModelP6VColorP13PARTICLE_DATAP13PARTICLE_WMATP14PARTICLE_COLOR
                    (pppPObject,param_2,param_3,vColor,iVar16,pPVar15,particleColor);
          bVar1 = true;
          iVar12 = iVar12 + 1;
          piVar7 = piVar14;
          for (iVar10 = 0; iVar10 < (int)(uint)*(ushort *)(param_3 + 0x12); iVar10 = iVar10 + 1) {
            for (iVar5 = 0; iVar5 < (int)(uint)*(ushort *)(param_3 + 0x10); iVar5 = iVar5 + 1) {
              if ((*(char *)(piVar7[1] + iVar5) == -1) && (*(char *)(piVar7[2] + iVar5) == -1)) {
                *(char *)(piVar7[1] + iVar5) = (char)iVar11;
                bVar1 = false;
                *(undefined *)(piVar7[2] + iVar5) = 1;
              }
              if (!bVar1) break;
            }
            if (!bVar1) break;
            piVar7 = piVar7 + 0x17;
          }
        }
      }
      else {
        UpdateParticle__FP12VBreathModelP12PBreathModelP13PARTICLE_DATAP6VColorP14PARTICLE_COLOR
                  (param_2,param_3,iVar16,vColor,particleColor);
      }
      if (pPVar15 != (PARTICLE_WMAT *)0x0) {
        pPVar15 = pPVar15 + 1;
      }
      if (particleColor != (_PARTICLE_COLOR *)0x0) {
        particleColor = particleColor + 1;
      }
      iVar16 = iVar16 + 0x98;
    }
    if (0 < iVar12) {
      *(undefined2 *)(param_2 + 0x44) = 0;
    }
    piVar7 = piVar14;
    for (iVar12 = 0; fVar3 = FLOAT_80330f80, fVar2 = FLOAT_80330f70,
        iVar12 < (int)(uint)*(ushort *)(param_3 + 0x12); iVar12 = iVar12 + 1) {
      if (((*piVar7 != 1) && (*(char *)piVar7[1] != -1)) && (*(char *)piVar7[2] == '\x01')) {
        local_40 = FLOAT_80330f70;
        local_3c = FLOAT_80330f70;
        local_38 = FLOAT_80330f80;
        piVar7[9] = *(int *)(param_3 + 0x14);
        local_58.x = fVar2;
        local_58.y = fVar2;
        local_58.z = fVar3;
        pppCopyVector__FR3Vec3Vec((Vec *)(piVar7 + 6),&local_58);
        fVar2 = FLOAT_80330f70;
        piVar7[5] = (int)FLOAT_80330f70;
        piVar7[4] = (int)fVar2;
        piVar7[3] = (int)fVar2;
        PSMTXCopy(&pppMngStPtr->m_matrix,(Mtx *)(piVar7 + 0xb));
        *piVar7 = 1;
      }
      piVar7 = piVar7 + 0x17;
    }
    for (iVar12 = 0; iVar12 < (int)(uint)*(ushort *)(param_3 + 0x12); iVar12 = iVar12 + 1) {
      if (*piVar14 != 0) {
        PSVECScale((float)piVar14[9],(Vec *)(piVar14 + 6),&VStack_4c);
        PSVECAdd(&VStack_4c,(Vec *)(piVar14 + 3),(Vec *)(piVar14 + 3));
      }
      piVar14 = piVar14 + 0x17;
    }
  }
  return;
}

