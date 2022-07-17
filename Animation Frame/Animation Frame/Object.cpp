#include "Object.h"
#include "Define.h"

unsigned int CObject::Id = 100;

static HPEN Green_Pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
static HPEN Red_Pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
static HPEN Black_Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

static HBRUSH Null_Brush = (HBRUSH)GetStockObject(NULL_BRUSH);
static HBRUSH Default_Brush = CreateSolidBrush(RGB(255, 255, 255));

CObject::CObject()
	: Position()
	, Scale()
	, CollisionScale()
	, ObjectLayer(OBJ_LAYER::MAX)
{
	PrevCollision = false;
	CurCollision = false;
	ObjectId = Id++;
}
CObject::CObject(Vector2D InPosition, Vector2D InScale)
	: Position(InPosition)
	, Scale(InScale)
	, CollisionScale(InScale)
	, ObjectLayer(OBJ_LAYER::MAX)
{
	PrevCollision = false;
	CurCollision = false;
	ObjectId = Id++;
}

CObject::~CObject()
{

}

void CObject::Init()
{

}

void CObject::Update(float InDeltaTime)
{
	CurCollision = false;
}

void CObject::LateUpdate(float InDeltaTime)
{
	PrevCollision = CurCollision;
}

void CObject::Render(HDC InHdc)
{
	Rectangle(InHdc,
		(int)(Position.x - (Scale.x * 0.5f)),
		(int)(Position.y - (Scale.y * 0.5f)),
		(int)(Position.x + (Scale.x * 0.5f)),
		(int)(Position.y + (Scale.y * 0.5f)));
}

void CObject::CollisionRender(HDC InHdc)
{
	if (CurCollision)
		SelectObject(InHdc, Red_Pen);
	else
		SelectObject(InHdc, Green_Pen);
	SelectObject(InHdc, Null_Brush);

	Rectangle(InHdc,
		Position.x - (CollisionScale.x * 0.5f),
		Position.y - (CollisionScale.y * 0.5f),
		Position.x + (CollisionScale.x * 0.5f),
		Position.y + (CollisionScale.y * 0.5f));

	SelectObject(InHdc, Black_Pen);
	SelectObject(InHdc, Default_Brush);
}

void CObject::Collision(const CObject* InOtherObject)
{
	CurCollision = true;
}
