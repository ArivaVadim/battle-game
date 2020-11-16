#include "resources_manager.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

ResourcesManager::ResourcesManager(const std::string& exePath)
{
	size_t found = exePath.find_last_of("/\\");
	executable_path = exePath.substr(0,found);
}

std::string ResourcesManager::getStringFromFile(const std::string& relative_file_path)
{
	std::ifstream file;
	file.open(executable_path + "/" + relative_file_path.c_str(), std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "ERROR::ResourcesManager::getStringFromFile() - file not open;\t" << executable_path + "/" + relative_file_path.c_str() + "\n";
		return std::string("Error");
	}
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

std::shared_ptr<ShaderProgram> ResourcesManager::loadShaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path)
{
	std::string vertex_string = getStringFromFile(vertex_path);
	if (vertex_string.empty())
	{
		std::cerr << "ERROR::ResourcesManager::loadShader() - file with vertex shader not open;\n";
		return nullptr;
	}

	std::string fragment_string = getStringFromFile(fragment_path);
	if (fragment_string.empty())
	{
		std::cerr << "ERROR::ResourcesManager::loadShader() - file with fragment shader not open;\n";
		return nullptr;
	}

	std::shared_ptr<ShaderProgram> &new_shader = shader_program_map.emplace(shader_name, std::make_shared<ShaderProgram>(vertex_string, fragment_string)).first->second;
	if (!new_shader->isCompile)
	{
		std::cerr << "ERROR::ResourcesManager::loadShader() - new shader no compile;\n";
		return nullptr;
	}
	return new_shader;
}

std::shared_ptr<ShaderProgram> ResourcesManager::getShaderProgram(const std::string& shader_name) const
{
	ShaderProgramMap::const_iterator it = shader_program_map.find(shader_name);
	if (it == shader_program_map.end())
	{
		std::cerr << "ERROR::ResourcesManager::getShader() - can't read shader program;\t"<< shader_name <<std::endl;
		return nullptr;
	}
	return it->second;
}

void ResourcesManager::loadTexture(const std::string& texture_name, const std::string& texture_path)
{
	int pixels_channels = 0;
	int texture_width = 0;
	int texture_height = 0;
	
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels_buffer = stbi_load(std::string(executable_path + "/" + texture_path).c_str(), &texture_width, &texture_height, &pixels_channels, 0);
	if (!pixels_buffer)
	{
		std::cerr << "ERROR::ResourcesManager::loadTexture() - can't load texture;\t"<< std::string(executable_path + "/" + texture_name).c_str() << std::endl;
		return;
	}

	stbi_image_free(pixels_buffer);
}