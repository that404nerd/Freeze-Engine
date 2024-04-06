#pragma once

#include "Core.h"

#include "AL/al.h"
#include "AL/alc.h"

namespace Freeze {
  
  namespace InitAudio {
  
    inline bool InitAudio()
    {
    }

    inline void DestroyAudioEngine()
    {
    }
  };

  class Audio {
  public:
    Audio() = default;

    void PlayAudio(const std::string& filePath);

    ~Audio() {};
  };

};
