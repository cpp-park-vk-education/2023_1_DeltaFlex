#pragma once

#include <memory>

#include <SDL2/SDL_mixer.h>

struct DFMusicFile
{
    std::unique_ptr<Mix_Music, void(*)(Mix_Music *)> mix_music_inner;

    DFMusicFile(const char *resoursePath): mix_music_inner(Mix_LoadMUS(resoursePath), Mix_FreeMusic) {}
};

struct DFAudioFile
{
    std::unique_ptr<Mix_Chunk, void(*)(Mix_Chunk *)> mix_audio_inner;

    DFAudioFile(const char *resoursePath): mix_audio_inner(Mix_LoadWAV(resoursePath), Mix_FreeChunk) {}
};

class DFAudioManager
{
public:
    DFAudioManager()
    {
        Mix_OpenAudio(48000, AUDIO_U16, 8, 4096);
    }

    ~DFAudioManager()
    {
        Mix_CloseAudio();
    }

    static void PlayMusic(DFMusicFile &music, int loops=0) { Mix_PlayMusic(music.mix_music_inner.get(), loops); }
    static void PlayAudio(DFAudioFile &audio, int loops=0) { Mix_PlayChannel(-1, audio.mix_audio_inner.get(), loops); }
};
