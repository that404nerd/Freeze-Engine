#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include "core/Core.h"

// This is a temporary example that can be referenced later on for abstracting the API

namespace Freeze 
{
  static ALCdevice* audioDevice = alcOpenDevice(nullptr); // Use the default device

  static void InitAudio()
  {
    if(!audioDevice)
    {
      FZ_ERROR("Audio device failed to open: {}", alGetError());
    }
  }

  static void DestroyAudio()
  {
    // Create an audio context
    ALCcontext* context = alcCreateContext(audioDevice, nullptr);

    ALenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
      FZ_ERROR("Failed to create context: {}", alGetError());
    }

    alcMakeContextCurrent(context);
  }

}