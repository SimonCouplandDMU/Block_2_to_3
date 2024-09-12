#pragma once

#include "systems/system.h"
#include <memory>
#include <unordered_map>
#include <soloud.h>
#include <soloud_wav.h>

namespace Engine
{
	class AudioSystem : public System
	{
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...) override//!< Start the system
		{
			m_audioSystem.init();
		}

		virtual void stop(SystemSignal close = SystemSignal::None, ...) override//!< Stop the system
		{
			m_audioSystem.deinit();
		}

		bool addSound(const std::string& tag, const std::string& filepath); //!< Add a sound file to our audio system
		bool playSound(const std::string& tag, float volume = 1.0f, float pan = 0.f, float playSpeed = 1.f); //!< play a sound already loaded
		bool setSoundLooping(const std::string& tag, bool looping); //!< Set sound looping property

	private:
		SoLoud::Soloud m_audioSystem;
		std::unordered_map<std::string, SoLoud::Wav> m_sounds;
	};
}