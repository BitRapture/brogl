#ifndef _TEXTURING_H_
#define _TEXTURING_H_

#include "../../brogl/brogl.h"
#include "../example.h"

struct texturing : public example
{
private: 
	bro::vbo vertices, texCoords, inds;
	bro::vao quad;
	bro::shaderprogram shader;
	std::vector<GLuint> indices;
	bro::texture quadTex;

	float angle{ 0 };

public:
	// Polymorphic example run override
	void example::Run(SDL_Window* _window) override;

	// Instantiation
	texturing();
	~texturing();
};

#endif // !_TEXTURING_H_
