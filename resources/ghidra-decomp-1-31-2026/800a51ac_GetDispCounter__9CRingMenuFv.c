// Function: GetDispCounter__9CRingMenuFv
// Entry: 800a51ac
// Size: 56 bytes

double GetDispCounter__9CRingMenuFv(CRingMenu *ringMenu)

{
  return -(double)((float)((double)CONCAT44(0x43300000,ringMenu->displayCounter ^ 0x80000000) -
                          DOUBLE_80330a00) * FLOAT_80330a08 - FLOAT_803309cc);
}

