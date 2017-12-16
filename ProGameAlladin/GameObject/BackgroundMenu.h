﻿#ifndef __BACKGROUNDMENU_H__

#define __BACKGROUNDMENU_H__
#include "../Framework/definitions.h"
#include "../Framework/Node.h"
#include "../Framework/Texture.h"

NS_JK_BEGIN

class BackgroundMenu: public Node
{
public:
	BackgroundMenu();
	BackgroundMenu(const string& srcFile, const int& layer);
	~BackgroundMenu();

	void init() override;
	void render() override;
	void release() override;

private:
	string _srcFile;
	Texture _textureBackground;
	int _layer;
};

NS_JK_END

#endif __BACKGROUNDMENU_H__
