// Function: C_MTX44Inverse
// Entry: 8018680c
// Size: 1008 bytes

/* WARNING: Removing unreachable block (ram,0x80186850) */
/* WARNING: Removing unreachable block (ram,0x8018684c) */
/* WARNING: Removing unreachable block (ram,0x80186844) */
/* WARNING: Removing unreachable block (ram,0x80186840) */
/* WARNING: Removing unreachable block (ram,0x80186838) */
/* WARNING: Removing unreachable block (ram,0x80186834) */

undefined4 C_MTX44Inverse(Mat4x4 *mtx,Mat4x4 *source)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  Mat4x4 local_48;
  
  PSMTX44Copy(mtx,&local_48);
  fVar4 = FLOAT_80333708;
  fVar3 = FLOAT_80333700;
  source->value[0][0] = FLOAT_80333700;
  source->value[0][1] = fVar4;
  source->value[0][2] = fVar4;
  source->value[0][3] = fVar4;
  source->value[1][0] = fVar4;
  source->value[1][1] = fVar3;
  source->value[1][2] = fVar4;
  source->value[1][3] = fVar4;
  source->value[2][0] = fVar4;
  source->value[2][1] = fVar4;
  source->value[2][2] = fVar3;
  source->value[2][3] = fVar4;
  source->value[3][0] = fVar4;
  source->value[3][1] = fVar4;
  source->value[3][2] = fVar4;
  source->value[3][3] = fVar3;
  iVar9 = 0;
  iVar6 = 0;
  iVar7 = 0;
  do {
    iVar5 = 4 - iVar9;
    iVar8 = iVar9 << 4;
    iVar10 = iVar9;
    iVar11 = iVar9;
    fVar1 = FLOAT_80333708;
    if (iVar9 < 4) {
      do {
        fVar2 = ABS(*(float *)((int)local_48.value[0] + iVar8 + iVar7));
        if (fVar1 < fVar2) {
          iVar10 = iVar11;
          fVar1 = fVar2;
        }
        iVar8 = iVar8 + 0x10;
        iVar5 = iVar5 + -1;
        iVar11 = iVar11 + 1;
      } while (iVar5 != 0);
    }
    if (fVar4 == fVar1) {
      return 0;
    }
    if (iVar10 != iVar9) {
      fVar1 = *(float *)((int)local_48.value[0] + iVar6);
      *(float *)((int)local_48.value[0] + iVar6) = local_48.value[iVar10][0];
      local_48.value[iVar10][0] = fVar1;
      fVar1 = *(float *)((int)source->value[0] + iVar6);
      *(float *)((int)source->value[0] + iVar6) = source->value[iVar10][0];
      source->value[iVar10][0] = fVar1;
      fVar1 = *(float *)((int)local_48.value[0] + iVar6 + 4);
      *(float *)((int)local_48.value[0] + iVar6 + 4) = local_48.value[iVar10][1];
      local_48.value[iVar10][1] = fVar1;
      fVar1 = *(float *)((int)source->value[0] + iVar6 + 4);
      *(float *)((int)source->value[0] + iVar6 + 4) = source->value[iVar10][1];
      source->value[iVar10][1] = fVar1;
      fVar1 = *(float *)((int)local_48.value[0] + iVar6 + 8);
      *(float *)((int)local_48.value[0] + iVar6 + 8) = local_48.value[iVar10][2];
      local_48.value[iVar10][2] = fVar1;
      fVar1 = *(float *)((int)source->value[0] + iVar6 + 8);
      *(float *)((int)source->value[0] + iVar6 + 8) = source->value[iVar10][2];
      source->value[iVar10][2] = fVar1;
      fVar1 = *(float *)((int)local_48.value[0] + iVar6 + 0xc);
      *(float *)((int)local_48.value[0] + iVar6 + 0xc) = local_48.value[iVar10][3];
      local_48.value[iVar10][3] = fVar1;
      fVar1 = *(float *)((int)source->value[0] + iVar6 + 0xc);
      *(float *)((int)source->value[0] + iVar6 + 0xc) = source->value[iVar10][3];
      source->value[iVar10][3] = fVar1;
    }
    fVar1 = fVar3 / *(float *)((int)local_48.value[0] + iVar6 + iVar7);
    *(float *)((int)local_48.value[0] + iVar6) = *(float *)((int)local_48.value[0] + iVar6) * fVar1;
    *(float *)((int)source->value[0] + iVar6) = *(float *)((int)source->value[0] + iVar6) * fVar1;
    *(float *)((int)local_48.value[0] + iVar6 + 4) =
         *(float *)((int)local_48.value[0] + iVar6 + 4) * fVar1;
    *(float *)((int)source->value[0] + iVar6 + 4) =
         *(float *)((int)source->value[0] + iVar6 + 4) * fVar1;
    *(float *)((int)local_48.value[0] + iVar6 + 8) =
         *(float *)((int)local_48.value[0] + iVar6 + 8) * fVar1;
    *(float *)((int)source->value[0] + iVar6 + 8) =
         *(float *)((int)source->value[0] + iVar6 + 8) * fVar1;
    *(float *)((int)local_48.value[0] + iVar6 + 0xc) =
         *(float *)((int)local_48.value[0] + iVar6 + 0xc) * fVar1;
    *(float *)((int)source->value[0] + iVar6 + 0xc) =
         *(float *)((int)source->value[0] + iVar6 + 0xc) * fVar1;
    iVar10 = 0;
    iVar8 = 0;
    iVar11 = 2;
    do {
      if (iVar10 != iVar9) {
        fVar1 = *(float *)((int)local_48.value[0] + iVar8 + iVar7);
        *(float *)((int)local_48.value[0] + iVar8) =
             *(float *)((int)local_48.value[0] + iVar8) -
             fVar1 * *(float *)((int)local_48.value[0] + iVar6);
        *(float *)((int)source->value[0] + iVar8) =
             *(float *)((int)source->value[0] + iVar8) -
             fVar1 * *(float *)((int)source->value[0] + iVar6);
        *(float *)((int)local_48.value[0] + iVar8 + 4) =
             *(float *)((int)local_48.value[0] + iVar8 + 4) -
             fVar1 * *(float *)((int)local_48.value[0] + iVar6 + 4);
        *(float *)((int)source->value[0] + iVar8 + 4) =
             *(float *)((int)source->value[0] + iVar8 + 4) -
             fVar1 * *(float *)((int)source->value[0] + iVar6 + 4);
        *(float *)((int)local_48.value[0] + iVar8 + 8) =
             *(float *)((int)local_48.value[0] + iVar8 + 8) -
             fVar1 * *(float *)((int)local_48.value[0] + iVar6 + 8);
        *(float *)((int)source->value[0] + iVar8 + 8) =
             *(float *)((int)source->value[0] + iVar8 + 8) -
             fVar1 * *(float *)((int)source->value[0] + iVar6 + 8);
        *(float *)((int)local_48.value[0] + iVar8 + 0xc) =
             *(float *)((int)local_48.value[0] + iVar8 + 0xc) -
             fVar1 * *(float *)((int)local_48.value[0] + iVar6 + 0xc);
        *(float *)((int)source->value[0] + iVar8 + 0xc) =
             *(float *)((int)source->value[0] + iVar8 + 0xc) -
             fVar1 * *(float *)((int)source->value[0] + iVar6 + 0xc);
      }
      if (iVar10 + 1 != iVar9) {
        fVar1 = *(float *)((int)local_48.value[1] + iVar7 + iVar8);
        *(float *)((int)local_48.value[1] + iVar8) =
             *(float *)((int)local_48.value[1] + iVar8) -
             fVar1 * *(float *)((int)local_48.value[0] + iVar6);
        *(float *)((int)source->value[1] + iVar8) =
             *(float *)((int)source->value[1] + iVar8) -
             fVar1 * *(float *)((int)source->value[0] + iVar6);
        *(float *)((int)local_48.value[1] + iVar8 + 4) =
             *(float *)((int)local_48.value[1] + iVar8 + 4) -
             fVar1 * *(float *)((int)local_48.value[0] + iVar6 + 4);
        *(float *)((int)source->value[1] + iVar8 + 4) =
             *(float *)((int)source->value[1] + iVar8 + 4) -
             fVar1 * *(float *)((int)source->value[0] + iVar6 + 4);
        *(float *)((int)local_48.value[1] + iVar8 + 8) =
             *(float *)((int)local_48.value[1] + iVar8 + 8) -
             fVar1 * *(float *)((int)local_48.value[0] + iVar6 + 8);
        *(float *)((int)source->value[1] + iVar8 + 8) =
             *(float *)((int)source->value[1] + iVar8 + 8) -
             fVar1 * *(float *)((int)source->value[0] + iVar6 + 8);
        *(float *)((int)local_48.value[1] + iVar8 + 0xc) =
             *(float *)((int)local_48.value[1] + iVar8 + 0xc) -
             fVar1 * *(float *)((int)local_48.value[0] + iVar6 + 0xc);
        *(float *)((int)source->value[1] + iVar8 + 0xc) =
             *(float *)((int)source->value[1] + iVar8 + 0xc) -
             fVar1 * *(float *)((int)source->value[0] + iVar6 + 0xc);
      }
      iVar10 = iVar10 + 2;
      iVar8 = iVar8 + 0x20;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    iVar9 = iVar9 + 1;
    iVar6 = iVar6 + 0x10;
    iVar7 = iVar7 + 4;
  } while (iVar9 < 4);
  return 1;
}

