// Function: DVDCompareDiskID
// Entry: 8018b4fc
// Size: 248 bytes

undefined4 DVDCompareDiskID(char *param_1,char *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (((*param_1 != '\0') && (*param_2 != '\0')) && (iVar1 = strncmp(param_1,param_2,4), iVar1 != 0)
     ) {
    return 0;
  }
  if (((param_1[4] == '\0') || (param_2[4] == '\0')) ||
     (iVar1 = strncmp(param_1 + 4,param_2 + 4,2), iVar1 != 0)) {
    uVar2 = 0;
  }
  else if (((param_1[6] == -1) || (param_2[6] == -1)) || (param_1[6] == param_2[6])) {
    if (((param_1[7] == -1) || (param_2[7] == -1)) || (param_1[7] == param_2[7])) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

