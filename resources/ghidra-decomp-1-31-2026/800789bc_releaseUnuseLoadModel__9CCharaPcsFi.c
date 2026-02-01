// Function: releaseUnuseLoadModel__9CCharaPcsFi
// Entry: 800789bc
// Size: 720 bytes

int releaseUnuseLoadModel__9CCharaPcsFi(CCharaPcs *charaPcs,uint param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar1 = GetSize__36CPtrArray<PQ29CCharaPcs10CLoadModel>Fv((CPtrArray *)&charaPcs->field_0x50);
  while (iVar1 = iVar1 + -1, -1 < iVar1) {
    piVar3 = (int *)__vc__36CPtrArray<PQ29CCharaPcs10CLoadModel>FUl(&charaPcs->field_0x50,iVar1);
    if ((((piVar3[4] < 0) || (piVar3[7] != 0)) && (piVar3[1] == 1)) ||
       ((-1 < piVar3[4] && ((param_2 & piVar3[5]) != 0)))) {
      if ((piVar3[7] == 0) || (piVar3[1] != 1)) {
        iVar4 = piVar3[1];
        piVar3[1] = iVar4 + -1;
        if ((iVar4 + -1 == 0) && (piVar3 != (int *)0x0)) {
          (**(code **)(*piVar3 + 8))(piVar3,1);
        }
        RemoveAt__36CPtrArray<PQ29CCharaPcs10CLoadModel>FUl
                  ((CPtrArray *)&charaPcs->field_0x50,iVar1);
      }
      else {
        piVar2 = (int *)piVar3[6];
        if (piVar2 != (int *)0x0) {
          iVar4 = piVar2[1];
          piVar2[1] = iVar4 + -1;
          if ((iVar4 + -1 == 0) && (piVar2 != (int *)0x0)) {
            (**(code **)(*piVar2 + 8))(piVar2,1);
          }
          piVar3[6] = 0;
        }
      }
    }
    else {
      iVar5 = iVar5 + 1;
    }
  }
  iVar1 = GetSize__38CPtrArray<PQ29CCharaPcs12CLoadTexture>Fv((CPtrArray *)&charaPcs->field_0x88);
  while (iVar1 = iVar1 + -1, -1 < iVar1) {
    piVar3 = (int *)__vc__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FUl(&charaPcs->field_0x88,iVar1);
    if ((((piVar3[4] < 0) || (piVar3[8] != 0)) && (piVar3[1] == 1)) ||
       ((-1 < piVar3[4] && ((param_2 & piVar3[5]) != 0)))) {
      if ((piVar3[8] == 0) || (piVar3[1] != 1)) {
        iVar4 = piVar3[1];
        piVar3[1] = iVar4 + -1;
        if ((iVar4 + -1 == 0) && (piVar3 != (int *)0x0)) {
          (**(code **)(*piVar3 + 8))(piVar3,1);
        }
        RemoveAt__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FUl
                  ((CPtrArray *)&charaPcs->field_0x88,iVar1);
      }
      else {
        piVar2 = (int *)piVar3[7];
        if (piVar2 != (int *)0x0) {
          iVar4 = piVar2[1];
          piVar2[1] = iVar4 + -1;
          if ((iVar4 + -1 == 0) && (piVar2 != (int *)0x0)) {
            (**(code **)(*piVar2 + 8))(piVar2,1);
          }
          piVar3[7] = 0;
        }
      }
    }
    else {
      iVar5 = iVar5 + 1;
    }
  }
  iVar1 = GetSize__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fv((CPtrArray *)&charaPcs->loadPdtArray);
  while (iVar1 = iVar1 + -1, -1 < iVar1) {
    piVar3 = (int *)__vc__33CPtrArray<PQ29CCharaPcs8CLoadPdt>FUl(&charaPcs->loadPdtArray,iVar1);
    if (((piVar3[6] < 0) && (piVar3[1] == 1)) || ((-1 < piVar3[6] && ((param_2 & piVar3[7]) != 0))))
    {
      iVar4 = piVar3[1];
      piVar3[1] = iVar4 + -1;
      if ((iVar4 + -1 == 0) && (piVar3 != (int *)0x0)) {
        (**(code **)(*piVar3 + 8))(piVar3,1);
      }
      RemoveAt__33CPtrArray<PQ29CCharaPcs8CLoadPdt>FUl((CPtrArray *)&charaPcs->loadPdtArray,iVar1);
    }
    else {
      iVar5 = iVar5 + 1;
    }
  }
  return iVar5;
}

