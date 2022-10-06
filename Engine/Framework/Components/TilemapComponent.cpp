#include "TilemapComponent.h"
#include "Engine.h"

namespace  dbf
{
    void TilemapComponent::init()
    {
        for (int i = 0; i < tiles.size(); i++)
        {
            int index = tiles[i];
            if (index == 0) continue;

            auto actor = Factory::instance().Create<Actor>(tile_names[index]);
            if (actor)
            {
                int x = i % num_columns;
                int y = i / num_columns;

                actor->m_transform.position = m_owner->m_transform.position + (Vector2{ x, y } *size);
                m_owner->getScene()->Add(std::move(actor));
            }
        }

    }

    void TilemapComponent::update()
    {
    }

    bool TilemapComponent::write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool TilemapComponent::read(const rapidjson::Value& value)
    {
        READ_DATA(value, num_columns);
        READ_DATA(value, num_rows);
        READ_DATA(value, size);
        READ_DATA(value, tile_names);
        READ_DATA(value, tiles);

        return true;
    }

}
