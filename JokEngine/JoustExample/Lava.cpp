#include "Lava.h"
#include "GameObject.h"
#include "EnemyEgg.h"
#include "Knight.h"
Lava::Lava(GameObject * go)
	:ComponentCloneable(go)
{

}

Lava::~Lava()
{
}

void Lava::Init()
{
	signalConnections.push_back(owner->OnCollisionEnter.connect(boost::bind(&Lava::OnCollisionEnter, this, _1)));
}

void Lava::Update()
{
}

void Lava::OnCollisionEnter(Collision col)
{
	EnemyEgg* PossibleEgg = col.gameObject->GetComponent<EnemyEgg>();
	Knight* PossibleKnight = col.gameObject->GetComponent<Knight>();
	if (PossibleEgg)
	{
		PossibleEgg->Die();
	}
	else if (PossibleKnight)
	{
		PossibleKnight->TakeDamage(GetOwner());
	}
}
