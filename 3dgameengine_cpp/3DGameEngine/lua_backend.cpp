#include "lua_backend.h"

#include "mymath.h"

#include "object.h"
#include "scene.h"

#include "input.h"

static Object* LUA_checkObject(lua_State *L, int index);

bool initLUAState()
{
	printf("Initializing LUA state...\n");

	L = luaL_newstate();
	luaL_openlibs(L);

	if(!L)
	{
		fprintf(stderr, "Error: Failed to initialize LUA state\n");
		return false;
	}

	printf("Successfully initialized LUA state...\n");

	initLUAClasses();
	
	return true;
}

void terminateLUAState()
{
	printf("Terminating LUA state...\n");

	lua_close(L);

	printf("Successfully terminated LUA state...\n");
}

void initLUAClasses()
{
	LUA_registerObject(L);

	lua_register(L, "isKeyDown", LUA_isKeyDown);
}

void lua_exec(const char *script)
{
	luaL_dofile(L, script);
}

void lua_exec_update(const char *script)
{
	luaL_dofile(L, script);

	lua_getglobal(L, "update");

	if(lua_isfunction(L, -1))
		lua_call(L, 0, 0);
}

void LUA_registerObject(lua_State *L)
{
	const struct luaL_Reg funcs[] =
	{
		{ "new", LUA_constructorObject },
		{ "find", LUA_findObject},
		{ "getTranslation", LUA_objectGetTranslation },
		{ "setTranslation", LUA_objectSetTranslation },
		{ "setRotation", LUA_objectSetRotation },
		{ "getRotation", LUA_objectGetRotation },
		{ "getScale", LUA_objectGetScale },
		{ "setScale", LUA_objectSetScale },
		{ "setMesh", LUA_objectSetMesh },
		{ "speak", LUA_objectSpeak },
		{ "destroy", LUA_destructorObject },
		{ NULL, NULL }
	};

	luaL_newmetatable(L, "LUAObject");
	luaL_register(L, 0, funcs);
	lua_pushvalue(L, -1);
	lua_setfield(L, -1, "__index");

	lua_setglobal(L, "Object");
}

int LUA_constructorObject(lua_State *L)
{
	Object **o = (Object**)lua_newuserdata(L, sizeof(Object*));

	const char *name = luaL_checkstring(L, 1);

	*o = new Object(name);

	Scene::addObject(name, *o);

	luaL_getmetatable(L, "LUAObject");

	lua_setmetatable(L, -2);

	return 1;
}

int LUA_destructorObject(lua_State *L)
{
	Object *o = LUA_checkObject(L, 1);
	delete o;

	return 0;
}

Object* LUA_checkObject(lua_State *L, int index)
{
	return *(Object**)luaL_checkudata(L, index, "LUAObject");
}

int LUA_objectGetTranslation(lua_State *L)
{
	Object *o = LUA_checkObject(L, 1);
	assert(o != 0);

	float x = o->getTransform()->getTranslation().x;
	float y = o->getTransform()->getTranslation().y;
	float z = o->getTransform()->getTranslation().z;

	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	lua_pushnumber(L, z);

	return 3;
}

int LUA_objectSetTranslation(lua_State *L)
{
	int n = lua_gettop(L);

	if (n == 4)
	{
		Object *o = LUA_checkObject(L, 1);
		assert(o != 0);

		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float z = (float)luaL_checknumber(L, 4);

		o->getTransform()->setTranslation(Vector3f(x, y, z));
	}
	else
		luaL_error(L, "invalid arguments in 'setTranslation' method");

	return 0;
}

int LUA_objectGetRotation(lua_State *L)
{
	Object *o = LUA_checkObject(L, 1);
	assert(o != 0);

	float x = o->getTransform()->getRotation().x;
	float y = o->getTransform()->getRotation().y;
	float z = o->getTransform()->getRotation().z;

	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	lua_pushnumber(L, z);

	return 3;
}

int LUA_objectSetRotation(lua_State *L)
{
	int n = lua_gettop(L);

	if (n == 4)
	{
		Object *o = LUA_checkObject(L, 1);
		assert(o != 0);

		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float z = (float)luaL_checknumber(L, 4);

		o->getTransform()->setRotation(Vector3f(x, y, z));
	}
	else
		luaL_error(L, "invalid arguments in 'setRotation' method");

	return 0;
}

int LUA_objectGetScale(lua_State *L)
{
	Object *o = LUA_checkObject(L, 1);
	assert(o != 0);

	float x = o->getTransform()->getScale().x;
	float y = o->getTransform()->getScale().y;
	float z = o->getTransform()->getScale().z;

	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	lua_pushnumber(L, z);

	return 3;
}

int LUA_objectSetScale(lua_State *L)
{
	int n = lua_gettop(L);

	if (n == 4)
	{
		Object *o = LUA_checkObject(L, 1);
		assert(o != 0);

		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float z = (float)luaL_checknumber(L, 4);

		o->getTransform()->setScale(Vector3f(x, y, z));
	}
	else
		luaL_error(L, "invalid arguments in 'setScale' method");

	return 0;
}

int LUA_objectSpeak(lua_State *L)
{
	int n = lua_gettop(L);

	if (n == 1)
	{
		Object *o = LUA_checkObject(L, 1);
		assert(o != 0);

		o->printObject();
	}
	else
		luaL_error(L, "invalid arguments in 'speak' method");

	return 0;
}

int LUA_objectSetMesh(lua_State *L)
{
	int n = lua_gettop(L);

	if (n == 2)
	{
		Object *o = LUA_checkObject(L, 1);
		assert(o != 0);

		const char *meshFile = luaL_checkstring(L, 2);

		o->setMesh(new Mesh(meshFile, NULL, PhongShader::getInstance()));
	}
	else
		luaL_error(L, "invalud arguments in 'setMesh' method");

	return 0;
}

int LUA_findObject(lua_State *L)
{
	const char *name = luaL_checkstring(L, 1);

	Object *o = Scene::getObject(name);

	if (!o)
	{
		fprintf(stderr, "Cannot find object '%s'.\n", name);

		return 0;
	}

	Object **result = (Object**)lua_newuserdata(L, sizeof(Object*));

	*result = o;
	
	luaL_getmetatable(L, "LUAObject");

	lua_setmetatable(L, -2);

	return 1;
}

int LUA_isKeyDown(lua_State *L)
{
	const char *queryKey = luaL_checkstring(L, 1);

	bool result = Input::isKeyDown(queryKey[0]);

	lua_pushboolean(L, result);

	return 1;
}

int LUA_isKeyReleased(lua_State *L)
{
	const char *queryKey = luaL_checkstring(L, 1);

	bool result = Input::isKeyReleased(queryKey[0]);

	lua_pushboolean(L, result);

	return 1;
}