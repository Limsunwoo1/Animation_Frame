#pragma once
#include "framework.h"
#include "Base.h"

enum class OBJ_LAYER : short {
	BACKGROUND = 0,
	BLOCK = 12,
	PLAYER = 24,
	BULLET = 28,
	UI = 30,
	MAX = 32,
};

class CObject : public CBase
{
	PROTECT_MEMBER(Vector2D, Position)

	PROTECT_MEMBER(Vector2D, Scale)

	PROTECT_MEMBER(Vector2D, CollisionScale)

	PROTECT_MEMBER(OBJ_LAYER, ObjectLayer)

private:
	static unsigned int Id;
	unsigned int ObjectId;

protected:

	bool PrevCollision;
	bool CurCollision;
public:
	CObject();
	CObject(Vector2D InPosition, Vector2D InScale);
	~CObject();

	virtual void Init();
	virtual void Update(float InDeltaTime);
	virtual void LateUpdate(float InDeltaTime); // Render 되기 전 마지막 업데이트
	virtual void Render(HDC InHdc);
	virtual void CollisionRender(HDC InHdc);

	virtual void Collision(const CObject* InOtherObject);

public:

	unsigned int GetId() const { return ObjectId; }
};

