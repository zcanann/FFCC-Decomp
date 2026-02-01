// Function: SetDrawFlag__8COctTreeFv
// Entry: 8002e1c0
// Size: 188 bytes

void SetDrawFlag__8COctTreeFv(COctTree *octTree)

{
  Mtx MStack_38;
  
  if ((((uint)octTree->field52_0x48 & 1) == 0) &&
     (*(char *)((int)octTree->field2_0x8 + 0x1d) == '\x01')) {
    PSMTXConcat((Mtx *)&MapMng.field_0x22928,(Mtx *)((int)octTree->field2_0x8 + 0xb8),
                (Mtx *)&octTree->field_0xc);
    PSMTXConcat((Mtx *)&MapMng.field_0x228f8,(Mtx *)((int)octTree->field2_0x8 + 0xb8),&MStack_38);
    PSMTXInverse(&MStack_38,&MStack_38);
    (octTree->field51_0x3c).x = MStack_38.value[0][3];
    (octTree->field51_0x3c).y = MStack_38.value[1][3];
    (octTree->field51_0x3c).z = MStack_38.value[2][3];
    ClearFlag__8COctTreeFUl(octTree,1);
    DrawTypeMesh_r__8COctTreeFP8COctNode(octTree,octTree->rootNode);
  }
  return;
}

