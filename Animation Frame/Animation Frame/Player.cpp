#include "Player.h"
#include "KeyManager.h"
#include "CSceneManager.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "CTexture.h"

CPlayer::CPlayer() : CAnimationObject(Vector2D{ 100, 100 }, Vector2D{ 50, 50 })
{

}

CPlayer::CPlayer(Vector2D InVector, Vector2D InScale) : CAnimationObject(Vector2D{ InVector.x , InVector.y }, Vector2D{ InScale.x, InScale.y })
{

}

CPlayer::~CPlayer()
{

}

void CPlayer::Init()
{
	CAnimationObject::Init();

	SetAnimState("RUN");
}

void CPlayer::Update(float InDeltaTime)
{
	CAnimationObject::Update(InDeltaTime);

	int SPEED = 1000;
	if (KEY_STATE(KEY::A) == KEY_STATE::HOLD)
	{
		Vector2D position = Position;
		position.x -= SPEED * InDeltaTime;

		if (position.x < 20)
		{
			position.x = 20;
		}

		Position = position;
	}

	if (KEY_STATE(KEY::D) == KEY_STATE::HOLD)
	{
		Vector2D position = Position;
		position.x += SPEED * InDeltaTime;

		if (position.x > 940)
		{
			position.x = 940;
		}

		Position = position;
	}

	if (KEY_STATE(KEY::SPACE) == KEY_STATE::TAB)
	{
		SetAnimState("DEAD");
		SetScale(Vector2D(100, 100));
		SetCollisionScale(Vector2D(100, 100));
	}

	if (KEY_STATE(KEY::SPACE) == KEY_STATE::AWAY)
	{
		SetAnimState("RUN");
		SetScale(Vector2D(75, 87));
		SetCollisionScale(Vector2D(75, 87));
	}
}

void CPlayer::Collision(const CObject* InOtherObject)
{
	CObject::Collision(InOtherObject);
}

void CPlayer::Render(HDC InHdc)
{
	CAnimationObject::Render(InHdc);
}