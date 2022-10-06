#include "Renderer.h"
#include "Math\MathUtils.h"
#include "Math\Transform.h"
#include "Math\Rectangle.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

namespace dbf
{
	void Renderer::init()
	{
		//view
		m_view = Mat3x3::identity;
		m_viewport = Mat3x3::identity;
		SDL_Init(SDL_INIT_VIDEO);
		//Images
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		
		//font
		TTF_Init();
	}

	void Renderer::shutdown()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		//font
		TTF_Quit();
		//Images
		IMG_Quit();
	}

	void Renderer::generateWindow(const char* name, int width, int height)
	{
		m_width = width;
		m_height = height;

		m_window = SDL_CreateWindow(name, 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}

	void Renderer::openFrame()
	{
		SDL_SetRenderDrawColor(m_renderer, m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		SDL_RenderClear(m_renderer);
	}

	void Renderer::closeFrame()
	{
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::DrawLine(float x1, float y1, float x2, float y2)
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
	}

	void Renderer::DrawLine(const dbf::Vector2& v1, const dbf::Vector2& v2, const dbf::Color& color)
	{
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLineF(m_renderer, v1.x, v1.y, v2.x, v2.y);
	}

	void Renderer::DrawPoint(float x, float y)
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderDrawPointF(m_renderer, x, y);
	}

	void Renderer::DrawPoint(const dbf::Vector2& v, const dbf::Color& color)
	{
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawPointF(m_renderer, v.x, v.y);
	}

	void Renderer::draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle, const Vector2& scale, const Vector2& registration)
	{


		Vector2 size = texture->GetSize();
		size = size * scale;

		Vector2 origin = size * registration;
		Vector2 tposition = position - origin;

		SDL_Rect dest;
		// !! make sure to cast to int to prevent compiler warnings 
		dest.x = (int)tposition.x;// !! set to position x 
		dest.y = (int)tposition.y;// !! set to position y 
		dest.w = (int)size.x;// !! set to size x 
		dest.h = (int)size.y;// !! set to size y 

		SDL_Point center{ (int)origin.x, (int)origin.y };

		SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, angle, &center, SDL_FLIP_NONE); //SDL_FLIP_NONE //SDL_FLIP_HORIZONTAL //SDL_FLIP_VERTICAL
	}

	void Renderer::draw(std::shared_ptr<Texture> texture, const Transform& transform, const Vector2& registration)
	{
		Vector2 size = texture->GetSize();
		size = size * transform.scale;

		Vector2 origin = size * registration;
		Vector2 tposition = transform.position - origin;

		SDL_Rect dest;
		// !! make sure to cast to int to prevent compiler warnings 
		dest.x = (int)(tposition.x);// !! set to position x 
		dest.y = (int)(tposition.y);// !! set to position y 
		dest.w = (int)(size.x);// !! set to size x 
		dest.h = (int)(size.y);// !! set to size y 

		SDL_Point center{ (int)origin.x, (int)origin.y };
		//transform.rotation = angle
		SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, transform.rotation, &center, SDL_FLIP_NONE); //SDL_FLIP_NONE //SDL_FLIP_HORIZONTAL //SDL_FLIP_VERTICAL
	}

	void Renderer::draw(std::shared_ptr<Texture> texture, const Rectangle& source, const Transform& transform, const Vector2& registration, bool flipH)
	{
		Mat3x3 mx = m_viewport * m_view * transform.matrix;

		Vector2 size = Vector2{ source.w, source.h };
		size = size * mx.GetScale();

		Vector2 origin = size * registration;
		Vector2 tposition = mx.GetTranslation() - origin;

		SDL_Rect dest;
		dest.x = (int)(tposition.x);
		dest.y = (int)(tposition.y);
		dest.w = (int)(size.x);
		dest.h = (int)(size.y);

		SDL_Rect src;
		src.x = source.x;
		src.y = source.y;
		src.w = source.w;
		src.h = source.h;

		SDL_Point center{ (int)origin.x, (int)origin.y };

		SDL_RendererFlip flip = (flipH) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		SDL_RenderCopyEx(m_renderer, texture -> m_texture, &src, &dest, math::RadtoDeg(mx.GetRotation()), &center, flip);
	}
}