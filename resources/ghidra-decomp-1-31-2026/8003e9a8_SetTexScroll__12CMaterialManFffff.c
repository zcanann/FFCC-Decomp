// Function: SetTexScroll__12CMaterialManFffff
// Entry: 8003e9a8
// Size: 380 bytes

/* WARNING: Removing unreachable block (ram,0x8003eb08) */
/* WARNING: Removing unreachable block (ram,0x8003eb00) */
/* WARNING: Removing unreachable block (ram,0x8003eaf8) */
/* WARNING: Removing unreachable block (ram,0x8003eaf0) */
/* WARNING: Removing unreachable block (ram,0x8003e9d0) */
/* WARNING: Removing unreachable block (ram,0x8003e9c8) */
/* WARNING: Removing unreachable block (ram,0x8003e9c0) */
/* WARNING: Removing unreachable block (ram,0x8003e9b8) */

void SetTexScroll__12CMaterialManFffff
               (double param_1,double param_2,double param_3,double param_4,
               CMaterialMan *materialMan)

{
  int iVar1;
  int iVar2;
  Mtx MStack_78;
  
  if (((*(uint *)&materialMan->field_0x120 & 0xff) < 0x3c) &&
     ((*(uint *)&materialMan->field_0x124 & 0xff) < 8)) {
    *(uint *)&materialMan->field_0x48 = *(uint *)&materialMan->field_0x48 | 0x20;
    PSMTXIdentity(&MStack_78);
    MStack_78.value[0][3] = (float)param_1;
    MStack_78.value[1][3] = (float)param_2;
    *(undefined4 *)&materialMan->field_0x144 = *(undefined4 *)&materialMan->field_0x120;
    *(undefined4 *)&materialMan->field_0x148 = *(undefined4 *)&materialMan->field_0x124;
    GXLoadTexMtxImm(&MStack_78,*(undefined4 *)&materialMan->field_0x120,1);
    iVar2 = *(int *)&materialMan->field_0x120;
    *(int *)&materialMan->field_0x120 = iVar2 + 3;
    iVar1 = *(int *)&materialMan->field_0x124;
    *(int *)&materialMan->field_0x124 = iVar1 + 1;
    GXSetTexCoordGen2(iVar1,1,4,iVar2,0,0x7d);
    if (((double)FLOAT_8032faf4 != param_3) || ((double)FLOAT_8032faf4 != param_4)) {
      *(uint *)&materialMan->field_0x48 = *(uint *)&materialMan->field_0x48 | 0x40;
      PSMTXIdentity(&MStack_78);
      MStack_78.value[0][3] = (float)param_3;
      MStack_78.value[1][3] = (float)param_4;
      *(undefined4 *)&materialMan->field_0x150 = *(undefined4 *)&materialMan->field_0x120;
      *(undefined4 *)&materialMan->field_0x154 = *(undefined4 *)&materialMan->field_0x124;
      GXLoadTexMtxImm(&MStack_78,*(undefined4 *)&materialMan->field_0x120,1);
      iVar2 = *(int *)&materialMan->field_0x120;
      *(int *)&materialMan->field_0x120 = iVar2 + 3;
      iVar1 = *(int *)&materialMan->field_0x124;
      *(int *)&materialMan->field_0x124 = iVar1 + 1;
      GXSetTexCoordGen2(iVar1,1,4,iVar2,0,0x7d);
    }
  }
  return;
}

