#include "DxLib.h"
#include "SceneManager.h"
#include "FPS.h"
#include "GameMain.h"

#define _SCREEN_HEIGHT_ 480
#define _SCREEN_WIDHT_	640
#define _SCREEN_COLOR_BIT_16_ 16
#define _SCREEN_COLOR_BIT_32_ 32

#define DEBUG

int WINAPI WinMain(_In_ HINSTANCE ih, _In_opt_ HINSTANCE ioh, _In_ LPSTR il, _In_ int ii)
{
	// ウィンドウモードで起動
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)
	{
		return -1;
	}

	// 画面サイズを変更
	if (SetGraphMode(_SCREEN_WIDHT_, _SCREEN_HEIGHT_, _SCREEN_COLOR_BIT_32_) != DX_CHANGESCREEN_OK)
	{
		return -1;
	}

	// DXライブラリの初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	SceneManager sceneMng(dynamic_cast<AbstractScene*>(new GameMain()));
	FPS fps;

	//ゲームループ
	while (ProcessMessage() != -1 && sceneMng.Update() != nullptr)
	{
		ClearDrawScreen();
		fps.Update();	//FPS計測
		sceneMng.Draw();//シーン描画
		fps.Wait();		//FPS同期
#ifdef DEBUG
		fps.Draw();		//FPS描画
#endif // DEBUG
		ScreenFlip();	
	}

	// DXライブラリの終了処理
	DxLib_End();

	return 0;
}
