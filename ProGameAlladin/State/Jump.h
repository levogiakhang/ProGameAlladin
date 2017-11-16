﻿#ifndef __JUMP_H__

#define __JUMP_H__
#include "State.h"


NS_JK_BEGIN

class Jump : public State
{
public:
	Jump(Node* node);
	~Jump() override;

	void onEnter() override;
	State* checkTransition() override;

};

NS_JK_END

#endif __JUMP_H__