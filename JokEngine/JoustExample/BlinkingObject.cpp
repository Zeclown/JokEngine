#include "BlinkingObject.h"
#include "Game.h"
#include "SpriteRenderer.h"
#include "TextUI.h"
void BlinkingObject::Init()
{
	owner->Update.connect(boost::bind(&BlinkingObject::Update,this));
	if (!ui)
	{
		displayComponent = (Component*)owner->GetComponent<SpriteRenderer>();
	}
	else
		displayComponent= (Component*)owner->GetComponent<TextUI>();
}

void BlinkingObject::Update()
{
	if (displayComponent)
	{
		timer -= Game::GetInstance().GetTimeService().GetDeltaTime();
		if (timer < 0)
		{
			blinking = !blinking;
			timer = secondsBeforeBlinks;
			if (blinking)
			{
				displayComponent->enabled = false;
			}
			else
			{
				displayComponent->enabled = true;
			}
		}
	}
}
