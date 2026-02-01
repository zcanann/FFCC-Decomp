// Function: pppConstruct2ConstrainCameraDir
// Entry: 80143298
// Size: 36 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstruct2ConstrainCameraDir(pppConstrainCameraDir *pppConstrainCameraDir,UnkC *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = DAT_803320c4;
  puVar2 = (undefined4 *)
           ((int)(&pppConstrainCameraDir->field0_0x0 + 2) + *param_2->m_serializedDataOffsets);
  puVar2[2] = DAT_803320c4;
  puVar2[1] = uVar1;
  *puVar2 = uVar1;
  return;
}

