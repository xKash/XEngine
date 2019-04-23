#include "TextureHandler.h"

std::unique_ptr<TextureHandler> TextureHandler::TextureHandlerInstance = nullptr;
std::map<std::string, Texture*> TextureHandler::textures = std::map<std::string, Texture*>();

TextureHandler::TextureHandler()
{
}


TextureHandler::~TextureHandler() {

	if (textures.size() > 0) {
		for (auto t : textures) {
			glDeleteTextures(sizeof(GLuint), &t.second->textureId);
			delete t.second;
			t.second = nullptr;
		}
		textures.clear();
	}	
}

TextureHandler * TextureHandler::GetInstance() {

	if (TextureHandlerInstance.get() == nullptr) {
		TextureHandlerInstance.reset(new TextureHandler);
	}
	return TextureHandlerInstance.get();
}

void TextureHandler::CreateTexture(const std::string & textureName_, const std::string & textureFileName_) {

	Texture* t = new Texture();
	SDL_Surface* surface = nullptr;

	try	{
		surface = IMG_Load(textureFileName_.c_str());
	}
	catch (const std::exception e)	{
		Debug::Error("Texture" + textureName_ + " failed to load", __FILE__, __LINE__);
		return;
	}
	if (surface == nullptr) {
		Debug::Error("Surface for texture " + textureName_ + " failed to create ", __FILE__, __LINE__);
		return;
	}

	t->width = surface->w;
	t->height = surface->h;

	glGenTextures(1, &t->textureId);
	glBindTexture(GL_TEXTURE_2D, t->textureId);
	int mode = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	   
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	

	textures[textureName_] = t;

	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(surface);
	surface = nullptr;
}

GLuint TextureHandler::GetTexture(const std::string & textureName_) {

	if (textures.find(textureName_.c_str()) != textures.end()) {
		return textures[textureName_]->textureId;
	}

	return 0;	
}

const Texture * TextureHandler::GetTextureData(const std::string & textureName_)
{
	if (textures.find(textureName_.c_str()) != textures.end()) {
		return textures[textureName_];
	}

	return 0;
}
