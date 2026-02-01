// Function: IgnoreParticle__13CFlatRuntime2FiPQ212CFlatRuntime7CObject
// Entry: 8006a08c
// Size: 92 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void IgnoreParticle__13CFlatRuntime2FiPQ212CFlatRuntime7CObject
               (CFlatRuntime2 *flatRuntime2,undefined2 param_2,CObject *object)

{
  byte bVar1;
  int16_t iVar2;
  int iVar3;
  
  iVar3 = pppGetIfDt__8CPartMngFs(&PartMng,param_2);
  bVar1 = *(byte *)(iVar3 + 6);
  if (bVar1 < 0x10) {
    iVar2 = object->m_particleId;
    *(byte *)(iVar3 + 6) = bVar1 + 1;
    *(int16_t *)(iVar3 + (uint)bVar1 * 2 + 8) = iVar2;
  }
  return;
}

