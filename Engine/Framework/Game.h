#pragma once
#include <memory>

namespace dbf
{
	class Renderer;
	class Scene;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual void init() = 0;
		virtual void shutdown() = 0;

		virtual void update() = 0;
		virtual void draw(Renderer& renderer) = 0;

		int getScore() { return m_score; }
		void addPoints(int points) { m_score += points; }

	protected:
		std::unique_ptr<Scene> m_scene;
		int m_score = 0;

	};
}