#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "session.h"
#include "radar.h"
#include "window.h"
#include "screen.h"

/* Pixel y of a row of the window, rows counted from its top edge */
static inline s32 Window_RowToY(struct Window *win, s32 row)
{
    return (win->y + row) * 8;
}

/* Text tile base of a window in slot 2 or 3 */
static inline s32 Window_SlotTextTile(struct Window *win)
{
    return win->slot == 2 ? 0x238 : 0x29C;
}

void Window_PrintNextItem(struct Window *win)
{
    s32 i;

    for (i = 0; i < win->rows; i++) {
        if (win->items[i].drawn == 0)
            break;
    }
    if (i < win->rows) {
        Text_Clear();
        Text_SetX(win->textX);
        Text_Print(win->items[i].text, TEXT_DRAW);
        Text_CopyToVram(Window_GetTextVram(win, i, 0), win->width);
        win->items[i].drawn = 1;
    }
}

void Window_PutText(struct Window *win, s32 row, s32 unused)
{
    Text_CopyToVram(Window_GetTextVram(win, row, 0), win->width);
}

s32 Window_GetItemPalette(s32 a, s32 b)
{
    s32 pal;

    if (a) {
        pal = 5;
        if (!b)
            pal = 3;
    } else {
        pal = 6;
        if (!b)
            pal = 4;
    }
    return pal << 12;
}

s32 Window_GetTextTile(s32 type)
{
    s32 tile;

    tile = 0x80;
    if (type != 0) {
        tile = 0x15C;
        if (type != 1) {
            tile = 0x29C;
            if (type == 2)
                tile = 0x238;
        }
    }
    return tile;
}

s32 Window_GetFrameTile(s32 type)
{
    s32 tile;

    tile = 0;
    if (type != 0) {
        tile = 32;
        if (type != 1) {
            tile = 64;
            if (type != 2) {
                tile = 0x300;
                if (type == 3)
                    tile = 96;
            }
        }
    }
    return tile;
}

void Window_Open(struct Window *win)
{
    s32 tile;
    s32 pal;

    if (win->slot == 0) {
        tile = 0;
        pal = 10;
    } else if (win->slot == 1) {
        tile = 32;
        pal = 11;
    } else if (win->slot == 2) {
        tile = 64;
        pal = 12;
    } else if (win->slot == 3) {
        tile = 96;
        pal = 13;
    } else {
        tile = 0x300;
        pal = 14;
    }
    tile += 4;
    pal <<= 12;

    switch (win->style) {
    case -1:
        Window_OpenStyleNone(win, tile, pal);
        break;
    case 0:
        if (win->variant)
            Window_OpenStyle0Horz(win, tile, pal);
        else
            Window_OpenStyle0(win, tile, pal, win->style);
        break;
    case 1:
    case 2:
    case 13:
        Window_OpenStyle1(win, tile, pal);
        break;
    case 3:
        Window_OpenStyle3(win, tile, pal);
        break;
    case 4:
        Window_OpenStyle4(win, tile, pal);
        break;
    case 5:
        Window_OpenStyle5(win, tile, pal);
        break;
    case 6:
        Window_OpenStyle6(win, tile, pal);
        break;
    case 7:
        Window_OpenStyle7(win, tile, pal);
        break;
    case 8:
        Window_OpenStyle8(win, tile, pal);
        break;
    case 9:
        Window_OpenStyle9(win, tile, pal);
        break;
    case 10:
        Window_OpenStyle0(win, tile, pal, win->style);
        break;
    case 14:
        Window_OpenStyle14(win, tile, pal);
        break;
    }
}

/*
 * --INFO--
 * PAL Address: 0x02005B84
 * PAL Size: 1216b
 * EN Address: 0x02005B54
 * EN Size: 1152b
 * JP Address: 0x02005D08
 * JP Size: 1152b
 */
void Window_OpenStyle0(struct Window *win, s32 tile, s32 pal, s32 type)
{
    u16 buf[30];
    s32 mod;
    s32 x;
    s32 py;
    s32 i;
    s32 y;
    s32 n;
    s32 t;
    s32 row;
    s32 k;
#if defined(VERSION_GCCP01)
    s32 edge;
#endif
    s32 attr;
    s32 flags;
    u16 *map;

    x = win->x * 8;
    y = win->y * 8 + win->anim;
    py = y + 8;

    if (win->anim == 0) {
        for (i = 0; i < win->width; i++) {
            if (i == 0 || i == win->width - 1)
                buf[i] = pal | tile;
            else if (i == 1 || i == win->width - 2)
                buf[i] = (tile + 1) | pal;
            else if (i == 2 || i == win->width - 3)
                buf[i] = (tile + 2) | pal;
            else
                buf[i] = (tile + 3) | pal;
            if (i >= win->width >> 1)
                buf[i] |= 0x400;
        }
        map = (u16 *)Bg_GetMapPtr(win->bg, win->x, win->y);
        DmaCopy16(0, buf, map, win->width << 1);
        attr = Window_GetItemPalette(win->items[0].enabled, win->slot);
        for (i = 0; i < win->width; i++) {
            if (i & 1)
                buf[i] = (tile - 4) | attr;
            else
                buf[i] = (tile - 2) | attr;
        }
        t = tile + 4;
        buf[0] = pal | t;
        buf[win->width - 1] = t | 0x400 | pal;
        map = (u16 *)Bg_GetMapPtr(win->bg, win->x, win->y + 1);
        DmaCopy16(0, buf, map, win->width << 1);
    } else {
        n = win->anim >> 3;
        mod = 0;
        t = 0;
        if (n == 0)
            goto sprites;
        k = Window_GetTextTile(win->slot);
        py = y;
        if (win->tallRows == 0) {
            t = !(n & 1);
            row = (n - 1) >> 1;
            k += row * 2 * win->width;
            k += t;
        } else {
            n--;
            mod = n % 3;
            if (mod <= 1) {
                t = mod & 1;
                row = n / 3;
                k += win->width * 2 * row;
                k += t;
            } else {
                k = tile - 4;
#if !defined(VERSION_GCCP01)
                row = 0;
#else
                row = n / 3;
#endif
            }
        }
        attr = Window_GetItemPalette(win->items[row].enabled, win->slot);
        for (i = 1; i < win->width - 1; i++) {
            if (i & 1) {
                buf[i] = attr | k;
            } else {
                buf[i] = (k + 2) | attr;
                if (mod <= 1)
                    k += 4;
            }
        }

#if !defined(VERSION_GCCP01)
        if ((row == 0 && !t) || (row == win->rows - 1 && t)) {
#else
        edge = 0;
        if (win->tallRows) {
            t = 0;
            if (mod > 1)
                t = 1;
            if ((row == 0 && mod == 0) || (row == win->rows - 1 && t))
                edge = 1;
        }
        if ((win->tallRows && edge) || (!win->tallRows && ((row == 0 && !t) || (row == win->rows - 1 && t)))) {
#endif
            buf[0] = (tile + 4) | pal;
            buf[win->width - 1] = (tile + 4) | pal;
            buf[win->width - 1] |= 0x400;
            if (row == win->rows - 1 && t) {
                buf[0] |= 0x800;
                buf[win->width - 1] |= 0x800;
            }
        } else {
            buf[0] = (tile + 5) | pal;
            buf[win->width - 1] = (tile + 5) | pal;
            buf[win->width - 1] |= 0x400;
        }
        map = (u16 *)Bg_GetMapPtr(win->bg, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
        py += 8;
        row = Window_RowToY(win, win->height) - 8;
        if (py < row)
            goto sprites;
        for (i = 0; i < win->width; i++) {
            if (i == 0 || i == win->width - 1)
                buf[i] = pal | tile;
            else if (i == 1 || i == win->width - 2)
                buf[i] = (tile + 1) | pal;
            else if (i == 2 || i == win->width - 3)
                buf[i] = (tile + 2) | pal;
            else
                buf[i] = (tile + 3) | pal;
            if (i >= win->width >> 1)
                buf[i] |= 0x400;
            buf[i] |= 0x800;
        }
        map = (u16 *)Bg_GetMapPtr(win->bg, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
    }

sprites:
    if ((py >> 3) - win->y < win->height) {
        flags = 0x20000000;
        for (i = 0; i < win->width; i++, x += 8) {
            if (i == 0 || i == win->width - 1)
                t = 0;
            else if (i == 1 || i == win->width - 2)
                t = 1;
            else if (i == 2 || i == win->width - 3)
                t = 2;
            else
                t = 3;
            if (i >= win->width >> 1)
                flags |= 0x10000000;
            k = 13;
            if (!type)
                k = 3;
            Obj_Draw(x, py, k, t, win->variant, win->bg, flags);
        }
    }
}

void Window_OpenStyle0Horz(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[2];
    s32 pal2;
    s32 w;
    s32 x;
    s32 y;
    u16 *map;
    s32 col;
    s32 n;
    s32 i;
    s32 k;
    s32 t;
    s32 frame;
    s32 flags;

    x = (win->x + (win->width >> 1)) * 8 - 8;
    x -= win->anim;
    y = win->y * 8;
    pal2 = Window_GetItemPalette(1, win->slot);
    w = ((win->anim + 8) >> 2) - 1;
    col = x >> 3;
    map = (u16 *)Bg_GetMapPtr(win->bg, col, win->y);
    n = win->width - 2;
    col -= win->x;
    if (col < 0)
        return;

    for (i = 0; i < win->height; i++) {
        if (col == 0 || i == 0 || i + 1 >= win->height) {
            if (col == 0) {
                if (i == 0 || i + 1 >= win->height)
                    buf[0] = (tile + 6) | pal;
                else if (i == 1 || i + 2 >= win->height)
                    buf[0] = (tile + 9) | pal;
                else if (i == 2 || i + 3 >= win->height)
                    buf[0] = (tile + 10) | pal;
                else
                    buf[0] = (tile + 11) | pal;
            } else if (col == 1) {
                buf[0] = (tile + 7) | pal;
            } else {
                buf[0] = (tile + 8) | pal;
            }
            if (i >= win->height >> 1)
                buf[0] |= 0x800;
            buf[1] = buf[0] | 0x400;
        } else {
            k = i - 1;
            if (k % 3 <= 1) {
                if (k % 3 == 0)
                    t = k / 3 * (n * 2 + n) + 128;
                else
                    t = k / 3 * (n * 2 + n) + 129;
                t += (col - 1) * 2;
            } else {
                t = k / 3 * (n * 2 + n) + 128 + n * 2 + (col - 1);
            }
            buf[0] = pal2 | t;
            if (k % 3 <= 1)
                t += w * 2;
            else
                t += w;
            buf[1] = t | pal2;
        }
        map[0] = buf[0];
        map[w] = buf[1];
        map += 32;
    }

    if (col == 0)
        return;
    x -= 8;
    w = (w + 2) * 8;
    flags = 0;
    for (i = 0; i < win->height; i++, y += 8) {
        if (i == 0 || i + 1 >= win->height)
            frame = 6;
        else if (i == 1 || i + 2 >= win->height)
            frame = 9;
        else if (i == 2 || i + 3 >= win->height)
            frame = 10;
        else
            frame = 11;
        if (i >= win->height >> 1)
            flags = 0x20000000;
        Obj_Draw(x, y, 3, frame, 0, win->bg, flags);
        Obj_Draw(x + w, y, 3, frame, 0, win->bg, flags | 0x10000000);
    }
}

void Window_OpenStyle1(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 x;
    s32 py;
    s32 y;
    s32 row;
    s32 mod;
    s32 t;
    s32 base;
    s32 pal2;
    s32 i;
    s32 n;
    u16 *map;

    x = win->x * 8;
    y = win->y * 8 + win->anim;
    py = y + 8;
    if (py >> 3 > win->y + win->height)
        return;

    if (win->anim == 0) {
        for (i = 0; i < win->width; i++) {
            if (i == 0)
                buf[0] = pal | tile;
            else if (i != win->width - 1) {
                if (i & 1)
                    buf[i] = pal | (tile + 1);
                else
                    buf[i] = pal | (tile + 2);
            } else
                buf[i] = pal | (tile + 3);
        }
        map = (u16 *)Bg_GetMapPtr(win->bg, win->x, win->y);
        DmaCopy16(0, buf, map, win->width << 1);
        pal2 = Window_GetItemPalette(win->items[0].enabled, win->slot);
        for (i = 0; i < win->width; i++) {
            if (i & 1)
                buf[i] = (tile - 4) | pal2;
            else
                buf[i] = (tile - 2) | pal2;
        }
        buf[0] = pal | (tile + 4);
        buf[win->width - 1] = pal | (tile + 5);
        map = (u16 *)Bg_GetMapPtr(win->bg, win->x, win->y + 1);
        DmaCopy16(0, buf, map, win->width << 1);
    } else {
        row = win->anim >> 3;
        row -= win->skipRows;
        if (row == 0)
            goto sprites;
        base = Window_GetTextTile(win->slot);
        py = y;
        if (win->tallRows == 0) {
            t = !(row & 1);
            mod = t;
            n = (row - 1) >> 1;
            base += win->width * 2 * n;
            base += t;
        } else {
            mod = (row - 1) % 3;
            if (mod <= 1) {
                t = mod & 1;
                n = (row - 1) / 3;
                base += win->width * 2 * n;
                base += t;
            } else {
                base = tile - 4;
                n = 0;
            }
        }
        pal2 = Window_GetItemPalette(win->items[n].enabled, win->slot);
        for (i = 1; i < win->width - 1; i++) {
            if (i & 1) {
                buf[i] = pal2 | base;
            } else {
                buf[i] = (base + 2) | pal2;
                if (mod <= 1)
                    base += 4;
            }
        }
        if (row & 1) {
            buf[0] = (tile + 4) | pal;
            buf[win->width - 1] = (tile + 5) | pal;
        } else {
            buf[0] = (tile + 6) | pal;
            buf[win->width - 1] = (tile + 7) | pal;
        }
        map = (u16 *)Bg_GetMapPtr(win->bg, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
        py += 8;
        n = Window_RowToY(win, win->height) - 8;
        if (py < n)
            goto sprites;
        for (i = 0; i < win->width; i++) {
            if (i == 0)
                buf[0] = (tile + 8) | pal;
            else if (i != win->width - 1) {
                if (i & 1)
                    buf[i] = (tile + 9) | pal;
                else
                    buf[i] = (tile + 10) | pal;
            } else
                buf[i] = (tile + 11) | pal;
        }
        map = (u16 *)Bg_GetMapPtr(win->bg, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
    }

sprites:
    if ((py >> 3) - win->y < win->height) {
        if (win->style == 1)
            n = 4;
        else if (win->style == 2)
            n = 5;
        else
            n = 16;
        for (i = 0; i < win->width; i++, x += 8) {
            if (i == 0)
                t = 8;
            else if (i != win->width - 1)
                t = 10;
            else
                t = 11;
            Obj_Draw(x, py, n, t, win->variant, win->bg, 0);
        }
    }
}

void Window_OpenStyle3(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    s32 t;
    s32 k;
    s32 n;
    s32 odd;
    s32 attr;
    u16 *map;

    px = win->x * 8;
    py = win->y * 8 + win->anim + 8;
    if ((py >> 3) > win->y + win->height)
        return;
    if (win->anim == 0 && win->keepFrame == 0) {
        for (i = 0; i < win->width; i++) {
            if (i == 0)
                t = tile;
            else if (i + 1 >= win->width)
                t = tile + 2;
            else
                t = tile + 1;
            buf[i] = t | pal;
        }
        map = Bg_GetMapPtr(win->bg, win->x, win->y);
        DmaCopy16(0, buf, map, win->width << 1);
    }
    if (gMode == MODE_FIELD) {
        if (win->anim != 0)
            goto draw_animated_rows;
        goto draw_sprites;
    }
    if (win->anim == 0)
        goto draw_text_rows;

draw_animated_rows:
    if (win->keepFrame == 0) {
        for (i = 0; i < win->width; i++) {
            if (i == 0)
                t = tile + 3;
            else if (i + 1 >= win->width)
                t = tile + 5;
            else
                t = tile + 4;
            if ((py >> 3) >= win->y + win->height)
                t += 3;
            buf[i] = t | pal;
        }
        map = Bg_GetMapPtr(win->bg, win->x, (py - 8) >> 3);
        DmaCopy16(0, buf, map, win->width << 1);
    }

draw_text_rows:
    k = win->anim >> 3;
    k -= win->skipRows;
    if ((gMode == MODE_FIELD ? k > 0 : k >= 0) && k <= win->rows * 2) {
        t = Window_GetTextTile(win->slot);
        if (gMode) {
            odd = k & 1;
            n = k >> 1;
        } else {
            odd = !(k & 1);
            n = (k - 1) >> 1;
        }
        t += win->width * 2 * n;
        t += odd;
        attr = win->items[n].enabled ? 7 : 8;
        attr <<= 12;
        for (i = 1; i < win->width - 1; i++) {
            if (i & 1) {
                buf[i] = attr | t;
            } else {
                buf[i] = (t + 2) | attr;
                t += 4;
            }
        }
        buf[0] = 0x3FF;
        buf[win->width - 1] = 0x3FF;
        map = Bg_GetMapPtr(win->bg - 1, win->x, (py - 8) >> 3);
        DmaCopy16(0, buf, map, win->width << 1);
    }

draw_sprites:
    if ((py >> 3) < win->y + win->height && win->keepFrame == 0) {
        for (i = 0; i < win->width; i++, px += 8) {
            if (i == 0)
                t = 6;
            else if (i + 1 >= win->width)
                t = 8;
            else
                t = 7;
            Obj_Draw(px, py, 6, t, win->variant, win->bg - 1, 0);
        }
    }
}

void Window_OpenStyle4(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    s32 t;
    s32 n;
    s32 odd;
    s32 grp;
    s32 attr;
    u16 *map;

    px = win->x * 8;
    py = win->y * 8 + win->anim + 8;
    if ((py >> 3) > win->y + win->height)
        return;
    if (win->anim == 0 && win->keepFrame == 0) {
        for (i = 0; i < win->width; i++) {
            if (i == 0)
                t = tile;
            else if (i == 1)
                t = tile + 1;
            else if (i >= win->width - 1)
                t = tile + 3;
            else
                t = tile + 2;
            buf[i] = t | pal;
        }
        map = Bg_GetMapPtr(win->bg, win->x, win->y);
        DmaCopy16(0, buf, map, win->width << 1);
    } else {
        n = win->anim >> 3;
        for (i = 0; i < win->width; i++) {
            if (n < win->height - 2) {
                if (i == 0)
                    t = tile + 4;
                else if (i >= win->width - 1)
                    t = tile + 6;
                else
                    t = tile + 5;
            } else if (n >= win->height - 1) {
                if (i == 0)
                    t = tile + 9;
                else if (i == win->width - 2)
                    t = tile + 11;
                else if (i >= win->width - 1)
                    t = tile + 12;
                else
                    t = tile + 10;
            } else {
                if (i == 0)
                    t = tile + 7;
                else if (i >= win->width - 1)
                    t = tile + 8;
                else
                    t = tile + 5;
            }
            buf[i] = t | pal;
        }
        if (win->keepFrame == 0) {
            map = Bg_GetMapPtr(win->bg, win->x, (py - 8) >> 3);
            DmaCopy16(0, buf, map, win->width << 1);
        }
        n -= win->skipRows;
        if (n > 0 && n <= win->rows * 2) {
            t = Window_GetTextTile(win->slot);
            odd = !(n & 1);
            grp = (n - 1) >> 1;
            t += win->width * 2 * grp;
            t += odd;
            if (n <= 4)
                attr = 7 << 12;
            else
                attr = 8 << 12;
            for (i = 1; i < win->width - 1; i++) {
                if (i & 1) {
                    buf[i] = attr | t;
                } else {
                    buf[i] = (t + 2) | attr;
                    t += 4;
                }
            }
            if (win->bg - 1 <= 1) {
                buf[0] = 0x3FF;
                buf[win->width - 1] = 0x3FF;
            } else {
                buf[0] = 0x2FF;
                buf[win->width - 1] = 0x2FF;
            }
            map = Bg_GetMapPtr(win->bg - 1, win->x, (py - 8) >> 3);
            DmaCopy16(0, buf, map, win->width << 1);
        }
    }
    if ((py >> 3) < win->y + win->height && win->keepFrame == 0) {
        for (i = 0; i < win->width; i++, px += 8) {
            if (i == 0)
                t = 9;
            else if (i == win->width - 2)
                t = 11;
            else if (i >= win->width - 1)
                t = 12;
            else
                t = 10;
            Obj_Draw(px, py, 7, t, win->variant, win->bg - 1, 0);
        }
    }
}

void Window_OpenStyle5(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 y;
    s32 py;
    s32 i;
    s32 t;
    s32 k;
    s32 odd;
    s32 n;
    s32 attr;
    u16 *map;

    px = win->x * 8;
    y = win->y * 8 + win->anim;
    py = y + 16;
    if ((py >> 3) - win->y >= win->height)
        return;
    if (win->anim == 0) {
        for (i = 0; i < win->width; i++) {
            if (i == 0)
                buf[0] = pal | tile;
            else if (i != win->width - 1) {
                if (i & 1)
                    buf[i] = (tile + 1) | pal;
                else
                    buf[i] = (tile + 2) | pal;
            } else
                buf[i] = (tile + 3) | pal;
        }
        map = Bg_GetMapPtr(win->bg, win->x, win->y);
        DmaCopy16(0, buf, map, win->width << 1);
        attr = Window_GetItemPalette(win->items[0].enabled, win->slot);
        for (i = 0; i < win->width; i++) {
            if (i & 1)
                buf[i] = (tile - 4) | attr;
            else
                buf[i] = (tile - 2) | attr;
        }
        buf[0] = pal | (tile + 4);
        buf[win->width - 1] = pal | (tile + 5);
        map = Bg_GetMapPtr(win->bg, win->x, win->y + 1);
        DmaCopy16(0, buf, map, win->width << 1);
    } else {
        k = win->anim >> 3;
        if (k != 0) {
            t = Window_GetTextTile(win->slot);
            py = y + 8;
            odd = !(k & 1);
            n = (k - 1) >> 1;
            t += win->width * 2 * n;
            t += odd;
            attr = Window_GetItemPalette(win->items[n].enabled, win->slot);
            for (i = 1; i < win->width - 1; i++) {
                if (i & 1) {
                    buf[i] = attr | t;
                } else {
                    buf[i] = (t + 2) | attr;
                    t += 4;
                }
            }
            if (k & 1) {
                buf[0] = (tile + 4) | pal;
                buf[win->width - 1] = (tile + 5) | pal;
            } else {
                buf[0] = (tile + 6) | pal;
                buf[win->width - 1] = (tile + 7) | pal;
            }
            map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
            DmaCopy16(3, buf, map, win->width << 1);
            py += 8;
            n = Window_RowToY(win, win->height) - 8;
            if (py >= n) {
                for (i = 0; i < win->width; i++) {
                    if (i == 0)
                        buf[i] = (tile + 8) | pal;
                    else if (i != win->width - 1) {
                        if (i & 1)
                            buf[i] = (tile + 9) | pal;
                        else
                            buf[i] = (tile + 10) | pal;
                    } else
                        buf[i] = (tile + 11) | pal;
                }
                map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
                DmaCopy16(3, buf, map, win->width << 1);
            }
        }
    }
    if ((py >> 3) - win->y - 1 < win->height) {
        for (i = 0; i < win->width; i++, px += 8) {
            if (i == 0)
                n = 8;
            else if (i != win->width - 1)
                n = 10;
            else
                n = 11;
            Obj_Draw(px, py, 8, n, win->variant, win->bg, 0);
        }
    }
}

void Window_OpenStyle6(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    s32 t;
    u16 *map;

    px = win->x * 8;
    py = win->y * 8 + win->anim + 8;
    if ((py >> 3) > win->y + win->height)
        return;
    if (win->anim == 0) {
        for (i = 0; i < win->width; i++) {
            if (i == 0)
                t = tile;
            else if (i + 1 >= win->width)
                t = tile + 2;
            else
                t = tile + 1;
            buf[i] = t | pal;
        }
        map = Bg_GetMapPtr(win->bg, win->x, win->y);
        DmaCopy16(0, buf, map, win->width << 1);
    }
    if (gMode == MODE_FIELD) {
        if (win->anim != 0)
            goto draw_animated_rows;
        goto draw_sprites;
    }
    if (win->anim == 0)
        goto draw_bottom_border;

draw_animated_rows:
    for (i = 0; i < win->width; i++) {
        if (i == 0)
            t = tile + 3;
        else if (i + 1 >= win->width)
            t = tile + 5;
        else
            t = tile + 4;
        if ((py >> 3) >= win->y + win->height)
            t += 3;
        buf[i] = t | pal;
    }
    map = Bg_GetMapPtr(win->bg, win->x, (py - 8) >> 3);
    DmaCopy16(0, buf, map, win->width << 1);

draw_bottom_border:
    if ((py >> 3) - win->y >= win->height - 1) {
        for (i = 0; i < win->width; i++) {
            if (i == 0)
                t = tile + 6;
            else if (i + 1 >= win->width)
                t = tile + 8;
            else
                t = tile + 7;
            buf[i] = t | pal;
        }
        map = Bg_GetMapPtr(win->bg, win->x, (py >> 3));
        DmaCopy16(0, buf, map, win->width << 1);
    }

draw_sprites:
    if ((py >> 3) < win->y + win->height) {
        for (i = 0; i < win->width; i++, px += 8) {
            if (i == 0)
                t = 6;
            else if (i + 1 >= win->width)
                t = 8;
            else
                t = 7;
            Obj_Draw(px, py, 9, t, win->variant, win->bg - 1, 0);
        }
    }
}

void Window_Nop(struct Window *win)
{
}

void Window_OpenStyle7(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 y;
    s32 py;
    s32 i;
    s32 j;
    s32 t;
    s32 k;
    s32 n;
    s32 grp;
    s32 attr;
    u16 *map;

    px = win->x * 8;
    y = win->y * 8 + win->anim;
    py = y + 16;
    Window_Nop(win);
    if ((py >> 3) - win->y >= win->height)
        return;
    if (win->anim == 0) {
        for (j = 0; j < 2; j++) {
            n = 0;
            for (i = 0; i < win->width; i++) {
                if (i <= 4) {
                    t = i;
                } else if (i < win->width - 7) {
                    t = 5;
                    n++;
                } else {
                    t = i - n;
                }
                if (j != 0)
                    t += 12;
                buf[i] = (tile + t) | pal;
            }
            map = Bg_GetMapPtr(win->bg, win->x, win->y + j);
            DmaCopy16(0, buf, map, win->width << 1);
        }
    } else {
        k = (win->anim >> 3) - 1;
        k -= win->skipRows;
        attr = 3 << 12;
        if (k < 0) {
            for (j = 1; j < win->width - 1; j++) {
                if (j & 1)
                    t = tile - 4;
                else
                    t = tile - 2;
                if (k & 1)
                    t++;
                buf[j] = t | attr;
            }
        } else {
            t = Window_GetTextTile(win->slot);
            n = k & 1;
            grp = k >> 1;
            t += win->width * 2 * grp;
            t += n;
            for (j = 1; j < win->width - 1; j++) {
                if (j & 1) {
                    buf[j] = attr | t;
                } else {
                    buf[j] = (t + 2) | attr;
                    t += 4;
                }
            }
        }
        if (k == 0) {
            buf[0] = (tile + 24) | pal;
            buf[win->width - 1] = (tile + 25) | pal;
        } else {
            buf[0] = (tile + 26) | pal;
            buf[win->width - 1] = (tile + 27) | pal;
        }
        map = Bg_GetMapPtr(win->bg, win->x, (y + 8) >> 3);
        DmaCopy16(0, buf, map, win->width << 1);
        if ((py >> 3) - win->y >= win->height - 1) {
            for (j = 0; j < win->width; j++) {
                if (j == 0)
                    t = 28;
                else if (j + 1 >= win->width)
                    t = 30;
                else
                    t = 29;
                buf[j] = (tile + t) | pal;
            }
            map = Bg_GetMapPtr(win->bg, win->x, (py >> 3));
            DmaCopy16(0, buf, map, win->width << 1);
        }
    }
    if ((py >> 3) - win->y < win->height - 1) {
        for (j = 0; j < win->width; j++, px += 8) {
            if (j == 0)
                t = 28;
            else if (j + 1 >= win->width)
                t = 30;
            else
                t = 29;
            Obj_Draw(px, py, 10, t, win->variant, win->bg - 1, 0);
        }
    }
}

void Window_OpenStyle8(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    s32 t;
    s32 a;
    s32 k;
    s32 attr;
    u8 n;
    u16 *map;

    px = win->x * 8;
    py = win->y * 8 + win->anim + 8;
    n = win->anim >> 3;
    if (n >= win->height)
        return;
    if (n <= 1) {
        for (i = 0; i < win->width; i++) {
            if (i == 0)
                k = tile;
            else if (i == 1)
                k = tile + 1;
            else if (i == win->width - 2)
                k = tile + 4;
            else if (i >= win->width - 1)
                k = tile + 5;
            else if (i & 2)
                k = tile + 2;
            else
                k = tile + 3;
            if (win->anim != 0)
                k += 6;
            buf[i] = k | pal;
        }
        tile = win->y + (win->anim >> 3);
        map = Bg_GetMapPtr(win->bg, win->x, tile);
        DmaCopy16(0, buf, map, win->width << 1);
    } else {
        s32 row = win->anim >> 3;
        if (row < win->height - 3) {
            k = row & 1;
            attr = Window_GetItemPalette(1, win->slot);
            for (i = 0; i < win->width; i++) {
                if (i <= 1 || i >= win->width - 2) {
                    if (i <= 1)
                        a = i + 12;
                    else
                        a = i - win->width + 16;
                    t = tile + a;
                    if (k)
                        t += 4;
                    a = pal;
                } else {
                    if (!(i & 2))
                        t = tile - 4;
                    else
                        t = tile - 2;
                    if (k)
                        t += 1;
                    a = attr;
                }
                buf[i] = t | a;
            }
            map = Bg_GetMapPtr(win->bg, win->x, (py - 8) >> 3);
            DmaCopy16(0, buf, map, win->width << 1);
        } else {
            for (i = 0; i < win->width; i++) {
                if (i == 0)
                    k = tile + 20;
                else if (i == 1)
                    k = tile + 21;
                else if (i == win->width - 2)
                    k = tile + 24;
                else if (i >= win->width - 1)
                    k = tile + 25;
                else if (i & 2)
                    k = tile + 22;
                else
                    k = tile + 23;
                k += (row - (win->height - 3)) * 6;
                buf[i] = k | pal;
            }
            map = Bg_GetMapPtr(win->bg, win->x, (py - 8) >> 3);
            DmaCopy16(0, buf, map, win->width << 1);
        }
    }
    if ((py >> 3) - win->y < win->height) {
        for (i = 0; i < win->width; i++, px += 8) {
            if (i == 0)
                k = 32;
            else if (i == 1)
                k = 33;
            else if (i > 1 && i <= win->width - 3) {
                if (i & 2)
                    k = 34;
                else
                    k = 35;
            } else if (i == win->width - 2)
                k = 36;
            else
                k = 37;
            Obj_Draw(px, py, 11, k, win->variant, win->bg, 0);
        }
    }
}

void Window_OpenStyle9(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 y;
    s32 py;
    s32 i;
    s32 t;
    s32 k;
    s32 odd;
    s32 n;
    s32 attr;
    u16 *map;

    px = win->x * 8;
    y = win->y * 8 + win->anim;
    py = y + 8;
    if ((py >> 3) - win->y >= win->height)
        return;
    if (win->anim == 0) {
        for (i = 0; i < win->width; i++) {
            if (i == 0)
                buf[i] = pal | tile;
            else if (i != win->width - 1) {
                if (i & 1)
                    buf[i] = (tile + 1) | pal;
                else
                    buf[i] = (tile + 2) | pal;
            } else
                buf[i] = (tile + 3) | pal;
        }
        map = Bg_GetMapPtr(win->bg, win->x, win->y);
        DmaCopy16(0, buf, map, win->width << 1);
        attr = win->slot == 2 ? 5 : 6;
        attr <<= 12;
        for (i = 0; i < win->width; i++) {
            if (i & 1)
                buf[i] = (tile - 4) | attr;
            else
                buf[i] = (tile - 2) | attr;
        }
        buf[0] = pal | (tile + 4);
        buf[win->width - 1] = pal | (tile + 5);
        map = Bg_GetMapPtr(win->bg, win->x, win->y + 1);
        DmaCopy16(0, buf, map, win->width << 1);
    } else {
        k = win->anim >> 3;
        if (k != 0) {
            t = Window_SlotTextTile(win);
            py = y;
            odd = !(k & 1);
            n = (k - 1) >> 1;
            t += win->width * 2 * n;
            t += odd;
            attr = win->slot == 2 ? 5 : 6;
            attr <<= 12;
            for (i = 1; i < win->width - 1; i++) {
                if (i & 1) {
                    buf[i] = attr | t;
                } else {
                    buf[i] = (t + 2) | attr;
                    t += 4;
                }
            }
            if (k < win->rows * 2) {
                buf[0] = (tile + 4) | pal;
                buf[win->width - 1] = (tile + 5) | pal;
            } else {
                buf[0] = (tile + 6) | pal;
                buf[win->width - 1] = (tile + 7) | pal;
            }
            map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
            DmaCopy16(3, buf, map, win->width << 1);
            py += 8;
            n = Window_RowToY(win, win->height) - 8;
            if (py >= n) {
                for (i = 0; i < win->width; i++) {
                    if (i == 0)
                        buf[i] = (tile + 8) | pal;
                    else if (i != win->width - 1) {
                        if (i & 1)
                            buf[i] = (tile + 9) | pal;
                        else
                            buf[i] = (tile + 10) | pal;
                    } else
                        buf[i] = (tile + 11) | pal;
                }
                map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
                DmaCopy16(3, buf, map, win->width << 1);
            }
        }
    }
    if ((py >> 3) - win->y - 1 < win->height) {
        for (i = 0; i < win->width; i++, px += 8) {
            if (i == 0)
                t = 8;
            else if (i != win->width - 1)
                t = 10;
            else
                t = 11;
            Obj_Draw(px, py, 12, t, win->variant, win->bg, 0);
        }
    }
}

void Window_OpenStyle14(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 y;
    s32 py;
    s32 i;
    s32 t;
    s32 k;
    s32 odd;
    s32 n;
    s32 attr;
    u32 flags;
    u16 *map;

    px = win->x * 8;
    y = win->y * 8 + win->anim;
    py = y + 8;
    if ((py >> 3) > win->y + win->height)
        return;
    if (win->anim == 0) {
        for (i = 0; i < win->width; i++) {
            if (i == 0 || i == win->width - 1)
                buf[i] = pal | tile;
            else if (i == 1 || i == win->width - 2)
                buf[i] = (tile + 1) | pal;
            else
                buf[i] = (tile + 2) | pal;
            if (i >= win->width - 2)
                buf[i] |= 0x400;
        }
        map = Bg_GetMapPtr(win->bg, win->x, win->y);
        DmaCopy16(0, buf, map, win->width << 1);
        attr = Window_GetItemPalette(win->items[0].enabled, win->slot);
        for (i = 0; i < win->width; i++) {
            if (i & 1)
                buf[i] = (tile - 4) | attr;
            else
                buf[i] = (tile - 2) | attr;
        }
        buf[0] = pal | (tile + 3);
        buf[win->width - 1] = (pal | (tile + 3)) | 0x400;
        map = Bg_GetMapPtr(win->bg, win->x, win->y + 1);
        DmaCopy16(0, buf, map, win->width << 1);
    } else {
        k = win->anim >> 3;
        k -= win->skipRows;
        if (k != 0) {
            t = Window_GetTextTile(win->slot);
            py = y;
            odd = !(k & 1);
            n = (k - 1) >> 1;
            t += win->width * 2 * n;
            t += odd;
            attr = Window_GetItemPalette(win->items[n].enabled, win->slot);
            for (i = 1; i < win->width - 1; i++) {
                if (i & 1) {
                    buf[i] = attr | t;
                } else {
                    buf[i] = (t + 2) | attr;
                    t += 4;
                }
            }
            n = win->anim >> 3;
            if (n == 1 || n == win->height - 2)
                buf[0] = (tile + 3) | pal;
            else
                buf[0] = (tile + 4) | pal;
            buf[win->width - 1] = buf[0] | 0x400;
            if (n >= win->width - 2) {
                buf[0] |= 0x800;
                buf[win->width - 1] |= 0x800;
            }
            map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
            DmaCopy16(3, buf, map, win->width << 1);
            py += 8;
            n = Window_RowToY(win, win->height) - 8;
            if (py >= n) {
                for (i = 0; i < win->width; i++) {
                    if (i == 0 || i == win->width - 1)
                        buf[i] = pal | tile;
                    else if (i == 1 || i == win->width - 2)
                        buf[i] = (tile + 1) | pal;
                    else
                        buf[i] = (tile + 2) | pal;
                    if (i >= win->width - 2)
                        buf[i] |= 0x400;
                    buf[i] |= 0x800;
                }
                map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
                DmaCopy16(3, buf, map, win->width << 1);
            }
        }
    }
    if ((py >> 3) - win->y < win->height) {
        for (i = 0; i < win->width; i++, px += 8) {
            flags = 0x20000000;
            if (i == 0 || i == win->width - 1)
                n = 0;
            else if (i == 1 || i == win->width - 2)
                n = 1;
            else
                n = 2;
            if (i >= win->width - 2)
                flags |= 0x10000000;
            Obj_Draw(px, py, 17, n, win->variant, win->bg, flags);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x02007D9C
 * PAL Size: 988b
 * EN Address: 0x02007D2C
 * EN Size: 986b
 * JP Address: 0x02007F60
 * JP Size: 986b
 */
void Window_OpenStyleNone(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 y;
    s32 i;
    s32 t;
    s32 n;
    s32 attr;
    s32 j;
    s32 k;
    u16 *map;

    attr = 0xF000;
    px = win->x * 8;
    y = win->y * 8 + win->anim;
    py = y + 8;
    if ((py >> 3) >= win->y + win->height)
        return;
    if (win->anim == 0) {
        for (i = 0; i < win->width; i++) {
            if (i == 0)
                buf[i] = pal | tile;
            else if (i != win->width - 1) {
                if (i & 1)
                    buf[i] = (tile + 1) | pal;
                else
                    buf[i] = (tile + 2) | pal;
            } else
                buf[i] = (tile + 3) | pal;
        }
        map = Bg_GetMapPtr(0, win->x, win->y);
        DmaCopy16(0, buf, map, win->width << 1);
        for (i = 0; i < win->width; i++) {
            if (i & 1)
                buf[i] = (tile - 4) | attr;
            else
                buf[i] = (tile - 2) | attr;
        }
        buf[0] = pal | (tile + 4);
        buf[win->width - 1] = pal | (tile + 5);
        map = Bg_GetMapPtr(0, win->x, win->y + 1);
        DmaCopy16(0, buf, map, win->width << 1);
    } else {
        n = win->anim >> 3;
        if (n == 1 || n == win->rows * 2) {
            for (i = 0; i < win->width; i++) {
                if (i & 1)
                    buf[i] = (tile - 4) | attr;
                else
                    buf[i] = (tile - 2) | attr;
            }
            buf[0] = pal | (tile + 4);
            buf[win->width - 1] = pal | (tile + 5);
            map = Bg_GetMapPtr(0, win->x, (py - 8) >> 3);
            DmaCopy16(0, buf, map, win->width << 1);
        } else {
            n--;
            k = !(n & 1);
            j = (n - 1) >> 1;
#if !defined(VERSION_GCCP01)
            t = 0x320;
#else
            t = 0x340;
#endif
            t += win->width * 2 * j;
            t += k;
            for (i = 1; i < win->width - 1; i++) {
                if (i & 1) {
                    buf[i] = attr | t;
                } else {
                    buf[i] = (t + 2) | attr;
                    t += 4;
                }
            }
            if (n < win->rows * 2) {
                buf[0] = (tile + 4) | pal;
                buf[win->width - 1] = (tile + 5) | pal;
            } else {
                buf[0] = (tile + 6) | pal;
                buf[win->width - 1] = (tile + 7) | pal;
            }
            map = Bg_GetMapPtr(0, win->x, (py - 8) >> 3);
            DmaCopy16(3, buf, map, win->width << 1);
        }
        j = Window_RowToY(win, win->height) - 8;
        if (py >= j) {
            for (i = 0; i < win->width; i++) {
                if (i == 0)
                    buf[i] = (tile + 8) | pal;
                else if (i != win->width - 1) {
                    if (i & 1)
                        buf[i] = (tile + 9) | pal;
                    else
                        buf[i] = (tile + 10) | pal;
                } else
                    buf[i] = (tile + 11) | pal;
            }
            map = Bg_GetMapPtr(0, win->x, (py >> 3));
            DmaCopy16(3, buf, map, win->width << 1);
        }
    }
    if ((py >> 3) - win->y < win->height - 1) {
        j = 12;
        for (i = 0; i < win->width; i++, px += 8) {
            if (i == 0)
                t = 8;
            else if (i != win->width - 1)
                t = 10;
            else
                t = 11;
            Obj_Draw(px, py, j, t, win->variant, 0, 0);
        }
    }
}

void Window_Close(struct Window *win)
{
    switch (win->style) {
    case -1:
        Window_CloseStyle9(win);
        break;
    case 0:
        if (win->variant)
            Window_CloseStyle0Horz(win);
        else
            Window_CloseStyle0(win);
        break;
    case 1:
    case 2:
    case 13:
        Window_CloseStyle1(win);
        break;
    case 3:
        Window_CloseStyle3(win);
        break;
    case 4:
        Window_CloseStyle4(win);
        break;
    case 5:
        Window_CloseStyle5(win);
        break;
    case 6:
        Window_CloseStyle6(win);
        break;
    case 7:
        Window_CloseStyle7(win);
        break;
    case 8:
        Window_CloseStyle8(win);
        break;
    case 9:
        Window_CloseStyle9(win);
        break;
    case 10:
        Window_CloseStyle0(win);
        break;
    case 14:
        Window_CloseStyle14(win);
        break;
    }
}

void Window_CloseStyle0(struct Window *win)
{
    s32 px;
    s32 py;
    s32 top;
    s32 last;
    s32 i;
    s32 frame;
    u32 flags;

    px = win->x * 8;
    top = win->y;
    last = win->height - 1;
    py = (last + top) * 8 - win->anim;
    if (py >> 3 > top) {
        Bg_FillBlank(win->bg, win->x, py >> 3, win->width, 1);
        if ((py >> 3) - 1 <= win->y)
            Bg_FillBlank(win->bg, win->x, (py >> 3) - 1, win->width, 1);
        if ((py >> 3) - 1 > win->y) {
            py -= 8;
            flags = 0x20000000;
            for (i = 0; i < win->width; i++, px += 8) {
                if (i == 0 || i == win->width - 1)
                    frame = 0;
                else if (i == 1 || i == win->width - 2)
                    frame = 1;
                else if (i == 2 || i == win->width - 3)
                    frame = 2;
                else
                    frame = 3;
                if (i >= win->width >> 1)
                    flags |= 0x10000000;
                Obj_Draw(px, py, 3, frame, win->variant, win->bg, flags);
            }
        }
    }
}

void Window_CloseStyle0Horz(struct Window *win)
{
    s32 px;
    s32 py;
    s32 x;
    s32 cols;
    s32 i;
    s32 frame;
    u32 flags;
    u16 tile;
    u16 *map;

    px = win->x * 8 + win->anim;
    py = win->y * 8;
    if (win->bg <= 1)
        tile = 0x3FF;
    else
        tile = 0x2FF;
    cols = win->width - (u8)((win->anim >> 2) + 1);
    x = px >> 3;
    map = Bg_GetMapPtr(win->bg, x, win->y);
    if (cols >= 0) {
        for (i = 0; i < win->height; i++) {
            map[0] = tile;
            map[cols] = tile;
            if (win->bg == 1 || win->bg == 2) {
                map[-0x400] = 0x3FF;
                map[cols - 0x400] = 0x3FF;
            }
            map += 32;
        }
        cols *= 8;
        flags = 0;
        for (i = 0; i < win->height; i++, py += 8) {
            if (i == 0 || i + 1 >= win->height)
                frame = 6;
            else if (i == 1 || i + 2 >= win->height)
                frame = 9;
            else if (i == 2 || i + 3 >= win->height)
                frame = 10;
            else
                frame = 11;
            if (i >= win->height >> 1)
                flags = 0x20000000;
            Obj_Draw(px, py, 3, frame, 0, win->bg, flags);
            Obj_Draw(px + cols, py, 3, frame, 0, win->bg, flags | 0x10000000);
        }
    }
}

void Window_CloseStyle1(struct Window *win)
{
    s32 px;
    s32 py;
    s32 top;
    s32 last;
    s32 i;
    s32 id;
    s32 frame;

    px = win->x * 8;
    top = win->y;
    last = win->height - 1;
    py = (last + top) * 8 - win->anim;
    if (py >> 3 > top) {
        Bg_FillBlank(win->bg, win->x, py >> 3, win->width, 1);
        if ((py >> 3) - 1 <= win->y)
            Bg_FillBlank(win->bg, win->x, (py >> 3) - 1, win->width, 1);
        if ((py >> 3) - 1 > win->y) {
            py -= 8;
            for (i = 0; i < win->width; i++, px += 8) {
                if (win->style == 1)
                    id = 4;
                else if (win->style == 2)
                    id = 5;
                else
                    id = 16;
                if (i == 0)
                    frame = 8;
                else if (i != win->width - 1)
                    frame = 10;
                else
                    frame = 11;
                Obj_Draw(px, py, id, frame, win->variant, win->bg, 0);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x02008540
 * PAL Size: 360b
 * EN Address: 0x020084D0
 * EN Size: 330b
 * JP Address: 0x02008704
 * JP Size: 330b
 */
void Window_CloseStyle3(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 top;
    s32 last;
    s32 i;
    u16 tile;
    u16 *map;
    s32 frame;

    px = win->x * 8;
    top = win->y;
    last = win->height - 1;
    py = (last + top) * 8 - win->anim;
    if (py >> 3 > top) {
        if (win->bg <= 1)
            tile = 0x3FF;
        else
            tile = 0x2FF;
        for (i = 0; i < ARRAY_COUNT(buf); i++)
            buf[i] = tile;
        map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
        if ((py >> 3) - 1 <= win->y)
            DmaCopy16(3, buf, map - 32, win->width << 1);
#if defined(VERSION_GCCP01)
        if (win->bg == 2) {
            tile = 0x3FF;
            for (i = 0; i < ARRAY_COUNT(buf); i++)
                buf[i] = tile;
        }
#endif
        map = Bg_GetMapPtr(win->bg - 1, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
        if ((py >> 3) - 1 <= win->y && gMode)
            DmaCopy16(3, buf, map - 32, win->width << 1);
        if ((py >> 3) - 1 > win->y) {
            py -= 8;
            for (i = 0; i < win->width; i++, px += 8) {
                if (i == 0)
                    frame = 6;
                else if (i + 1 >= win->width)
                    frame = 8;
                else
                    frame = 7;
                Obj_Draw(px, py, 6, frame, win->variant, win->bg - 1, 0);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x020086A8
 * PAL Size: 320b
 * EN Address: 0x0200861C
 * EN Size: 304b
 * JP Address: 0x02008850
 * JP Size: 304b
 */
void Window_CloseStyle4(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 top;
    s32 last;
    s32 i;
    s32 tile;
    u16 *map;

    px = win->x * 8;
    top = win->y;
    last = win->height - 1;
    py = (last + top) * 8 - win->anim;
    if (py >> 3 > top) {
        if (win->bg <= 1)
            tile = 0x3FF;
        else
            tile = 0x2FF;
        for (i = 0; i < ARRAY_COUNT(buf); i++)
            buf[i] = tile;
        map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
        if ((py >> 3) - 1 <= win->y)
            DmaCopy16(3, buf, map - 32, win->width << 1);
#if defined(VERSION_GCCP01)
        if (win->bg == 2) {
            tile = 0x3FF;
            for (i = 0; i < ARRAY_COUNT(buf); i++)
                buf[i] = tile;
        }
#endif
        map = Bg_GetMapPtr(win->bg - 1, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
        if ((py >> 3) - 1 > win->y) {
            py -= 8;
            for (i = 0; i < win->width; i++, px += 8) {
                if (i == 0)
                    tile = 9;
                else if (i == win->width - 2)
                    tile = 11;
                else if (i >= win->width - 1)
                    tile = 12;
                else
                    tile = 10;
                Obj_Draw(px, py, 7, tile, win->variant, win->bg - 1, 0);
            }
        }
    }
}

void Window_CloseStyle5(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 top;
    s32 last;
    s32 i;
    s32 tile;
    u16 *map;

    px = win->x * 8;
    top = win->y;
    last = win->height - 1;
    py = (last + top) * 8 - win->anim;
    if (py >> 3 > top) {
        if (win->bg <= 1)
            tile = 0x3FF;
        else
            tile = 0x2FF;
        for (i = 0; i < ARRAY_COUNT(buf); i++)
            buf[i] = tile;
        map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
        if ((py >> 3) - 1 <= win->y)
            DmaCopy16(3, buf, map - 32, win->width << 1);
        if ((py >> 3) - 1 > win->y) {
            py -= 8;
            for (i = 0; i < win->width; i++, px += 8) {
                if (i == 0)
                    tile = 8;
                else if (i != win->width - 1)
                    tile = 10;
                else
                    tile = 11;
                Obj_Draw(px, py, 8, tile, win->variant, win->bg, 0);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x020088E0
 * PAL Size: 360b
 * EN Address: 0x02008844
 * EN Size: 330b
 * JP Address: 0x02008A78
 * JP Size: 330b
 */
void Window_CloseStyle6(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 top;
    s32 last;
    s32 i;
    u16 tile;
    u16 *map;
    s32 frame;

    px = win->x * 8;
    top = win->y;
    last = win->height - 1;
    py = (last + top) * 8 - win->anim;
    if (py >> 3 > top) {
        if (win->bg <= 1)
            tile = 0x3FF;
        else
            tile = 0x2FF;
        for (i = 0; i < ARRAY_COUNT(buf); i++)
            buf[i] = tile;
        map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
        if ((py >> 3) - 1 <= win->y)
            DmaCopy16(3, buf, map - 32, win->width << 1);
#if defined(VERSION_GCCP01)
        if (win->bg == 2) {
            tile = 0x3FF;
            for (i = 0; i < ARRAY_COUNT(buf); i++)
                buf[i] = tile;
        }
#endif
        map = Bg_GetMapPtr(win->bg - 1, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
        if ((py >> 3) - 1 <= win->y && gMode)
            DmaCopy16(3, buf, map - 32, win->width << 1);
        if ((py >> 3) - 1 > win->y) {
            py -= 8;
            for (i = 0; i < win->width; i++, px += 8) {
                if (i == 0)
                    frame = 6;
                else if (i + 1 >= win->width)
                    frame = 8;
                else
                    frame = 7;
                Obj_Draw(px, py, 9, frame, win->variant, win->bg - 1, 0);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x02008A48
 * PAL Size: 324b
 * EN Address: 0x02008990
 * EN Size: 300b
 * JP Address: 0x02008BC4
 * JP Size: 300b
 */
void Window_CloseStyle7(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 top;
    s32 last;
    s32 i;
    u16 tile;
    u16 *map;
    s32 frame;

    px = win->x * 8;
    top = win->y;
    last = win->height - 1;
    py = (last + top) * 8 - win->anim;
    if (py >> 3 > top) {
        if (win->bg <= 1)
            tile = 0x3FF;
        else
            tile = 0x2FF;
        for (i = 0; i < ARRAY_COUNT(buf); i++)
            buf[i] = tile;
#if defined(VERSION_GCCP01)
        map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
#else
        map = Bg_GetMapPtr(win->bg - 1, win->x, py >> 3);
#endif
        DmaCopy16(3, buf, map, win->width << 1);
#if defined(VERSION_GCCP01)
        if (win->bg == 2) {
            tile = 0x3FF;
            for (i = 0; i < ARRAY_COUNT(buf); i++)
                buf[i] = tile;
        }
#endif
#if defined(VERSION_GCCP01)
        map = Bg_GetMapPtr(win->bg - 1, win->x, py >> 3);
#else
        map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
#endif
        DmaCopy16(3, buf, map, win->width << 1);
        if ((py >> 3) - 2 <= win->y) {
            for (i = 0; i < 2; i++) {
                map -= 32;
                DmaCopy16(3, buf, map, win->width << 1);
            }
        }
        if ((py >> 3) - 2 > win->y) {
            py -= 8;
            for (i = 0; i < win->width; i++, px += 8) {
                if (i == 0)
                    frame = 28;
                else if (i + 1 >= win->width)
                    frame = 30;
                else
                    frame = 29;
                Obj_Draw(px, py, 10, frame, win->variant, win->bg - 1, 0);
            }
        }
    }
}

void Window_CloseStyle8(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 top;
    s32 last;
    s32 i;
    s32 tile;
    u16 *map;

    px = win->x * 8;
    top = win->y;
    last = win->height - 1;
    py = (last + top) * 8 - win->anim;
    if (py >> 3 >= top) {
        tile = win->bg <= 1 ? 0x3FF : 0x2FF;
        for (i = 0; i < ARRAY_COUNT(buf); i++)
            buf[i] = tile;
        map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
        for (i = 0; i < ARRAY_COUNT(buf); i++)
            buf[i] = 0x3FF;
        map = Bg_GetMapPtr(win->bg - 1, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
        if ((py >> 3) - 1 > win->y) {
            py -= 8;
            for (i = 0; i < win->width; i++, px += 8) {
                if (i == 0)
                    tile = 32;
                else if (i == 1)
                    tile = 33;
                else if (i > 1 && i <= win->width - 3) {
                    if (i & 2)
                        tile = 34;
                    else
                        tile = 35;
                } else if (i == win->width - 2)
                    tile = 36;
                else
                    tile = 37;
                Obj_Draw(px, py, 11, tile, win->variant, win->bg, 0);
            }
        }
    }
}

void Window_CloseStyle9(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 top;
    s32 last;
    s32 i;
    s32 tile;
    u16 *map;

    px = win->x * 8;
    top = win->y;
    last = win->height - 1;
    py = (last + top) * 8 - win->anim;
    if (py >> 3 > top) {
        if (win->bg <= 1)
            tile = 0x3FF;
        else
            tile = 0x2FF;
        for (i = 0; i < ARRAY_COUNT(buf); i++)
            buf[i] = tile;
        map = Bg_GetMapPtr(win->bg, win->x, py >> 3);
        DmaCopy16(3, buf, map, win->width << 1);
        if ((py >> 3) - 1 <= win->y)
            DmaCopy16(3, buf, map - 32, win->width << 1);
        if ((py >> 3) - 1 > win->y) {
            py -= 8;
            for (i = 0; i < win->width; i++, px += 8) {
                if (i == 0)
                    tile = 8;
                else if (i != win->width - 1)
                    tile = 10;
                else
                    tile = 11;
                Obj_Draw(px, py, 12, tile, win->variant, win->bg, 0);
            }
        }
    }
}

void Window_CloseStyle14(struct Window *win)
{
    s32 px;
    s32 py;
    s32 last;
    s32 i;
    s32 frame;
    s32 bottom;
    s32 top;
    u32 flags;

    px = win->x * 8;
    bottom = win->y;
    top = bottom;
    last = win->height - 1;
    bottom = (last + bottom) * 8;
    py = bottom - win->anim;
    if (py >> 3 > top) {
        Bg_FillBlank(win->bg, win->x, py >> 3, win->width, 1);
        if ((py >> 3) - 1 <= win->y)
            Bg_FillBlank(win->bg, win->x, (py >> 3) - 1, win->width, 1);
        if ((py >> 3) - 1 > win->y) {
            py -= 8;
            for (i = 0; i < win->width; i++, px += 8) {
                flags = 0x20000000;
                if (i == 0 || i == win->width - 1)
                    frame = 0;
                else if (i == 1 || i == win->width - 2)
                    frame = 1;
                else
                    frame = 2;
                if (i >= win->width - 2)
                    flags |= 0x10000000;
                Obj_Draw(px, py, 17, frame, win->variant, win->bg, flags);
            }
        }
    }
}

void Obj_DrawBanner(s32 prio, s32 x, s32 y, s32 n, s32 offset, s32 mode)
{
    s32 px;
    s32 t;
    s32 i;
    s32 frame;
    s32 count;
    s32 palette;

    px = x + offset;
    t = y + 10;
    if (mode == 0) {
        for (i = 0; i <= 9; i++, px += 16)
            Obj_Draw(px, t, 22, i, 0, 0, 0);
    }
    count = n;
    px = x;
    t = mode;
    if (t == 0)
        t = 15;
    else
        t = 18;
    palette = 0;
    for (i = 0; i < count; i++, px += 8) {
        if (i <= 2)
            frame = i;
        else if (i >= count - 3)
            frame = 7 - (count - i);
        else
            frame = 3;
        Obj_Draw(px, y, t, frame, palette, prio, 0);
        Obj_Draw(px, y + 16, t, frame + 7, palette, prio, 0);
    }
}

void Session_OnMask(struct JoyBytes cmd)
{
    u16 v;

    v = (cmd.b[1] << 8) | cmd.b[2];
    if ((v & 0xFF) != (gMask & 0xFF)) {
        gScreen = 0;
        gShopMenuPos[0] = 0;
        gShopMenuPos[1] = 0xFF;
    }
    gMask = v;
}

void Obj_DrawGil(s32 x, s32 y, s32 len, s32 pal, u32 value, s32 color)
{
    u32 max;
    s32 i;
    s32 div;
    u32 rem;
    s32 digit;
    s32 c;

    div = (len * 8 - 80) >> 1;
    x += div;
    max = 1;
    for (i = 0; i < 8; i++)
        max *= 10;
    div = max / 10;
    rem = value;
    if (color < 0)
        c = Obj_GetPalette(1, 0);
    else
        c = color;
    for (i = 0; i < 8; i++, x += 8, rem %= div, div /= 10) {
        if (value >= max) {
            digit = 9;
        } else {
            digit = rem / div;
            if (digit == 0 && value <= div && i + 1 < 8)
                continue;
        }
        Obj_Draw(x, y, 1, digit, c, pal, 0);
    }
    if ((gLanguage & 15) == 1)
        i = 54;
    else
        i = 44;
    c = Obj_GetPalette(0, i);
    Obj_Draw(x + 1, y, 0, i, c, pal, 0);
}

void Obj_DrawGauge(s32 x, s32 y, s32 n, s32 pal, s32 fill)
{
    s32 i;
    s32 k;
    s32 frame;
    u32 flags;

    k = 0;
    for (i = 0; i < n; i++, x += 8) {
        flags = 0;
        if (i == 0 || i + 1 >= n) {
            frame = 0;
            if (i != 0)
                flags = 0x10000000;
        } else {
            k += 2;
            if (k <= fill) {
                if (fill <= 4)
                    frame = 22;
                else if (fill <= 6)
                    frame = 20;
                else
                    frame = 1;
            } else if (k == fill + 1) {
                if (fill <= 4)
                    frame = 23;
                else if (fill <= 6)
                    frame = 21;
                else
                    frame = 2;
            } else {
                frame = 3;
            }
        }
        Obj_Draw(x, y, 2, frame, Obj_GetPalette(2, frame), pal, flags);
    }
}

void Mode_OnSet(u32 data)
{
    struct JoyBytes *cmd = (struct JoyBytes *)&data;

    gMode = cmd->b[1];
    if (gMode != MODE_FIELD) {
        gSession.outsideMiasma = 0;
        if (gMode == MODE_CONTROLLER) {
            Map_SetStage(33, 0);
            gParty[Link_GetPlayerNo()].hp = 0;
        }
    }
    if (gMode == MODE_FIELD || gMode == MODE_CONTROLLER)
        gMenuHasInput = 0;
    else
        gMenuHasInput = 1;
    if (gMode == MODE_CMAKE)
        CMake_Reset();
    Smith_ResetList();
    if (gWasConnected)
        gScreen = 0;
    else
        gSavedScreen = 0;
    gShopMenuPos[0] = 0;
    gShopMenuPos[1] = 0xFF;
    Screen_Reset();
    Bg_ClearMaps();
    Bg_SetBlend(0);
    Header_Clear();
}
