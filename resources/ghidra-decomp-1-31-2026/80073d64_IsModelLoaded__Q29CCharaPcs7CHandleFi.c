// Function: IsModelLoaded__Q29CCharaPcs7CHandleFi
// Entry: 80073d64
// Size: 68 bytes

undefined4 IsModelLoaded__Q29CCharaPcs7CHandleFi(CCharaPcsCHandle *handle,int param_2)

{
  if ((((handle->m_asyncState == 0) || (handle->m_asyncState == 7)) &&
      (handle->m_model != (CModel *)0x0)) &&
     ((param_2 == 0 || (handle->m_model->m_texSet != (CTextureSet *)0x0)))) {
    return 1;
  }
  return 0;
}

