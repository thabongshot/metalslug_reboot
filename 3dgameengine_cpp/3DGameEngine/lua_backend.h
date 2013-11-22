#ifndef _LUA_BACKEND_H_
#define _LUA_BACKEND_H_

extern "C"
{
#include "lua5.1\include\lua.h"
#include "lua5.1\include\lualib.h"
#include "lua5.1\include\lauxlib.h"
}

#include <assert.h>

static lua_State *L;

bool initLUAState();
void terminateLUAState();

void initLUAClasses();

void lua_exec(const char *script);
void lua_exec_update(const char *script);

// LUA Object

void LUA_registerObject(lua_State *L);

int LUA_constructorObject(lua_State *L);

int LUA_destructorObject(lua_State *L);

int LUA_objectSetTranslation(lua_State *L);

int LUA_objectSetRotation(lua_State *L);

int LUA_objectSetScale(lua_State *L);

int LUA_objectSpeak(lua_State *L);

int LUA_objectSetMesh(lua_State *L);

int LUA_findObject(lua_State *L);

int LUA_objectGetTranslation(lua_State *L);

int LUA_objectGetRotation(lua_State *L);

int LUA_objectGetScale(lua_State *L);

int LUA_objectMove(lua_State *L);

int LUA_objectRotate(lua_State *L);

// LUA Input

int LUA_isKeyDown(lua_State *L);

int LUA_isKeyReleased(lua_State *L);

#endif