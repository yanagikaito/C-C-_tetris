#include "DxLib.h"

/*** キーボード設定 ***/
#define DEF_KEY_PRESS_TIME (100)					// キーボード長押し回数

// ブロックに関する定数定義
#define BLOCK_NUM_X (10)
#define BLOCK_NUM_Y (20)

// ブロックの1個1個の大きさ
#define BLOCK_EDGE  (32)

// 列挙体(ブロックタイプ)
enum e_Color {

    Col_No,
    Col_Red,
    Col_Blue,
    Col_Green,
    Col_Yellow,
    Col_Total
};

struct BLOCK {

    // x,y座標,色
    int x;
    int y;
    int c;
};

// 色を決定する関数
unsigned int Color(int c) {

    // 色代入
    switch (c) {
        // 白
    case e_Color::Col_No:
        c = GetColor(255, 255, 255);
        break;
        // 赤
    case e_Color::Col_Red:
        c = GetColor(255, 0, 0);
        break;
        // 青
    case e_Color::Col_Blue:
        c = GetColor(0, 0, 255);
        break;
        // 緑
    case e_Color::Col_Green:
        c = GetColor(0, 0, 255);
        break;
        // 黄色
    case e_Color::Col_Yellow:
        c = GetColor(0, 0, 255);
        break;
    }

    return c;
}

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
void Game_Ini(int y, int x, struct BLOCK(*p)) {

    for (int y = 0; y < BLOCK_NUM_Y; y++) {
        for (int x = 0; x < BLOCK_NUM_X; x++) {
            p->x = x;
            p->y = y;
            p->c = e_Color::Col_No;
        }
    }
}

// ゲーム終了時の処理を行う関数
void Game_End() {

}

// ゲームの計算処理を行う関数
void Game_Cal() {

}

// ゲームの描画処理を行う関数
void Game_Draw(int y, int x, struct BLOCK(*p)) {

    // フレームX
    for (int x = 0; x < BLOCK_NUM_X + 2; x = x + 1) {
        DrawBox(x * BLOCK_EDGE,
            BLOCK_EDGE * BLOCK_NUM_Y,
            BLOCK_EDGE * BLOCK_EDGE,
            BLOCK_EDGE * BLOCK_NUM_Y + BLOCK_EDGE,
            GetColor(100, 100, 100),
            TRUE);
    }

    // フレームY
    for (int x = 0; x < 2; x = x + 1) {
        for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
            DrawBox(
                x * (BLOCK_NUM_X + 1) * BLOCK_EDGE,
                y * BLOCK_EDGE,
                x * (BLOCK_NUM_X + 1) * BLOCK_EDGE + BLOCK_EDGE,
                y * BLOCK_EDGE + BLOCK_EDGE,
                GetColor(100, 100, 100),
                TRUE);
        }
    }

    // 描画用シフト分の座標
    const int shi_x = BLOCK_EDGE;

    // ブロック
    for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
            DrawBox(shi_x + p->x * BLOCK_EDGE + BLOCK_EDGE,
                p->y * BLOCK_EDGE,
                shi_x + p->x - BLOCK_EDGE,
                p->y + BLOCK_EDGE,
                Color(p->c),
                TRUE);
        }
    }
}

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance,
    _In_opt_  HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd) {

    struct BLOCK block[BLOCK_NUM_X][BLOCK_NUM_Y];

    for (int y = 0; y < BLOCK_NUM_Y; y++) {
        for (int x = 0; x < BLOCK_NUM_X; x++) {
            block[x][y] = {
                x * BLOCK_EDGE,
                y * BLOCK_EDGE,
                e_Color::Col_No,
            };
        }
    }

    struct BLOCK* p = &block[BLOCK_NUM_X][BLOCK_NUM_Y];

    ChangeWindowMode(TRUE);
    DxLib_Init();

    /*** Window Init ***/
    SetWindowText("tetris");
    SetWindowInitPosition(0, 0);
    SetGraphMode(900, 800, 32);
    SetBackgroundColor(0, 0, 0);				    // ウィンドウの背景色
    SetDrawScreen(DX_SCREEN_BACK);					// 描画先画面を裏画面にする
    SetAlwaysRunFlag(TRUE);							// ウインドウ非アクティブ状態でも処理を続行する


    Game_Ini(BLOCK_NUM_X, BLOCK_NUM_Y, p);


    /*** ループ処理 ***/
    while (ScreenFlip() == 0 &&		                // 裏画面の内容を表画面に反映
        ClearDrawScreen() == 0 &&	                // 画面を初期化
        Key.GetKey() == 0 &&						// キーボード入力情報取得
        ProcessMessage() == 0)		                // ウインドウのメッセージを処理
    {
        Game_Cal();
        Game_Draw(BLOCK_NUM_X, BLOCK_NUM_Y, p);
    }

    DxLib_End();					                // ＤＸライブラリ使用の終了処理

    return 0;						                // ソフトの終了 
}