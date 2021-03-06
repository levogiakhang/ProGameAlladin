#include "SitAndThrow.h"
#include "../Framework/Input.h"
#include "SitAndSlash.h"
#include "Jump.h"
#include "../GameObject/Aladdin.h"
#include "Sit.h"
#include "../GameObject/Weapons/AppleToThrow.h"
#include "../Framework/Scene.h"
#include "../Framework/Audio.h"
#include "../Lv1Scene.h"
#include "../BossScene.h"
US_NS_JK

SitAndThrow::SitAndThrow(Node* node) :State(node)
{
}

SitAndThrow::~SitAndThrow()
{
}

void SitAndThrow::onEnter()
{
	// TODO: setScale()
	// TODO: loadAnimation()
	auto aladdin = static_cast<Aladdin*>(_node);

	auto lv1 = static_cast<Lv1Scene*>(aladdin->getCurrentScene());
	auto boss = static_cast<BossScene*>(aladdin->getCurrentScene());

	if (aladdin->getEScene() == Aladdin::ENUM_LV1_SCENE)
	{
		Audio::get()->play(lv1->getsoundThrowing(), false);
	}

	if (aladdin->getEScene() == Aladdin::ENUM_BOSS_SCENE)
	{
		Audio::get()->play(boss->getsoundThrowing(), false);
	}

	if (Input::getInstance()->getKey(KEY_LEFT_ARROW))
		aladdin->setScale(Vec2(-1, 1));

	if (Input::getInstance()->getKey(KEY_RIGHT_ARROW))
		aladdin->setScale(Vec2(1, 1));

	aladdin->setActionName("SitAndThrow");

	const auto apple = new AppleToThrow(aladdin,Vec2(aladdin->getRigidPosition().getX(), aladdin->getRigidPosition().getY() - 20), Size(5, 5));
	if (aladdin->getScale() == Vec2(1, 1))
	{
		apple->getRigidBody()->setVelocity(Vec2(400, 0));
	}
	else
	{
		apple->getRigidBody()->setVelocity(Vec2(-400, 0));
	}

	apple->setCurrentScene(aladdin->getCurrentScene());
	aladdin->getCurrentScene()->addNode(apple);

}

void SitAndThrow::onUpdate()
{
	const auto aladdin = static_cast<Aladdin*>(_node);

	if (Input::getInstance()->getKey(KEY_LEFT_ARROW))
		aladdin->setScale(Vec2(-1, 1));
	if (Input::getInstance()->getKey(KEY_RIGHT_ARROW))
		aladdin->setScale(Vec2(1, 1));
}

State* SitAndThrow::checkTransition()
{
	const auto aladdin = static_cast<Aladdin*>(_node);

	if (Input::getInstance()->getKey(KEY_S))
		return new SitAndSlash(_node);
	if (Input::getInstance()->getKey(KEY_D))
		return new Jump(_node);
	if (!Input::getInstance()->getKey(KEY_DOWN_ARROW))
		return new Idle(_node);

	if (aladdin->getIndex() >= 4)
		return new Sit(_node);



	return nullptr;
}
