// Function: Chara_DrawShadowMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
// Entry: 800d7ef4
// Size: 216 bytes

void Chara_DrawShadowMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
               (int param_1,int param_2,int param_3,int param_4,int param_5)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = *(int *)(param_1 + 0xac);
  bVar1 = *(char *)(param_3 + 0x3b) == '\0';
  if (bVar1) {
    if (bVar1) {
      *(undefined *)(param_2 + 0xfc) = 0xff;
      *(undefined *)(param_2 + 0xfd) = 0xff;
      *(undefined *)(param_2 + 0xfe) = 0xff;
      *(undefined *)(param_2 + 0xff) = 0xff;
    }
  }
  else {
    *(undefined *)(param_2 + 0xfc) = 0xff;
    *(undefined *)(param_2 + 0xfd) = 0xff;
    *(undefined *)(param_2 + 0xfe) = 0xff;
    *(undefined *)(param_2 + 0xff) = *(undefined *)(param_3 + 0x3b);
  }
  DCFlushRange(param_2 + 0xfc,4);
  GXSetArray(0xb,param_2 + 0xfc,4);
  puVar3 = (undefined4 *)(*(int *)(*(int *)(iVar2 + param_4 * 0x14 + 8) + 0x50) + param_5 * 0xc);
  SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
            (&MaterialMan,*(CMaterialSet **)(*(int *)(param_1 + 0xa4) + 0x24),
             (uint)*(ushort *)(puVar3 + 2),0,0);
  GXCallDisplayList(puVar3[1],*puVar3);
  return;
}

