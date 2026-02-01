// Function: __sinit_cflat_runtime2_cpp
// Entry: 8006e864
// Size: 252 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void __sinit_cflat_runtime2_cpp(void)

{
  undefined4 uVar1;
  
  uVar1 = __ct__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
  __register_global_object(uVar1,__dt__13CFlatRuntime2Fv,ARRAY_80299f40);
  __construct_array(m_gBaseObjArr,__ct__9CGBaseObjFv,0,0x50,0x28);
  __construct_array(m_gObjQuadArr,__ct__9CGQuadObjFv,0,0xac,0x18);
  __construct_array(m_gObjArr,__ct__8CGObjectFv,0,0x518,0x38);
  __construct_array(m_objItem,__ct__9CGItemObjFv,0,0x57c,0x20);
  __construct_array(m_objParty,__ct__10CGPartyObjFv,0,0x6f8,4);
  __construct_array(&m_objParty[3].field_0x6e0,__ct__8CGMonObjFv,0,0x740,0x40);
  return;
}

