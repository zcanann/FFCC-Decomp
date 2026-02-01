// Function: CancelMove__8CGObjectFi
// Entry: 8007def8
// Size: 88 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CancelMove__8CGObjectFi(CGObject *gObject,undefined4 param_2)

{
  undefined4 local_8 [2];
  
  *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
       *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xdf;
  local_8[0] = param_2;
  SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
            (&CFlat,gObject,2,7,1,local_8,(CStack *)0x0);
  return;
}

