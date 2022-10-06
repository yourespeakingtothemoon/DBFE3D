#pragma once 
#include "RenderComponent.h" 
#include <map> 

namespace dbf
{
	class Texture;

	class SpriteAnimComponent : public RenderComponent
	{
	public:
		struct Sequence
		{
			std::string name;

			float fps = 0;
			int num_columns = 0;
			int num_rows = 0;

			int start_frame = 0;
			int end_frame = 0;

			bool loop = true;

			std::shared_ptr<Texture> texture;
		};

	public:
		CLASS_DECLARATION(SpriteAnimComponent)

			virtual void update() override;
		virtual void draw(Renderer& renderer) override;

		virtual void setSequence(const std::string& name);
		
		Rectangle& GetSource() override;

		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

	public:
		int frame = 0;
		float frameTimer = 0;

		std::map<std::string, Sequence> m_sequences;
		Sequence* m_sequence = nullptr;
	};
}