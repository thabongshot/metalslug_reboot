#define _CRT_SECURE_NO_WARNINGS

#include "glew-1.10.0\include\GL\glew.h"

#include "shader.h"

#include "renderUtil.h"
#include "transform.h"

#include <limits.h>
#include <string.h>

// Shader Class

Shader::Shader()
{
	program = glCreateProgram();

	if(program == 0)
	{
		fprintf(stderr, "Error: Cannot create a shader program\n");
		getchar();
		exit(1);
	}
}

std::string Shader::loadShader(std::string fileName)
{
	std::fstream file;
	std::string result;
	file.open(fileName, std::ios::in);

	if(!file.good())
	{
		fprintf(stderr, "Error: Cannot open file '%s'. Check if it's in the appropriate directory\n", fileName.c_str());
		getchar();
		exit(1);
	}

	while(!file.eof())
	{
		std::string tmp;

		std::getline(file, tmp);

		tmp.append("\n");

		result.append(tmp);
	}

	return result;
}

void Shader::bind()
{
	glUseProgram(program);
}

void Shader::addVertexShaderFromFile(std::string text)
{
	addProgram(loadShader(text), GL_VERTEX_SHADER);
}

void Shader::addGeometryShaderFromFile(std::string text)
{
	addProgram(loadShader(text), GL_GEOMETRY_SHADER);
}

void Shader::addFragmentShaderFromFile(std::string text)
{
	addProgram(loadShader(text), GL_FRAGMENT_SHADER);
}

void Shader::addTessControlShaderFromFile(std::string text)
{
	addProgram(loadShader(text), GL_TESS_CONTROL_SHADER);
}

void Shader::addTessEvalShaderFromFile(std::string text)
{
	addProgram(loadShader(text), GL_TESS_EVALUATION_SHADER);
}

void Shader::addVertexShader(std::string text)
{
	addProgram(text, GL_VERTEX_SHADER);
}

void Shader::addGeometryShader(std::string text)
{
	addProgram(text, GL_GEOMETRY_SHADER);
}

void Shader::addFragmentShader(std::string text)
{
	addProgram(text, GL_FRAGMENT_SHADER);
}

void Shader::addTessControlShader(std::string text)
{
	addProgram(text, GL_TESS_CONTROL_SHADER);
}

void Shader::addTessEvalShader(std::string text)
{
	addProgram(text, GL_TESS_EVALUATION_SHADER);
}

void Shader::compileShader()
{
	glLinkProgram(program);

	int programLinkState;
	glGetProgramiv(program, GL_LINK_STATUS, &programLinkState);
	
	if(programLinkState == 0)
	{
		char infoLog[1024];
		int logLength = strlen(infoLog);

		glGetProgramInfoLog(program, 1, &logLength, infoLog);
		fprintf(stderr, "Error: '%s'\n", infoLog);
		getchar();
		exit(1);
	}

	glValidateProgram(program);

	int programValidationState;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &programValidationState);

	if(programValidationState == 0)
	{
		char infoLog[1024];
		int logLength = strlen(infoLog);

		glGetProgramInfoLog(program, 1, &logLength, infoLog);
		fprintf(stderr, "Error: '%s'\n", infoLog);
		getchar();
		exit(1);
	}
}

void Shader::addProgram(std::string text, int type)
{
	int shader = glCreateShader(type);

	if(shader == 0)
	{
		fprintf(stderr, "Error: Cannot create shader\n");
		getchar();
		exit(1);
	}

	const char *text_char = text.c_str();
	int text_length = text.length();

	glShaderSource(shader, 1, &text_char, &text_length);
	glCompileShader(shader);

	int shaderCompileState;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompileState);

	if(shaderCompileState == 0)
	{
		char infoLog[1024];
		int logLength = strlen(infoLog);

		glGetShaderInfoLog(shader, 1, &logLength, infoLog);
		fprintf(stderr, "Error: '%s'\n", infoLog);
		getchar();
		exit(1);
	}

	glAttachShader(program, shader);
}

int Shader::getUniformLocation(const char* uniform)
{
	int location = glGetUniformLocation(program, uniform);

	if(location == 0xFFFFFFFF)
	{
		fprintf(stderr, "Error: Cannot find uniform '%s'\n", uniform);
		getchar();
		exit(1);
	}

	return location;
}

// ------------------------------------------------------------------------------------- //

// Basic Shader Class

BasicShader *BasicShader::pInstance;

BasicShader::BasicShader() : Shader()
{
	addVertexShaderFromFile("shaders/basicVertex.vs");
	addFragmentShaderFromFile("shaders/basicFragment.vfs");
	compileShader();

	u_transform = getUniformLocation("transform");
	u_color = getUniformLocation("color");
	u_sampler = getUniformLocation("sampler");
}

BasicShader *BasicShader::getInstance()
{
	if(!pInstance)
		pInstance = new BasicShader();

	return pInstance;
}

void BasicShader::updateUniforms(Matrix4f worldMatrix, Matrix4f projectedMatrix, Material *material)
{
	if(material->getTexture())
		material->getTexture()->bind();
	else
		unbindTextures();
	
	glUniform1f(u_sampler, 0);

	glUniformMatrix4fv(u_transform, 1, GL_TRUE, &projectedMatrix.m[0][0]);
	glUniform3f(u_color, material->getColor().x, material->getColor().y, material->getColor().z);
}

// ------------------------------------------------------------------------------------------------------ //

// Phong Shader Class

PhongShader *PhongShader::pInstance;
Vector3f PhongShader::ambientLight;
DirectionalLight PhongShader::directionalLight;
PointLight PhongShader::pointLights[MAX_POINT_LIGHTS];
SpotLight PhongShader::spotLights[MAX_SPOT_LIGHTS];

PhongShader::PhongShader() : Shader()
{
	addVertexShaderFromFile("shaders/phongVertex.vs");
	addFragmentShaderFromFile("shaders/phongFragment.vfs");
	//addTessControlShaderFromFile("shaders/tessControl.tcs");
	//addTessEvalShaderFromFile("shaders/tessEval.tes");
	compileShader();

	u_directionalLight.u_baseLight.u_color = getUniformLocation("directionalLight.Base.Color");
	u_directionalLight.u_baseLight.u_intensity = getUniformLocation("directionalLight.Base.Intensity");
	u_directionalLight.u_direction = getUniformLocation("directionalLight.Direction");

	for(int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char name[128];
		memset(name, 0, sizeof(name));

		_snprintf(name, sizeof(name), "pointLights[%d].Base.Color", i);
		u_pointLight[i].u_baseLight.u_color = getUniformLocation(name);
		_snprintf(name, sizeof(name), "pointLights[%d].Base.Intensity", i);
		u_pointLight[i].u_baseLight.u_intensity = getUniformLocation(name);

		_snprintf(name, sizeof(name), "pointLights[%d].Atten.Constant", i);
		u_pointLight[i].u_attenuation.u_constant= getUniformLocation(name);
		_snprintf(name, sizeof(name), "pointLights[%d].Atten.Linear", i);
		u_pointLight[i].u_attenuation.u_linear = getUniformLocation(name);
		_snprintf(name, sizeof(name), "pointLights[%d].Atten.Exponent", i);
		u_pointLight[i].u_attenuation.u_exponent = getUniformLocation(name);

		_snprintf(name, sizeof(name), "pointLights[%d].Position", i);
		u_pointLight[i].u_position = getUniformLocation(name);

		_snprintf(name, sizeof(name), "pointLights[%d].Range", i);
		u_pointLight[i].u_range = getUniformLocation(name);
	}

	for(int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		char name[128];
		memset(name, 0, sizeof(name));

		_snprintf(name, sizeof(name), "spotLights[%d].PointLight.Base.Color", i);
		u_spotLight[i].u_pointLight.u_baseLight.u_color = getUniformLocation(name);
		_snprintf(name, sizeof(name), "spotLights[%d].PointLight.Base.Intensity", i);
		u_spotLight[i].u_pointLight.u_baseLight.u_intensity = getUniformLocation(name);

		_snprintf(name, sizeof(name), "spotLights[%d].PointLight.Atten.Constant", i);
		u_spotLight[i].u_pointLight.u_attenuation.u_constant = getUniformLocation(name);
		_snprintf(name, sizeof(name), "spotLights[%d].PointLight.Atten.Linear", i);
		u_spotLight[i].u_pointLight.u_attenuation.u_linear = getUniformLocation(name);
		_snprintf(name, sizeof(name), "spotLights[%d].PointLight.Atten.Exponent", i);
		u_spotLight[i].u_pointLight.u_attenuation.u_exponent = getUniformLocation(name);

		_snprintf(name, sizeof(name), "spotLights[%d].PointLight.Position", i);
		u_spotLight[i].u_pointLight.u_position = getUniformLocation(name);

		_snprintf(name, sizeof(name), "spotLights[%d].PointLight.Range", i);
		u_spotLight[i].u_pointLight.u_range = getUniformLocation(name);

		_snprintf(name, sizeof(name), "spotLights[%d].Direction", i);
		u_spotLight[i].u_direction = getUniformLocation(name);

		_snprintf(name, sizeof(name), "spotLights[%d].Cutoff", i);
		u_spotLight[i].u_cutOff = getUniformLocation(name);
	}

	u_transform = getUniformLocation("transform");
	u_transformProjected = getUniformLocation("transformProjected");
	u_baseColor = getUniformLocation("baseColor");

	u_ambientLight = getUniformLocation("ambientLight");

	u_eyePos = getUniformLocation("eyePos");
	u_specularIntensity = getUniformLocation("specularIntensity");
	u_specularPower = getUniformLocation("specularPower");

	//u_tess_eyeWorldPos = getUniformLocation("tessEyeWorldPos");

	u_sampler = getUniformLocation("sampler");
}

PhongShader *PhongShader::getInstance()
{
	if(!pInstance)
		pInstance = new PhongShader();

	return pInstance;
}

void PhongShader::setAmbientLight(Vector3f ambientLight)
{
	PhongShader::ambientLight = ambientLight;
}

void PhongShader::setDirectionalLight(DirectionalLight directionalLight)
{
	PhongShader::directionalLight = directionalLight;
}

void PhongShader::setPointLight(unsigned int location, PointLight pointLight)
{
	if(location >= MAX_POINT_LIGHTS)
	{
		fprintf(stderr, "Error: Invalid point light initialization location\n");
		getchar();
		exit(1);
	}

	pointLights[location] = pointLight;
}

void PhongShader::setSpotLight(unsigned int location, SpotLight spotLight)
{
	if(location >= MAX_POINT_LIGHTS)
	{
		fprintf(stderr, "Error: Invalid point light initialization location\n");
		getchar();
		exit(1);
	}

	spotLights[location] = spotLight;
}

Vector3f PhongShader::getAmbientLight()
{
	return ambientLight;
}

DirectionalLight *PhongShader::getDirectionalLight()
{
	return &directionalLight;
}

PointLight *PhongShader::getPointLight(unsigned int location)
{
	if(location >= MAX_POINT_LIGHTS)
	{
		fprintf(stderr, "Error: Invalid point light initialization location\n");
		getchar();
		exit(1);
	}

	return &pointLights[location];
}

SpotLight *PhongShader::getSpotLight(unsigned int location)
{
	if(location >= MAX_POINT_LIGHTS)
	{
		fprintf(stderr, "Error: Invalid point light initialization location\n");
		getchar();
		exit(1);
	}

	return &spotLights[location];
}

void PhongShader::updateUniforms(Matrix4f worldMatrix, Matrix4f projectedMatrix, Material *material)
{
	if(material->getTexture())
		material->getTexture()->bind();
	else
		unbindTextures();

	glUniform1i(u_sampler, 0);

	glUniformMatrix4fv(u_transform, 1, GL_TRUE, &worldMatrix.m[0][0]);
	glUniformMatrix4fv(u_transformProjected, 1, GL_TRUE, &projectedMatrix.m[0][0]);
	glUniform3f(u_baseColor, material->getColor().x, material->getColor().y, material->getColor().z);

	glUniform3f(u_ambientLight, ambientLight.x, ambientLight.y, ambientLight.z);

	glUniform3f(u_directionalLight.u_baseLight.u_color, directionalLight.baseLight.color.x, directionalLight.baseLight.color.y, directionalLight.baseLight.color.z);
	glUniform1f(u_directionalLight.u_baseLight.u_intensity, directionalLight.baseLight.intensity);
	glUniform3f(u_directionalLight.u_direction, directionalLight.direction.x, directionalLight.direction.y, directionalLight.direction.z);

	for(int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		glUniform3f(u_pointLight[i].u_baseLight.u_color, pointLights[i].baseLight.color.x, pointLights[i].baseLight.color.y, pointLights[i].baseLight.color.z);
		glUniform1f(u_pointLight[i].u_baseLight.u_intensity, pointLights[i].baseLight.intensity);
		glUniform3f(u_pointLight[i].u_position, pointLights[i].position.x, pointLights[i].position.y, pointLights[i].position.z);
		glUniform1f(u_pointLight[i].u_attenuation.u_constant, pointLights[i].attenuation.constant);
		glUniform1f(u_pointLight[i].u_attenuation.u_linear, pointLights[i].attenuation.linear);
		glUniform1f(u_pointLight[i].u_attenuation.u_exponent, pointLights[i].attenuation.exponent);
		glUniform1f(u_pointLight[i].u_range, pointLights[i].range);
	}

	for(int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		glUniform3f(u_spotLight[i].u_pointLight.u_baseLight.u_color, spotLights[i].pointLight.baseLight.color.x, spotLights[i].pointLight.baseLight.color.y, spotLights[i].pointLight.baseLight.color.z);
		glUniform1f(u_spotLight[i].u_pointLight.u_baseLight.u_intensity, spotLights[i].pointLight.baseLight.intensity);
		glUniform3f(u_spotLight[i].u_pointLight.u_position, spotLights[i].pointLight.position.x, spotLights[i].pointLight.position.y, spotLights[i].pointLight.position.z);
		glUniform1f(u_spotLight[i].u_pointLight.u_attenuation.u_constant, spotLights[i].pointLight.attenuation.constant);
		glUniform1f(u_spotLight[i].u_pointLight.u_attenuation.u_linear, spotLights[i].pointLight.attenuation.linear);
		glUniform1f(u_spotLight[i].u_pointLight.u_attenuation.u_exponent, spotLights[i].pointLight.attenuation.exponent);
		glUniform1f(u_spotLight[i].u_pointLight.u_range, spotLights[i].pointLight.range);
		glUniform3f(u_spotLight[i].u_direction, spotLights[i].direction.x, spotLights[i].direction.y, spotLights[i].direction.z);
		glUniform1f(u_spotLight[i].u_cutOff, spotLights[i].cutOff);
	}

	Vector3f camPos = Transform::getCamera()->getPosition();
	glUniform3f(u_eyePos, camPos.x, camPos.y, camPos.z);
	glUniform1f(u_specularIntensity, material->getSpecularIntensity());
	glUniform1f(u_specularPower, material->getSpecularPower());
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- //