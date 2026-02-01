// Function: CCClass__8CGObjectFiifP3Vecf
// Entry: 8007d730
// Size: 636 bytes

/* WARNING: Removing unreachable block (ram,0x8007d990) */
/* WARNING: Removing unreachable block (ram,0x8007d988) */
/* WARNING: Removing unreachable block (ram,0x8007d980) */
/* WARNING: Removing unreachable block (ram,0x8007d978) */
/* WARNING: Removing unreachable block (ram,0x8007d970) */
/* WARNING: Removing unreachable block (ram,0x8007d968) */
/* WARNING: Removing unreachable block (ram,0x8007d768) */
/* WARNING: Removing unreachable block (ram,0x8007d760) */
/* WARNING: Removing unreachable block (ram,0x8007d758) */
/* WARNING: Removing unreachable block (ram,0x8007d750) */
/* WARNING: Removing unreachable block (ram,0x8007d748) */
/* WARNING: Removing unreachable block (ram,0x8007d740) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CGObject *
CCClass__8CGObjectFiifP3Vecf
          (double param_1,undefined8 param_2,CGObject *gObject,int param_4,uint param_5,Vec *param_6
          )

{
  CGObject *pCVar1;
  CGObject *gObject_00;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  Vec VStack_a8;
  Vec VStack_9c;
  Vec VStack_90;
  Vec local_84;
  
  local_84.x = (gObject->m_worldPosition).x;
  local_84.y = (float)((double)(gObject->m_worldPosition).y + param_1);
  local_84.z = (gObject->m_worldPosition).z;
  PSVECSubtract(param_6,&local_84,&VStack_90);
  dVar2 = (double)PSVECMag(&VStack_90);
  if ((double)FLOAT_80330350 == dVar2) {
    pCVar1 = (CGObject *)0x0;
  }
  else {
    PSVECNormalize(&VStack_90,&VStack_9c);
    dVar3 = (double)atan2(param_2,dVar2);
    dVar7 = (double)(float)dVar3;
    dVar3 = (double)FLOAT_80330394;
    pCVar1 = (CGObject *)0x0;
    for (gObject_00 = (CGObject *)FindGObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
        gObject_00 != (CGObject *)0x0;
        gObject_00 = (CGObject *)
                     FindGObjNext__13CFlatRuntime2FP8CGObject((CFlatRuntime2 *)&CFlat,gObject_00)) {
      if ((gObject != gObject_00) && ((gObject_00->m_attrFlags & param_5) != 0)) {
        dVar4 = (double)(gObject_00->m_worldPosition).x;
        dVar5 = (double)(gObject_00->m_worldPosition).y;
        dVar6 = (double)(gObject_00->m_worldPosition).z;
        if (((float)(dVar4 - dVar2) <= local_84.x) &&
           (((((float)(dVar5 - dVar2) <= local_84.y && ((float)(dVar6 - dVar2) <= local_84.z)) &&
             (local_84.x <= (float)(dVar4 + dVar2))) &&
            ((local_84.y <= (float)(dVar5 + dVar2) && (local_84.z <= (float)(dVar6 + dVar2))))))) {
          PSVECSubtract(&gObject_00->m_worldPosition,&local_84,&VStack_a8);
          dVar4 = (double)PSVECMag(&VStack_a8);
          dVar5 = (double)FLOAT_80330350;
          if ((dVar5 < dVar4) && (dVar4 < dVar2)) {
            if (param_4 != 0) {
              dVar5 = (double)atan((double)(float)((double)(float)((double)(float)((double)
                                                  gObject_00->m_bodyEllipsoidRadius * dVar4) / dVar2
                                                  ) / dVar4));
              dVar5 = (double)(float)dVar5;
            }
            PSVECScale((float)((double)FLOAT_80330338 / dVar4),&VStack_a8,&VStack_a8);
            PSVECDotProduct(&VStack_a8,&VStack_9c);
            dVar6 = (double)acos();
            if (((float)dVar6 < (float)(dVar7 + dVar5)) && (dVar4 < dVar3)) {
              pCVar1 = gObject_00;
              dVar3 = dVar4;
            }
          }
        }
      }
    }
    AddDebugDrawCC__13CFlatRuntime2FP3VecP3Vecfii
              (param_2,(CFlatRuntime2 *)&CFlat,&local_84,&VStack_90,0,0);
  }
  return pCVar1;
}

