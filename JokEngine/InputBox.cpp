#include "InputBox.h"
#include "InputReader.h"
void InputBox::Init()
{
	signalConnections.push_back(InputReader::OnTextInput.connect(boost::bind(&InputBox::ReceiveInput, this)));
	isReadingInput = true;
}

void InputBox::ReceiveInput(unsigned int input)
{
	if (isReadingInput)
	{
		if (maxCharacters > text.size() && isTruncating)
		{
			text.resize(maxCharacters-1);
		}
		if (maxCharacters < text.size())
		{
			wchar_t c = static_cast<wchar_t>(input);
			text += toupper(input);
		}
	}
}
