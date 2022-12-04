#pragma once
#include "Texture.h"
#include <vector>

namespace dbf
{
	class CubemapTexture : public Texture
	{
	public:
		bool Create(std::string filename, ...) override;
		bool Load(const std::vector<std::string>& filenames);
	private:
		std::vector<std::string> generateCMNames(const std::string& basename, const std::string& extention);

	};
}