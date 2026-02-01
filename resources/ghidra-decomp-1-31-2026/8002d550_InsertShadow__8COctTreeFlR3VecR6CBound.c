// Function: InsertShadow__8COctTreeFlR3VecR6CBound
// Entry: 8002d550
// Size: 216 bytes

void InsertShadow__8COctTreeFlR3VecR6CBound
               (COctTree *octTree,undefined4 param_2,Vec *param_3,float *param_4)

{
  Vec VStack_58;
  Mtx MStack_4c;
  
  if (*(char *)&octTree->vtable == '\0') {
    DAT_8032eca4 = param_2;
    PSMTXInverse((Mtx *)((int)octTree->field2_0x8 + 0xb8),&MStack_4c);
    PSMTXMultVec(&MStack_4c,param_3,&VStack_58);
    s_bound[0].x = *param_4;
    s_bound[0].y = param_4[1];
    s_bound[0].z = param_4[2];
    s_bound[1].x = param_4[3];
    s_bound[1].y = param_4[4];
    s_bound[1].z = param_4[5];
    PSVECAdd(s_bound,&VStack_58,s_bound);
    PSVECAdd(s_bound + 1,&VStack_58,s_bound + 1);
    DAT_8032eca8 = 0;
    InsertShadow_r__FP8COctNode(octTree->rootNode);
  }
  return;
}

