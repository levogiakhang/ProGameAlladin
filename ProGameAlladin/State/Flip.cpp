﻿#include "Flip.h"
#include "../Aladdin.h"
#include "../Framework/Input.h"
#include "HeadUpAndSlash.h"
US_NS_JK


Flip::Flip(Node* node) :State(node)
{

}

Flip::~Flip()
{
}

void Flip::onEnter()
{
	const auto aladdin = static_cast<Aladdin*>(_node);
	aladdin->setVelocity(Vec2(0, -300));

	aladdin->setActionName("Flip");
}

State* Flip::checkTransition()
{
	const auto aladdin = static_cast<Aladdin*>(_node);

	if (aladdin->getisOnTheGround())
		return new Idle(_node);

	return nullptr;
}
