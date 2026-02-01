// Function: DeleteOld__9CGItemObjFiiPQ212CFlatRuntime7CObjectPQ212CFlatRuntime7CObject
// Entry: 80125eac
// Size: 260 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int DeleteOld__9CGItemObjFiiPQ212CFlatRuntime7CObjectPQ212CFlatRuntime7CObject
              (uint param_1,int param_2)

{
  CObject *gItemObj;
  void *pvVar1;
  CObject *object;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (param_2 <= iVar2) {
      return iVar2;
    }
    pvVar1 = (void *)0x989680;
    object = (CObject *)0x0;
    for (gItemObj = (CObject *)FindGItemObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
        gItemObj != (CObject *)0x0;
        gItemObj = (CObject *)
                   FindGItemObjNext__13CFlatRuntime2FP9CGItemObj
                             ((CFlatRuntime2 *)&CFlat,(CGItemObj *)gItemObj)) {
      if ((((gItemObj[0x11].m_0x44 == 0) &&
           ((int)((uint)*(byte *)&gItemObj[1].m_freeListNode << 0x1c |
                 (uint)(*(byte *)&gItemObj[1].m_freeListNode >> 4)) < 0)) &&
          (((int)*(char *)((int)&gItemObj[1].m_freeListNode + 3) & param_1) != 0)) &&
         ((int)gItemObj[1].m_vtable < (int)pvVar1)) {
        pvVar1 = gItemObj[1].m_vtable;
        object = gItemObj;
      }
    }
    if (object == (CObject *)0x0) break;
    deleteObject__12CFlatRuntimeFPQ212CFlatRuntime7CObject((CFlatRuntime *)&CFlat,object);
    iVar2 = iVar2 + 1;
  }
  if ((uint)System.m_execParam < 3) {
    return iVar2;
  }
  Printf__7CSystemFPce(&System,&DAT_801dced4);
  return iVar2;
}

