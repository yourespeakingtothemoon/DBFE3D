#pragma once 
#include "Math\Vector2.h" 
#include "Resource/Resource.h"
#include "Renderer/Renderer.h"
#include <string> 

 
struct SDL_Texture; 
struct SDL_Surface;
namespace dbf
{ 
	class Renderer;
	class Texture : public Resource
	{
public:
	Texture() = default;
	~Texture();

	bool Create(std::string filename, ...) override;

	bool Create(Renderer& renderer, const std::string& filename);
	bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);

	void bind() { glBindTexture(m_target, m_texture); }

	Vector2 getSize() const;

	friend class Renderer;

	private:
		void FlipSurface(SDL_Surface* surface);

private:
	GLuint m_texture = 0;
	GLenum m_target = GL_TEXTURE_2D;
	GLuint m_unit = GL_TEXTURE0;
	//SDL_Texture* m_texture = nullptr;
	};
}