// Function: AddDebugDrawCC__13CFlatRuntime2FP3VecP3Vecfii
// Entry: 8006b688
// Size: 304 bytes

void AddDebugDrawCC__13CFlatRuntime2FP3VecP3Vecfii
               (double param_1,CFlatRuntime2 *flatRuntime2,undefined4 *param_3,undefined4 *param_4,
               char param_5,char param_6)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (*(uint *)&flatRuntime2->field_0xcd1c < 0x10) {
    puVar2 = (undefined4 *)
             (&flatRuntime2->field_0xcd24 + *(uint *)&flatRuntime2->field_0xcd1c * 0x20);
    *puVar2 = *param_3;
    puVar2[1] = param_3[1];
    puVar2[2] = param_3[2];
    puVar2 = (undefined4 *)
             (&flatRuntime2->field_0xcd30 + *(int *)&flatRuntime2->field_0xcd1c * 0x20);
    *puVar2 = *param_4;
    puVar2[1] = param_4[1];
    puVar2[2] = param_4[2];
    iVar1 = *(int *)&flatRuntime2->field_0xcd1c * 0x20;
    (&flatRuntime2->field_0xcd20)[iVar1] =
         (byte)((int)param_5 << 7) | (&flatRuntime2->field_0xcd20)[iVar1] & 0x7f;
    iVar1 = *(int *)&flatRuntime2->field_0xcd1c * 0x20;
    (&flatRuntime2->field_0xcd20)[iVar1] =
         (byte)((int)param_6 << 6) & 0x40 | (&flatRuntime2->field_0xcd20)[iVar1] & 0xbf;
    iVar1 = *(int *)&flatRuntime2->field_0xcd1c;
    *(int *)&flatRuntime2->field_0xcd1c = iVar1 + 1;
    *(float *)(&flatRuntime2->field_0xcd3c + iVar1 * 0x20) = (float)param_1;
  }
  else {
    if (DAT_8032ed9c == '\0') {
      DAT_8032ed98 = 0;
      DAT_8032ed9c = '\x01';
    }
    if (DAT_8032ed98 != System.m_frameCounter) {
      printf(&DAT_801d8fc4);
      DAT_8032ed98 = System.m_frameCounter;
    }
  }
  return;
}

