// Function: pppRenderMana2
// Entry: 80107e48
// Size: 92 bytes

void pppRenderMana2(void)

{
  Printf__8CGraphicFPce(&Graphic,s_Render_Mana2___801dc4d0);
  GXSetNumTevStages(1);
  GXSetNumTexGens(1);
  GXSetNumChans(1);
  SetViewport__8CGraphicFv(&Graphic);
  pppInitBlendMode__Fv();
  return;
}

