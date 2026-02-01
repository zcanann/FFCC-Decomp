// Function: CalcSkin__Q26CChara6CModelFv
// Entry: 800722f4
// Size: 176 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcSkin__Q26CChara6CModelFv(CModel *model)

{
  uint32_t uVar1;
  uint32_t uVar2;
  CMesh *mesh;
  uint uVar3;
  
  uVar2 = model->m_data->m_posQuant;
  uVar1 = model->m_data->m_normQuant;
  gqrInit__6CCharaFUlUlUl
            (&Chara,uVar2 << 0x18 | 0x70000 | uVar2 << 8 | 7,
             uVar1 << 0x18 | 0x70000 | uVar1 << 8 | 7,0xc070c07);
  mesh = model->m_meshes;
  for (uVar3 = 0; uVar3 < model->m_data->m_meshCount; uVar3 = uVar3 + 1) {
    Calc__Q26CChara5CMeshFPQ26CChara6CModel(mesh,model);
    mesh = mesh + 1;
  }
  return;
}

