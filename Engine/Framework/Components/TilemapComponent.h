#pragma once
#include "RenderComponent.h"
#include "Math/Rectangle.h"
#include "Math/Vector2.h"
#include <vector>

namespace dbf
{
	class TilemapComponent : public Component
	{
	public:
		CLASS_DECLARATION(TilemapComponent)

		virtual void init() override;
		virtual void update() override;

		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;


	private:
		int num_columns = 0;
		int num_rows = 0;
		Vector2 size;

		std::vector<std::string> tile_names;
		std::vector<int> tiles;
	};
}