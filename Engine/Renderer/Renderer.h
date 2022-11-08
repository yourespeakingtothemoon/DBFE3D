#pragma once
#include "Math\Vector2.h"
#include "Math\Color.h"
#include "Math\Rectangle.h"
#include "Math/Mat3x3.h"
#include "Math/MathUtils.h"
#include <glad/glad.h> 
#include <SDL.h> 

struct SDL_Renderer;
struct SDL_Window;



namespace dbf
{
	class Texture;
	struct Transform;
	struct Rectangle;

	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		void init();
		void shutdown();

		void generateWindow(const char* name, int width, int height, bool fullscreen);
		void openFrame();
		void closeFrame();
		void setClearColor(const Color& color) { m_clearColor = color; }

		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawLine(const Vector2& v1, const Vector2& v2, const Color& color);
		void DrawPoint(float x, float y);
		void DrawPoint(const Vector2& v, const Color& color);

		void draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle = 0, const Vector2& scale = Vector2{ 1, 1 }, const Vector2& registration = Vector2{ 0.5f, 0.5f });
		//void draw(std::shared_ptr<Texture> texture, const Transform& transform, const Vector2& registration = Vector2{ 0.5f, 0.5f });
		//void draw(std::shared_ptr<Texture> texture, const Rectangle& source, const Transform& transform, const Vector2& registration = Vector2{ 0.5f, 0.5f }, bool flipH = false);

		int getWidth() { return m_width; }
		int getHeight() { return m_height; }

		const glm::mat4& getView() { return m_view; }
		void setView(const glm::mat4& view) { m_view = view; }

		const glm::mat4& getProjection() { return m_projection; }
		void setProjection(const glm::mat4& projection) { m_projection = projection; }

		friend class Text;
		friend class Texture;

	private:
		int m_width = 0;
		int m_height = 0;

		Color m_clearColor{ 0, 0, 0, 255 };

		glm::mat4 m_view{ 1 };
		glm::mat4 m_projection{ 1 };

		SDL_Renderer* m_renderer = nullptr;
		SDL_Window* m_window = nullptr;

		SDL_GLContext m_context;
	};

}