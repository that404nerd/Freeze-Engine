#pragma once

#include "core/Core.h"

#include "soloud.h"
#include "soloud_wav.h"

namespace Freeze 
{

  namespace Audio {

    inline SoLoud::Soloud* g_AudioEngine;
    inline SoLoud::Wav g_AudioWAV;

    inline SoLoud::handle g_Handle;
    inline bool g_IsPlaying;
  
    inline void InitAudioSystem()
    {
      g_AudioEngine = new SoLoud::Soloud;
      g_AudioEngine->init();
      FZ_INFO("Audio Initialised");
    }

    inline void SetPlayingStatus(bool status) { g_IsPlaying = status; }
    inline bool IsPlaying() { return g_IsPlaying; }

    inline void LoadAudioFile(const std::string& filePath)
    {
      g_AudioWAV.load(filePath.c_str());
      SetPlayingStatus(true);
    }

    inline void PlayAudio()
    {
      if(g_IsPlaying)
      {
        g_Handle = g_AudioEngine->play(g_AudioWAV);
        SetPlayingStatus(false);
      } 
      else {
        return;
      }
    }

    inline void PauseAudio()
    {
      if(!g_IsPlaying) {
        g_AudioEngine->setPause(g_Handle, true);
        SetPlayingStatus(true);
      }
      else
        return;
    }

    inline void DestroyAudioSystem()
    {
      if(g_AudioEngine != nullptr)
      {
        g_AudioEngine->deinit();
        FZ_INFO("Destroyed audio system");
      }
      else
        FZ_WARN("Audio system not destroyed...");
    }

  };

}
