#ifndef ResourcesManager_H
#define ResourcesManager_H

#include <string>
#include <memory>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>

class ShaderProgram;
class Texture2D;

class  ResourcesManager {
public:
	ResourcesManager(const std::string& exe_path);
	~ResourcesManager() = default;
	std::shared_ptr<ShaderProgram> loadShaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path);
	std::shared_ptr<ShaderProgram> getShaderProgram(const std::string& shader_name) const;
	std::shared_ptr<Texture2D> loadTexture(const std::string& texture_name, const std::string& texture_path);
	std::shared_ptr<Texture2D> getTexture(const std::string& texture_name) const;
	
	ResourcesManager() = delete;
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;

private:
	std::string executable_path;

	typedef std::map<const std::string, std::shared_ptr<ShaderProgram>> ShaderProgramMap;
	ShaderProgramMap m_shader_program_map;
	
	typedef std::map<const std::string, std::shared_ptr<Texture2D>> Texture2DMap;
	Texture2DMap m_texture_map;

	std::string getStringFromFile(const std::string& relative_file_path);
};
	   	  
#endif // ResourcesManager_H