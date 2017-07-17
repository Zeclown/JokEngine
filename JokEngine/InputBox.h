#pragma once
#include "TextUI.h"
class InputBox :public ComponentCloneable<TextUI,InputBox>
{
	using ComponentCloneable<TextUI, InputBox>::ComponentCloneable;
public:
	virtual void Init() override;
	void ReceiveInput(unsigned int input);
	int maxCharacters;
	bool isTruncating;
	bool isReadingInput;
};