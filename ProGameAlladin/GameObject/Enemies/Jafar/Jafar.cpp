﻿#include "Jafar.h"
#include "../../Framework/Graphics.h"
#include "../../../Framework/GameManager.h"
#include "JafarIdleState.h"
#include "JafarAttackState.h"
#include "Transform/TransformIdleState.h"
#include "Transform/TransformAttackState.h"

US_NS_JK

Jafar::Jafar()
{
}

Jafar::Jafar(const Vec2& position, const Size& size, const GameObjectType& tag, GameObject* target)
	:Enemy(position, size, tag, target)
{
	_attackRange = 280;
	setScale(Vec2(1, 1));

	_health = 21;

	_rigid->setTag("jafar");
	_isCollisionWithApple = false;
	_isTransform = false;
	_isDeHeal = false;
	_isDie = false;

#pragma region READ - XML
	pugi::xml_document doc;
	const auto result = doc.load_file("Resources/Boss/Jafar.xml");

	if (result)
	{
		for (auto animation : doc.child("Animations").children())
		{
			const pugi::char_t* name = animation.attribute("name").value();
			vector<Rect> rects;

			for (auto rect : animation.children())
			{
				rects.push_back(Rect(rect.attribute("x").as_float(),
					rect.attribute("y").as_float(),
					rect.attribute("w").as_float(),
					rect.attribute("h").as_float()));
			}
			_animations.emplace(name, rects);
		}
	}
#pragma endregion 

#pragma region READ - XML
	const auto resultTransform = doc.load_file("Resources/Boss/Transform.xml");

	if (resultTransform)
	{
		for (auto animation : doc.child("Animations").children())
		{
			const pugi::char_t* name = animation.attribute("name").value();
			vector<Rect> rects;

			for (auto rect : animation.children())
			{
				rects.push_back(Rect(rect.attribute("x").as_float(),
					rect.attribute("y").as_float(),
					rect.attribute("w").as_float(),
					rect.attribute("h").as_float()));
			}
			_transformAnimations.emplace(name, rects);
		}
	}
#pragma endregion 

	_currentState = new JafarIdleState(this);
}
Jafar::~Jafar()
{
}

void Jafar::init()
{
	_textureJafar.setSrcFile("Resources/Boss/jafar.png");
	//_textureJafar.setSrcFile("Resources/red_rect.png");
	_textureJafar.setName("Jafar");
	Graphics::getInstance()->loadTexture(_textureJafar);

	_textureTransform.setSrcFile("Resources/Boss/transform.png");
	//_textureJafar.setSrcFile("Resources/red_rect.png");
	_textureTransform.setName("Jafar");
	Graphics::getInstance()->loadTexture(_textureTransform);
}

void Jafar::release()
{
}

void Jafar::update()
{
	_currentState->onUpdate();
	if(_target->getRigidPosition().getX() < _rigid->getPosition().getX())
	{
		setScale(Vec2(-1, 1));
	}
	else
	{
		setScale(Vec2(1, 1));
	}

	_position = _rigid->getPosition() - _rigid->getOffset();


	auto const apple = std::find(std::begin(_rigid->getCollidingBodies()), std::end(_rigid->getCollidingBodies()), "appletothrow");

	if(apple != _rigid->getCollidingBodies().end())
	{
		_isCollisionWithApple = true;
	}
	else
	{
		_isCollisionWithApple = false;
		_isDeHeal = false;
	}



	if(_isCollisionWithApple && !_isDeHeal)
	{
		if (_health > 0)
		{
			_health--;
			_isCollisionWithApple = false;
			_isDeHeal = true;
			OutputDebugString(std::to_string(_health).c_str());
		}
	}


	if (!_isTransform && _health <= (21 - 8))
	{
		// bien hinh
		_isTransform = true;
		_currentState->onExit();
		delete _currentState;
		_currentState = new TransformIdleState(this);
		_animationIndex = 0;
	}

	if(_health == 0)
	{
		_rigid->setActive(false);
		_isDie = true;
		OutputDebugString("dieeeeeeeeeeeeeeeeeeeeeeeeeee");
	}

//	_rigid->getCollidingBodies().clear();

	Enemy::update();

	EnemyState* newState = _currentState->checkTransition();

	if (newState != nullptr)
	{
		_currentState->onExit();
		delete _currentState;
		_currentState = newState;
		_animationIndex = 0;
	}
}

void Jafar::render()
{
	if (_isTransform)
	{
		if (!_isDie)
		{
			const auto rect = _transformAnimations[_actionName][_animationIndex];
			const auto expect = 0.07;

			auto origin = Vec2(0.5f, 1.0f);

			Graphics::getInstance()->drawSprite(_textureTransform, origin, getTransformMatrix(), Color(255, 255, 255, 255),
				rect, 1);

			if (_index <= expect)
			{
				Graphics::getInstance()->drawSprite(_textureTransform, origin, getTransformMatrix(), Color(255, 255, 255, 255), rect, 1);
				_index += GameManager::getInstance()->getDeltaTime();
			}
			else
			{
				_index = 0;
				_animationIndex++;
				if (_animationIndex == _transformAnimations[_actionName].size())
					_animationIndex = 0;

			}
		}
		else
		{
			_animationIndex = 1;
		}
	}
	else
	{
		const auto rect = _animations[_actionName][_animationIndex];
		const auto expect = 0.05;

		auto origin = Vec2(0.5f, 1.0f);

		Graphics::getInstance()->drawSprite(_textureJafar, origin, getTransformMatrix(), Color(255, 255, 255, 255),
			rect, 1);

		if (_index <= expect)
		{
			Graphics::getInstance()->drawSprite(_textureJafar, origin, getTransformMatrix(), Color(255, 255, 255, 255), rect, 1);
			_index += GameManager::getInstance()->getDeltaTime();
		}
		else
		{
			_index = 0;
			_animationIndex++;
			if (_animationIndex == _animations[_actionName].size())
				_animationIndex = 0;

		}
	}
}

bool Jafar::isTransform() const
{
	return _isTransform;
}

Rect Jafar::getRect()
{
	return Rect(0, 0, 0, 0);
}
