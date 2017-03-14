#ifndef TEXTURE_H
#define TEXTURE_H

#include <map>
#include <string>
#include <GL/glew.h>

class Texture
{
	public:
		static Texture* load(const std::string pTexturePath);

		virtual ~Texture();

		GLuint getId();

		std::string getName();
		void setName(std::string replacement);

	protected:

		//all previously loaded meshes;
		static std::map<std::string, Texture*> _textures;
        static Texture* _loadFromFile(const std::string pTexturePath);

	    //OpenGL id for texture buffer
		GLuint _id;

		Texture();
	private:
		std::string _name;

};

#endif // TEXTURE_H
