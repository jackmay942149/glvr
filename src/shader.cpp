#include "shader.hpp"
#include "fstream"
#include "sstream"
#include "iostream"
#include "glad.h"

Shader::Shader(const char* vertexPath, const char* fragPath){
  std::string vertexCode;
  std::string fragCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  
  // ensure ifstream can throw exceptions
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  
  try {
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragPath);
    std::stringstream vShaderStream;
    std::stringstream fShaderStream;
  
    // read file buffer into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    // close files
    vShaderFile.close();
    fShaderFile.close();

    // convert stream to string
    vertexCode = vShaderStream.str();
    fragCode = fShaderStream.str();
  }
  catch(std::ifstream::failure e){
    std::cout << "ERROR (TODO:ErrorCode): Shader file not successfully read" << std::endl;
  }

  const char* vertexShaderSrc = vertexCode.c_str();
  const char* fragmentShaderSrc = fragCode.c_str();
 
	// Compile Shaders
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	
	// Check Shader Compilation
	int success;
	char infoLog[512];
	glCompileShader(vertexShader);
	
	// -- Vertex Checking ERROR_S1
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR_S1: Vertex Shader Compilation Failed\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	// -- Frag Checking ERROR_S2
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR_S2: Fragment Shader Compilation Failed\n" << infoLog << std::endl;
	}
	
	// -- Shader Program
	uid = glCreateProgram();
	glAttachShader(uid, vertexShader);
	glAttachShader(uid, fragmentShader);
	glLinkProgram(uid);

	// Checker Shader Program Linking
	glGetProgramiv(uid, GL_LINK_STATUS, &success);
	if (!success) {
		glad_glGetProgramInfoLog(uid, 512, NULL, infoLog);
		std::cout << "ERROR_S3: Shader Linking Failed\n" << infoLog << std::endl;
	}

	// Link Shader and Free Resources
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use(){
  glUseProgram(uid);
}

void Shader::setBool(const std::string& name, bool value){
  glUniform1i(glGetUniformLocation(uid, name.c_str()), (int) value);
}

void Shader::setInt(const std::string& name, int value){
  glUniform1i(glGetUniformLocation(uid, name.c_str()), value);
  
}

void Shader::setFloat(const std::string& name, float value){
  glUniform1f(glGetUniformLocation(uid, name.c_str()), value);
  
}

void Shader::setVec2(const std::string& name, float x, float y){
  glUniform2f(glGetUniformLocation(uid, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, float x, float y, float z){
  glUniform3f(glGetUniformLocation(uid, name.c_str()), x, y, z);
}
