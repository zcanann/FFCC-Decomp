// Function: __ct__8COctNodeFv
// Entry: 8002f354
// Size: 48 bytes

void __ct__8COctNodeFv(COctNode *octNode)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8032f970;
  fVar1 = FLOAT_8032f96c;
  (octNode->boundsMin).z = FLOAT_8032f96c;
  (octNode->boundsMin).y = fVar1;
  (octNode->boundsMin).x = fVar1;
  (octNode->boundsMax).z = fVar2;
  (octNode->boundsMax).y = fVar2;
  (octNode->boundsMax).x = fVar2;
  octNode->ptrA = (void *)0x0;
  octNode->ptrB = (void *)0x0;
  return;
}

