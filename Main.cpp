#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance,
    _In_opt_  HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd) {
    ChangeWindowMode(TRUE);
    DxLib_Init();

    /*** Window Init ***/
    SetWindowText("TEST 2D GAME");
    SetWindowInitPosition(0, 0);
    SetGraphMode(900, 900, 32);
    SetBackgroundColor(0, 0, 0);				    // ウィンドウの背景色
    SetDrawScreen(DX_SCREEN_BACK);					// 描画先画面を裏画面にする
    SetAlwaysRunFlag(TRUE);							// ウインドウ非アクティブ状態でも処理を続行する


    /*** ループ処理 ***/
    while (ScreenFlip() == 0 &&		                // 裏画面の内容を表画面に反映
        ClearDrawScreen() == 0 &&	                // 画面を初期化
        ProcessMessage() == 0)		                // ウインドウのメッセージを処理
    {
    }

    DxLib_End();					                // ＤＸライブラリ使用の終了処理

    return 0;						                // ソフトの終了 
}