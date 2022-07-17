#include "AnimationObject.h"
#include "ResourceManager.h"
#include "CTexture.h"

CAnimationObject::CAnimationObject() 
: CObject(Vector2D{ 100, 100 }, Vector2D{ 50, 50 })
, CurFrame(0)
, CurTime(0.f)
, IsAnimate(true)
{
	
}

CAnimationObject::CAnimationObject(Vector2D InPosition, Vector2D InScale) 
: CObject(Vector2D{ InPosition.x , InPosition.y }, Vector2D{ InScale.x, InScale.y })
, CurFrame(0)
, CurTime(0.f)
, IsAnimate(true)
{

}

CAnimationObject::~CAnimationObject()
{
	TextureMap.clear();
}

void CAnimationObject::Init()
{
	CObject::Init();
}

void CAnimationObject::Update(float InDeltaTime)
{
	CObject::Update(InDeltaTime);

	if(!IsAnimate)
		return;

	CurTime += TextureMap[CurAnimName].Speed * InDeltaTime;
	if (CurTime > 1.f)
	{
		CurFrame++;
		CurTime -= 1.f;
	}
	if (CurFrame >= TextureMap[CurAnimName].TotalFrame)
	{
		if (TextureMap[CurAnimName].Loop)
			CurFrame = 0;
		else
			CurFrame = TextureMap[CurAnimName].TotalFrame - 1;
	}
}

void CAnimationObject::LateUpdate(float InDeltaTime)
{
	CObject::LateUpdate(InDeltaTime);
}

void CAnimationObject::Render(HDC InHdc)
{
	int Width = (int)TextureMap[CurAnimName].Texture->GetWidth() / TextureMap[CurAnimName].TotalFrame;
	int Height = (int)TextureMap[CurAnimName].Texture->GetHeight();

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = 255;

	AlphaBlend(InHdc,
		(int)(Position.x - (Scale.x * 0.5f)),
		(int)(Position.y - (Scale.y * 0.5f)),
		(int)Scale.x,
		(int)Scale.y,
		TextureMap[CurAnimName].Texture->GetHdc(),
		Width * CurFrame,
		0,
		Width,
		Height,
		bf);
}

void CAnimationObject::SetTexture(const std::string& InAnimName, CTexture* InTexture, int InFrame, float InSpeed, bool InLoop)
{
	TextureMap[InAnimName] = TextureInfo{InTexture, InFrame, InSpeed, InLoop};
	CurAnimName = InAnimName;
	IsAnimate = true;
}

void CAnimationObject::SetTexture(const std::string& InAnimName, const std::string& InFilePath, int InFrame, float InSpeed, bool InLoop)
{
	SetTexture(InAnimName, CResourceManager::GetInstance()->FindTexture(InFilePath), InFrame, InSpeed, InLoop);
}

void CAnimationObject::SetAnimState(const std::string& InAnimName)
{
	if(TextureMap.find(InAnimName) == TextureMap.end())
		return;

	CurAnimName = InAnimName;
	CurFrame = 0;
	CurTime = 0.f;
}