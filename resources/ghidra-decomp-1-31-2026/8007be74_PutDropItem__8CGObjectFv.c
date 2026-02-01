// Function: PutDropItem__8CGObjectFv
// Entry: 8007be74
// Size: 192 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void PutDropItem__8CGObjectFv(CGObject *gObject)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  CGObject *pCVar5;
  
  uVar4 = 0;
  iVar3 = 0;
  pCVar5 = gObject;
  do {
    uVar1 = (uint)(short)pCVar5->m_dropItemCodes[0];
    if (0 < (short)pCVar5->m_dropItemCodes[0]) {
      if ((uVar1 & 0xc000) == 0x4000) {
        uVar1 = uVar1 & 0xffff3fff;
        uVar2 = 2;
      }
      else {
        uVar2 = 0;
      }
      CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS
                ((double)(FLOAT_80330344 *
                         (float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - DOUBLE_80330348))
                 ,uVar2,4,uVar1,gObject,0);
      uVar4 = uVar4 + 1;
    }
    iVar3 = iVar3 + 1;
    pCVar5 = (CGObject *)((int)&(pCVar5->base_object).object.m_id + 2);
  } while (iVar3 < 4);
  return;
}

