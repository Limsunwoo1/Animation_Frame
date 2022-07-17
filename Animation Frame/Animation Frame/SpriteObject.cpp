#include "SpriteObject.h"
#include "ResourceManager.h"
#include "CTexture.h"

CSpriteObject::CSpriteObject()
: CObject(Vector2D{ 100, 100 }, Vector2D{ 50, 50 })
, Texture(nullptr)
{

}

CSpriteObject::CSpriteObject(Vector2D InPosition, Vector2D InScale)
: CObject(Vector2D{ InPosition.x , InPosition.y }, Vector2D{ InScale.x, InScale.y })
, Texture(nullptr)
{

}

CSpriteObject::~CSpriteObject()
{

}

void CSpriteObject::Init()
{
	CObject::Init();
}

void CSpriteObject::Update(float InDeltaTime)
{
	CObject::Update(InDeltaTime);
}

void CSpriteObject::LateUpdate(float InDeltaTime)
{
	CObject::LateUpdate(InDeltaTime);
}

void CSpriteObject::Render(HDC InHdc)
{
	if (!Texture)
		CObject::Render(InHdc);

	// 알파값 == 투명값
	// 투명하게 띄우는거, 반투명하게 띄우는거를 알파블렌딩 이라고 한다
	// 색상을 섞는다는 블렌딩의 의미

	// bmp 파일은 보통 색상이 24비트짜리
	// R : 8비트
	// G : 8비트
	// B : 8비트 0 ~ 255 값
	// 32 비트는 여기에 A : 8 비트가 추가된 값 ( 알파값 )

	// 32비트 bmp 는 bf.AlphaFormat = AC_SRC_ALPHA
		// 24비트 bmp 는 bf.AlphaFormat = 0

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	AlphaBlend(InHdc,
		(int)(Position.x - (Texture->GetWidth() * 0.5f)),
		(int)(Position.y - (Texture->GetHeight() * 0.5f)),
		Texture->GetWidth(),
		Texture->GetHeight(),
		Texture->GetHdc(),
		0,
		0,
		Texture->GetWidth(),
		Texture->GetHeight(),
		bf);

	// 특정 영역의 색상을 아예 그리지 않는다
/*	TransparentBlt(InHdc,
		Position.x - (Texture->GetWidth() * 0.5f),
		Position.y - (Texture->GetHeight() * 0.5f),
		Texture->GetWidth(),
		Texture->GetHeight(),
		Texture->GetHdc(),
		0,
		0,
		Texture->GetWidth(),
		Texture->GetHeight(),
		RGB(0, 0, 0));*/

		//BitBlt(InHdc,
		//	Position.x - (Texture->GetWidth() * 0.5f),
		//	Position.y - (Texture->GetHeight() * 0.5f),
		//	//Scale.x,
		//	//Scale.y,
		//	Texture->GetWidth(),
		//	Texture->GetHeight(),
		//	Texture->GetHdc(),
		//	0,
		//	0,
		//	SRCCOPY);
}

void CSpriteObject::SetTexture(CTexture* InTexture)
{
	Texture = InTexture;

	SetScale(Vector2D((int)Texture->GetWidth(), (int)Texture->GetHeight()));
	SetCollisionScale(Vector2D((int)Texture->GetWidth(), (int)Texture->GetHeight()));
}

void CSpriteObject::SetTexture(const std::string& InFilePath)
{
	SetTexture(CResourceManager::GetInstance()->FindTexture(InFilePath));
}