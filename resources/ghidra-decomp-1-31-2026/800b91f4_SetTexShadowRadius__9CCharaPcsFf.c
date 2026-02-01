// Function: SetTexShadowRadius__9CCharaPcsFf
// Entry: 800b91f4
// Size: 8 bytes

void SetTexShadowRadius__9CCharaPcsFf(float texShadowRadius,CCharaPcs *charaPcs)

{
  *(float *)&charaPcs->field_0x188 = texShadowRadius;
  return;
}

