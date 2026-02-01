// Function: damagedFuncGolem__8CGMonObjFv
// Entry: 801329b4
// Size: 52 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void damagedFuncGolem__8CGMonObjFv(CGMonObj *gMonObj)

{
  if (*(short *)((gMonObj->gObject).m_scriptHandle + 7) == 0) {
    DispCharaParts__8CGObjectFi(&gMonObj->gObject,7);
  }
  return;
}

