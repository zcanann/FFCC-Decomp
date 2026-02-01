// Function: Draw__Q29CCharaPcs7CHandleFi
// Entry: 8007537c
// Size: 132 bytes

void Draw__Q29CCharaPcs7CHandleFi(CCharaPcsCHandle *handle,int param_2)

{
  if ((MiniGamePcs._25732_4_ & 0x8000) != 0) {
    if ((param_2 == 4) && ((handle->m_flags & 0x10000) != 0)) {
      draw__Q29CCharaPcs7CHandleFii(handle,3,0);
    }
    draw__Q29CCharaPcs7CHandleFii(handle,param_2,(4U - param_2 | param_2 - 4U) >> 0x1f);
  }
  return;
}

