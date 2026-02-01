// Function: pppKeShpTail3XCon
// Entry: 80089230
// Size: 304 bytes

/* WARNING: Removing unreachable block (ram,0x80089338) */
/* WARNING: Removing unreachable block (ram,0x80089240) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppKeShpTail3XCon(pppKeShpTail3X *pppKeShpTail3X,UnkC *param_2)

{
  undefined2 uVar2;
  int iVar1;
  int iVar3;
  undefined *puVar4;
  undefined *puVar5;
  double dVar6;
  
  puVar4 = (undefined *)((int)(&pppKeShpTail3X->pppPObject + 2) + *param_2->m_serializedDataOffsets)
  ;
  puVar4[0x1c3] = 0;
  puVar4[0x1c2] = 0;
  *(undefined2 *)(puVar4 + 0x1bc) = 0;
  *(undefined4 *)(puVar4 + 0x1b8) = 0;
  uVar2 = rand();
  *(undefined2 *)(puVar4 + 0x1c0) = uVar2;
  memset(puVar4,0,8);
  memset(puVar4 + 8,0,8);
  memset(puVar4 + 0x10,0,8);
  memset(puVar4 + 0x18,0,8);
  memset(puVar4 + 0x20,0,8);
  memset(puVar4 + 0x28,0,8);
  dVar6 = (double)FLOAT_80330520;
  iVar3 = 0;
  puVar5 = puVar4;
  do {
    iVar1 = rand();
    iVar3 = iVar3 + 1;
    *(short *)(puVar5 + 0x180) =
         (short)iVar1 +
         ((short)((ulonglong)((longlong)iVar1 * 0xb60b60b7) >> 0x28) -
         (short)(iVar1 / 0x168 + (iVar1 >> 0x1f) >> 0x1f)) * -0x168;
    puVar5 = puVar5 + 2;
    *(float *)(puVar4 + 0x38) = (float)dVar6;
    *(float *)(puVar4 + 0x34) = (float)dVar6;
    *(float *)(puVar4 + 0x30) = (float)dVar6;
    puVar4 = puVar4 + 0xc;
  } while (iVar3 < 0x1c);
  return;
}

