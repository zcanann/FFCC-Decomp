// Function: CalcSphereNearPos__8CGObjectFffR3Vec
// Entry: 8007c278
// Size: 260 bytes

/* WARNING: Removing unreachable block (ram,0x8007c35c) */
/* WARNING: Removing unreachable block (ram,0x8007c354) */
/* WARNING: Removing unreachable block (ram,0x8007c290) */
/* WARNING: Removing unreachable block (ram,0x8007c288) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcSphereNearPos__8CGObjectFffR3Vec(double scale,double param_2,CGObject *gObject,Vec *vec)

{
  Vec VStack_98;
  Vec local_8c;
  Vec VStack_80;
  Vec VStack_74;
  Vec VStack_68;
  Mtx MStack_5c;
  
  local_8c.x = DAT_801d9b94;
  local_8c.y = DAT_801d9b98;
  local_8c.z = DAT_801d9b9c;
  PSVECNormalize(&gObject->m_worldPosition,&VStack_80);
  PSVECCrossProduct(&VStack_80,&local_8c,&VStack_68);
  PSVECNormalize(&VStack_68,&VStack_68);
  PSVECCrossProduct(&VStack_80,&VStack_68,&VStack_74);
  PSVECNormalize(&VStack_74,&VStack_74);
  PSMTXRotAxisRad((float)((double)gObject->m_rotBaseY + param_2),&MStack_5c,&VStack_80);
  PSMTXMultVec(&MStack_5c,&VStack_74,&VStack_74);
  PSVECScale((float)scale,&VStack_74,&VStack_98);
  PSVECAdd(&gObject->m_worldPosition,&VStack_98,vec);
  return;
}

