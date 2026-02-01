// Function: onScriptChanged__10CCameraPcsFPci
// Entry: 8003a0a0
// Size: 168 bytes

void onScriptChanged__10CCameraPcsFPci(CCameraPcs *cameraPcs,undefined4 param_2,int param_3)

{
  float fVar1;
  float fVar2;
  
  PSMTXCopy((Mtx *)&Math.field_0x4,(Mtx *)&cameraPcs->field_0x34);
  PSMTXInverse((Mtx *)&Math.field_0x4,(Mtx *)&cameraPcs->field_0x64);
  fVar2 = FLOAT_8032fa88;
  fVar1 = FLOAT_8032fa34;
  *(float *)&cameraPcs->field_0xdc = FLOAT_8032fa34;
  *(float *)&cameraPcs->field_0xd8 = fVar1;
  *(float *)&cameraPcs->field_0xd4 = fVar1;
  *(float *)&cameraPcs->field_0xe0 = fVar1;
  *(float *)&cameraPcs->field_0xe4 = fVar2;
  *(float *)&cameraPcs->field_0xe8 = fVar2;
  if (param_3 != 0) {
    *(undefined4 *)&cameraPcs->field_0x444 = 1;
  }
  memset(&cameraPcs->field_0x47c,0,0x14);
  *(float *)&cameraPcs->field_0x48c = FLOAT_8032fa1c;
  return;
}

