// Function: onPush__9CGBaseObjFP9CGBaseObji
// Entry: 8010b1a8
// Size: 76 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onPush__9CGBaseObjFP9CGBaseObji(CGBaseObj *gBaseObj,CGBaseObj *other,undefined4 param_3)

{
  int local_8;
  undefined4 local_4;
  
  local_8 = (int)(other->object).m_particleId;
  local_4 = param_3;
  SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
            (&CFlat,gBaseObj,2,4,2,&local_8,(CStack *)0x0);
  return;
}

