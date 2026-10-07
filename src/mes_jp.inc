/*
 * --INFO--
 * PAL Address: 0x80099460
 * PAL Size: 6900b
 * EN Address: 0x80098C90
 * EN Size: 7076b
 * JP Address: 0x800981D4
 * JP Size: 3956b
 */
void CMes::addString(char** text, int branchMode)
{
    CFont* font = getFont(mFontIndex, 0);

    int running = 1;
    unsigned short uch;
    unsigned short ch;
    while (running)
    {
        if ((ch = (unsigned char)*(*text)++) == 0)
        {
            running = 0;
            goto updateBounds;
        }

        if (((ch >= 0x80) && (ch <= 0x9F)) ||
            ((ch >= 0xE0) && (ch <= 0xFF))) {
            uch = ch << 8;
            uch |= (unsigned char)*(*text)++;
            goto renderGlyph;
        }
        if (ch < 0xA0) {
            goto renderChar;
        }
        uch = ch - 0xA0;

        switch (uch)
        {
        case 0:
        advanceLine:
        {
            mCurrentX = 0.0f;
            float lineAdvance = (float)font->m_glyphHeight * font->scaleY;
            mCurrentY = mCurrentY + (8.0f + lineAdvance);
            if (mRubyEnabled != 0)
            {
                mRubyLine = mRubyLine + 1;
                mCurrentX = mCurrentX + (28.0f + mLineSpacing);
            }
            break;
        }
        case 1:
        {
            int wait = 2;
            if (mRubyEnabled != 0)
            {
                wait = 3;
            }
            mWaitFrames = wait;
            running = 0;
            mWaitActive = 1;
            goto advanceLine;
        }
        case 0x29:
            mWaitFrames = 5;
            running = 0;
            mWaitActive = 1;
            goto advanceLine;
        case 2:
            mWaitFrames = 4;
            running = 0;
            mWaitActive = 1;
            goto advanceLine;
        case 3:
            mRevealCursor = mRevealCursor + GET_1(text);
            break;
        case 4:
            mFontAlign = 0;
            break;
        case 5:
            mFontAlign = 2;
            break;
        case 6:
            mFontAlign = 1;
            break;
        case 7:
            mRubyEnabled = 1;
            mRubyLine = 0;
            mRubyHeight = GET_1(text);
            {
                float rubyAdvance = (float)font->m_glyphHeight * font->scaleY;
                mRubySpacing = 8.0f + rubyAdvance;
            }
            mRubyY = mCurrentY;
            mRubyOffset = GET_1(text);
            mCurrentX = mCurrentX + (28.0f + mLineSpacing);
            break;
        case 8:
        {
            char colorTag = GET_1(text);
            int oldColor = mColor;
            if (colorTag != 0)
            {
                mColor = 6;
            }
            char* flatText = (char*)Game.m_caravanWorkArr[mFlagVars[GET_1(text)] & 0xFFFF].m_name;
            addString(&flatText, branchMode);
            mColor = oldColor;
            break;
        }
        case 9:
        {
            char colorTag = GET_1(text);
            int oldColor = mColor;
            if (colorTag != 0) {
                mColor = 5;
            }
            int value = mFlagVars[GET_1(text)] & 0xFFFF;
            char* name = Game.GetItemName(value);
            addString(&name, branchMode);
            mColor = oldColor;
            break;
        }
        case 0x2A:
        {
            char colorTag = GET_1(text);
            int oldColor = mColor;
            if (colorTag != 0) {
                mColor = 0;
            }
            int value = mFlagVars[GET_1(text)] & 0xFFFF;
            char* name = Game.GetMonName(value);
            addString(&name, branchMode);
            mColor = oldColor;
            break;
        }
        case 0x2B:
        {
            char colorTag = GET_1(text);
            int oldColor = mColor;
            if (colorTag != 0) {
                mColor = 6;
            }
            int value = mFlagVars[GET_1(text)] & 0xFFFF;
            char* name = Game.GetNPCName(value);
            addString(&name, branchMode);
            mColor = oldColor;
            break;
        }
        case 0x2C:
        {
            char colorTag = GET_1(text);
            int oldColor = mColor;
            if (colorTag != 0) {
                mColor = 4;
            }
            int value = mFlagVars[GET_1(text)] & 0xFFFF;
            char* name = Game.GetPlaceName(value);
            addString(&name, branchMode);
            mColor = oldColor;
            break;
        }
        case 0x2D:
        {
            char colorTag = GET_1(text);
            int oldColor = mColor;
            if (colorTag != 0) {
                mColor = 3;
            }
            int value = mFlagVars[GET_1(text)] & 0xFFFF;
            char* name = Game.GetPlaceName(value + 0x3C);
            addString(&name, branchMode);
            mColor = oldColor;
            break;
        }
        case 0x2E:
        {
            char* flatText = Game.GetLetterSubject(mFlagVars[GET_1(text)] & 0xFFFF);
            addString(&flatText, branchMode);
            break;
        }
        case 0x2F:
        {
            char* townName = Game.m_gameWork.m_townName;
            addString(&townName, branchMode);
            break;
        }
        case 0x30:
        {
            char number[256];
            int value = mFlagVars[GET_1(text)];
            char* numberPtr = number;
            sprintf(number, "%d", value);
            addString(&numberPtr, branchMode);
            break;
        }
        case 0x0A:
        {
            unsigned char idx = GET_1(text);
            short value = (short)GET_2(text);
            mFlagVars[idx] = value;
            if (branchMode == 0)
            {
                CFlag flag;
                flag.m_param.m_index = idx;
                flag.m_param.m_value = value;
                flag.m_type = 2;
                addFlag(flag);
            }
            break;
        }
        case 0x0B:
        {
            unsigned char idx = GET_1(text);
            mFlagVars[idx]++;
            if (branchMode == 0)
            {
                CFlag flag;
                flag.m_param.m_index = idx;
                flag.m_type = 1;
                addFlag(flag);
            }
            break;
        }
        case 0x0C:
        case 0x0D:
        case 0x0E:
        case 0x0F:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
            mColor = (unsigned int)uch - 0x0C;
            break;
        case 0x24:
            running = 0;
            mWaitFrames = 2;
            goto advanceLine;
        case 0x28:
            running = 0;
            mWaitFrames = 1;
            goto advanceLine;
        case 0x26:
            mTextAlign = GET_1(text);
            break;
        case 0x27:
            mFadeFrames = GET_1(text);
            break;
        case 0x25:
        {
            int value = GET_1(text);
            if (mFontCount != 0)
            {
                if ((unsigned int)System.m_execParam >= 1U)
                {
                    System.Printf(const_cast<char*>(s_MessageSpeedTagUsed));
                }
            }
            else
            {
                mAdvanceStep = value;
            }
            break;
        }
        case 0x31:
            mCurrentX = (float)GET_2(text);
            mCurrentY = (float)GET_2(text);
            break;
        case 0x32:
            mColor = 9;
            break;
        case 0x33:
            mLineSpacing = (float)GET_1(text);
            break;
        case 0x34:
        {
            mFontIndex = GET_1(text);
            font = getFont(mFontIndex, 0);
            break;
        }
        case 0x35:
            mScaleX = (float)GET_2(text) / 100.0f;
            font->SetScale(mScaleX);
            break;
        case 0x36:
        {
            unsigned char idx = GET_1(text);
            if (branchMode == 0)
            {
                CFlag flag;
                flag.m_param.m_index = idx;
                flag.m_type = 4;
                addFlag(flag);
            }
            break;
        }

        }

        goto updateBounds;

    renderChar:
        uch = gUtil.AsciiToMulti(ch);
    renderGlyph:
        {
            CMesCharCell* glyph = &m_chars[mCounter];
            glyph->m_color = mColor;
            glyph->m_char = uch;
            glyph->m_x = mCurrentX;
            glyph->m_y = mCurrentY;
            font->renderFlags.snapPosition = 1;
            glyph->m_width = font->GetWidth(uch);
            font->renderFlags.snapPosition = 0;
            glyph->m_reveal = mRevealCursor;
            glyph->m_fadeFrames = mTextAlign;
            glyph->m_fadeCursor = 0;
            glyph->m_flagCount = mFlagCount;
            glyph->m_fontAlign = mFontAlign;
            glyph->m_fontIndex = mFontIndex;
            glyph->m_scale = mScaleX;
            mCurrentX = mCurrentX + (glyph->m_width + mLineSpacing);
            mRevealCursor = mRevealCursor + mAdvanceStep;
            mCounter = mCounter + 1;
        }

    updateBounds:
        mLineWidth = (mCurrentX < mLineWidth) ? mLineWidth : mCurrentX;
        mLineHeight = (mCurrentY < mLineHeight) ? mLineHeight : mCurrentY;
    }
}
