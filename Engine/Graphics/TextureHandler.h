#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <memory>
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <glew.h>
#include "../Core/Debug.h"

struct Texture {
	GLuint textureId = 0;
	int width = 0;
	int height = 0;
};

class TextureHandler
{
public:
	static TextureHandler* GetInstance();

	// Make impossible do instantiate this class
	TextureHandler(const TextureHandler&) = delete;
	TextureHandler(TextureHandler&&) = delete;
	TextureHandler& operator=(const TextureHandler&) = delete;
	TextureHandler& operator=(TextureHandler&&) = delete;

	void CreateTexture(const std::string& textureName_, const std::string & textureFileName_);
	static GLuint GetTexture(const std::string& textureName_);
	static const Texture* GetTextureData(const std::string& textureName_);

private:
	TextureHandler();
	~TextureHandler();

	static std::unique_ptr<TextureHandler> TextureHandlerInstance;
	friend std::default_delete<TextureHandler>;

	static std::map<std::string, Texture*> textures;    
};
#endif // !TEXTUREHANDLER_H




