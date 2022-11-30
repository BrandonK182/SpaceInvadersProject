#pragma once

class Texture{
	private:
		unsigned int id;
	public:
		Texture(const char* filepath);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void unBind() const;
};