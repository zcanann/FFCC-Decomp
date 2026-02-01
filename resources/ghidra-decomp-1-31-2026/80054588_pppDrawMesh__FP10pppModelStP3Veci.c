// Function: pppDrawMesh__FP10pppModelStP3Veci
// Entry: 80054588
// Size: 236 bytes

void pppDrawMesh__FP10pppModelStP3Veci(pppModelSt *pppModelSt,Vec *param_2,int param_3)

{
  MaterialMan._296_4_ = MaterialMan._284_4_;
  MaterialMan._300_4_ = MaterialMan._288_4_;
  MaterialMan._304_4_ = MaterialMan._292_4_;
  MaterialMan._64_4_ = MaterialMan._72_4_;
  if (param_2 == (Vec *)0x0) {
    GXSetArray(9,(pppModelSt->m_mapMesh).field14_0x2c,0xc);
  }
  else {
    GXSetArray(9,param_2,0xc);
  }
  GXSetArray(0xb,(pppModelSt->m_mapMesh).field18_0x3c,4);
  GXSetArray(0xd,(pppModelSt->m_mapMesh).field17_0x38,4);
  GXSetArray(0xe,(pppModelSt->m_mapMesh).field17_0x38,4);
  MaterialMan._4_4_ = (pppModelSt->m_mapMesh).field15_0x30;
  if (param_3 == 0) {
    GXSetArray(10,MaterialMan._4_4_,6);
  }
  DrawPart__8CMapMeshFP12CMaterialSeti(&pppModelSt->m_mapMesh,pppEnvStPtr->m_materialSetPtr,param_3)
  ;
  return;
}

