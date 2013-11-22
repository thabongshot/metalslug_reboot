#ifndef _RENDERUTIL_H_
#define _RENDERUTIL_H_

#define WIDTH 800
#define HEIGHT 600
#define TITLE "3D Engine"

#define FRAME_CAP 60.0

void initFXAA();

void setFXAAEnabled(bool value);

void prepareRender();

void postRender();

void initGraphics();

void unbindTextures();

#endif