/*
 * --INFO--
 * PAL Address: 0x80012BB8
 * PAL Size: 1696b
 * EN Address: 0x80012B98
 * EN Size: 1696b
 * JP Address: 0x80012B58
 * JP Size: 1840b
 */
void CFile::DrawError(DVDFileInfo& info, int errorCode)
{
    _GXTexObj backupTexObj;
    if ((unsigned int)System.m_execParam >= 1)
    {
        System.Printf("CFile::drawError: %d\n", errorCode);
    }

    int usingFallbackFont = 0;
    CFont* font = MenuPcs.m_fonts[0];
    if (MenuPcs.m_fonts[0] == 0)
    {
        font = FontMan.m_font;
        usingFallbackFont = 1;
    }

    if (font == 0)
    {
        return;
    }

    Graphic._WaitDrawDone("file.cpp", FileErrorDrawBeginLine);

    int hasScratchTexture = (int)Graphic.m_scratchTextureBuffer;
    hasScratchTexture = hasScratchTexture != 0;
    int compactLayout = (bool)(hasScratchTexture && usingFallbackFont == 0);

    if (compactLayout)
    {
        Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backupTexObj, 0, 0, 0x280, 0x70, 0, GX_NEAR, GX_TF_RGBA8, 0);

        gUtil.RenderColorQuad(0.0f, 0.0f, 640.0f, 112.0f, CColor(0, 0, 0, 255).color);
        memcpy((void*)((char*)Graphic.m_scratchTextureBuffer + 0x46000), (void*)((char*)Graphic.m_frameBuffer + 0x34800), FileErrorCopySize);
        DCFlushRange((void*)((char*)Graphic.m_scratchTextureBuffer + 0x46000), FileErrorCopySize);
    }
    else
    {
        gUtil.RenderColorQuad(0.0f, 0.0f, 640.0f, 448.0f, CColor(0, 0, 0, 255).color);
    }

    font->SetScale(1.0f);
    font->SetShadow(1);
    font->SetMargin(1.0f);
    font->SetZMode(0, 0);
    font->SetColor(CColor(255, 255, 255, 255).color);
    font->SetTlut(usingFallbackFont ? -1 : 7);
    font->DrawInit();

    int baseY = 200;
    if (compactLayout)
    {
        baseY = 0x20;
    }

    switch (errorCode)
    {
    case 0x0B:
        font->SetPosX(32.0f);
        font->SetPosY((float)baseY);
        font->SetPosZ(0.0f);
        font->Draw("\x83\x66\x83\x42\x83\x58\x83\x4E\x82\xF0\x93\xC7\x82\xDF\x82\xDC\x82\xB9\x82\xF1\x82\xC5\x82\xB5\x82\xBD\x81\x42");
        font->SetPosX(32.0f);
        font->SetPosY((float)(baseY + 0x1C));
        font->SetPosZ(0.0f);
        font->Draw("\x82\xAD\x82\xED\x82\xB5\x82\xAD\x82\xCD\x81\x41\x96\x7B\x91\xCC\x82\xCC\x8E\xE6\x88\xB5\x90\xE0\x96\xBE\x8F\x91\x82\xF0\x82\xA8\x93\xC7\x82\xDD\x82\xAD\x82\xBE\x82\xB3\x82\xA2\x81\x42");
        break;
    case 5:
        font->SetPosX(32.0f);
        font->SetPosY((float)baseY);
        font->SetPosZ(0.0f);
        font->Draw("\x83\x66\x83\x42\x83\x58\x83\x4E\x83\x4A\x83\x6F\x81\x5B\x82\xAA\x8A\x4A\x82\xA2\x82\xC4\x82\xA2\x82\xDC\x82\xB7\x81\x42");
        font->SetPosX(32.0f);
        font->SetPosY((float)(baseY + 0x1C));
        font->SetPosZ(0.0f);
        font->Draw("\x83\x51\x81\x5B\x83\x80\x82\xF0\x91\xB1\x82\xAF\x82\xE9\x8F\xEA\x8D\x87\x82\xCD\x81\x41\x83\x66\x83\x42\x83\x58\x83\x4E\x83\x4A\x83\x6F\x81\x5B\x82\xF0\x95\xC2\x82\xDF\x82\xC4\x82\xAD\x82\xBE\x82\xB3\x82\xA2\x81\x42");
        break;
    case 4:
    case 6:
        font->SetPosX(32.0f);
        font->SetPosY((float)baseY);
        font->SetPosZ(0.0f);
        font->Draw("\x83\x74\x83\x40\x83\x43\x83\x69\x83\x8B\x83\x74\x83\x40\x83\x93\x83\x5E\x83\x57\x81\x5B\x81\x45\x83\x4E\x83\x8A\x83\x58\x83\x5E\x83\x8B\x83\x4E\x83\x8D\x83\x6A\x83\x4E\x83\x8B\x82\xCC\x83\x66\x83\x42\x83\x58\x83\x4E\x82\xF0");
        font->SetPosX(32.0f);
        font->SetPosY((float)(baseY + 0x1C));
        font->SetPosZ(0.0f);
        font->Draw("\x83\x5A\x83\x62\x83\x67\x82\xB5\x82\xC4\x82\xAD\x82\xBE\x82\xB3\x82\xA2\x81\x42");
        break;
    case -1:
        font->SetPosX(32.0f);
        font->SetPosY((float)(baseY - 14));
        font->SetPosZ(0.0f);
        font->Draw("\x83\x47\x83\x89\x81\x5B\x82\xAA\x94\xAD\x90\xB6\x82\xB5\x82\xDC\x82\xB5\x82\xBD\x81\x42");
        font->SetPosX(32.0f);
        font->SetPosY((float)(baseY + 14));
        font->SetPosZ(0.0f);
        font->Draw("\x96\x7B\x91\xCC\x82\xCC\x83\x70\x83\x8F\x81\x5B\x83\x7B\x83\x5E\x83\x93\x82\xF0\x89\x9F\x82\xB5\x82\xC4\x81\x41\x93\x64\x8C\xB9\x82\xF0\x82\x6E\x82\x65\x82\x65\x82\xC9\x82\xB5\x81\x41");
        font->SetPosX(32.0f);
        font->SetPosY((float)(baseY + 42));
        font->SetPosZ(0.0f);
        font->Draw("\x96\x7B\x91\xCC\x82\xCC\x8E\xE6\x88\xB5\x90\xE0\x96\xBE\x8F\x91\x82\xCC\x8E\x77\x8E\xA6\x82\xC9\x8F\x5D\x82\xC1\x82\xC4\x89\xBA\x82\xB3\x82\xA2\x81\x42");
        m_fatalDiskErrorFlag = 1;
        break;
    }

    font->DrawQuit();

    if (compactLayout)
    {
        GXSetDispCopySrc(0, 0, 0x280, 0x70);
        GXSetDispCopyDst(0x280, 0x70);
        GXCopyDisp((void*)((char*)Graphic.m_frameBuffer + 0x34800), GX_FALSE);
    }
    else
    {
        GXSetDispCopySrc(0, 0, 0x280, 0x1C0);
        GXSetDispCopyDst(0x280, 0x1C0);
        GXCopyDisp(Graphic.m_frameBuffer, GX_FALSE);
    }

    Graphic._WaitDrawDone("file.cpp", FileErrorCopyLine);
    Graphic.SetStdDispCopySrc();
    Graphic.SetStdDispCopyDst();
    Graphic._WaitDrawDone("file.cpp", FileErrorDisplayLine);
    VIWaitForRetrace();
    Sound.PauseDiscError(1);
    VISetBlack(FALSE);
    VIFlush();

    while (true)
    {
        int status = DVDGetCommandBlockStatus(&info.cb);
        if (status != errorCode)
        {
            break;
        }
        VIWaitForRetrace();
    }

    Sound.PauseDiscError(0);

    if (compactLayout)
    {
        gUtil.RenderTextureQuad(0.0f, 0.0f, 640.0f, 112.0f, &backupTexObj, 0, 0, 0, GX_BL_SRCALPHA,
                                       GX_BL_INVSRCALPHA);
        memcpy((void*)((char*)Graphic.m_frameBuffer + 0x34800), (void*)((char*)Graphic.m_scratchTextureBuffer + 0x46000), FileErrorCopySize);
        DCFlushRange((void*)((char*)Graphic.m_frameBuffer + 0x34800), FileErrorCopySize);
    }
    else
    {
        gUtil.RenderColorQuad(0.0f, 0.0f, 640.0f, 448.0f, CColor(0, 0, 0, 255).color);
        GXCopyDisp(Graphic.m_frameBuffer, GX_FALSE);
    }

    Graphic._WaitDrawDone("file.cpp", FileErrorDrawEndLine);
    m_fatalDiskErrorFlag = 0;
}
