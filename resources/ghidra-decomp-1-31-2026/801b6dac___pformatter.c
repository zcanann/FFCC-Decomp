// Function: __pformatter
// Entry: 801b6dac
// Size: 1908 bytes

/* WARNING: Type propagation algorithm not settling */

int __pformatter(code *param_1,undefined4 param_2,char *param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  undefined4 *puVar5;
  undefined8 *puVar6;
  int *piVar7;
  undefined *puVar8;
  byte *pbVar9;
  undefined4 unaff_r22;
  undefined4 unaff_r23;
  undefined *puVar10;
  undefined *puVar11;
  int iVar12;
  uint unaff_r28;
  undefined8 uVar13;
  undefined local_2b8;
  char local_2b7 [3];
  undefined4 local_2b4;
  undefined4 local_2b0;
  int local_2ac;
  undefined *local_2a8;
  undefined4 local_2a4;
  undefined4 local_2a0;
  int local_29c;
  undefined *local_298;
  undefined4 local_294;
  undefined4 local_290;
  int local_28c;
  undefined *local_288;
  undefined4 local_284;
  undefined4 local_280;
  int local_27c;
  undefined *local_278;
  undefined4 local_274;
  undefined4 local_270;
  int local_26c;
  undefined *local_268;
  undefined4 local_264;
  undefined4 local_260;
  int local_25c;
  undefined *local_258;
  undefined4 local_254;
  undefined4 local_250;
  int local_24c;
  undefined *local_248;
  byte local_244 [511];
  undefined auStack_45 [17];
  
  puVar10 = auStack_45 + 1;
  iVar12 = 0;
  local_2b7[0] = ' ';
LAB_801b74fc:
  if (*param_3 == '\0') {
    return iVar12;
  }
  iVar2 = strchr(param_3,0x25);
  if (iVar2 == 0) {
    iVar2 = strlen(param_3);
    if (iVar2 == 0) {
      return iVar12 + iVar2;
    }
    iVar3 = (*param_1)(param_2,param_3);
    if (iVar3 != 0) {
      return iVar12 + iVar2;
    }
    return -1;
  }
  iVar12 = iVar12 + (iVar2 - (int)param_3);
  if ((iVar2 - (int)param_3 != 0) && (iVar3 = (*param_1)(param_2,param_3), iVar3 == 0)) {
    return -1;
  }
  param_3 = (char *)parse_format(iVar2,param_4,&local_254);
  if (local_250._1_1_ == 0x68) goto LAB_801b737c;
  if (local_250._1_1_ < 0x68) {
    if (local_250._1_1_ == 0x58) goto LAB_801b7038;
    if (local_250._1_1_ < 0x58) {
      if (local_250._1_1_ == 0x41) {
LAB_801b71a0:
        if (local_250._0_1_ == '\x05') {
          puVar6 = (undefined8 *)__va_arg(param_4,3);
          uVar13 = *puVar6;
        }
        else {
          puVar6 = (undefined8 *)__va_arg(param_4,3);
          uVar13 = *puVar6;
        }
        local_2b4 = local_254;
        local_2b0 = local_250;
        local_2ac = local_24c;
        local_2a8 = local_248;
        pbVar9 = (byte *)double2hex(uVar13,puVar10,&local_2b4);
        if (pbVar9 == (byte *)0x0) goto LAB_801b737c;
        puVar8 = auStack_45 + -(int)pbVar9;
      }
      else {
        if (0x40 < local_250._1_1_) {
          if ((0x47 < local_250._1_1_) || (local_250._1_1_ < 0x45)) goto LAB_801b737c;
          goto LAB_801b7134;
        }
        if (local_250._1_1_ != 0x25) goto LAB_801b737c;
        pbVar9 = local_244;
        local_244[0] = 0x25;
        puVar8 = (undefined *)0x1;
      }
    }
    else if (local_250._1_1_ == 99) {
      pbVar9 = local_244;
      puVar5 = (undefined4 *)__va_arg(param_4,1);
      local_244[0] = (byte)*puVar5;
      puVar8 = (undefined *)0x1;
    }
    else {
      if (local_250._1_1_ < 99) {
        if (local_250._1_1_ != 0x61) goto LAB_801b737c;
        goto LAB_801b71a0;
      }
      if (local_250._1_1_ < 0x65) goto LAB_801b6f3c;
LAB_801b7134:
      if (local_250._0_1_ == '\x05') {
        puVar6 = (undefined8 *)__va_arg(param_4,3);
        uVar13 = *puVar6;
      }
      else {
        puVar6 = (undefined8 *)__va_arg(param_4,3);
        uVar13 = *puVar6;
      }
      local_2a4 = local_254;
      local_2a0 = local_250;
      local_29c = local_24c;
      local_298 = local_248;
      pbVar9 = (byte *)float2str(uVar13,puVar10,&local_2a4);
      if (pbVar9 == (byte *)0x0) goto LAB_801b737c;
      puVar8 = auStack_45 + -(int)pbVar9;
    }
  }
  else {
    if (local_250._1_1_ == 0x74) goto LAB_801b737c;
    if (local_250._1_1_ < 0x74) {
      if (local_250._1_1_ != 0x6f) {
        if (local_250._1_1_ < 0x6f) {
          if (local_250._1_1_ < 0x6e) {
            if (0x69 < local_250._1_1_) goto LAB_801b737c;
LAB_801b6f3c:
            if (local_250._0_1_ == '\x03') {
              puVar4 = (uint *)__va_arg(param_4,1);
              unaff_r28 = *puVar4;
            }
            else if (local_250._0_1_ == '\x04') {
              puVar5 = (undefined4 *)__va_arg(param_4,2);
              unaff_r22 = *puVar5;
              unaff_r23 = puVar5[1];
            }
            else {
              puVar4 = (uint *)__va_arg(param_4,1);
              unaff_r28 = *puVar4;
            }
            if (local_250._0_1_ == '\x02') {
              unaff_r28 = (uint)(short)unaff_r28;
            }
            if (local_250._0_1_ == '\x01') {
              unaff_r28 = (uint)(char)unaff_r28;
            }
            if (local_250._0_1_ == '\x04') {
              local_264 = local_254;
              local_260 = local_250;
              local_25c = local_24c;
              local_258 = local_248;
              pbVar9 = (byte *)longlong2str(unaff_r22,unaff_r23,puVar10,&local_264);
            }
            else {
              local_274 = local_254;
              local_270 = local_250;
              local_26c = local_24c;
              local_268 = local_248;
              pbVar9 = (byte *)long2str(unaff_r28,puVar10,&local_274);
            }
            if (pbVar9 == (byte *)0x0) goto LAB_801b737c;
            puVar8 = auStack_45 + -(int)pbVar9;
            goto LAB_801b73bc;
          }
          puVar5 = (undefined4 *)__va_arg(param_4,1);
          piVar7 = (int *)*puVar5;
          if (local_250._0_1_ == 2) {
            *(short *)piVar7 = (short)iVar12;
          }
          else if (local_250._0_1_ < 2) {
            if (local_250._0_1_ == 0) {
              *piVar7 = iVar12;
            }
          }
          else if (local_250._0_1_ == 4) {
            piVar7[1] = iVar12;
            *piVar7 = iVar12 >> 0x1f;
          }
          else if (local_250._0_1_ < 4) {
            *piVar7 = iVar12;
          }
          goto LAB_801b74fc;
        }
        if (local_250._1_1_ < 0x73) goto LAB_801b737c;
        if (local_250._0_1_ == '\x06') {
          puVar5 = (undefined4 *)__va_arg(param_4,1);
          puVar8 = (undefined *)*puVar5;
          if (puVar8 == (undefined *)0x0) {
            puVar8 = &DAT_8032ec08;
          }
          iVar3 = wcstombs(local_244,puVar8,0x200);
          if (iVar3 < 0) goto LAB_801b737c;
          pbVar9 = local_244;
        }
        else {
          puVar5 = (undefined4 *)__va_arg(param_4,1);
          pbVar9 = (byte *)*puVar5;
        }
        puVar11 = local_248;
        if (pbVar9 == (byte *)0x0) {
          pbVar9 = &DAT_801e70b8;
        }
        if ((char)local_254 == '\0') {
          if (local_254._2_1_ == '\0') {
            puVar8 = (undefined *)strlen(pbVar9);
          }
          else {
            iVar2 = memchr(pbVar9,0,local_248);
            puVar8 = puVar11;
            if (iVar2 != 0) {
              puVar8 = (undefined *)(iVar2 - (int)pbVar9);
            }
          }
        }
        else {
          puVar8 = (undefined *)(uint)*pbVar9;
          pbVar9 = pbVar9 + 1;
          if ((local_254._2_1_ != '\0') && ((int)local_248 < (int)puVar8)) {
            puVar8 = puVar11;
          }
        }
        goto LAB_801b73bc;
      }
    }
    else if ((local_250._1_1_ != 0x78) && ((0x77 < local_250._1_1_ || (0x75 < local_250._1_1_))))
    goto LAB_801b737c;
LAB_801b7038:
    if (local_250._0_1_ == '\x03') {
      puVar4 = (uint *)__va_arg(param_4,1);
      unaff_r28 = *puVar4;
    }
    else if (local_250._0_1_ == '\x04') {
      puVar5 = (undefined4 *)__va_arg(param_4,2);
      unaff_r22 = *puVar5;
      unaff_r23 = puVar5[1];
    }
    else {
      puVar4 = (uint *)__va_arg(param_4,1);
      unaff_r28 = *puVar4;
    }
    if (local_250._0_1_ == '\x02') {
      unaff_r28 = unaff_r28 & 0xffff;
    }
    if (local_250._0_1_ == '\x01') {
      unaff_r28 = unaff_r28 & 0xff;
    }
    if (local_250._0_1_ == '\x04') {
      local_284 = local_254;
      local_280 = local_250;
      local_27c = local_24c;
      local_278 = local_248;
      pbVar9 = (byte *)longlong2str(unaff_r22,unaff_r23,puVar10,&local_284);
    }
    else {
      local_294 = local_254;
      local_290 = local_250;
      local_28c = local_24c;
      local_288 = local_248;
      pbVar9 = (byte *)long2str(unaff_r28,puVar10,&local_294);
    }
    if (pbVar9 == (byte *)0x0) {
LAB_801b737c:
      iVar3 = strlen(iVar2);
      if (iVar3 == 0) {
        return iVar12 + iVar3;
      }
      iVar2 = (*param_1)(param_2,iVar2);
      if (iVar2 != 0) {
        return iVar12 + iVar3;
      }
      return -1;
    }
    puVar8 = auStack_45 + -(int)pbVar9;
  }
LAB_801b73bc:
  puVar11 = puVar8;
  if (local_254._0_1_ != '\0') {
    local_2b7[0] = ' ';
    if (local_254._0_1_ == '\x02') {
      local_2b7[0] = '0';
    }
    bVar1 = *pbVar9;
    if ((((bVar1 == 0x2b) || (bVar1 == 0x2d)) || (bVar1 == 0x20)) && (local_2b7[0] == '0')) {
      iVar2 = (*param_1)(param_2,pbVar9,1);
      if (iVar2 == 0) {
        return -1;
      }
      pbVar9 = pbVar9 + 1;
      puVar11 = puVar8 + -1;
    }
    for (; (int)puVar8 < local_24c; puVar8 = puVar8 + 1) {
      iVar2 = (*param_1)(param_2,local_2b7,1);
      if (iVar2 == 0) {
        return -1;
      }
    }
  }
  if ((puVar11 != (undefined *)0x0) && (iVar2 = (*param_1)(param_2,pbVar9,puVar11), iVar2 == 0)) {
    return -1;
  }
  if (local_254._0_1_ == '\0') {
    for (; (int)puVar8 < local_24c; puVar8 = puVar8 + 1) {
      local_2b8 = 0x20;
      iVar2 = (*param_1)(param_2,&local_2b8,1);
      if (iVar2 == 0) {
        return -1;
      }
    }
  }
  iVar12 = iVar12 + (int)puVar8;
  goto LAB_801b74fc;
}

