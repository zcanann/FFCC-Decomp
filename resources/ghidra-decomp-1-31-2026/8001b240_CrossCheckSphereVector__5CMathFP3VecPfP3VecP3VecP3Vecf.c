// Function: CrossCheckSphereVector__5CMathFP3VecPfP3VecP3VecP3Vecf
// Entry: 8001b240
// Size: 772 bytes

/* WARNING: Removing unreachable block (ram,0x8001b51c) */
/* WARNING: Removing unreachable block (ram,0x8001b514) */
/* WARNING: Removing unreachable block (ram,0x8001b50c) */
/* WARNING: Removing unreachable block (ram,0x8001b504) */
/* WARNING: Removing unreachable block (ram,0x8001b268) */
/* WARNING: Removing unreachable block (ram,0x8001b260) */
/* WARNING: Removing unreachable block (ram,0x8001b258) */
/* WARNING: Removing unreachable block (ram,0x8001b250) */

undefined4
CrossCheckSphereVector__5CMathFP3VecPfP3VecP3VecP3Vecf
          (double param_1,double param_2,double param_3,undefined4 param_4,Vec *param_5,
          float *param_6,Vec *param_7,float *param_8,Vec *param_9)

{
  float fVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  Vec VStack_84;
  Vec local_78;
  Vec local_6c;
  Vec local_60;
  
  dVar8 = (double)(float)(param_2 + param_1);
  dVar10 = (double)(float)(dVar8 / (double)(float)(param_3 + param_1));
  PSVECSubtract(param_7,param_9,&local_60);
  dVar9 = (double)(float)(dVar8 * dVar8);
  local_78.y = (float)((double)local_60.y * dVar10);
  local_6c.x = *param_8;
  local_6c.y = (float)((double)param_8[1] * dVar10);
  local_6c.z = param_8[2];
  local_78.x = local_60.x;
  local_78.z = local_60.z;
  local_60.y = local_78.y;
  dVar8 = (double)PSVECDotProduct(&local_78,&local_78);
  if (dVar8 < dVar9) {
    if (param_6 != (float *)0x0) {
      *param_6 = FLOAT_8032f740;
    }
    if (param_5 != (Vec *)0x0) {
      param_5->x = local_60.x;
      param_5->y = local_60.y;
      param_5->z = local_60.z;
    }
    bVar2 = true;
  }
  else {
    dVar6 = (double)PSVECDotProduct(&local_6c,&local_78);
    if ((double)FLOAT_8032f740 < dVar6) {
      bVar2 = false;
    }
    else {
      dVar7 = (double)PSVECDotProduct(&local_6c,&local_6c);
      fVar1 = (float)(dVar6 * dVar6 - (double)(float)(dVar7 * (double)(float)(dVar8 - dVar9)));
      dVar8 = (double)fVar1;
      if (dVar8 < (double)FLOAT_8032f740) {
        bVar2 = false;
      }
      else {
        if (dVar8 <= (double)FLOAT_8032f740) {
          if (DOUBLE_8032f778 <= dVar8) {
            uVar3 = (uint)fVar1 & 0x7f800000;
            if (uVar3 == 0x7f800000) {
              if (((uint)fVar1 & 0x7fffff) == 0) {
                iVar4 = 2;
              }
              else {
                iVar4 = 1;
              }
            }
            else if ((uVar3 < 0x7f800000) && (uVar3 == 0)) {
              if (((uint)fVar1 & 0x7fffff) == 0) {
                iVar4 = 3;
              }
              else {
                iVar4 = 5;
              }
            }
            else {
              iVar4 = 4;
            }
            if (iVar4 == 1) {
              dVar8 = (double)DAT_8032ec20;
            }
          }
          else {
            dVar8 = (double)DAT_8032ec20;
          }
        }
        else {
          dVar9 = 1.0 / SQRT(dVar8);
          dVar9 = DOUBLE_8032f768 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_8032f770);
          dVar9 = DOUBLE_8032f768 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_8032f770);
          dVar8 = (double)(float)(dVar8 * DOUBLE_8032f768 * dVar9 *
                                          -(dVar8 * dVar9 * dVar9 - DOUBLE_8032f770));
        }
        dVar8 = (double)(float)(-dVar6 - dVar8);
        if ((dVar8 <= (double)FLOAT_8032f740) || (dVar7 < dVar8)) {
          bVar2 = false;
        }
        else {
          if (param_6 != (float *)0x0) {
            *param_6 = (float)(dVar8 / dVar7);
          }
          if (param_5 != (Vec *)0x0) {
            PSVECScale((float)(dVar8 / dVar7),&local_6c,&VStack_84);
            PSVECAdd(&local_60,&VStack_84,param_5);
          }
          bVar2 = true;
        }
      }
    }
  }
  if (bVar2) {
    if (param_5 != (Vec *)0x0) {
      PSVECSubtract(param_5,&local_60,param_5);
      param_5->y = (float)((double)param_5->y / dVar10);
      PSVECAdd(param_5,param_7,param_5);
    }
    uVar5 = 1;
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}

