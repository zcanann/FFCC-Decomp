// Function: AddFrame__11CTexAnimSetFv
// Entry: 800440ec
// Size: 852 bytes

/* WARNING: Removing unreachable block (ram,0x80044424) */
/* WARNING: Removing unreachable block (ram,0x8004441c) */
/* WARNING: Removing unreachable block (ram,0x80044104) */
/* WARNING: Removing unreachable block (ram,0x800440fc) */

void AddFrame__11CTexAnimSetFv(CTexAnimSet *texAnimSet)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined4 *puVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  Vec VStack_68;
  Vec VStack_5c;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  
  uVar10 = 0;
  do {
    uVar6 = GetSize__21CPtrArray<P8CTexAnim>Fv((CPtrArray *)&(texAnimSet->texAnims).size);
    if (uVar6 <= uVar10) {
      return;
    }
    iVar3 = __vc__21CPtrArray<P8CTexAnim>FUl(&(texAnimSet->texAnims).size,uVar10);
    iVar3 = __vc__25CPtrArray<P11CTexAnimSeq>FUl
                      (*(int *)(iVar3 + 8) + 0x110,*(undefined4 *)(iVar3 + 0xc));
    fVar1 = FLOAT_8032fb3c;
    if ((int)((uint)*(byte *)(iVar3 + 0x110) << 0x19 | (uint)(*(byte *)(iVar3 + 0x110) >> 7)) < 0) {
      fVar1 = FLOAT_8032fb4c;
    }
    dVar14 = (double)fVar1;
    iVar3 = __vc__21CPtrArray<P8CTexAnim>FUl(&(texAnimSet->texAnims).size,uVar10);
    iVar4 = __vc__25CPtrArray<P11CTexAnimSeq>FUl
                      (*(int *)(iVar3 + 8) + 0x110,*(undefined4 *)(iVar3 + 0xc));
    uVar6 = (uint)*(byte *)(iVar4 + 0x110) << 0x1a | (uint)(*(byte *)(iVar4 + 0x110) >> 6);
    if ((((-1 < (int)uVar6) || (-1 < (int)uVar6)) || (FLOAT_8032fb3c != *(float *)(iVar3 + 0x10)))
       || (iVar5 = Rand__5CMathFUl(&Math,0x1e), iVar5 == 0)) {
      uStack_4c = *(undefined4 *)(iVar4 + 0x108);
      local_50 = 0x43300000;
      dVar12 = (double)fmod((double)*(float *)(iVar3 + 0x10),
                            (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8032fb40
                                           ));
      iVar5 = *(int *)(iVar4 + 0x10c);
      fVar1 = (float)dVar12;
      puVar8 = *(undefined4 **)(iVar4 + 0x114);
      uVar6 = 0;
      uVar7 = iVar5 - 1;
      puVar11 = puVar8;
      for (; iVar5 != 0; iVar5 = iVar5 + -1) {
        if (uVar6 < uVar7) {
          uStack_4c = puVar11[0xc];
        }
        else {
          uStack_4c = *(undefined4 *)(iVar4 + 0x108);
        }
        local_50 = 0x43300000;
        fVar2 = (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8032fb40);
        puVar9 = puVar8;
        if (uVar6 < uVar7) {
          puVar9 = puVar8 + (uVar6 + 1) * 0xc;
        }
        uStack_44 = *puVar11;
        local_48 = 0x43300000;
        if (((float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8032fb40) <= fVar1) &&
           (fVar1 < fVar2)) {
          dVar13 = (double)FLOAT_8032fb38;
          local_48 = 0x43300000;
          dVar12 = (double)(fVar2 - (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8032fb40
                                           ));
          if (dVar13 != dVar12) {
            dVar13 = (double)(float)((double)(fVar1 - (float)((double)CONCAT44(0x43300000,uStack_44)
                                                             - DOUBLE_8032fb40)) / dVar12);
            uStack_4c = uStack_44;
          }
          local_50 = 0x43300000;
          PSVECScale((float)((double)FLOAT_8032fb3c - dVar13),(Vec *)(puVar11 + 9),&VStack_68);
          PSVECScale((float)dVar13,(Vec *)(puVar9 + 9),&VStack_5c);
          PSVECAdd(&VStack_68,&VStack_5c,(Vec *)(iVar3 + 0x18));
          if (-1 < (int)((uint)*(byte *)(iVar4 + 0x110) << 0x18)) {
            *(undefined4 *)(iVar3 + 0x18) = puVar11[9];
            *(undefined4 *)(iVar3 + 0x1c) = puVar11[10];
          }
          break;
        }
        puVar11 = puVar11 + 0xc;
        uVar6 = uVar6 + 1;
      }
      dVar12 = DOUBLE_8032fb40;
      if (*(int *)(iVar3 + 0x14) != -3) {
        local_48 = 0x43300000;
        *(float *)(iVar3 + 0x10) = (float)((double)*(float *)(iVar3 + 0x10) + dVar14);
        uStack_44 = *(undefined4 *)(iVar4 + 0x108);
        if ((float)((double)CONCAT44(0x43300000,uStack_44) - dVar12) <= *(float *)(iVar3 + 0x10)) {
          iVar5 = *(int *)(iVar3 + 0x14);
          if (iVar5 == -1) {
            *(float *)(iVar3 + 0x10) = (float)((double)CONCAT44(0x43300000,uStack_44) - dVar12);
          }
          else if (-1 < iVar5) {
            *(int *)(iVar3 + 0xc) = iVar5;
            *(undefined4 *)(iVar3 + 0x14) = 0xfffffffe;
          }
          uStack_44 = *(undefined4 *)(iVar4 + 0x108);
          local_48 = 0x43300000;
          *(float *)(iVar3 + 0x10) =
               *(float *)(iVar3 + 0x10) -
               (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8032fb40);
        }
      }
    }
    iVar3 = __vc__21CPtrArray<P8CTexAnim>FUl(&(texAnimSet->texAnims).size,uVar10);
    iVar3 = __vc__25CPtrArray<P11CTexAnimSeq>FUl
                      (*(int *)(iVar3 + 8) + 0x110,*(undefined4 *)(iVar3 + 0xc));
    if ((int)((uint)*(byte *)(iVar3 + 0x110) << 0x19 | (uint)(*(byte *)(iVar3 + 0x110) >> 7)) < 0) {
      iVar3 = __vc__21CPtrArray<P8CTexAnim>FUl(&(texAnimSet->texAnims).size,uVar10);
      *(undefined4 *)&texAnimSet->field_0x24 = *(undefined4 *)(iVar3 + 0x20);
    }
    else {
      *(float *)&texAnimSet->field_0x24 = FLOAT_8032fb38;
    }
    uVar10 = uVar10 + 1;
  } while( true );
}

