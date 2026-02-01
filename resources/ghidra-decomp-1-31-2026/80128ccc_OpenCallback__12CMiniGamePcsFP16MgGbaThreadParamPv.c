// Function: OpenCallback__12CMiniGamePcsFP16MgGbaThreadParamPv
// Entry: 80128ccc
// Size: 980 bytes

void OpenCallback__12CMiniGamePcsFP16MgGbaThreadParamPv(int param_1,int param_2)

{
  undefined uVar1;
  bool bVar2;
  bool bVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int local_28;
  int local_24 [2];
  
  bVar2 = true;
  bVar3 = false;
  if (*(char *)(param_2 + 0xc4) != '\0') {
    Printf__7CSystemFPce
              (&System,s_isConnectedLine_Chan__d_Line_____801dd2f4,(int)*(char *)(param_2 + 0xbc),
               0x3e1);
  }
  *(undefined *)(param_2 + 0xc4) = 0;
  *(undefined *)(param_2 + 0xc6) = 0;
  *(undefined *)(param_2 + 0xbf) = 3;
  iVar6 = *(int *)(param_2 + 0x30);
  *(undefined4 *)(param_2 + 0x30) =
       *(undefined4 *)(param_1 + *(char *)(param_2 + 0xbc) * 0x60 + 0x16b4);
  if (*(char *)(param_2 + 0x28) == '\0') {
    if (*(char *)(param_2 + 0x2b) == '\0') {
      GbaThreadInitGbaContext__12CMiniGamePcsFP16MgGbaThreadParami(param_1,param_2,1);
      *(undefined *)(param_1 + *(char *)(param_2 + 0xbc) * 0x60 + 0x16ae) =
           *(undefined *)(param_2 + 0x2a);
      *(undefined4 *)(param_1 + *(char *)(param_2 + 0xbc) * 0x60 + 0x16b8) =
           *(undefined4 *)(param_2 + 0x34);
      uVar4 = OSGetTick();
      *(undefined4 *)(param_2 + 0x88) = uVar4;
      *(undefined4 *)(param_1 + *(char *)(param_2 + 0xbc) * 0x60 + 0x16b4) =
           *(undefined4 *)(param_2 + 0x88);
      if (*(char *)(param_2 + 0xc4) != '\0') {
        Printf__7CSystemFPce
                  (&System,s_isConnectedLine_Chan__d_Line_____801dd2f4,
                   (int)*(char *)(param_2 + 0xbc),0x3fc);
      }
      Printf__7CSystemFPce
                (&System,s_chan__d_MG_GBA_THREAD_MSG_SETPOR_801dd318,(int)*(char *)(param_2 + 0xbc),
                 DAT_8032ee98);
      OSSendMessage(param_2,5,1);
    }
    else {
      iVar5 = memcmp(param_2 + 0x28,param_1 + *(char *)(param_2 + 0xbc) * 0x60 + 0x16ac,0x60);
      if ((iVar5 == 0) &&
         ((iVar5 = param_1 + *(char *)(param_2 + 0xbc) * 0x60, iVar6 == *(int *)(iVar5 + 0x16b4) ||
          (iVar6 == *(int *)(param_2 + 0x88))))) {
        *(int *)(iVar5 + 0x16b4) = iVar6;
        bVar2 = false;
        *(int *)(param_2 + 0x88) = iVar6;
      }
      if (bVar2) {
        bVar3 = true;
        OSSendMessage(param_2,4,1);
      }
    }
  }
  else {
    uVar1 = *(undefined *)(param_2 + 0x2a);
    *(undefined *)(param_2 + 0x2a) =
         *(undefined *)(param_1 + *(char *)(param_2 + 0xbc) * 0x60 + 0x16ae);
    uVar4 = *(undefined4 *)(param_2 + 0x34);
    *(undefined4 *)(param_2 + 0x34) =
         *(undefined4 *)(param_1 + *(char *)(param_2 + 0xbc) * 0x60 + 0x16b8);
    iVar5 = memcmp(param_2 + 0x28,param_1 + *(char *)(param_2 + 0xbc) * 0x60 + 0x16ac,0x60);
    if ((iVar5 == 0) &&
       ((iVar5 = param_1 + *(char *)(param_2 + 0xbc) * 0x60, iVar6 == *(int *)(iVar5 + 0x16b4) ||
        (iVar6 == *(int *)(param_2 + 0x88))))) {
      *(int *)(iVar5 + 0x16b4) = iVar6;
      bVar2 = false;
      *(int *)(param_2 + 0x88) = iVar6;
      *(undefined *)(param_1 + *(char *)(param_2 + 0xbc) * 0x60 + 0x16ae) = uVar1;
      *(undefined4 *)(param_1 + *(char *)(param_2 + 0xbc) * 0x60 + 0x16b8) = uVar4;
    }
    if (bVar2) {
      OSSendMessage(param_2,3,1);
    }
  }
  if ((((!bVar2) || (bVar3)) &&
      (iVar5 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0), iVar5 == 0)) &&
     (*(char *)(param_2 + 0xc0) == '0')) {
    local_24[0] = iVar6;
    if (!bVar3) {
      local_24[0] = OSGetTick();
      *(int *)(param_1 + *(char *)(param_2 + 0xbc) * 0x60 + 0x16b4) = local_24[0];
    }
    iVar6 = GBAWrite((int)*(char *)(param_2 + 0xbc),local_24,param_2 + 0xc0);
    if (((((iVar6 == 0) && ((*(byte *)(param_2 + 0xc0) & 0x30) == 0x30)) &&
         ((iVar6 = GBAGetStatus((int)*(char *)(param_2 + 0xbc),param_2 + 0xc0), iVar6 == 0 &&
          ((*(char *)(param_2 + 0xc0) == '8' &&
           (iVar6 = GBARead((int)*(char *)(param_2 + 0xbc),&local_28,param_2 + 0xc0), !bVar3))))))
        && (iVar6 == 0)) &&
       ((local_24[0] == local_28 && ((*(byte *)(param_2 + 0xc0) & 0x30) == 0x30)))) {
      *(int *)(param_2 + 0x88) = local_24[0];
      *(undefined *)(param_2 + 0xc4) = 1;
      *(undefined *)(param_2 + 199) = 0;
      *(undefined *)(param_2 + 0xc5) = 1;
      *(undefined *)(param_2 + 0xbf) = 0;
    }
  }
  return;
}

