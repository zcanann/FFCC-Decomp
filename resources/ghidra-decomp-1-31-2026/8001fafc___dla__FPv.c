// Function: __dla__FPv
// Entry: 8001fafc
// Size: 284 bytes

void __dla__FPv(void *ptr)

{
  int iVar1;
  
  if (ptr != (void *)0x0) {
    if ((*(short *)((int)ptr + -0x40) != 0x4b41) || (*(short *)((int)ptr + -2) != 0x4d49)) {
      Printf__7CSystemFPce
                (&System,&DAT_801d6648,ptr,(int)ptr + -0x26,*(undefined2 *)((int)ptr + -0x28));
    }
    *(byte *)((int)ptr + -0x3e) = *(byte *)((int)ptr + -0x3e) & 0xfb;
    if ((*(byte *)(*(int *)((int)ptr + -0x38) + 2) & 4) == 0) {
      *(int *)((int)ptr + -0x30) =
           *(int *)(*(int *)((int)ptr + -0x38) + 0x10) + *(int *)((int)ptr + -0x30) + 0x40;
      *(int *)(*(int *)(*(int *)((int)ptr + -0x38) + 8) + 4) = (int)ptr + -0x40;
      *(undefined4 *)((int)ptr + -0x38) = *(undefined4 *)(*(int *)((int)ptr + -0x38) + 8);
    }
    iVar1 = *(int *)((int)ptr + -0x3c);
    if ((*(byte *)(iVar1 + 2) & 4) == 0) {
      *(int *)(iVar1 + 0x10) = *(int *)((int)ptr + -0x30) + *(int *)(iVar1 + 0x10) + 0x40;
      *(undefined4 *)(*(int *)((int)ptr + -0x3c) + 8) = *(undefined4 *)((int)ptr + -0x38);
      *(undefined4 *)(*(int *)((int)ptr + -0x38) + 4) = *(undefined4 *)((int)ptr + -0x3c);
    }
    *(int *)(*(int *)((int)ptr + -0x34) + 0x124) = *(int *)(*(int *)((int)ptr + -0x34) + 0x124) + -1
    ;
    return;
  }
  return;
}

