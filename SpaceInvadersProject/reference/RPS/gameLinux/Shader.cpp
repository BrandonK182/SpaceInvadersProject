#include "Shader.h"
#include "Renderer.h"

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

Shader::Shader(const std::string &filepath):id(0){
	ShaderProgramSource source = ParseShader(filepath);
	id = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader(){
	glDeleteProgram(id);
}

ShaderProgramSource Shader::ParseShader(const std::string &filepath){
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while(getline(stream,line)){

		if (line.find("#shader") != std::string::npos){

			if(line.find("vertex") != std::string::npos)

				type = ShaderType::VERTEX;

			else if (line.find("fragment") != std::string::npos)

				type = ShaderType::FRAGMENT;

		}
		else{
			ss[(int)type] << line << "\n";
		}
	}
	return{
		ss[0].str(), ss[1].str()
	};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source){
	unsigned int id = glCreateShader(type);
	const char* src = &source[0];
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE){
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile!" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	
	return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader){
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	
	glDeleteShader(vs);
	glDeleteShader(fs);
	
	return program;
}

void Shader::Bind() const{
	glUseProgram(id);
}

void Shader::unBind() const{
	glUseProgram(0);
}

void Shader::SetUniform4f(const std::string &name, float f0, float f1, float f2, float f3){
	glUniform4f(GetUniformLocation(name), f0, f1, f2, f3);
}

void Shader::SetUniform1i(const std::string &name, int i){
	glUniform1i(GetUniformLocation(name), i);
}

int Shader::GetUniformLocation(const std::string &name){
	
	if(UniformLocationCache.find(name) != UniformLocationCache.end())
		return UniformLocationCache[name];

	int location = glGetUniformLocation(id, name.c_str());
	if(location == -1)
		std::cout << "Uniform " << name << " does not exist." << std::endl;
	
	UniformLocationCache[name] = location;
	return location;
}