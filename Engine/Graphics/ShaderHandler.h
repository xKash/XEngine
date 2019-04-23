#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <memory>
#include <glew.h>
#include "../Core/Debug.h"


class ShaderHandler {
private:

	ShaderHandler();
	~ShaderHandler();

	static std::unique_ptr<ShaderHandler> shaderInstance;
	friend std::default_delete<ShaderHandler>;
	std::string ReadShader(const std::string& fileName_);
	GLuint CreateShader(GLenum shaderType_, const std::string& source_, const std::string& shaderName_);

	static std::map<std::string, GLuint> programs;

public:

	// Make impossible do instantiate this class
	ShaderHandler(const ShaderHandler&) = delete;
	ShaderHandler(ShaderHandler&&) = delete;
	ShaderHandler& operator=(const ShaderHandler&) = delete;
	ShaderHandler& operator=(ShaderHandler&&) = delete;

	static ShaderHandler* GetInstance();
	void CreateProgram(const std::string& shaderName_, const std::string& vertexShaderName_, const std::string& fragmentShaderName_);
	static const GLuint GetShader(const std::string shaderName_);
};
#endif // !SHADERHANDLER_H

