// Function: InsertLight__8COctTreeFlR3VecfUl
// Entry: 8002dbd8
// Size: 208 bytes

/* WARNING: Removing unreachable block (ram,0x8002dc88) */
/* WARNING: Removing unreachable block (ram,0x8002dbe8) */

void InsertLight__8COctTreeFlR3VecfUl
               (double param_1,COctTree *octTree,undefined4 param_3,Vec *param_4,uint param_5)

{
  Vec local_58;
  Mtx MStack_4c;
  
  if ((*(char *)&octTree->vtable == '\0') &&
     ((*(uint *)((int)octTree->field2_0x8 + 0x38) & param_5) != 0)) {
    DAT_8032eca0 = param_3;
    PSMTXInverse((Mtx *)((int)octTree->field2_0x8 + 0xb8),&MStack_4c);
    PSMTXMultVec(&MStack_4c,param_4,&local_58);
    s_bound[0].x = (float)((double)local_58.x - param_1);
    s_bound[1].x = (float)((double)local_58.x + param_1);
    s_bound[0].y = (float)((double)local_58.y - param_1);
    s_bound[0].z = (float)((double)local_58.z - param_1);
    s_bound[1].y = (float)((double)local_58.y + param_1);
    s_bound[1].z = (float)((double)local_58.z + param_1);
    InsertLight_r__FP8COctNode(octTree->rootNode);
  }
  return;
}

