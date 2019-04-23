#include "TextInput.h"



TextInput::TextInput() {

}


TextInput::~TextInput() {

}

void TextInput::CharacterCallback(Window* window_, unsigned int keyCode_) {
	std::cout << keyCode_ << std::endl;
}

void TextInput::CharacterModCallback(Window* window_, unsigned int keyCode_, int modifierKey_) {
	std::cout << keyCode_ << std::endl;

	if (modifierKey_ == 1) {
		std::cout << "Shift key is pressed" << std::endl;
	}
}
