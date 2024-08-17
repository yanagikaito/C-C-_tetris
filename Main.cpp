#include "DxLib.h"
/*** キーボード設定 ***/
#define DEF_KEY_PRESS_TIME (100)					// キーボード長押し回数

/*** Keyクラス ***/
class
{
public:
    int input[256];									// キーボード入力情報

    int GetKey()
    {
        char allkey[256];
        GetHitKeyStateAll(allkey);
        for (int i = 0; i < 256; i++)
        {
            if (allkey[i] == 1)						// 特定のキーは押されているか
            {
                if (input[i] < DEF_KEY_PRESS_TIME)	// 長押し上限まで押されているかどうか
                {
                    input[i] = input[i] + 1;		// 保存
                }
            }
            else if (allkey[i] == 0)				// 特定のキーは押されていないか
            {
                input[i] = 0;
            }
        }
        return 0;
    }
private:

}Key;

// ゲーム開始時の処理を行う関数
void Game_Ini() {

}

// ゲーム終了時の処理を行う関数
void Game_End() {

}

// ゲームの計算処理を行う関数
void Game_Cal() {

}

// ゲームの描画処理を行う関数
void Game_Draw() {

}

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance,
    _In_opt_  HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd) {
    ChangeWindowMode(TRUE);
    DxLib_Init();

    /*** Window Init ***/
    SetWindowText("tetris");
    SetWindowInitPosition(0, 0);
    SetGraphMode(900, 900, 32);
    SetBackgroundColor(0, 0, 0);				    // ウィンドウの背景色
    SetDrawScreen(DX_SCREEN_BACK);					// 描画先画面を裏画面にする
    SetAlwaysRunFlag(TRUE);							// ウインドウ非アクティブ状態でも処理を続行する


    /*** ループ処理 ***/
    while (ScreenFlip() == 0 &&		                // 裏画面の内容を表画面に反映
        ClearDrawScreen() == 0 &&	                // 画面を初期化
        Key.GetKey() == 0 &&						// キーボード入力情報取得
        ProcessMessage() == 0)		                // ウインドウのメッセージを処理
    {
    }

    DxLib_End();					                // ＤＸライブラリ使用の終了処理

    return 0;						                // ソフトの終了 
}