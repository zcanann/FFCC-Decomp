// Function: main
// Entry: 80019f88
// Size: 204 bytes

void main(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (param_1 != 0) {
    iVar2 = param_1 + -1;
    puVar3 = (undefined4 *)(param_2 + 4);
    if (1 < param_1) {
      do {
        cVar1 = *(char *)*puVar3;
        if ((cVar1 == '-') || (cVar1 == '/')) {
          cVar1 = ((char *)*puVar3)[1];
          if (cVar1 == 'w') {
            Pad._440_4_ = 1;
          }
          else if ((cVar1 < 'w') && (cVar1 == 'r')) {
            Pad._436_4_ = 1;
          }
        }
        puVar3 = puVar3 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  Init__7CSystemFv(&System);
  game__FiPPc(param_1,param_2);
  Quit__7CSystemFv(&System);
  return;
}

