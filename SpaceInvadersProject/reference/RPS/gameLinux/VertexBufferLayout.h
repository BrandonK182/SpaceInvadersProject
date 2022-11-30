#pragma once

#include <vector>
#include "Renderer.h"


struct VertexBufferElement{
	unsigned int type;
	unsigned int i;
	unsigned char normal;

	static unsigned int sizeofType(unsigned int type){
		switch(type){
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}
};

class VertexBufferLayout{
	private:
		std::vector<VertexBufferElement> elements;
		unsigned int stride;
	public:
		VertexBufferLayout():stride(0){

		}

		template<typename T>
		void Push(unsigned int i){
			static_assert(sizeof(T) == 0); 
		}

		inline const std::vector<VertexBufferElement> GetElements() const& {return elements;}
		inline unsigned int GetStride() const {return stride;}

};

		template<> inline void VertexBufferLayout::Push<float>(unsigned int i){
			elements.push_back({GL_FLOAT, i, GL_FALSE});
			stride += i * VertexBufferElement::sizeofType(GL_FLOAT);
		}

		template<> inline void VertexBufferLayout::Push<unsigned int>(unsigned int i){
			elements.push_back({GL_UNSIGNED_INT, i, GL_FALSE});
			stride += i *VertexBufferElement::sizeofType(GL_UNSIGNED_INT);
		}

		template<> inline void VertexBufferLayout::Push<char>(unsigned int i){
			elements.push_back({GL_UNSIGNED_BYTE, i, GL_TRUE});
			stride += i * VertexBufferElement::sizeofType(GL_UNSIGNED_BYTE);
		}