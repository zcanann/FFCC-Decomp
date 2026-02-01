// Function: CloseRequest__8CMesMenuFi
// Entry: 8009b4f0
// Size: 268 bytes

void CloseRequest__8CMesMenuFi(int param_1,undefined4 param_2)

{
  undefined4 local_18;
  undefined4 local_14;
  
  *(undefined4 *)(param_1 + 0x3da4) = param_2;
  if (*(int *)(param_1 + 0xc) < 2) {
    if ((*(uint *)(param_1 + 0x3d8c) & 0x40) == 0) {
      *(undefined4 *)(param_1 + 0xc) = 2;
      *(undefined4 *)(param_1 + 0x10) = 0;
      *(undefined4 *)(param_1 + 0x14) = 4;
      if (((*(uint *)(param_1 + 0x3d8c) & 1) == 0) && ((*(uint *)(param_1 + 0x3d8c) & 0x4000) == 0))
      {
        PlaySe__6CSoundFiiii(&Sound,6,0x40,0x7f,0);
      }
    }
    else {
      Set__4CMesFPci(param_1 + 0x1c,0,0);
      local_18 = *(undefined4 *)(param_1 + 0x18);
      local_14 = *(undefined4 *)(param_1 + 0x3da4);
      SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                (&CFlat,0,1,3,2,&local_18,(CStack *)0x0);
      *(undefined4 *)(param_1 + 0xc) = 4;
      *(undefined4 *)(param_1 + 8) = 0;
      if (*(int *)(param_1 + 0x18) < 4) {
        SetFade__9CRingMenuFi
                  (*(undefined4 *)(&MenuPcs.field_0x13c + *(int *)(param_1 + 0x18) * 4),1);
      }
    }
  }
  return;
}

