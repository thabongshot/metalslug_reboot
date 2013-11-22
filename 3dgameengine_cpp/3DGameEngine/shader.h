#ifndef _SHADER_H_
#define _SHADER_H_

#include "glew-1.10.0\include\GL\glew.h"

#include <fstream>
#include <sstream>

#include "mymath.h"
#include "material.h"

#include "lights.h"

class Shader
{
private:
	int program;

	static std::string loadShader(std::string fileName);

	void addProgram(std::string text, int type);

public:
	Shader();

	void bind();

	void addVertexShaderFromFile(std::string text);
	void addGeometryShaderFromFile(std::string text);
	void addFragmentShaderFromFile(std::string text);
	void addTessControlShaderFromFile(std::string text);
	void addTessEvalShaderFromFile(std::string text);

	void addVertexShader(std::string text);
	void addGeometryShader(std::string text);
	void addFragmentShader(std::string text);
	void addTessControlShader(std::string text);
	void addTessEvalShader(std::string text);

	void compileShader();

	int getUniformLocation(const char* uniform);

	virtual void updateUniforms(Matrix4f worldMatrix, Matrix4f projectedMatrix, Material *material)
	{

	}
};

class BasicShader : public Shader
{
private:
	static BasicShader *pInstance;

	int u_transform;
	int u_color;
	int u_sampler;

	BasicShader();

public:
	static BasicShader *getInstance();

	virtual void updateUniforms(Matrix4f worldMatrix, Matrix4f projectedMatrix, Material *material);
};

#define MAX_POINT_LIGHTS 4
#define MAX_SPOT_LIGHTS 4

class PhongShader : public Shader
{
private:
	static PhongShader *pInstance;

	static DirectionalLight directionalLight;
	static PointLight pointLights[MAX_POINT_LIGHTS];
	static SpotLight spotLights[MAX_SPOT_LIGHTS];
	static Vector3f ambientLight;

	struct 
	{
		struct
		{
			int u_color;
			int u_intensity;

		}u_baseLight;

		int u_direction;

	}u_directionalLight;

	struct
	{
		struct
		{
			int u_color;
			int u_intensity;

		}u_baseLight;

		int u_position;

		struct
		{
			int u_constant;
			int u_linear;
			int u_exponent;

		}u_attenuation;

		int u_range;

	}u_pointLight[MAX_POINT_LIGHTS];

	struct
	{
		struct
		{
			struct
			{
				int u_color;
				int u_intensity;

			}u_baseLight;

			int u_position;

			struct
			{
				int u_constant;
				int u_linear;
				int u_exponent;

			}u_attenuation;

			int u_range;

		}u_pointLight;

		int u_direction;

		int u_cutOff;

	}u_spotLight[MAX_SPOT_LIGHTS];

	int u_transform;
	int u_transformProjected;

	int u_baseColor;

	int u_ambientLight;
	
	int u_eyePos;
	int u_specularIntensity;
	int u_specularPower;

	//int u_tess_eyeWorldPos;

	int u_sampler;

	PhongShader();

public:
	static PhongShader *getInstance();

	static void setAmbientLight(Vector3f ambientLight);

	static void setDirectionalLight(DirectionalLight directionalLight);

	static void setPointLight(unsigned int location, PointLight pointLight);

	static void setSpotLight(unsigned int location, SpotLight spotLight);

	static Vector3f getAmbientLight();

	static DirectionalLight *getDirectionalLight();

	static PointLight *getPointLight(unsigned int location);

	static SpotLight *getSpotLight(unsigned int location);

	virtual void updateUniforms(Matrix4f worldMatrix, Matrix4f projectedMatrix, Material *material);
};

#endif