#pragma once
#include "Object.h"
#include <map>

class CTexture;

class CAnimationObject :
    public CObject
{
protected:
	typedef struct _TextureInfo {
		CTexture*	Texture;
		int			TotalFrame;
		float		Speed;
		bool		Loop;
	}TextureInfo;
	typedef std::map<std::string, TextureInfo> FTextureMap;

protected:
	PROTECT_MEMBER(bool, IsAnimate)

protected:
	FTextureMap	TextureMap;
	std::string	CurAnimName;

	int CurFrame;
	float CurTime;

public:
	CAnimationObject();
	CAnimationObject(Vector2D InPosition, Vector2D InScale);
	~CAnimationObject();

	virtual void Init();
	virtual void Update(float InDeltaTime);
	virtual void LateUpdate(float InDeltaTime); // Render 되기 전 마지막 업데이트
	virtual void Render(HDC InHdc);

public:
	void SetTexture(const std::string& InAnimName, CTexture* InTexture, int InFrame, float InSpeed, bool InLoop = true);
	void SetTexture(const std::string& InAnimName, const std::string& InFilePath, int InFrame, float InSpeed, bool InLoop = true);

	void SetAnimState(const std::string& InAnimName);
};

