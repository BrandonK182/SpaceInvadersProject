#pragma once

#include<string>
#include<unordered_map>

struct ShaderProgramSource{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader{
	private:
		unsigned int id;
		//caching
		std::unordered_map<std::string, int>UniformLocationCache;

		ShaderProgramSource ParseShader(const std::string &filepath);
		unsigned int CompileShader(unsigned int type, const std::string &source);
		unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
		int GetUniformLocation(const std::string &name);

	public:
		Shader(const std::string &filepath);
		~Shader();

		void Bind() const;
		void unBind() const;

		//set uniforms
		void SetUniform4f(const std::string &name, float f0, float f1, float f2, float f3);
		void SetUniform1i(const std::string &name, int i);
};