#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "../Core/Window.h"
#include <math.h>
#include <iostream>

class TextInput
{
private:

public:
	void CharacterCallback(Window* window_, unsigned int keyCode_);
	void CharacterModCallback(Window* window_, unsigned int keyCode_, int modifierKey_);
	TextInput();
	~TextInput();
};

#endif // !TEXTINPUT_H
