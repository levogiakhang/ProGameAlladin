﻿#include "Sit.h"
US_NS_JK

Sit::Sit(Node* node):State(_node)
{
}

Sit::~Sit()
{
}

void Sit::onEnter()
{
}

State* Sit::checkTransition()
{
	if (Input::getInstance()->getKey(KEY_D))
		return new Jump(_node);
	if (Input::getInstance()->getKey(KEY_S))
		return new SitAndSlash(_node);
	if (Input::getInstance()->getKey(KEY_A))
		return new SitAndThrow(_node);

	return nullptr;
}