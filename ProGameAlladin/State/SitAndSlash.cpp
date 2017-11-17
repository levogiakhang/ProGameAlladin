﻿#include "SitAndSlash.h"
#include "../Framework/Input.h"
#include "SitAndThrow.h"
#include "Jump.h"
#include "../Aladdin.h"
US_NS_JK

SitAndSlash::SitAndSlash(Node* node):State(node)
{
}

SitAndSlash::~SitAndSlash()
{
}

void SitAndSlash::onEnter()
{
	// TODO: setScale()
	// TODO: loadAnimation()
	auto aladdin = static_cast<Aladdin*>(_node);

	if (Input::getInstance()->getKey(KEY_LEFT_ARROW))
		aladdin->setScale(Vec2(-1, 1));

	if (Input::getInstance()->getKey(KEY_RIGHT_ARROW))
		aladdin->setScale(Vec2(1, 1));

	aladdin->setActionName("SitAndSlash");
}

State* SitAndSlash::checkTransition()
{
	if (Input::getInstance()->getKey(KEY_A))
		return new SitAndThrow(_node);
	if (Input::getInstance()->getKey(KEY_D))
		return new Jump(_node);

		return nullptr;
}
