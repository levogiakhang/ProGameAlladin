﻿#include "BeingRescued.h"
US_NS_JK

BeingRescued::BeingRescued(Node* node):State(node)
{
}

BeingRescued::~BeingRescued()
{
}

void BeingRescued::onEnter()
{
	// TODO: setScale()
	// TODO: loadAnimation()
}

State* BeingRescued::checkTransition()
{
	return nullptr;
}
