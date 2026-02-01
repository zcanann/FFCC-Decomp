// Function: SetTexShadowPos__9CCharaPcsFP3Vec
// Entry: 800b9228
// Size: 28 bytes

void SetTexShadowPos__9CCharaPcsFP3Vec(CCharaPcs *charaPcs,Vec *vec)

{
  *(float *)&charaPcs->field_0x17c = vec->x;
  *(float *)&charaPcs->field_0x180 = vec->y;
  *(float *)&charaPcs->field_0x184 = vec->z;
  return;
}

