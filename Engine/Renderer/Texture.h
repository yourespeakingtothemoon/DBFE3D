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
	bool CreateTexture(int w, int h);
	bool CreateDepthTexture(int w, int h);
	
	bool Load(const std::string& filename);

	void setActive(GLuint unit) { glActiveTexture(unit); }
	void bind() { glBindTexture(m_target, m_texture); }


	glm::ivec2 getSize() const;
	static GLenum getInternalFormat(GLuint format);

	friend class Renderer;
	friend class Framebuffer;

	protected:
		void FlipSurface(SDL_Surface* surface);

protected:
	GLuint m_texture = 0;
	GLenum m_target = GL_TEXTURE_2D;


	int m_width = 0;
	int m_height = 0;
	//GLuint m_unit = GL_TEXTURE0;
	//SDL_Texture* m_texture = nullptr;
	};
}