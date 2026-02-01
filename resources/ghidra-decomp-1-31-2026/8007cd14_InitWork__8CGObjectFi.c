// Function: InitWork__8CGObjectFi
// Entry: 8007cd14
// Size: 160 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void InitWork__8CGObjectFi(CGObject *gObject,int param_2)

{
  char cVar1;
  
  cVar1 = gObject->m_ownerType;
  if (cVar1 == '\x01') {
    (**(code **)((int)*gObject->m_scriptHandle + 0xc))
              (gObject->m_scriptHandle,param_2,Game.game.unkCFlatData0[1] + param_2 * 0x1d0,0);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    (**(code **)((int)*gObject->m_scriptHandle + 0xc))
              (gObject->m_scriptHandle,param_2,Game.game.unkCFlatData0[0] + param_2 * 0x1d0,0);
  }
  return;
}

