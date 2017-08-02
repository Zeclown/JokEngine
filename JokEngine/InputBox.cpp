#include "InputBox.h"
#include "InputReader.h"
void InputBox::Init()
{
	signalConnections.push_back(InputReader::OnTextInput.connect(boost::bind(&InputBox::ReceiveInput, this, _1)));
	isReadingInput = true;
}

void InputBox::ReceiveInput(unsigned int input)
{
	if (isReadingInput)
	{
		if (maxCharacters <= text.size() && isTruncating)
		{
			text.erase(0,1);
		}
		if (maxCharacters > text.size())
		{
			wchar_t c = static_cast<wchar_t>(input);
			text += toupper(input);
		}
	}
}
