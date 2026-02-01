// Function: SetShow_r__7CMapObjFi
// Entry: 8002a008
// Size: 592 bytes

void SetShow_r__7CMapObjFi(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  do {
    if (param_2 == 0) {
      *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    }
    else {
      *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) | 1;
    }
    for (iVar8 = *(int *)(param_1 + 4); iVar8 != 0; iVar8 = *(int *)(iVar8 + 8)) {
      if (param_2 == 0) {
        *(byte *)(iVar8 + 0x18) = *(byte *)(iVar8 + 0x18) & 0xfe;
      }
      else {
        *(byte *)(iVar8 + 0x18) = *(byte *)(iVar8 + 0x18) | 1;
      }
      for (iVar7 = *(int *)(iVar8 + 4); iVar7 != 0; iVar7 = *(int *)(iVar7 + 8)) {
        if (param_2 == 0) {
          *(byte *)(iVar7 + 0x18) = *(byte *)(iVar7 + 0x18) & 0xfe;
        }
        else {
          *(byte *)(iVar7 + 0x18) = *(byte *)(iVar7 + 0x18) | 1;
        }
        for (iVar6 = *(int *)(iVar7 + 4); iVar6 != 0; iVar6 = *(int *)(iVar6 + 8)) {
          if (param_2 == 0) {
            *(byte *)(iVar6 + 0x18) = *(byte *)(iVar6 + 0x18) & 0xfe;
          }
          else {
            *(byte *)(iVar6 + 0x18) = *(byte *)(iVar6 + 0x18) | 1;
          }
          for (iVar5 = *(int *)(iVar6 + 4); iVar5 != 0; iVar5 = *(int *)(iVar5 + 8)) {
            if (param_2 == 0) {
              *(byte *)(iVar5 + 0x18) = *(byte *)(iVar5 + 0x18) & 0xfe;
            }
            else {
              *(byte *)(iVar5 + 0x18) = *(byte *)(iVar5 + 0x18) | 1;
            }
            for (iVar4 = *(int *)(iVar5 + 4); iVar4 != 0; iVar4 = *(int *)(iVar4 + 8)) {
              if (param_2 == 0) {
                *(byte *)(iVar4 + 0x18) = *(byte *)(iVar4 + 0x18) & 0xfe;
              }
              else {
                *(byte *)(iVar4 + 0x18) = *(byte *)(iVar4 + 0x18) | 1;
              }
              for (iVar3 = *(int *)(iVar4 + 4); iVar3 != 0; iVar3 = *(int *)(iVar3 + 8)) {
                if (param_2 == 0) {
                  *(byte *)(iVar3 + 0x18) = *(byte *)(iVar3 + 0x18) & 0xfe;
                }
                else {
                  *(byte *)(iVar3 + 0x18) = *(byte *)(iVar3 + 0x18) | 1;
                }
                for (iVar2 = *(int *)(iVar3 + 4); iVar2 != 0; iVar2 = *(int *)(iVar2 + 8)) {
                  if (param_2 == 0) {
                    *(byte *)(iVar2 + 0x18) = *(byte *)(iVar2 + 0x18) & 0xfe;
                  }
                  else {
                    *(byte *)(iVar2 + 0x18) = *(byte *)(iVar2 + 0x18) | 1;
                  }
                  for (iVar1 = *(int *)(iVar2 + 4); iVar1 != 0; iVar1 = *(int *)(iVar1 + 8)) {
                    if (param_2 == 0) {
                      *(byte *)(iVar1 + 0x18) = *(byte *)(iVar1 + 0x18) & 0xfe;
                    }
                    else {
                      *(byte *)(iVar1 + 0x18) = *(byte *)(iVar1 + 0x18) | 1;
                    }
                    if (*(int *)(iVar1 + 4) != 0) {
                      SetShow_r__7CMapObjFi(*(int *)(iVar1 + 4),param_2);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    param_1 = *(int *)(param_1 + 8);
  } while (param_1 != 0);
  return;
}

