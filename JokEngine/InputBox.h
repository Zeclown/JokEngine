#pragma once
#include "TextUI.h"
class InputBox :public ComponentCloneable<TextUI,InputBox>
{
public:
	virtual void Init() override;
	void ReceiveInput(unsigned int input);
	int maxCharacters;
	bool isTruncating;
	bool isReadingInput;
};