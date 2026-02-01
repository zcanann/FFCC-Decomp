// Function: pppRenderYmMana
// Entry: 800d6908
// Size: 68 bytes

void pppRenderYmMana(void)

{
  GXSetNumTevStages(1);
  GXSetNumTexGens(1);
  GXSetNumChans(1);
  SetViewport__8CGraphicFv(&Graphic);
  pppInitBlendMode__Fv();
  return;
}

