// Function: addtev_stdShadow__12CMaterialManFUl
// Entry: 80042454
// Size: 124 bytes

void addtev_stdShadow__12CMaterialManFUl(int param_1,uint param_2)

{
  int iVar1;
  
  if ((param_2 & 0x10) != 0) {
    for (iVar1 = 0; iVar1 < *(int *)(param_1 + 0x58); iVar1 = iVar1 + 1) {
      if (*(char *)(param_1 + iVar1 + 0x4d) == '\0') {
        addtev_shadow__12CMaterialManFl(param_1,iVar1);
      }
      else {
        addtev_lightmap__12CMaterialManFl(param_1,iVar1);
      }
    }
  }
  return;
}

