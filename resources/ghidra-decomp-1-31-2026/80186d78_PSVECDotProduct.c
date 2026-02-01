// Function: PSVECDotProduct
// Entry: 80186d78
// Size: 32 bytes

/* WARNING: Removing unreachable block (ram,0x80186d88) */
/* WARNING: Removing unreachable block (ram,0x80186d84) */
/* WARNING: Removing unreachable block (ram,0x80186d7c) */
/* WARNING: Removing unreachable block (ram,0x80186d78) */

double PSVECDotProduct(Vec *inVecA,Vec *inVecB)

{
  return (double)inVecA->x * (double)inVecB->x + (double)inVecA->y * (double)inVecB->y +
         (double)inVecA->z * (double)inVecB->z;
}

