#pragma once

#include <glad/glad.h>

#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"

class Renderer{
	public:
		void Draw(const VertexArray &vArray, const IndexBuffer &iBuffer, const Shader &shader) const;
		void Clear() const;
};