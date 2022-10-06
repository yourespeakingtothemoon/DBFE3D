#pragma once
#include <string>
struct SDL_Texture;

namespace dbf
{
	struct Vector2;
	struct Color;
	class Font;
	class Renderer;

	class Text
	{
	public:
		Text() = default;
		Text(Font* font) : m_font{ font } {}
		~Text();

		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void draw(Renderer& renderer, const Vector2& position);

		friend class Renderer;
		friend class Font;

	private:
		Font* m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
	};
}