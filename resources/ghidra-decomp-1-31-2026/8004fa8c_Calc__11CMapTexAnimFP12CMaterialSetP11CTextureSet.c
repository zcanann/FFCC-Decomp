// Function: Calc__11CMapTexAnimFP12CMaterialSetP11CTextureSet
// Entry: 8004fa8c
// Size: 1496 bytes

void Calc__11CMapTexAnimFP12CMaterialSetP11CTextureSet
               (int param_1,CMaterialSet *materialSet,CTextureSet *textureSet)

{
  short sVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int local_48;
  int local_44;
  float local_40 [2];
  undefined8 local_38;
  undefined4 local_30;
  uint uStack_2c;
  
  if (*(char *)(param_1 + 0x15) == '\0') {
    local_40[0] = *(float *)(param_1 + 0x1c);
    uVar10 = (uint)local_40[0];
    local_38 = (double)(longlong)(int)uVar10;
    iVar4 = __vc__21CPtrArray<P8CTexture>FUl
                      (&textureSet->textures,
                       *(undefined2 *)(*(int *)(param_1 + 0x20) + (uVar10 & 0xffff) * 2));
    sVar1 = *(short *)(param_1 + 10);
    iVar5 = __vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,(int)*(short *)(param_1 + 8));
    iVar9 = iVar5 + sVar1 * 4;
    piVar6 = *(int **)(iVar9 + 0x3c);
    if (piVar6 != (int *)0x0) {
      iVar7 = piVar6[1];
      piVar6[1] = iVar7 + -1;
      if ((iVar7 + -1 == 0) && (piVar6 != (int *)0x0)) {
        (**(code **)(*piVar6 + 8))(piVar6,1);
      }
      *(undefined4 *)(iVar9 + 0x3c) = 0;
    }
    *(int *)(iVar9 + 0x3c) = iVar4;
    *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 1;
    if ((uint)*(ushort *)(iVar5 + 0x18) <= (uint)(int)sVar1) {
      *(short *)(iVar5 + 0x18) = sVar1 + 1;
    }
    dVar3 = DOUBLE_8032fd30;
    *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x1c) + *(float *)(param_1 + 0x18);
    uVar8 = (uint)*(short *)(param_1 + 0x10);
    local_38 = (double)(CONCAT44(0x43300000,uVar8) ^ 0x80000000);
    if ((float)(local_38 - dVar3) <= *(float *)(param_1 + 0x1c)) {
      if (*(char *)(param_1 + 0x16) == '\0') {
        local_38 = (double)CONCAT44(0x43300000,uVar8 ^ 0x80000000);
        *(float *)(param_1 + 0x1c) = (float)(local_38 - dVar3);
      }
      else {
        local_38 = (double)(CONCAT44(0x43300000,uVar8 - (int)*(short *)(param_1 + 0xe)) ^ 0x80000000
                           );
        *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x1c) - (float)(local_38 - dVar3);
      }
    }
    if (*(char *)(param_1 + 0x14) != '\0') {
      uVar8 = uVar10 + 1 & 0xffff;
      uStack_2c = (int)*(short *)(param_1 + 0xc) ^ 0x80000000;
      local_38 = (double)(CONCAT44(0x43300000,uVar10 + 1) & 0xffffffff0000ffff);
      local_30 = 0x43300000;
      if ((float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_8032fd30) <=
          (float)(local_38 - DOUBLE_8032fd40)) {
        uVar8 = 0;
      }
      iVar4 = __vc__21CPtrArray<P8CTexture>FUl
                        (&textureSet->textures,*(undefined2 *)(*(int *)(param_1 + 0x20) + uVar8 * 2)
                        );
      sVar1 = *(short *)(param_1 + 10);
      uVar8 = (int)sVar1 + 1;
      iVar5 = __vc__22CPtrArray<P9CMaterial>FUl
                        (&materialSet->materials,(int)*(short *)(param_1 + 8));
      iVar9 = iVar5 + uVar8 * 4;
      piVar6 = *(int **)(iVar9 + 0x3c);
      if (piVar6 != (int *)0x0) {
        iVar7 = piVar6[1];
        piVar6[1] = iVar7 + -1;
        if ((iVar7 + -1 == 0) && (piVar6 != (int *)0x0)) {
          (**(code **)(*piVar6 + 8))(piVar6,1);
        }
        *(undefined4 *)(iVar9 + 0x3c) = 0;
      }
      *(int *)(iVar9 + 0x3c) = iVar4;
      *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 1;
      if (*(ushort *)(iVar5 + 0x18) <= uVar8) {
        *(short *)(iVar5 + 0x18) = sVar1 + 2;
      }
      iVar4 = __vc__22CPtrArray<P9CMaterial>FUl
                        (&materialSet->materials,(int)*(short *)(param_1 + 8));
      *(char *)(iVar4 + 0xa4) =
           (char)(int)(FLOAT_8032fd38 *
                      (local_40[0] -
                      (float)((double)CONCAT44(0x43300000,uVar10 & 0xffff) - DOUBLE_8032fd40)));
      *(uint *)(iVar4 + 0x24) = *(uint *)(iVar4 + 0x24) | 0x8000;
    }
  }
  else {
    iVar4 = IsRun__12CMapKeyFrameFv((CMapKeyFrame *)(param_1 + 0x24));
    if (iVar4 != 0) {
      iVar4 = Get__12CMapKeyFrameFRiRiRf
                        ((CMapKeyFrame *)(param_1 + 0x24),&local_44,&local_48,local_40);
      if (iVar4 == 0) {
        iVar4 = __vc__21CPtrArray<P8CTexture>FUl
                          (&textureSet->textures,
                           *(undefined2 *)(*(int *)(param_1 + 0x20) + local_44 * 2));
        sVar1 = *(short *)(param_1 + 10);
        iVar5 = __vc__22CPtrArray<P9CMaterial>FUl
                          (&materialSet->materials,(int)*(short *)(param_1 + 8));
        iVar9 = iVar5 + sVar1 * 4;
        piVar6 = *(int **)(iVar9 + 0x3c);
        if (piVar6 != (int *)0x0) {
          iVar7 = piVar6[1];
          piVar6[1] = iVar7 + -1;
          if ((iVar7 + -1 == 0) && (piVar6 != (int *)0x0)) {
            (**(code **)(*piVar6 + 8))(piVar6,1);
          }
          *(undefined4 *)(iVar9 + 0x3c) = 0;
        }
        *(int *)(iVar9 + 0x3c) = iVar4;
        *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 1;
        if ((uint)*(ushort *)(iVar5 + 0x18) <= (uint)(int)sVar1) {
          *(short *)(iVar5 + 0x18) = sVar1 + 1;
        }
        if (*(char *)(param_1 + 0x14) != '\0') {
          iVar4 = __vc__21CPtrArray<P8CTexture>FUl
                            (&textureSet->textures,
                             *(undefined2 *)(*(int *)(param_1 + 0x20) + local_48 * 2));
          sVar1 = *(short *)(param_1 + 10);
          uVar10 = (int)sVar1 + 1;
          iVar5 = __vc__22CPtrArray<P9CMaterial>FUl
                            (&materialSet->materials,(int)*(short *)(param_1 + 8));
          iVar9 = iVar5 + uVar10 * 4;
          piVar6 = *(int **)(iVar9 + 0x3c);
          if (piVar6 != (int *)0x0) {
            iVar7 = piVar6[1];
            piVar6[1] = iVar7 + -1;
            if ((iVar7 + -1 == 0) && (piVar6 != (int *)0x0)) {
              (**(code **)(*piVar6 + 8))(piVar6,1);
            }
            *(undefined4 *)(iVar9 + 0x3c) = 0;
          }
          *(int *)(iVar9 + 0x3c) = iVar4;
          *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 1;
          if (*(ushort *)(iVar5 + 0x18) <= uVar10) {
            *(short *)(iVar5 + 0x18) = sVar1 + 2;
          }
          iVar4 = __vc__22CPtrArray<P9CMaterial>FUl
                            (&materialSet->materials,(int)*(short *)(param_1 + 8));
          *(undefined *)(iVar4 + 0xa4) = 0;
          *(uint *)(iVar4 + 0x24) = *(uint *)(iVar4 + 0x24) | 0x8000;
        }
      }
      else {
        iVar4 = __vc__21CPtrArray<P8CTexture>FUl
                          (&textureSet->textures,
                           *(undefined2 *)(*(int *)(param_1 + 0x20) + local_44 * 2));
        sVar1 = *(short *)(param_1 + 10);
        iVar5 = __vc__22CPtrArray<P9CMaterial>FUl
                          (&materialSet->materials,(int)*(short *)(param_1 + 8));
        iVar9 = iVar5 + sVar1 * 4;
        piVar6 = *(int **)(iVar9 + 0x3c);
        if (piVar6 != (int *)0x0) {
          iVar7 = piVar6[1];
          piVar6[1] = iVar7 + -1;
          if ((iVar7 + -1 == 0) && (piVar6 != (int *)0x0)) {
            (**(code **)(*piVar6 + 8))(piVar6,1);
          }
          *(undefined4 *)(iVar9 + 0x3c) = 0;
        }
        *(int *)(iVar9 + 0x3c) = iVar4;
        *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 1;
        if ((uint)*(ushort *)(iVar5 + 0x18) <= (uint)(int)sVar1) {
          *(short *)(iVar5 + 0x18) = sVar1 + 1;
        }
        if (*(char *)(param_1 + 0x14) != '\0') {
          iVar4 = __vc__21CPtrArray<P8CTexture>FUl
                            (&textureSet->textures,
                             *(undefined2 *)(*(int *)(param_1 + 0x20) + local_48 * 2));
          sVar1 = *(short *)(param_1 + 10);
          uVar10 = (int)sVar1 + 1;
          iVar5 = __vc__22CPtrArray<P9CMaterial>FUl
                            (&materialSet->materials,(int)*(short *)(param_1 + 8));
          iVar9 = iVar5 + uVar10 * 4;
          piVar6 = *(int **)(iVar9 + 0x3c);
          if (piVar6 != (int *)0x0) {
            iVar7 = piVar6[1];
            piVar6[1] = iVar7 + -1;
            if ((iVar7 + -1 == 0) && (piVar6 != (int *)0x0)) {
              (**(code **)(*piVar6 + 8))(piVar6,1);
            }
            *(undefined4 *)(iVar9 + 0x3c) = 0;
          }
          *(int *)(iVar9 + 0x3c) = iVar4;
          *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 1;
          if (*(ushort *)(iVar5 + 0x18) <= uVar10) {
            *(short *)(iVar5 + 0x18) = sVar1 + 2;
          }
          fVar2 = FLOAT_8032fd38 * local_40[0];
          local_38 = (double)(longlong)(int)fVar2;
          iVar4 = __vc__22CPtrArray<P9CMaterial>FUl
                            (&materialSet->materials,(int)*(short *)(param_1 + 8));
          *(char *)(iVar4 + 0xa4) = (char)(int)fVar2;
          *(uint *)(iVar4 + 0x24) = *(uint *)(iVar4 + 0x24) | 0x8000;
        }
      }
      Calc__12CMapKeyFrameFv((CMapKeyFrame *)(param_1 + 0x24));
    }
  }
  return;
}

