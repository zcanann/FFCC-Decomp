// Function: CCClassRot__8CGObjectFiiffff
// Entry: 8007d648
// Size: 232 bytes

/* WARNING: Removing unreachable block (ram,0x8007d70c) */
/* WARNING: Removing unreachable block (ram,0x8007d704) */
/* WARNING: Removing unreachable block (ram,0x8007d6fc) */
/* WARNING: Removing unreachable block (ram,0x8007d6f4) */
/* WARNING: Removing unreachable block (ram,0x8007d670) */
/* WARNING: Removing unreachable block (ram,0x8007d668) */
/* WARNING: Removing unreachable block (ram,0x8007d660) */
/* WARNING: Removing unreachable block (ram,0x8007d658) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CCClassRot__8CGObjectFiiffff
               (double param_1,undefined8 param_2,double param_3,undefined8 param_4,
               CGObject *gObject,undefined4 param_6,undefined4 param_7)

{
  double dVar1;
  float local_68;
  float local_64;
  float local_60;
  
  dVar1 = (double)sin(param_2);
  local_68 = (float)(param_3 * (double)(float)dVar1 + (double)(gObject->m_worldPosition).x);
  local_64 = (float)((double)(gObject->m_worldPosition).y + param_1);
  dVar1 = (double)cos(param_2);
  local_60 = (float)(param_3 * (double)(float)dVar1 + (double)(gObject->m_worldPosition).z);
  CCClass__8CGObjectFiifP3Vecf(param_1,param_4,gObject,param_6,param_7,&local_68);
  return;
}

