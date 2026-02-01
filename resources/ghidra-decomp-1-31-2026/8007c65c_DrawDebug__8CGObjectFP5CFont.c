// Function: DrawDebug__8CGObjectFP5CFont
// Entry: 8007c65c
// Size: 136 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawDebug__8CGObjectFP5CFont(CGObject *gObject,CFont *font)

{
  float fVar1;
  float local_8 [2];
  
  if (((int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1a |
            (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 6)) < 0) &&
     (FLOAT_80330350 < gObject->m_screenDepth)) {
    fVar1 = FLOAT_80330338 / gObject->m_screenDepth;
    local_8[0] = -(FLOAT_80330374 * (gObject->m_projection).z * fVar1 - FLOAT_80330374);
    (**(code **)((int)(gObject->base_object).object.m_vtable + 0x40))
              ((double)(FLOAT_80330370 * (gObject->m_projection).y * fVar1 + FLOAT_80330370),
               (double)((gObject->m_projection).w * fVar1),gObject,font,local_8);
  }
  return;
}

