// Function: CcClass2D__13CFlatRuntime2FiiP3VecffiPP8CGObject
// Entry: 8006b1dc
// Size: 1196 bytes

/* WARNING: Removing unreachable block (ram,0x8006b66c) */
/* WARNING: Removing unreachable block (ram,0x8006b664) */
/* WARNING: Removing unreachable block (ram,0x8006b65c) */
/* WARNING: Removing unreachable block (ram,0x8006b654) */
/* WARNING: Removing unreachable block (ram,0x8006b204) */
/* WARNING: Removing unreachable block (ram,0x8006b1fc) */
/* WARNING: Removing unreachable block (ram,0x8006b1f4) */
/* WARNING: Removing unreachable block (ram,0x8006b1ec) */

int CcClass2D__13CFlatRuntime2FiiP3VecffiPP8CGObject
              (undefined8 param_1,double param_2,CFlatRuntime2 *flatRuntime2,uint param_4,
              uint param_5,Vec *vec,int param_7,int *param_8)

{
  byte bVar1;
  float fVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  Vec local_84;
  Vec VStack_78;
  
  dVar12 = (double)(float)(param_2 * param_2);
  for (iVar8 = *(int *)(CFlat._2288_4_ + 0x24); iVar8 != -0x7fd657d4; iVar8 = *(int *)(iVar8 + 0x24)
      ) {
    if (-1 < *(short *)(iVar8 + 0x14)) {
      bVar1 = *(byte *)(iVar8 + 0x38);
      if (((-1 < (int)((uint)bVar1 << 0x18)) &&
          (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
         (uVar3 = (**(code **)(*(int *)(iVar8 + 0x48) + 0xc))(iVar8), (uVar3 & 5) == 5))
      goto LAB_8006b2b0;
    }
  }
  iVar8 = 0;
LAB_8006b2b0:
  iVar7 = 0;
LAB_8006b648:
  do {
    if (iVar8 == 0) {
      return iVar7;
    }
    iVar6 = iVar7;
    if (((*(uint *)(iVar8 + 0x180) & param_5) != 0) &&
       (((param_4 & 1) == 0 ||
        ((*(int *)(iVar8 + 0x58) != 0 && (*(short *)(*(int *)(iVar8 + 0x58) + 0x1c) != 0)))))) {
      dVar11 = (double)*(float *)(iVar8 + 0x15c);
      dVar10 = (double)vec->x;
      if (((dVar11 != dVar10) || (*(float *)(iVar8 + 0x164) != vec->z)) &&
         ((double)(float)(dVar10 - param_2) <= dVar11)) {
        if ((((float)((double)vec->z - param_2) <= *(float *)(iVar8 + 0x164)) &&
            (dVar11 <= (double)(float)(dVar10 + param_2))) &&
           (*(float *)(iVar8 + 0x164) <= (float)((double)vec->z + param_2))) {
          PSVECSubtract((Vec *)(iVar8 + 0x15c),vec,&VStack_78);
          VStack_78.y = FLOAT_80330144;
          dVar10 = (double)PSVECSquareMag(&VStack_78);
          if (((double)FLOAT_80330144 < dVar10) && (dVar10 < dVar12)) {
            if (dVar10 <= (double)FLOAT_80330144) {
              if (DOUBLE_80330178 <= dVar10) {
                fVar2 = (float)dVar10;
                uVar3 = (uint)fVar2 & 0x7f800000;
                if (uVar3 == 0x7f800000) {
                  if (((uint)fVar2 & 0x7fffff) == 0) {
                    iVar5 = 2;
                  }
                  else {
                    iVar5 = 1;
                  }
                }
                else if ((uVar3 < 0x7f800000) && (uVar3 == 0)) {
                  if (((uint)fVar2 & 0x7fffff) == 0) {
                    iVar5 = 3;
                  }
                  else {
                    iVar5 = 5;
                  }
                }
                else {
                  iVar5 = 4;
                }
                if (iVar5 == 1) {
                  dVar10 = (double)DAT_8032ec20;
                }
              }
              else {
                dVar10 = (double)DAT_8032ec20;
              }
            }
            else {
              dVar11 = 1.0 / SQRT(dVar10);
              dVar11 = DOUBLE_80330168 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_80330170);
              dVar11 = DOUBLE_80330168 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_80330170);
              dVar10 = (double)(float)(dVar10 * DOUBLE_80330168 * dVar11 *
                                                -(dVar10 * dVar11 * dVar11 - DOUBLE_80330170));
            }
            if (dVar10 < param_2) {
              if ((param_4 & 2) != 0) {
                PSVECScale((float)((double)FLOAT_80330140 / dVar10),&VStack_78,&VStack_78);
                dVar11 = (double)sin(param_1);
                local_84.x = (float)dVar11;
                local_84.y = FLOAT_80330144;
                dVar11 = (double)cos(param_1);
                local_84.z = (float)dVar11;
                dVar11 = (double)PSVECDotProduct(&VStack_78,&local_84);
                if (dVar11 <= (double)FLOAT_80330144) goto LAB_8006b5d8;
              }
              if ((param_4 & 4) == 0) {
                iVar5 = 0;
                piVar4 = param_8;
                if (0 < iVar7) {
                  do {
                    if (dVar10 < (double)*(float *)(*piVar4 + 0x44)) break;
                    piVar4 = piVar4 + 1;
                    iVar5 = iVar5 + 1;
                    iVar6 = iVar6 + -1;
                  } while (iVar6 != 0);
                }
                iVar6 = iVar7;
                if (iVar7 < param_7 + -1) {
                  iVar6 = param_7 + -1;
                }
                piVar4 = param_8 + iVar6;
                uVar3 = iVar6 - iVar5;
                if (iVar5 < iVar6) {
                  uVar9 = uVar3 >> 3;
                  if (uVar9 != 0) {
                    do {
                      *piVar4 = piVar4[-1];
                      piVar4[-1] = piVar4[-2];
                      piVar4[-2] = piVar4[-3];
                      piVar4[-3] = piVar4[-4];
                      piVar4[-4] = piVar4[-5];
                      piVar4[-5] = piVar4[-6];
                      piVar4[-6] = piVar4[-7];
                      piVar4[-7] = piVar4[-8];
                      piVar4 = piVar4 + -8;
                      uVar9 = uVar9 - 1;
                    } while (uVar9 != 0);
                    uVar3 = uVar3 & 7;
                    if (uVar3 == 0) goto LAB_8006b5b4;
                  }
                  do {
                    *piVar4 = piVar4[-1];
                    piVar4 = piVar4 + -1;
                    uVar3 = uVar3 - 1;
                  } while (uVar3 != 0);
                }
LAB_8006b5b4:
                *(float *)(iVar8 + 0x44) = (float)dVar10;
                param_8[iVar5] = iVar8;
                iVar6 = param_7;
                if (iVar7 + 1 < param_7) {
                  iVar6 = iVar7 + 1;
                }
              }
              else {
                iVar6 = iVar7 + 1;
                param_8[iVar7] = iVar8;
                if (iVar6 == param_7) {
                  return iVar6;
                }
              }
            }
          }
        }
      }
    }
LAB_8006b5d8:
    for (iVar8 = *(int *)(iVar8 + 0x24); iVar7 = iVar6, iVar8 != -0x7fd657d4;
        iVar8 = *(int *)(iVar8 + 0x24)) {
      if (-1 < *(short *)(iVar8 + 0x14)) {
        bVar1 = *(byte *)(iVar8 + 0x38);
        if (((-1 < (int)((uint)bVar1 << 0x18)) &&
            (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
           (uVar3 = (**(code **)(*(int *)(iVar8 + 0x48) + 0xc))(iVar8), (uVar3 & 5) == 5))
        goto LAB_8006b648;
      }
    }
    iVar8 = 0;
  } while( true );
}

