// Function: AlarmHandler
// Entry: 801877b0
// Size: 132 bytes

void AlarmHandler(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((&DAT_8030c950)[DAT_8032f05c * 5] == 1) {
    iVar1 = DAT_8032f05c * 5;
    iVar2 = DAT_8032f05c * 5;
    iVar3 = DAT_8032f05c * 5;
    iVar4 = DAT_8032f05c * 5;
    DAT_8032f05c = DAT_8032f05c + 1;
    Read((&DAT_8030c954)[iVar1],(&DAT_8030c958)[iVar2],(&DAT_8030c95c)[iVar3],(&DAT_8030c960)[iVar4]
        );
  }
  else if ((&DAT_8030c950)[DAT_8032f05c * 5] == 2) {
    iVar1 = DAT_8032f05c * 5;
    iVar2 = DAT_8032f05c * 5;
    DAT_8032f05c = DAT_8032f05c + 1;
    DVDLowSeek((&DAT_8030c95c)[iVar1],(&DAT_8030c960)[iVar2]);
  }
  return;
}

