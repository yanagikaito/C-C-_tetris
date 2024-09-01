#include "DxLib.h"
#include "iostream"


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

struct GATHER {

    // ブロック4種類
    BLOCK block[4];
    // 形状
    int t;
    // 回転
    int r;
};

// ブロックの集まりのタイプを列挙体で定義
enum e_Type {

    // 四角形
    Typ_squ,

    // ストレート
    Typ_str,

    // 2blo2
    Typ_2to2,

    // blo_mid
    Typ_mid,

    // blo_end
    Typ_end,

    Typ_Total
};

char allKey[256];

// ブロックの集まり定義
GATHER move;

// 次に現れるブロックの集まりの定義
GATHER next[5];


// ブロックの集まりに関する変数代入
GATHER Move_Sub(GATHER m, int x, int y) {

    // 形状と色を代入
    switch (m.t) {

    case e_Type::Typ_squ:

        m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
        m.block[1] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[1].c };
        m.block[2] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 0 + y, m.block[2].c };
        m.block[3] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 1 + y, m.block[3].c };

        break;

    case e_Type::Typ_str:

        switch (m.r) {

        case 0:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[3].c };

            break;

        case 1:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * -1 + x, BLOCK_EDGE * 1 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 1 + y, m.block[3].c };

            break;

        case 2:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 2 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * -1 + x, BLOCK_EDGE * 1 + y, m.block[3].c };

            break;

        case 3:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * -1 + x, BLOCK_EDGE * 0 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 0 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[3].c };

            break;
        }

        break;

    case e_Type::Typ_2to2:

        switch (m.r) {

        case 0:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 1 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 2 + y, m.block[3].c };

            break;

        case 1:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * -1 + x, BLOCK_EDGE * 1 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 1 + y, m.block[3].c };

            break;

        case 2:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * -1 + x, BLOCK_EDGE * 1 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * -1 + x, BLOCK_EDGE * 2 + y, m.block[3].c };

            break;

        case 3:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * -1 + x, BLOCK_EDGE * 0 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 1 + y, m.block[3].c };

            break;
        }

        break;

    case e_Type::Typ_mid:

        switch (m.r) {

        case 0:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 2 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 1 + y, m.block[3].c };

            break;

        case 1:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * -1 + x, BLOCK_EDGE * 1 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 1 + y, m.block[3].c };

            break;

        case 2:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 2 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * -1 + x, BLOCK_EDGE * 1 + y, m.block[3].c };

            break;

        case 3:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * -1 + x, BLOCK_EDGE * 0 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 0 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[3].c };

            break;

        }

        break;

    case e_Type::Typ_end:

        switch (m.r) {

        case 0:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 2 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 2 + y, m.block[3].c };

            break;

        case 1:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * -1 + x, BLOCK_EDGE * 1 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * -2 + x, BLOCK_EDGE * 1 + y, m.block[3].c };

            break;

        case 2:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 0 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 1 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 2 + y, m.block[3].c };

            break;

        case 3:

            m.block[0] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 0 + y, m.block[0].c };
            m.block[1] = { BLOCK_EDGE * 0 + x, BLOCK_EDGE * 1 + y, m.block[1].c };
            m.block[2] = { BLOCK_EDGE * 1 + x, BLOCK_EDGE * 0 + y, m.block[2].c };
            m.block[3] = { BLOCK_EDGE * 2 + x, BLOCK_EDGE * 0 + y, m.block[3].c };

            break;
        }

        break;

    }

    return m;

}

// ブロックの集まりを初期化
void Move_Ini(int n) {

    // 色をランダムで決定
    unsigned int c =
        GetRand(e_Color::Col_Total - e_Color::Col_Red - 1)
        + e_Color::Col_Red;

    // 色を代入
    for (int i = 0; i < 4; i = i + 1) {

        next[n].block[i].c = c;
    }

    // 形状をランダムで決定
    next[n].t = GetRand(e_Type::Typ_Total - 1);

    // 回転をランダムで決定
    next[n].t = GetRand(4 - 1);

    // next代入
    next[n] = Move_Sub(
        next[n],
        BLOCK_EDGE * 4,
        BLOCK_EDGE * 0);

    // move代入
    move = next[0];
}

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
        c = GetColor(124, 252, 0);
        break;
        // 黄色
    case e_Color::Col_Yellow:
        c = GetColor(255, 255, 0);
        break;
    }

    return c;
}

// カウンタ
int Cou;

/*** Keyクラス ***/
class
{
public:
    int input[256];									// キーボード入力情報

    int GetKey()
    {
        GetHitKeyStateAll(allKey);
        for (int i = 0; i < 256; i++)
        {
            if (allKey[i] == 1)						// 特定のキーは押されているか
            {
                if (input[i] < DEF_KEY_PRESS_TIME)	// 長押し上限まで押されているかどうか
                {
                    input[i] = input[i] + 1;		// 保存
                }
            }
            else if (allKey[i] == 0)				// 特定のキーは押されていないか
            {
                input[i] = 0;
            }
        }
        return 0;
    }
private:

}Key;


// ゲーム開始時の処理を行う関数
void Game_Ini(BLOCK* p) {

    for (int y = 0; y < BLOCK_NUM_Y; y++) {
        for (int x = 0; x < BLOCK_NUM_X; x++) {
            p->x = x;
            p->y = y;
            p->c = e_Color::Col_No;
        }
    }

    // ブロックの集まりの初期化
    for (int i = 0; i < 5; i = i + 1) {
        Move_Ini(i);
    }

    // nextずらす
    for (int i = 0; i < 5 - 1; i = i + 1) {
        next[i] = next[i + 1];
    }

    // カウント初期化
    Cou = 0;
}

// ブロックの集まりの範囲列挙体定義
enum e_Move_Lim {

    e_範囲内,
    e_xが0未満,
    e_xが300以上,
    e_yが600以上,
};

// 壁や底のリミットを返す関数
int Move_Lim() {

    for (int i = 0; i < 4; i = i + 1) {

        // 壁の左側に接触した場合
        if (move.block[i].x < 0) {
            return e_Move_Lim::e_xが0未満;
        }
        // 壁の右側に接触した場合
        if (move.block[i].x >= 300) {
            return e_Move_Lim::e_xが300以上;
        }
        // 底に接触した場合
        if (move.block[i].y >= 600) {
            return e_Move_Lim::e_yが600以上;
        }
    }
    return e_Move_Lim::e_範囲内;
}

// ブロックとブロックの接触判定
bool HitJudg(BLOCK* p, int xs, int ys) {

    for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
            for (int i = 0; i < 4; i = i + 1) {

                // 配列外は探索不可能なため関数終了(x方向)
                if (x - xs < 0 ||
                    x + xs == BLOCK_NUM_X ||
                    y + ys == BLOCK_NUM_Y) {

                    // 非接触
                    return FALSE;
                }

                // 同じ座標の指定した場所にブロックが存在する場合
                if (move.block[i].x == p->x &&
                    move.block[i].y == p->y &&
                    move.block[i].c != e_Color::Col_No &&
                    (p + x + xs)[y + ys].c != e_Color::Col_No) {

                    // 接触
                    return TRUE;
                }
            }
        }
    }

    // 非接触
    return FALSE;
}

// moveY方向計算
bool Move_Ycal(BLOCK* p) {

    Cou = Cou + 1;

    // 座標更新
    move = Move_Sub(
        move,
        move.block[0].x,

        // 1秒間に1個Y方向に移動する
        BLOCK_EDGE * (int)(Cou / 60));

    // ブロックy座標の範囲制約
    if (Move_Lim() == e_Move_Lim::e_yが600以上 ||
        HitJudg(p, 0, 0) == TRUE) {

        // 座標前の状態に戻す
        move = Move_Sub(
            move,
            move.block[0].x,
            move.block[0].y - BLOCK_EDGE);

        // moveをblockに代入
        for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
            for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
                for (int i = 0; i < 4; i = i + 1) {
                    if (p->x == move.block[i].x &&
                        p->y == move.block[i].y) {
                        p->c = move.block[i].c;
                    }
                }
            }
        }

        // カウント初期化
        Cou = 0;

        // ブロック消去判断
        bool del = TRUE;

        // 消去する個数
        int del_row = 0;

        // 消去する座標
        int del_y = 0;

        for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {

            // 初期化
            del = TRUE;

            for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {

                // 横1列に1つでも空白が存在する場合
                if (p->c == e_Color::Col_No) {

                    // 消去中止
                    del = FALSE;
                }
            }

            if (del == TRUE) {

                // 消去列数カウント
                del_row = del_row + 1;

                // 消去した最後の列を代入
                del_y = y;

                //横1列のブロックを全て消去
                for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
                    p->c = e_Color::Col_No;
                }
            }
        }

        // 消去した列数分のブロックの位置移動
        if (del_row != 0) {

            for (int y = BLOCK_NUM_Y - 1; y > 0; y = y - 1) {

                // 消去した最後の列の場合,列数分ブロックの位置移動
                if (y == del_y) {

                    // ブロック底からループ
                    for (int y = del_y; y != del_row; y = y - 1) {
                        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
                            p->c = (p + BLOCK_NUM_Y * x)[y - del_row].c;
                            (p + BLOCK_NUM_Y * x)[y - del_row].c = e_Color::Col_No;
                        }
                    }

                    break;
                }
            }
        }

        // ブロックの集まりの初期化
        Move_Ini(5 - 1);

        // nextずらす
        for (int i = 0; i < 5 - 1; i = i + 1) {
            next[i] = next[i + 1];
        }

        // 接触
        return TRUE;
    }

    // 非接触
    return FALSE;
}

// ゲーム終了時の処理を行う関数
bool Game_End(BLOCK* p) {

    for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {

        // 1番上の列にブロックが存在しているか判断
        if (p->c != e_Color::Col_No) {

            // ゲーム終了
            return TRUE;
        }
    }

    // ゲーム続行
    return FALSE;
}

// ゲームの計算処理を行う関数
void Game_Cal(BLOCK* p) {

    // ブロック回転
    // 左回転(反時計回り)
    if (allKey[KEY_INPUT_L] == 1) {

        move.r = move.r + 1;
    }

    // 右回転(時計回り)
    else if (allKey[KEY_INPUT_R] == 1) {

        move.r = move.r - 1;
    }

    // ブロック回転範囲
    if (move.r < 0) {

        move.r = 3;
    }

    else if (move.r > 3) {

        move.r = 0;
    }

    // ブロック集まり右方向への移動
    if (allKey[KEY_INPUT_D] == 1) {

        // ブロック更新
        move = Move_Sub(
            move,
            move.block[0].x + BLOCK_EDGE,
            move.block[0].y);

        // ブロックの座標制約
        if (HitJudg(p, +1, 0) == TRUE || Move_Lim() == e_Move_Lim::e_xが300以上) {


            move = Move_Sub(
                move,
                move.block[0].x - BLOCK_EDGE,
                move.block[0].y);
        }
    }

    // ブロック集まり左方向への移動
    if (allKey[KEY_INPUT_A] == 1) {


        // ブロック更新
        move = Move_Sub(
            move,
            move.block[0].x - BLOCK_EDGE,
            move.block[0].y);

        // ブロックの座標制約
        if (HitJudg(p, +1, 0) == TRUE || Move_Lim() == e_Move_Lim::e_xが0未満) {

            move = Move_Sub(
                move,
                move.block[0].x + BLOCK_EDGE,
                move.block[0].y);
        }
    }

    bool y_fla = FALSE;

    // ブロック集まり下方向への移動
    if (allKey[KEY_INPUT_S] == 1) {

        while (1) {

            if (Move_Ycal(p) == TRUE) {

                // 無限ループ解除
                break;
            }
        }
    }

    // ブロックY方向移動計算(時間)
    Move_Ycal(p);

    // ゲームオーバーか否か判断
    if (Game_End(p) == TRUE) {

        // ゲーム初期化
        Game_Ini(p);
    }
}

// ゲームの描画処理を行う関数
void Game_Draw(BLOCK* p) {

    // フレームX
    for (int x = 0; x < BLOCK_NUM_X + 3; x = x + 1) {
        DrawBox(x * BLOCK_EDGE,
            BLOCK_EDGE * BLOCK_NUM_Y,
            BLOCK_EDGE + BLOCK_EDGE,
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
            DrawBox(
                // 左上頂点のX座標
                shi_x + p->x * BLOCK_EDGE + BLOCK_EDGE,
                // 左上頂点のY座標
                p->y = y * BLOCK_EDGE + BLOCK_EDGE,
                // 右下頂点のX座標
                shi_x + p->x - BLOCK_EDGE + p->x * 3 - p->x + 5,
                // 右下頂点のY座標
                p->y = y + BLOCK_EDGE,
                Color(p->c),
                TRUE);
        }
    }

    //move
    for (int i = 0; i < 4; i = i + 1) {

        DrawBox(
            shi_x + move.block[i].x,
            move.block[i].y,
            shi_x + move.block[i].x + BLOCK_EDGE,
            move.block[i].y + BLOCK_EDGE,
            Color(move.block[i].c), TRUE);

        // String 
        DrawFormatString(
            shi_x + move.block[i].x + 20,
            move.block[i].y + 15,
            GetColor(0, 0, 0),
            "%d", move.block[i].c);
    }

    // 網目
    for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {

            // 網目
            DrawBox(
                x * BLOCK_EDGE + BLOCK_EDGE,
                y * BLOCK_EDGE,
                x * BLOCK_EDGE + 2 * BLOCK_EDGE,
                y * BLOCK_EDGE + BLOCK_EDGE,
                GetColor(0, 0, 0),
                FALSE);
        }
    }

    // Next
    for (int i = 0; i < 5 - 1; i = i + 1) {
        for (int j = 0; j < 4; j = j + 1) {
            DrawBox(
                500 + next[i].block[j].x,
                i * 200 + next[i].block[j].y,
                500 + next[i].block[j].x + BLOCK_EDGE,
                i * 200 + next[i].block[i].y + BLOCK_EDGE,
                Color(next[i].block[j].c), TRUE);

            DrawBox(
                500 + next[i].block[j].x,
                i * 200 + next[i].block[j].y,
                500 + next[i].block[j].x + BLOCK_EDGE,
                i * 200 + next[i].block[j].y + BLOCK_EDGE,
                GetColor(0, 0, 0), FALSE);
        }
    }
}

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance,
    _In_opt_  HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{

    BLOCK block[BLOCK_NUM_X][BLOCK_NUM_Y];

    for (int y = 0; y < BLOCK_NUM_Y; y++) {
        for (int x = 0; x < BLOCK_NUM_X; x++) {
            block[x][y] = {
                x * BLOCK_EDGE,
                y * BLOCK_EDGE,
                e_Color::Col_No,
            };
        }
    }

    ChangeWindowMode(TRUE);
    DxLib_Init();

    /*** Window Init ***/
    SetWindowText("tetris");
    SetWindowInitPosition(0, 0);
    SetGraphMode(1000, 1200, 32);
    SetBackgroundColor(0, 0, 0);				    // ウィンドウの背景色
    SetDrawScreen(DX_SCREEN_BACK);					// 描画先画面を裏画面にする
    SetAlwaysRunFlag(TRUE);			                // ウインドウ非アクティブ状態でも処理を続行する

    for (int y = 0; y < BLOCK_NUM_Y; y++) {
        for (int x = 0; x < BLOCK_NUM_X; x++) {
            Game_Ini(&block[x][y]);
        };
    }

    /*** ループ処理 ***/
    while (ScreenFlip() == 0 &&		                // 裏画面の内容を表画面に反映
        ClearDrawScreen() == 0 &&	                // 画面を初期化
        Key.GetKey() == 0 &&						// キーボード入力情報取得
        ProcessMessage() == 0)		                // ウインドウのメッセージを処理
    {
        BLOCK* p;

        p = &block[0][0];

        Game_Cal(p);

        for (int y = 0; y < BLOCK_NUM_Y; y++) {
            for (int x = 0; x < BLOCK_NUM_X; x++) {
                Game_Draw(&block[x][y]);
            };
        }
    }

    DxLib_End();					                // ＤＸライブラリ使用の終了処理

    return 0;						                // ソフトの終了 
}