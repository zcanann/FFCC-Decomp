// Function: fopen
// Entry: 801b5b94
// Size: 592 bytes

uint32_t * fopen(uint32_t param_1,undefined4 param_2)

{
  ushort uVar1;
  uint32_t *puVar2;
  int iVar3;
  uint32_t uVar4;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [4];
  
  __begin_critical_region(2);
  puVar2 = (uint32_t *)__find_unopened_file();
  __stdio_atexit();
  if (puVar2 != (uint32_t *)0x0) {
    if ((puVar2 != (uint32_t *)0x0) && (uVar1 = *(ushort *)(puVar2 + 1) >> 6 & 7, uVar1 != 0)) {
      if (puVar2 == (uint32_t *)0x0) {
        __flush_all();
      }
      else if ((*(char *)((int)puVar2 + 10) == '\0') && (uVar1 != 0)) {
        if ((*(byte *)(puVar2 + 1) >> 3 & 7) != 1) {
          if (2 < *(byte *)(puVar2 + 2) >> 5) {
            *(byte *)(puVar2 + 2) = *(byte *)(puVar2 + 2) & 0x1f | 0x40;
          }
          if (*(byte *)(puVar2 + 2) >> 5 == 2) {
            puVar2[10] = 0;
          }
          if (*(byte *)(puVar2 + 2) >> 5 == 1) {
            if ((*(ushort *)(puVar2 + 1) >> 6 & 7) == 1) {
              uVar4 = ftell(puVar2);
            }
            else {
              uVar4 = 0;
            }
            iVar3 = __flush_buffer(puVar2,0);
            if (iVar3 == 0) {
              *(byte *)(puVar2 + 2) = *(byte *)(puVar2 + 2) & 0x1f;
              puVar2[6] = uVar4;
              puVar2[10] = 0;
            }
            else {
              *(undefined *)((int)puVar2 + 10) = 1;
              puVar2[10] = 0;
            }
          }
          else {
            *(byte *)(puVar2 + 2) = *(byte *)(puVar2 + 2) & 0x1f;
          }
        }
      }
      (*(code *)puVar2[0x11])(*puVar2);
      *(ushort *)(puVar2 + 1) = *(ushort *)(puVar2 + 1) & 0xfe3f;
      *puVar2 = 0;
      if ((*(byte *)(puVar2 + 2) >> 4 & 1) != 0) {
        free(puVar2[7]);
      }
    }
    clearerr(puVar2);
    iVar3 = __get_file_modes(param_2,&local_28);
    if (iVar3 == 0) {
      puVar2 = (uint32_t *)0x0;
    }
    else {
      local_24 = local_28;
      __init_file(puVar2,&local_24,0,0x400);
      local_20[0] = local_28;
      iVar3 = __open_file(param_1,local_20,puVar2);
      if (iVar3 == 0) {
        if ((local_28._0_1_ >> 3 & 4) != 0) {
          fseek(puVar2,0,2);
        }
      }
      else {
        *(ushort *)(puVar2 + 1) = *(ushort *)(puVar2 + 1) & 0xfe3f;
        if ((*(byte *)(puVar2 + 2) >> 4 & 1) != 0) {
          free(puVar2[7]);
        }
        puVar2 = (uint32_t *)0x0;
      }
    }
  }
  else {
    puVar2 = (uint32_t *)0x0;
  }
  __end_critical_region(2);
  return puVar2;
}

