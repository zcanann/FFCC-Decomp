// Function: CheckFrustum0__6CBoundFR6CBound
// Entry: 8001b99c
// Size: 1084 bytes

/* WARNING: Removing unreachable block (ram,0x8001bdbc) */
/* WARNING: Removing unreachable block (ram,0x8001b9ac) */

int CheckFrustum0__6CBoundFR6CBound(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  Vec local_48;
  Vec local_3c;
  
  fVar2 = FLOAT_8032f788;
  fVar1 = FLOAT_8032f784;
  param_2[2] = FLOAT_8032f784;
  param_2[1] = fVar1;
  *param_2 = fVar1;
  param_2[5] = fVar2;
  param_2[4] = fVar2;
  param_2[3] = fVar2;
  if ((((param_1[3] < s_f_vpos.x) || (param_1[4] < s_f_vpos.y)) || (param_1[5] < s_f_vpos.z)) ||
     (((s_f_vpos.x < *param_1 || (s_f_vpos.y < param_1[1])) || (s_f_vpos.z < param_1[2])))) {
    dVar10 = (double)FLOAT_8032f740;
    uVar5 = 0xf;
    uVar7 = 0;
    iVar8 = 0;
    do {
      if (iVar8 == 0) {
        local_3c.x = *param_1;
      }
      else {
        local_3c.x = param_1[3];
      }
      iVar6 = 0;
      do {
        if (iVar6 == 0) {
          local_3c.y = param_1[1];
        }
        else {
          local_3c.y = param_1[4];
        }
        iVar4 = 0;
        do {
          if (iVar4 == 0) {
            local_3c.z = param_1[2];
          }
          else {
            local_3c.z = param_1[5];
          }
          PSMTXMultVec(&s_f_lvmtx,&local_3c,&local_48);
          fVar1 = local_48.x;
          if (*param_2 < local_48.x) {
            fVar1 = *param_2;
          }
          *param_2 = fVar1;
          fVar1 = local_48.y;
          if (param_2[1] < local_48.y) {
            fVar1 = param_2[1];
          }
          param_2[1] = fVar1;
          fVar1 = local_48.z;
          if (param_2[2] < local_48.z) {
            fVar1 = param_2[2];
          }
          param_2[2] = fVar1;
          fVar1 = local_48.x;
          if (local_48.x < param_2[3]) {
            fVar1 = param_2[3];
          }
          param_2[3] = fVar1;
          fVar1 = local_48.y;
          if (local_48.y < param_2[4]) {
            fVar1 = param_2[4];
          }
          param_2[4] = fVar1;
          fVar1 = local_48.z;
          if (local_48.z < param_2[5]) {
            fVar1 = param_2[5];
          }
          param_2[5] = fVar1;
          dVar9 = (double)local_48.z;
          if (dVar9 <= dVar10) {
            if ((double)local_48.x <= -dVar9) {
              if (dVar9 <= (double)local_48.x) {
                uVar3 = 0;
              }
              else {
                uVar3 = 2;
              }
            }
            else {
              uVar3 = 1;
            }
            if ((double)local_48.y <= -dVar9) {
              if ((double)local_48.y < dVar9) {
                uVar3 = uVar3 | 8;
              }
            }
            else {
              uVar3 = uVar3 | 4;
            }
          }
          else {
            if ((double)local_48.x <= -dVar9) {
              if (dVar9 <= (double)local_48.x) {
                uVar3 = 0x10;
              }
              else {
                uVar3 = 0x12;
              }
            }
            else {
              uVar3 = 0x11;
            }
            if ((double)local_48.y <= -dVar9) {
              if ((double)local_48.y < dVar9) {
                uVar3 = uVar3 | 0x18;
              }
            }
            else {
              uVar3 = uVar3 | 0x14;
            }
          }
          iVar4 = iVar4 + 1;
          uVar5 = uVar5 & uVar3;
          uVar7 = uVar7 | uVar3;
        } while (iVar4 < 2);
        iVar6 = iVar6 + 1;
      } while (iVar6 < 2);
      iVar8 = iVar8 + 1;
    } while (iVar8 < 2);
    if (uVar5 == 0) {
      uVar5 = countLeadingZeros(uVar7);
      iVar8 = (uVar5 >> 5) + 1;
    }
    else {
      iVar8 = 0;
    }
  }
  else {
    iVar8 = 0;
    do {
      if (iVar8 == 0) {
        local_3c.x = *param_1;
      }
      else {
        local_3c.x = param_1[3];
      }
      iVar6 = 0;
      do {
        if (iVar6 == 0) {
          local_3c.y = param_1[1];
        }
        else {
          local_3c.y = param_1[4];
        }
        iVar4 = 0;
        do {
          if (iVar4 == 0) {
            local_3c.z = param_1[2];
          }
          else {
            local_3c.z = param_1[5];
          }
          PSMTXMultVec(&s_f_lvmtx,&local_3c,&local_48);
          fVar1 = local_48.x;
          if (*param_2 < local_48.x) {
            fVar1 = *param_2;
          }
          *param_2 = fVar1;
          fVar1 = local_48.y;
          if (param_2[1] < local_48.y) {
            fVar1 = param_2[1];
          }
          param_2[1] = fVar1;
          fVar1 = local_48.z;
          if (param_2[2] < local_48.z) {
            fVar1 = param_2[2];
          }
          param_2[2] = fVar1;
          fVar1 = local_48.x;
          if (local_48.x < param_2[3]) {
            fVar1 = param_2[3];
          }
          param_2[3] = fVar1;
          fVar1 = local_48.y;
          if (local_48.y < param_2[4]) {
            fVar1 = param_2[4];
          }
          param_2[4] = fVar1;
          fVar1 = local_48.z;
          if (local_48.z < param_2[5]) {
            fVar1 = param_2[5];
          }
          iVar4 = iVar4 + 1;
          param_2[5] = fVar1;
        } while (iVar4 < 2);
        iVar6 = iVar6 + 1;
      } while (iVar6 < 2);
      iVar8 = iVar8 + 1;
    } while (iVar8 < 2);
    iVar8 = 1;
  }
  return iVar8;
}

