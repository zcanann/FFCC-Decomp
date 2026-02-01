// Function: searchID__11CDbgMenuPcsFiRQ211CDbgMenuPcs3CDM
// Entry: 8012bb0c
// Size: 576 bytes

int searchID__11CDbgMenuPcsFiRQ211CDbgMenuPcs3CDM(undefined4 param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  
  iVar3 = param_3;
  do {
    if (*(int *)(iVar3 + 0x38) == param_2) {
      return iVar3;
    }
    iVar4 = *(int *)(iVar3 + 0x50);
    iVar17 = iVar4;
    if (iVar4 != 0) {
      do {
        iVar2 = iVar17;
        if (*(int *)(iVar17 + 0x38) == param_2) goto LAB_8012bd18;
        iVar10 = *(int *)(iVar17 + 0x50);
        iVar16 = iVar10;
        if (iVar10 != 0) {
          do {
            iVar2 = iVar16;
            if (*(int *)(iVar16 + 0x38) == param_2) goto LAB_8012bcf8;
            iVar9 = *(int *)(iVar16 + 0x50);
            iVar15 = iVar9;
            if (iVar9 != 0) {
              do {
                iVar2 = iVar15;
                if (*(int *)(iVar15 + 0x38) == param_2) goto LAB_8012bcd8;
                iVar8 = *(int *)(iVar15 + 0x50);
                iVar14 = iVar8;
                if (iVar8 != 0) {
                  do {
                    iVar2 = iVar14;
                    if (*(int *)(iVar14 + 0x38) == param_2) goto LAB_8012bcb8;
                    iVar7 = *(int *)(iVar14 + 0x50);
                    iVar13 = iVar7;
                    if (iVar7 != 0) {
                      do {
                        iVar2 = iVar13;
                        if (*(int *)(iVar13 + 0x38) == param_2) goto LAB_8012bc98;
                        iVar6 = *(int *)(iVar13 + 0x50);
                        iVar12 = iVar6;
                        if (iVar6 != 0) {
                          do {
                            iVar2 = iVar12;
                            if (*(int *)(iVar12 + 0x38) == param_2) goto LAB_8012bc78;
                            iVar5 = *(int *)(iVar12 + 0x50);
                            iVar11 = iVar5;
                            if (iVar5 != 0) {
                              do {
                                iVar2 = iVar11;
                                if ((*(int *)(iVar11 + 0x38) == param_2) ||
                                   ((*(int *)(iVar11 + 0x50) != 0 &&
                                    (iVar2 = searchID__11CDbgMenuPcsFiRQ211CDbgMenuPcs3CDM
                                                       (param_1,param_2), iVar2 != 0))))
                                goto LAB_8012bc58;
                                piVar1 = (int *)(iVar11 + 0x48);
                                iVar11 = *piVar1;
                              } while (*piVar1 != iVar5);
                              iVar2 = 0;
LAB_8012bc58:
                              if (iVar2 != 0) goto LAB_8012bc78;
                            }
                            piVar1 = (int *)(iVar12 + 0x48);
                            iVar12 = *piVar1;
                          } while (*piVar1 != iVar6);
                          iVar2 = 0;
LAB_8012bc78:
                          if (iVar2 != 0) goto LAB_8012bc98;
                        }
                        piVar1 = (int *)(iVar13 + 0x48);
                        iVar13 = *piVar1;
                      } while (*piVar1 != iVar7);
                      iVar2 = 0;
LAB_8012bc98:
                      if (iVar2 != 0) goto LAB_8012bcb8;
                    }
                    piVar1 = (int *)(iVar14 + 0x48);
                    iVar14 = *piVar1;
                  } while (*piVar1 != iVar8);
                  iVar2 = 0;
LAB_8012bcb8:
                  if (iVar2 != 0) goto LAB_8012bcd8;
                }
                piVar1 = (int *)(iVar15 + 0x48);
                iVar15 = *piVar1;
              } while (*piVar1 != iVar9);
              iVar2 = 0;
LAB_8012bcd8:
              if (iVar2 != 0) goto LAB_8012bcf8;
            }
            piVar1 = (int *)(iVar16 + 0x48);
            iVar16 = *piVar1;
          } while (*piVar1 != iVar10);
          iVar2 = 0;
LAB_8012bcf8:
          if (iVar2 != 0) goto LAB_8012bd18;
        }
        piVar1 = (int *)(iVar17 + 0x48);
        iVar17 = *piVar1;
      } while (*piVar1 != iVar4);
      iVar2 = 0;
LAB_8012bd18:
      if (iVar2 != 0) {
        return iVar2;
      }
    }
    iVar3 = *(int *)(iVar3 + 0x48);
    if (iVar3 == param_3) {
      return 0;
    }
  } while( true );
}

