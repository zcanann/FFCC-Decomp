// Function: Duplicate__Q26CChara6CModelFPQ27CMemory6CStage
// Entry: 80072530
// Size: 1016 bytes

CRef * Duplicate__Q26CChara6CModelFPQ27CMemory6CStage(CModel *model,CStage *stage)

{
  float fVar1;
  float fVar2;
  CRef *ref;
  undefined4 uVar3;
  void *pvVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint8_t *puVar8;
  uint32_t uVar9;
  undefined4 *puVar10;
  
  ref = (CRef *)__nw__FUlPQ27CMemory6CStagePci(0x124,stage,s_chara_cpp_801d90c8,0x25a);
  if (ref != (CRef *)0x0) {
    __ct__4CRefFv(ref);
    ref->vtable = &PTR_PTR_s_CChara_CModel_801fccf4;
    __ct__7CVectorFv(&ref[0x18].refCount);
    ref[0x14].refCount = 0;
    ref[0x16].vtable = (void *)0x0;
    ref[0x1a].vtable = (void *)0x0;
    ref[0x1a].refCount = 0;
    ref[0x15].vtable = (void *)0x0;
    ref[0x15].refCount = 0;
    PSMTXIdentity((Mtx *)(ref + 1));
    fVar2 = FLOAT_803301fc;
    ref[0x22].vtable = (void *)FLOAT_803301e4;
    fVar1 = FLOAT_803301b0;
    ref[0x22].refCount = (int)fVar2;
    fVar2 = FLOAT_803301bc;
    ref[0x16].refCount = (int)fVar1;
    ref[0x17].vtable = (void *)fVar1;
    ref[0x18].refCount = (int)fVar1;
    ref[0x19].vtable = (void *)fVar1;
    ref[0x19].refCount = (int)fVar1;
    *(undefined2 *)&ref[0x1b].vtable = 0;
    *(undefined2 *)((int)&ref[0x1b].vtable + 2) = 0;
    ref[0x13].vtable = (void *)0xffffffff;
    ref[0x17].refCount = (int)fVar1;
    ref[0x18].vtable = (void *)fVar1;
    ref[0x1c].vtable = (void *)fVar1;
    ref[0x1b].refCount = (int)fVar1;
    ref[0x13].refCount = (int)fVar2;
    ref[0x1c].refCount = 0;
    ref[0x1d].vtable = (void *)0x0;
    ref[0x1e].vtable = (void *)0x0;
    ref[0x1d].refCount = 0;
    ref[0x1e].refCount = 0;
    ref[0x1f].vtable = (void *)0x0;
    ref[0x1f].refCount = 0;
    ref[0x20].vtable = (void *)0x0;
    ref[0x20].refCount = 0;
    ref[0x21].vtable = (void *)0x0;
    *(byte *)&ref[0x21].refCount = *(byte *)&ref[0x21].refCount & 0x7f | 0x80;
    *(byte *)&ref[0x14].vtable = *(byte *)&ref[0x14].vtable & 0x7f;
    *(byte *)&ref[0x14].vtable = *(byte *)&ref[0x14].vtable & 0xbf;
    *(byte *)&ref[0x14].vtable = *(byte *)&ref[0x14].vtable & 0xdf | 0x20;
    *(byte *)&ref[0x21].refCount = *(byte *)&ref[0x21].refCount & 0xbf;
    ref[0x23].vtable = (void *)fVar2;
    ref[0x23].refCount = (int)fVar2;
    *(undefined *)((int)&ref[0x14].vtable + 1) = 0;
    ref[0x24].vtable = (void *)fVar1;
  }
  ref[0x14].refCount = (int)model->m_data;
  (model->m_data->ref).refCount = (model->m_data->ref).refCount + 1;
  uVar9 = model->m_data->m_nodeCount;
  uVar3 = __nwa__FUlPQ27CMemory6CStagePci(uVar9 * 0xc0 + 0x10,stage,s_chara_cpp_801d90c8,0x263);
  pvVar4 = (void *)__construct_new_array
                             (uVar3,__ct__Q26CChara5CNodeFv,__dt__Q26CChara5CNodeFv,0xc0,uVar9);
  ref[0x15].vtable = pvVar4;
  iVar7 = 0;
  for (uVar6 = 0; uVar6 < model->m_data->m_nodeCount; uVar6 = uVar6 + 1) {
    puVar8 = model->m_nodes->unk_0x8_0x43 + iVar7 + -8;
    puVar10 = (undefined4 *)((int)ref[0x15].vtable + iVar7);
    *puVar10 = *(undefined4 *)puVar8;
    PSMTXCopy((Mtx *)(puVar8 + 0x14),(Mtx *)(puVar10 + 5));
    PSMTXCopy((Mtx *)(puVar8 + 0x6c),(Mtx *)(puVar10 + 0x1b));
    iVar7 = iVar7 + 0xc0;
    puVar10[0x11] = *(float *)(puVar8 + 0x44);
    puVar10[0x12] = *(float *)(puVar8 + 0x48);
    puVar10[0x13] = ((Vec *)(puVar8 + 0x4c))->x;
    puVar10[0x14] = *(float *)(puVar8 + 0x50);
    puVar10[0x15] = *(float *)(puVar8 + 0x54);
    puVar10[0x16] = ((Vec *)(puVar8 + 0x58))->x;
    puVar10[0x17] = *(float *)(puVar8 + 0x5c);
    puVar10[0x18] = *(float *)(puVar8 + 0x60);
    puVar10[0x19] = ((Mtx *)(puVar8 + 100))->value[0][0];
    puVar10[0x1a] = *(float *)(puVar8 + 0x68);
    *(byte *)(puVar10 + 0x2f) =
         (byte)(((int)((uint)puVar8[0xbc] << 0x18) >> 0x1f) << 7) | *(byte *)(puVar10 + 0x2f) & 0x7f
    ;
  }
  uVar9 = model->m_data->m_meshCount;
  uVar3 = __nwa__FUlPQ27CMemory6CStagePci(uVar9 * 0x14 + 0x10,stage,s_chara_cpp_801d90c8,0x26c);
  iVar7 = __construct_new_array(uVar3,__ct__Q26CChara5CMeshFv,__dt__Q26CChara5CMeshFv,0x14,uVar9);
  iVar5 = 0;
  ref[0x15].refCount = iVar7;
  for (uVar6 = 0; uVar6 < model->m_data->m_meshCount; uVar6 = uVar6 + 1) {
    puVar10 = (undefined4 *)((int)&model->m_meshes->m_data + iVar5);
    iVar7 = ref[0x15].refCount + iVar5;
    iVar5 = iVar5 + 0x14;
    *(undefined4 *)(iVar7 + 8) = *puVar10;
    *(undefined4 *)(iVar7 + 0xc) = 0;
    *(undefined4 *)(iVar7 + 0x10) = 0;
  }
  if (model->m_texSet != (CTextureSet *)0x0) {
    ref[0x16].vtable = model->m_texSet;
    *(int *)((int)ref[0x16].vtable + 4) = *(int *)((int)ref[0x16].vtable + 4) + 1;
  }
  if (model->m_texAnimSet != (CTexAnimSet *)0x0) {
    iVar7 = Duplicate__11CTexAnimSetFPQ27CMemory6CStage(model->m_texAnimSet,stage);
    ref[0x1a].refCount = iVar7;
  }
  fVar2 = FLOAT_803301bc;
  fVar1 = FLOAT_803301b0;
  ref[0x16].refCount = (int)FLOAT_803301b0;
  ref[0x17].vtable = (void *)fVar1;
  ref[0x18].refCount = (int)fVar1;
  ref[0x19].vtable = (void *)fVar1;
  ref[0x19].refCount = (int)fVar1;
  *(undefined2 *)&ref[0x1b].vtable = 0;
  *(undefined2 *)((int)&ref[0x1b].vtable + 2) = 0;
  ref[0x13].vtable = (void *)0xffffffff;
  ref[0x17].refCount = (int)fVar1;
  ref[0x18].vtable = (void *)fVar1;
  ref[0x1c].vtable = (void *)fVar1;
  ref[0x1b].refCount = (int)fVar1;
  ref[0x13].refCount = (int)fVar2;
  ref[0x1c].refCount = 0;
  ref[0x1d].vtable = (void *)0x0;
  ref[0x1e].vtable = (void *)0x0;
  ref[0x1d].refCount = 0;
  ref[0x1e].refCount = 0;
  ref[0x1f].vtable = (void *)0x0;
  ref[0x1f].refCount = 0;
  ref[0x20].vtable = (void *)0x0;
  ref[0x20].refCount = 0;
  ref[0x21].vtable = (void *)0x0;
  *(byte *)&ref[0x21].refCount = *(byte *)&ref[0x21].refCount & 0x7f | 0x80;
  *(byte *)&ref[0x14].vtable = *(byte *)&ref[0x14].vtable & 0x7f;
  *(byte *)&ref[0x14].vtable = *(byte *)&ref[0x14].vtable & 0xbf;
  *(byte *)&ref[0x14].vtable = *(byte *)&ref[0x14].vtable & 0xdf | 0x20;
  *(byte *)&ref[0x21].refCount = *(byte *)&ref[0x21].refCount & 0xbf;
  ref[0x23].vtable = (void *)fVar2;
  ref[0x23].refCount = (int)fVar2;
  *(undefined *)((int)&ref[0x14].vtable + 1) = 0;
  ref[0x24].vtable = (void *)fVar1;
  setup__Q26CChara6CModelFv(ref);
  return ref;
}

