#pragma once

#include "core/Core.h"

#include "soloud.h"
#include "soloud_wav.h"

namespace Freeze 
{

  namespace Audio {

    inline SoLoud::Soloud g_AudioEngine;
    inline SoLoud::Wav g_AudioWAV;
  
    inline void InitAudioSystem()
    {
      g_AudioEngine.init();
    }


    inline void LoadAudioFile(const std::string& filePath)
    {
      g_AudioWAV.load(filePath.c_str());
    }

    inline void PlayAudio()
    {
      
        g_AudioEngine.play(g_AudioWAV);
    }

    inline void DestroyAudioSystem()
    {
     
    }

  };

}