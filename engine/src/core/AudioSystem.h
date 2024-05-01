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
    inline bool g_IsPlaying = false;
  
    inline void InitAudioSystem()
    {
      g_AudioEngine = new SoLoud::Soloud;
      g_AudioEngine->init();
      FZ_INFO("Audio Initialised");
    }


    inline void LoadAudioFile(const std::string& filePath)
    {
      g_AudioWAV.load(filePath.c_str());
    }

    inline bool PlayAudio()
    {
      if(g_AudioEngine)
      {
        g_IsPlaying = true;
        g_Handle = g_AudioEngine->play(g_AudioWAV);
        
        return g_IsPlaying;
      }

      return !g_IsPlaying;
      
    }

    inline void PauseAudio()
    {
      if(g_IsPlaying == true)
        g_AudioEngine->setPause(g_Handle, true);
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
