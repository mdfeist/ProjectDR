#include "StdAfx.h"
#include "RenderManager.h"

#include "OpenGL.h"

#include <iostream>

#include "Actor.h"

RenderManager::RenderManager(void)
{
}

RenderManager::~RenderManager(void)
{
	actors.clear();
}

void RenderManager::initGL() {
	if ( glewInit() != GLEW_OK )						// Init GLEW
	{
		std::cout << "Failed to initialize GLEW." << std::endl;
		return;
	}

	if ( !glewIsSupported("GL_VERSION_1_5") && !glewIsSupported( "GL_ARB_vertex_buffer_object" ) )
	{
		std::cout << "- ARB_vertex_buffer_object not supported" << std::endl;
		return;
	}

	glewGetExtension("glMultiTexCoord2fvARB");  
	if(glewGetExtension("GL_EXT_framebuffer_object") ) std::cout << "- GL_EXT_framebuffer_object support " << std::endl;
	if(glewGetExtension("GL_EXT_renderbuffer_object")) std::cout << "- GL_EXT_renderbuffer_object support " << std::endl;
	if(glewGetExtension("GL_ARB_vertex_buffer_object")) std::cout << "- GL_ARB_vertex_buffer_object support" << std::endl;
	if(GL_ARB_multitexture) std::cout << "- GL_ARB_multitexture support " << std::endl;
	
	if (glewGetExtension("GL_ARB_fragment_shader")      != GL_TRUE ||
		glewGetExtension("GL_ARB_vertex_shader")        != GL_TRUE ||
		glewGetExtension("GL_ARB_shader_objects")       != GL_TRUE ||
		glewGetExtension("GL_ARB_shading_language_100") != GL_TRUE)
	{
		 std::cout << "- Driver does not support OpenGL Shading Language" << std::endl;
	}

	glEnable (GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(1.f, 0.f, 0.f, 0.f);					// Set Background Color
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glDisable(GL_LIGHTING);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
}

void RenderManager::addActor(Actor* actor) {
	actors.push_back(actor);
}

void RenderManager::removeActor(Actor* actor) {
	for (int i = actors.size() - 1; i >= 0; i--) { 
		if (actor->getID() == actors[i]->getID()) {
			actors.erase(actors.begin() + i);
		}
	}
}

void RenderManager::update() {
	for each (Actor* actor in actors)
		if (actor->needsInit())
			actor->init();
}

void RenderManager::render(Camera* camera) {
	for each (Actor* actor in actors)
		actor->render(camera);
}