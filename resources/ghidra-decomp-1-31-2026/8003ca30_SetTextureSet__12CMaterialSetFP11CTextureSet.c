// Function: SetTextureSet__12CMaterialSetFP11CTextureSet
// Entry: 8003ca30
// Size: 908 bytes

void SetTextureSet__12CMaterialSetFP11CTextureSet(CMaterialSet *param_1,CTextureSet *textureSet)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  
  uVar10 = 0;
  do {
    uVar6 = _UnkMaterialSetGetter((CMaterial *)&param_1->materials);
    if (uVar6 <= uVar10) {
      return;
    }
    iVar2 = __vc__22CPtrArray<P9CMaterial>FUl(&param_1->materials,uVar10);
    if (iVar2 != 0) {
      if (*(short *)(iVar2 + 0x18) == 0) {
        *(uint *)(iVar2 + 0x24) = *(uint *)(iVar2 + 0x24) | 1;
      }
      else {
        iVar8 = iVar2;
        iVar11 = iVar2;
        for (iVar9 = 0; iVar9 < (int)(uint)*(ushort *)(iVar2 + 0x18); iVar9 = iVar9 + 1) {
          piVar3 = *(int **)(iVar11 + 0x3c);
          if (piVar3 != (int *)0x0) {
            iVar7 = piVar3[1];
            piVar3[1] = iVar7 + -1;
            if ((iVar7 + -1 == 0) && (piVar3 != (int *)0x0)) {
              (**(code **)(*piVar3 + 8))(piVar3,1);
            }
            *(undefined4 *)(iVar11 + 0x3c) = 0;
          }
          if (textureSet != (CTextureSet *)0x0) {
            uVar6 = (uint)*(short *)(iVar8 + 0x1a);
            if (((int)uVar6 < 0) ||
               (uVar4 = GetSize__21CPtrArray<P8CTexture>Fv(&textureSet->textures), uVar4 <= uVar6))
            {
              *(undefined4 *)(iVar11 + 0x3c) = 0;
            }
            else {
              uVar5 = __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,uVar6);
              *(undefined4 *)(iVar11 + 0x3c) = uVar5;
              iVar7 = *(int *)(iVar11 + 0x3c);
              if (iVar7 != 0) {
                bVar1 = true;
                *(int *)(iVar7 + 4) = *(int *)(iVar7 + 4) + 1;
                iVar7 = *(int *)(*(int *)(iVar11 + 0x3c) + 0x60);
                if ((iVar7 != 9) && (iVar7 != 8)) {
                  bVar1 = false;
                }
                if (bVar1) {
                  *(uint *)(iVar2 + 0x24) = *(uint *)(iVar2 + 0x24) | 0x200;
                }
                else if (iVar7 == 1) {
                  *(uint *)(iVar2 + 0x24) = *(uint *)(iVar2 + 0x24) | 0x400;
                }
                if (*(char *)(*(int *)(iVar11 + 0x3c) + 0x71) != '\0') {
                  *(uint *)(iVar2 + 0x24) = *(uint *)(iVar2 + 0x24) | 0x800;
                }
              }
            }
          }
          iVar11 = iVar11 + 4;
          iVar8 = iVar8 + 2;
        }
        if ((((*(char *)(iVar2 + 0xa2) != '\0') && (1 < *(ushort *)(iVar2 + 0x18))) &&
            (*(int *)(iVar2 + 0x3c) != 0)) && (*(int *)(iVar2 + 0x40) != 0)) {
          iVar8 = 0x1f;
          uVar6 = *(uint *)(*(int *)(iVar2 + 0x3c) + 100) / *(uint *)(*(int *)(iVar2 + 0x40) + 100);
          iVar11 = 4;
          do {
            iVar9 = iVar8;
            if ((((((uVar6 & 1 << iVar8) != 0) || (iVar9 = iVar8 + -1, (uVar6 & 1 << iVar9) != 0))
                 || ((iVar9 = iVar8 + -2, (uVar6 & 1 << iVar9) != 0 ||
                     ((iVar9 = iVar8 + -3, (uVar6 & 1 << iVar9) != 0 ||
                      (iVar9 = iVar8 + -4, (uVar6 & 1 << iVar9) != 0)))))) ||
                (iVar9 = iVar8 + -5, (uVar6 & 1 << iVar9) != 0)) ||
               ((iVar9 = iVar8 + -6, (uVar6 & 1 << iVar9) != 0 ||
                (iVar9 = iVar8 + -7, (uVar6 & 1 << iVar8 + -7) != 0)))) goto LAB_8003cc94;
            iVar8 = iVar8 + -8;
            iVar11 = iVar11 + -1;
          } while (iVar11 != 0);
          iVar9 = -1;
LAB_8003cc94:
          *(char *)(iVar2 + 0x34) = (char)iVar9;
          if (*(char *)(iVar2 + 0x34) == -1) {
            *(undefined *)(iVar2 + 0x34) = 0;
          }
          iVar8 = 0x1f;
          uVar6 = *(uint *)(*(int *)(iVar2 + 0x3c) + 0x68) /
                  *(uint *)(*(int *)(iVar2 + 0x40) + 0x68);
          iVar11 = 4;
          do {
            iVar9 = iVar8;
            if (((((uVar6 & 1 << iVar8) != 0) || (iVar9 = iVar8 + -1, (uVar6 & 1 << iVar9) != 0)) ||
                (iVar9 = iVar8 + -2, (uVar6 & 1 << iVar9) != 0)) ||
               (((iVar9 = iVar8 + -3, (uVar6 & 1 << iVar9) != 0 ||
                 (iVar9 = iVar8 + -4, (uVar6 & 1 << iVar9) != 0)) ||
                ((iVar9 = iVar8 + -5, (uVar6 & 1 << iVar9) != 0 ||
                 ((iVar9 = iVar8 + -6, (uVar6 & 1 << iVar9) != 0 ||
                  (iVar9 = iVar8 + -7, (uVar6 & 1 << iVar9) != 0)))))))) goto LAB_8003cd78;
            iVar8 = iVar8 + -8;
            iVar11 = iVar11 + -1;
          } while (iVar11 != 0);
          iVar9 = -1;
LAB_8003cd78:
          *(char *)(iVar2 + 0x35) = (char)iVar9;
          if (*(char *)(iVar2 + 0x35) == -1) {
            *(undefined *)(iVar2 + 0x35) = 0;
          }
        }
      }
    }
    uVar10 = uVar10 + 1;
  } while( true );
}

