// Function: CheckFrustum0__6CBoundFf
// Entry: 8001b728
// Size: 628 bytes

/* WARNING: Removing unreachable block (ram,0x8001b980) */
/* WARNING: Removing unreachable block (ram,0x8001b978) */
/* WARNING: Removing unreachable block (ram,0x8001b970) */
/* WARNING: Removing unreachable block (ram,0x8001b748) */
/* WARNING: Removing unreachable block (ram,0x8001b740) */
/* WARNING: Removing unreachable block (ram,0x8001b738) */

int CheckFrustum0__6CBoundFf(double param_1,float *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  Vec local_68;
  Vec local_5c;
  
  if ((((param_2[3] < s_f_vpos.x) || (param_2[4] < s_f_vpos.y)) || (param_2[5] < s_f_vpos.z)) ||
     (((s_f_vpos.x < *param_2 || (s_f_vpos.y < param_2[1])) || (s_f_vpos.z < param_2[2])))) {
    dVar8 = (double)FLOAT_8032f780;
    dVar9 = (double)FLOAT_8032f740;
    uVar6 = 0xf;
    uVar5 = 0;
    iVar2 = 0;
    do {
      if (iVar2 == 0) {
        local_5c.x = *param_2;
      }
      else {
        local_5c.x = param_2[3];
      }
      iVar4 = 0;
      do {
        if (iVar4 == 0) {
          local_5c.y = param_2[1];
        }
        else {
          local_5c.y = param_2[4];
        }
        iVar3 = 0;
        do {
          if (iVar3 == 0) {
            local_5c.z = param_2[2];
          }
          else {
            local_5c.z = param_2[5];
          }
          PSMTXMultVec(&s_f_lvmtx,&local_5c,&local_68);
          dVar7 = (double)local_68.z;
          if (dVar8 < dVar7) {
            dVar8 = dVar7;
          }
          if (dVar7 <= dVar9) {
            if ((double)local_68.x <= -dVar7) {
              if (dVar7 <= (double)local_68.x) {
                uVar1 = 0;
              }
              else {
                uVar1 = 2;
              }
            }
            else {
              uVar1 = 1;
            }
            if ((double)local_68.y <= -dVar7) {
              if ((double)local_68.y < dVar7) {
                uVar1 = uVar1 | 8;
              }
            }
            else {
              uVar1 = uVar1 | 4;
            }
          }
          else {
            if ((double)local_68.x <= -dVar7) {
              if (dVar7 <= (double)local_68.x) {
                uVar1 = 0x10;
              }
              else {
                uVar1 = 0x12;
              }
            }
            else {
              uVar1 = 0x11;
            }
            if ((double)local_68.y <= -dVar7) {
              if ((double)local_68.y < dVar7) {
                uVar1 = uVar1 | 0x18;
              }
            }
            else {
              uVar1 = uVar1 | 0x14;
            }
          }
          iVar3 = iVar3 + 1;
          uVar6 = uVar6 & uVar1;
          uVar5 = uVar5 | uVar1;
        } while (iVar3 < 2);
        iVar4 = iVar4 + 1;
      } while (iVar4 < 2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 2);
    if (param_1 <= dVar8) {
      if (uVar6 == 0) {
        uVar5 = countLeadingZeros(uVar5);
        iVar2 = (uVar5 >> 5) + 1;
      }
      else {
        iVar2 = 0;
      }
    }
    else {
      iVar2 = 0;
    }
  }
  else {
    iVar2 = 1;
  }
  return iVar2;
}

