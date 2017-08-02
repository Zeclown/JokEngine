#include"TextUI.h"
void TextUI::DrawText(TextRenderingService &renderer)
{
	renderer.RenderText(text, position.x, position.y, scale, worldCoordinates,justify,color);
}