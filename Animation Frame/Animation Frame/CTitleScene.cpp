#include "CTitleScene.h"
#include "Func.h"
#include "Button.h"
#include "Player.h"
#include "CSceneManager.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "UtilLog.h"
#include "UtilString.h"
#include "Loger.h"
#include <string>

CTitleScene::CTitleScene() 
{
}

CTitleScene::~CTitleScene()
{

}

void CTitleScene::Init()
{
	CPlayer* Player = new CPlayer();
	Player->SetPosition(Vector2D(500, 550));
	Player->SetScale(Vector2D(75, 87));
	Player->SetCollisionScale(Vector2D(75, 87));
	Player->SetTexture("RUN", "PLAYER_RUN", 6, 30.f);
	Player->SetTexture("DEAD", "PLAYER_DEAD", 4, 5.f, false);
	AddObject(OBJ_LAYER::PLAYER, Player);

	
	// UI는 충돌체크하면 로직이 꼬일수도 있음 체크해도 UI 끼리만 하도록 주의
	std::vector<OBJ_LAYER> checkLayerList;
	checkLayerList.push_back(OBJ_LAYER::PLAYER);
	CheckCollisionLayer[OBJ_LAYER::BULLET] = checkLayerList;
	checkLayerList.push_back(OBJ_LAYER::BLOCK);
	CheckCollisionLayer[OBJ_LAYER::BULLET] = checkLayerList;

	LOG_TODO("로그 예시 코드 확인했으면 지워도 무방");
	LOG("일반 로그 테스트");
	WARN_LOG("경고 로그 테스트");
	ERROR_LOG("에러 로그 테스트");
	ETC1_LOG("커스텀 로그 테스트");
	LOG(STRING("문자열 포매팅 테스트 : %d !!!", 30));

	CButton* Button = new CButton(Vector2D(500, 100), Vector2D(200, 100));
	AddObject(OBJ_LAYER::UI, Button);
}

void CTitleScene::Clear()
{	
	CScene::Clear();
}

void CTitleScene::Update(float InDeltaTime)
{
	CScene::Update(InDeltaTime);
}