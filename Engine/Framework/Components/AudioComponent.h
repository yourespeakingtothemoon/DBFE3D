#pragma once 
#include "Component.h" 
#include "Audio/AudioChannel.h"

namespace dbf
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent() = default;
		~AudioComponent();

		CLASS_DECLARATION(AudioComponent)

		void init() override;
		void update() override;

		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

		void Play();
		void Stop();

	public:
		AudioChannel m_channel;

		// !! your names do not have to be the same 
		std::string sound_name;
		float volume = 1;
		float pitch = 1;
		bool play_on_start = false;
		bool loop = false;
	};
}