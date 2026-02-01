// Function: __num2dec_internal
// Entry: 801b3178
// Size: 948 bytes

void __num2dec_internal(double param_1,char *param_2)

{
  undefined uVar1;
  uint uVar2;
  int iVar3;
  char cVar4;
  undefined extraout_r4;
  undefined *puVar5;
  uint uVar6;
  undefined *puVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  undefined8 uVar11;
  longlong lVar12;
  double local_a8;
  int local_a0 [2];
  undefined8 local_98;
  undefined8 local_88;
  undefined8 local_80;
  undefined auStack_78 [44];
  undefined local_4c [2];
  short local_4a;
  byte local_48;
  undefined local_47 [39];
  
  local_a8._0_4_ = (uint)((ulonglong)param_1 >> 0x20);
  cVar4 = -(char)((longlong)param_1 >> 0x3f);
  if (DOUBLE_80333930 == param_1) {
    *param_2 = cVar4;
    param_2[2] = '\0';
    param_2[3] = '\0';
    param_2[4] = '\x01';
    param_2[5] = '\0';
  }
  else {
    local_88._4_4_ = SUB84(param_1,0);
    if ((local_a8._0_4_ & 0x7ff00000) == 0x7ff00000) {
      if ((((ulonglong)param_1 & 0xfffff00000000) == 0) && (local_88._4_4_ == 0)) {
        uVar2 = 2;
      }
      else {
        uVar2 = 1;
      }
    }
    else if (((local_a8._0_4_ & 0x7ff00000) < 0x7ff00000) &&
            (((ulonglong)param_1 & 0x7ff0000000000000) == 0)) {
      if ((((ulonglong)param_1 & 0xfffff00000000) == 0) && (local_88._4_4_ == 0)) {
        uVar2 = 3;
      }
      else {
        uVar2 = 5;
      }
    }
    else {
      uVar2 = 4;
    }
    if (uVar2 < 3) {
      *param_2 = cVar4;
      param_2[2] = '\0';
      param_2[3] = '\0';
      param_2[4] = '\x01';
      if ((local_a8._0_4_ & 0x7ff00000) == 0x7ff00000) {
        if ((((ulonglong)param_1 & 0xfffff00000000) == 0) && (local_88._4_4_ == 0)) {
          iVar3 = 2;
        }
        else {
          iVar3 = 1;
        }
      }
      else if (((local_a8._0_4_ & 0x7ff00000) < 0x7ff00000) &&
              (((ulonglong)param_1 & 0x7ff0000000000000) == 0)) {
        if ((((ulonglong)param_1 & 0xfffff00000000) == 0) && (local_88._4_4_ == 0)) {
          iVar3 = 3;
        }
        else {
          iVar3 = 5;
        }
      }
      else {
        iVar3 = 4;
      }
      cVar4 = 'I';
      if (iVar3 == 1) {
        cVar4 = 'N';
      }
      param_2[5] = cVar4;
    }
    else {
      local_a8 = param_1;
      if (cVar4 != '\0') {
        local_a8 = -param_1;
      }
      local_88 = param_1;
      uVar11 = frexp(local_a8,local_a0);
      local_98._4_4_ = (uint)uVar11;
      if (local_98._4_4_ == 0) {
        local_98._0_4_ = (uint)((ulonglong)uVar11 >> 0x20);
        uVar6 = 0x10;
        iVar9 = 0;
        iVar3 = 0x10;
        local_98._0_4_ = local_98._0_4_ | 0x100000;
        uVar2 = 0xffff;
        iVar8 = 0x20;
        while (iVar8 != 0) {
          if ((local_98._0_4_ & uVar2) == 0) {
            iVar9 = iVar9 + iVar3;
            local_98._0_4_ = local_98._0_4_ >> iVar3;
            iVar8 = iVar8 - iVar3;
          }
          else if (uVar2 == 1) break;
          if (1 < uVar6) {
            uVar6 = (int)uVar6 >> 1;
          }
          if (1 < uVar2) {
            uVar2 = uVar2 >> uVar6;
            iVar3 = iVar3 - uVar6;
          }
        }
        iVar9 = iVar9 + 0x20;
      }
      else {
        uVar6 = 0x10;
        iVar9 = 0;
        iVar8 = 0x20;
        iVar3 = 0x10;
        uVar2 = 0xffff;
        while (iVar8 != 0) {
          if ((local_98._4_4_ & uVar2) == 0) {
            iVar9 = iVar9 + iVar3;
            local_98._4_4_ = local_98._4_4_ >> iVar3;
            iVar8 = iVar8 - iVar3;
          }
          else if (uVar2 == 1) break;
          if (1 < uVar6) {
            uVar6 = (int)uVar6 >> 1;
          }
          if (1 < uVar2) {
            uVar2 = uVar2 >> uVar6;
            iVar3 = iVar3 - uVar6;
          }
        }
      }
      local_98 = uVar11;
      __two_exp(auStack_78,local_a0[0] - (0x35 - iVar9));
      ldexp(uVar11,0x35 - iVar9);
      modf(&local_80);
      lVar12 = __cvt_dbl_usll(local_80);
      local_4c[0] = 0;
      if (lVar12 == 0) {
        local_4a = 0;
        local_48 = 1;
        local_47[0] = 0;
      }
      else {
        local_48 = 0;
        while( true ) {
          uVar10 = (undefined4)((ulonglong)lVar12 >> 0x20);
          if (lVar12 == 0) break;
          __mod2u(uVar10,(int)lVar12,0,10);
          uVar2 = (uint)local_48;
          local_48 = local_48 + 1;
          local_47[uVar2] = extraout_r4;
          lVar12 = __div2u(uVar10,(int)lVar12,0,10);
        }
        puVar5 = local_47 + local_48;
        for (puVar7 = local_47; puVar5 = puVar5 + -1, puVar7 < puVar5; puVar7 = puVar7 + 1) {
          uVar1 = *puVar7;
          *puVar7 = *puVar5;
          *puVar5 = uVar1;
        }
        local_4a = local_48 - 1;
      }
      __timesdec(param_2,local_4c,auStack_78);
      *param_2 = cVar4;
    }
  }
  return;
}

