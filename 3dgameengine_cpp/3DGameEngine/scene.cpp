#include "scene.h"

#include "shader.h"
#include "input.h"
#include "transform.h"
#include "time.h"
#include "mainComponent.h"

#include "lua_backend.h"

#include <string.h>

Shader *shader;

Camera *camera;

Material *material;

std::vector<Object *> Scene::objects;

Scene::Scene()
{
	material = new Material(Texture("textures/blank_white.png"), Texture(), Vector3f(1, 1, 1), 2, 6);

	shader = PhongShader::getInstance();

	camera = new Camera();

	addObject("plane", new Object("plane", new Transform(Vector3f(0, -1, 5), Vector3f(0, 0, 0), Vector3f(10, 1, 10)), new Mesh("models/plane.obj", material, shader)));
	addObject("monkey", new Object("monkey", new Transform(Vector3f(3, 0, 5), Vector3f(0, 0, 0), Vector3f(1, 1, 1)), new Mesh("models/monkey_high.obj", material, shader)));
	addObject("bunny", new Object("bunny", new Transform(Vector3f(0, -1, 5), Vector3f(0, 0, 0), Vector3f(0.3f, 0.3f, 0.3f)), new Mesh("models/stanford_bunny.obj", material, shader)));

	Object *bunny = getObject("bunny");
	if (bunny)
		bunny->addComponent(new ScriptComponent(bunny, "scripts/test.lua"));

	//Transform::setOrthographicProjection(-1, 1, -1, 1, 0.1f, 1000.0f);
	Transform::setPerspectiveProjection(70, (float)glutGet(GLUT_WINDOW_WIDTH), (float)glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 1000.0f);
	Transform::setCamera(camera);

	PhongShader::setAmbientLight(Vector3f(0.2f, 0.2f, 0.2f));
	//PhongShader::setDirectionalLight(DirectionalLight(BaseLight(Vector3f(1, 1, 1), 0.2f), Vector3f(0, 1, -1)));

	PhongShader::setPointLight(0, PointLight(BaseLight(Vector3f(1, 0, 0), 0.8f), Vector3f(cosf(0.0f) * 2, 0, 5 + sinf(0.0f) * 2), 0, 0, 1, 40));
	PhongShader::setPointLight(1, PointLight(BaseLight(Vector3f(0, 1, 0), 0.8f), Vector3f(cosf(90.0f) * 2, 0, 5 + sinf(90.0f) * 2), 0, 0, 1, 40));
	PhongShader::setPointLight(2, PointLight(BaseLight(Vector3f(0, 0, 1), 0.8f), Vector3f(cosf(180.0f) * 2, 0, 5 + sinf(180.0f) * 2), 0, 0, 1, 40));

	//PhongShader::setSpotLight(0, SpotLight(PointLight(BaseLight(Vector3f(1, 1, 1), 0.8f), Vector3f(0, 0, 5), 0, 0, 1, 40), Vector3f(0, -1, 0), 0.7f));
}

void Scene::input()
{
	//camera->input();

	if(Input::isKeyReleased('q'))
		MainComponent::postMsg(MSG_QUIT);
}

void Scene::update()
{
	float amount = (float)Time::getTime() / 800.0f;

	PhongShader::getPointLight(0)->position = Vector3f(cosf(amount) * 2, 0, 5 + sinf(amount) * 2);
	PhongShader::getPointLight(1)->position = Vector3f(cosf(amount + 90.0f) * 2, 0, 5 + sinf(amount + 90.0f) * 2);
	PhongShader::getPointLight(2)->position = Vector3f(cosf(amount + 180.0f) * 2, 0, 5 + sinf(amount + 180.0f) * 2);

	for (unsigned int i = 0; i < objects.size(); i++)
	{
		Object *o = objects.at(i);

		if (o)
			o->update();
	}

	camera->setPosition(getObject("bunny")->getTransform()->getTranslation() + Vector3f(0, 1, -5));
}

void Scene::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (unsigned int i = 0; i < objects.size(); i++)
	{
		Object *o = objects.at(i);

		if (o)
			o->draw();
	}
}

void Scene::addObject(const char *name, Object *object)
{
	objects.push_back(object);
}

Object *Scene::getObject(const char *name)
{
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		Object *o = objects.at(i);

		const char *oName = o->getName();

		if (strcmp(o->getName(), name) == 0)
			return o;
	}

	return NULL;
}