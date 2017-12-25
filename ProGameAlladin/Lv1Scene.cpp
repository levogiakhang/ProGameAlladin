﻿#include "Lv1Scene.h"
#include "Framework/Camera.h"
#include "GameObject/Enemies/Enemy.h"
#include "GameObject/Weapons/AppleToThrow.h"
#include "GameObject/Wall/Wall.h"
#include "GameObject/BackgroundSky.h"
#include "Framework/Text.h"
#include "GameObject/Aladdin.h"
#include "Framework/Audio.h"

US_NS_JK

Lv1Scene::Lv1Scene()
{
	
}



Lv1Scene::~Lv1Scene()
{
	_gameMap->~GameMap();
}


void Lv1Scene::init()
{


#pragma region Sound 
	_soundAbu = new Sound("Resources/Audio/Abu.wav");
	//Audio::get()->load(_soundAbu);
	//Audio::get()->play(_soundAbu,true);
	//_soundBackground = LoadSound("Resources/Audio/AgrabahMarket.wave");
	//_soundBackground->Play();
#pragma endregion 

	mAladdin = new Aladdin(Vec2(300, 600), Size(10, 60));
	_vectNode.push_back(mAladdin);
	mAladdin->setCurrentScene(this);


	_vectNode.push_back(new BackgroundSky("Resources/bg_sky.jpg", 0));
	//_vectNode.push_back(new Rope(Vec2(300, 440), Size(5, 220)));

	_gameMap = new GameMap("Resources/AgrabahMarket.tmx", mQuadTree, mAladdin);


	Camera::getInstance()->follow(mAladdin);
	Camera::getInstance()->setScaleFactor(Vec2(0.8, 0.8));
	_vectNode.push_back(Camera::getInstance());




	for (auto ground : _gameMap->getListGround())
	{
		_vectNode.push_back(ground);
	}

	_gameMap->init();

	_alaLife = new Text("Arial", "3", Camera::getInstance()->getCameraX(), Camera::getInstance()->getCameraX(), 20, 30, FW_BOLD, Color(255, 255, 255, 255));
	_vectNode.push_back(_alaLife);
	//for (auto object : staticobject)
	//{
	//	object->init();
	//	mQuadTree->insertObject(object);
	//}
	Scene::init();

}

void Lv1Scene::release()
{
	_gameMap->release();
	Scene::release();
}

void Lv1Scene::update()
{
	//checkVisibility();
	_alaLife->setPosition(Vec2(Camera::getInstance()->getCameraX(), Camera::getInstance()->getCameraY()));
	_gameMap->update();
	Scene::update();

}

void Lv1Scene::render()
{
	_gameMap->draw();
	Scene::render();
	//for (auto object : listVisible)
	//{
	//	object->render();
	//}
}



//
//void Lv1Scene::checkVisibility()
//{
//	listVisible.clear();
//
// 	mQuadTree->getObjectsVisibility(listVisible, mQuadTree->getVisibilityArea(mAladdin), 1);
//}

