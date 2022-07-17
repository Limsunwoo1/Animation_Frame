#pragma once
#include "Object.h"

class CTexture;

class CSpriteObject :
    public CObject
{
private:
    CTexture* Texture;

public:
	CSpriteObject();
	CSpriteObject(Vector2D InPosition, Vector2D InScale);
	~CSpriteObject();

	virtual void Init();
	virtual void Update(float InDeltaTime);
	virtual void LateUpdate(float InDeltaTime); // Render 되기 전 마지막 업데이트
	virtual void Render(HDC InHdc);

public:
	void SetTexture(CTexture* InTexture);
	void SetTexture(const std::string& InFilePath);
};

