#include "global.h"
#include "obj.h"
#include "link.h"
#include "sound.h"

struct Sound gSound;

void Sound::Init()
{
}

void Sound::UpdateListener()
{
    struct Actor *actor = &gGame.actors[gPlayerNo];

    listener = actor->pos;
}

void Sound::PlaySong(u16 song, void *source)
{
    m4aSongNumStart(song);
}
