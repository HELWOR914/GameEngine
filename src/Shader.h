#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include <glm/glm.hpp>

class Shader
{
private:
GLuint shaderID;

public:
	
	~Shader()
	{
		glDeleteProgram(shaderID);
	}
	
	void CreateFast(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		Create();
		Add(vertexShaderPath, GL_VERTEX_SHADER);
		Add(fragmentShaderPath, GL_FRAGMENT_SHADER);
		LinkProgramm();
	}

	void Create()
	{
		shaderID = glCreateProgram();
		if(!shaderID)
		{
			std::cerr << "failed to create SHADER program" << std::endl;
			return;
		}
	}
	
	void Add(const char* path, GLenum shaderType)
	{
		//========reading file========
		const char* code;
		std::string str;
		std::ifstream file(path);
		if(file.is_open())
		{
			std::ostringstream ss;
			
			ss << file.rdbuf();
			str = ss.str();
			
			file.close();
			code = str.c_str();
		}
		else
		{
			std::cerr << "failed to open shader file: " << path << std::endl;
			return;
		}
		//============================
		
		
		GLuint sh = glCreateShader(shaderType);
		
		glShaderSource(sh, 1, &code, nullptr);
	
		glCompileShader(sh);
		
		
		//=========Error log==========
		GLint res = 0;
		GLchar ErrLog[512];
		
		glGetShaderiv(sh, GL_COMPILE_STATUS, &res);
		
		if(!res)
		{
			glGetShaderInfoLog(sh, sizeof(ErrLog), nullptr, ErrLog);
			std::cout << ErrLog << std::endl;
			return;
		}
		//============================
		glAttachShader(shaderID, sh);
		glDeleteShader(sh);
	}
	
	void LinkProgramm()
	{
		glLinkProgram(shaderID);
		
		//=========Error log==========
		GLint res;
		GLchar ErrLog[512];
		
		glGetProgramiv(shaderID, GL_LINK_STATUS, &res);
		if(!res)
		{
			glGetProgramInfoLog(shaderID, sizeof(ErrLog), nullptr, ErrLog);
			std::cout << ErrLog << std::endl;
			return;
		}
		//============================
		
		glValidateProgram(shaderID);
		glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &res);
		
		//=========Error log==========
		if(!res)
		{
			glGetProgramInfoLog(shaderID, sizeof(ErrLog), nullptr, ErrLog);
			std::cout << ErrLog << std::endl;
			return;
		}
		//============================
	}
	
	inline void Use()
	{
		glUseProgram(shaderID);
	}
	
	inline void SetBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
    }
	
    inline void SetInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
    }
	
    inline void SetFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
    }
	
    inline void SetVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value.x);
    }
	
    inline void SetVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);
    }
	
    inline void SetVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value.x);
    }
	
    inline void SetVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);
    }
	
    inline void SetVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value.x);
    }
	
    inline void SetVec4(const std::string& name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);
    }
	
    inline void SetMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0].x);
    }
	
    inline void SetMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0].x);
    }
	
    inline void SetMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0].x);
    }
};