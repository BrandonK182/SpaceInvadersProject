#include<SOIL/SOIL.h>
#include<string>
#include"Texture.h"
#include"Renderer.h"

Texture::Texture(const char* filepath){
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	int width, height;
	unsigned char* image =
    SOIL_load_image(filepath, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);


}


Texture::~Texture(){
	glDeleteTextures(1, &id);

}

void Texture::Bind(unsigned int slot) const{
	glActiveTexture(GL_TEXTURE0 + slot); 
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unBind() const{
	glBindTexture(GL_TEXTURE_2D, 0);
}