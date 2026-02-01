// Function: C_MTXLookAt
// Entry: 80186080
// Size: 396 bytes

void C_MTXLookAt(Mtx *destination,Vec *cameraPosition,Vec *cameraUp,Vec *targetPosition)

{
  Vec local_38;
  Vec local_2c;
  Vec local_20;
  
  local_20.x = cameraPosition->x - targetPosition->x;
  local_20.y = cameraPosition->y - targetPosition->y;
  local_20.z = cameraPosition->z - targetPosition->z;
  PSVECNormalize(&local_20,&local_20);
  PSVECCrossProduct(cameraUp,&local_20,&local_2c);
  PSVECNormalize(&local_2c,&local_2c);
  PSVECCrossProduct(&local_20,&local_2c,&local_38);
  destination->value[0][0] = local_2c.x;
  destination->value[0][1] = local_2c.y;
  destination->value[0][2] = local_2c.z;
  destination->value[0][3] =
       -(cameraPosition->z * local_2c.z +
        cameraPosition->x * local_2c.x + cameraPosition->y * local_2c.y);
  destination->value[1][0] = local_38.x;
  destination->value[1][1] = local_38.y;
  destination->value[1][2] = local_38.z;
  destination->value[1][3] =
       -(cameraPosition->z * local_38.z +
        cameraPosition->x * local_38.x + cameraPosition->y * local_38.y);
  destination->value[2][0] = local_20.x;
  destination->value[2][1] = local_20.y;
  destination->value[2][2] = local_20.z;
  destination->value[2][3] =
       -(cameraPosition->z * local_20.z +
        cameraPosition->x * local_20.x + cameraPosition->y * local_20.y);
  return;
}

