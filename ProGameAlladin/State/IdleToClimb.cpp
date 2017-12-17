﻿#include "IdleToClimb.h"
#include "../GameObject/Aladdin.h"
#include "../Framework/Input.h"
#include "Climb.h"
#include "SlashWhenClimb.h"
#include "JumpWhileClimb.h"
#include "ThrowWhenClimb.h"
US_NS_JK

IdleToClimb::IdleToClimb(Node* node):State(node)
{
}

IdleToClimb::~IdleToClimb()
{
}

void IdleToClimb::onEnter()
{
	auto aladdin = static_cast<Aladdin*>(_node);
	aladdin->setActionName("IdleToClimb");

	aladdin->getRigidBody()->setGravityScale(0);
	aladdin->setVelocity(Vec2(0, 0));

}

void IdleToClimb::onUpdate()
{
	const auto aladdin = static_cast<Aladdin*>(_node);

	if (Input::getInstance()->getKey(KEY_LEFT_ARROW))
	{
		aladdin->setScale(Vec2(1, 1));
		aladdin->setVelocity(Vec2(0, 0));
	}
		
	if (Input::getInstance()->getKey(KEY_RIGHT_ARROW))
	{
		aladdin->setScale(Vec2(-1, 1));
		aladdin->setVelocity(Vec2(0, 0));
	}
		
	if (Input::getInstance()->getKey(KEY_D) && Input::getInstance()->getKey(KEY_LEFT_ARROW))
	{
		aladdin->getRigidBody()->setGravityScale(1);
		aladdin->setVelocity(Vec2(-100, aladdin->getVelocity().getY()));
	}
	if (Input::getInstance()->getKey(KEY_D) && Input::getInstance()->getKey(KEY_RIGHT_ARROW))
	{
		aladdin->getRigidBody()->setGravityScale(1);
		aladdin->setVelocity(Vec2(100, aladdin->getVelocity().getY()));
	}




}

State* JaKa::IdleToClimb::checkTransition()
{
	auto aladdin = static_cast<Aladdin*>(_node);
	if (Input::getInstance()->getKey(KEY_D))
		return new JumpWhileClimb(_node);
	if (Input::getInstance()->isKeyDown(KEY_S))
		return new SlashWhenClimb(_node);
	if (Input::getInstance()->getKey(KEY_A))
		return new ThrowWhenClimb(_node);
	if (Input::getInstance()->getKey(KEY_UP_ARROW))
		return new Climb(_node);
	if (Input::getInstance()->getKey(KEY_DOWN_ARROW))
		return new Climb(_node);
	
	return nullptr;
}