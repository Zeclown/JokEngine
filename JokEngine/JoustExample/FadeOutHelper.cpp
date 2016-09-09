#include "FadeOutHelper.h"
#include "GameObject.h"
#include "Game.h"
void FadeOutHelper::Init()
{
	owner->Update.connect(boost::bind(&FadeOutHelper::Update, this));
	if (timeToFadeInSeconds == 0)
	{
		timeToFadeInSeconds = 1;
	}
	timer = timeToFadeInSeconds;
	sp = owner->GetComponent<SpriteDrawable>();
}

void FadeOutHelper::Update()
{
	if (timer >= 0)
	{
		timer -= Game::GetInstance().GetTimeService().GetDeltaTime();
		sp->color.w = timer / timeToFadeInSeconds;
	}
}
