#include "DxLib.h"
#include "iostream"

/*** �L�[�{�[�h�ݒ� ***/
#define DEF_KEY_PRESS_TIME (100)					// �L�[�{�[�h��������

// �u���b�N�Ɋւ���萔��`
#define BLOCK_NUM_X (10)
#define BLOCK_NUM_Y (20)

// �u���b�N��1��1�̑傫��
#define BLOCK_EDGE  (32)

// �񋓑�(�u���b�N�^�C�v)
enum e_Color {

    Col_No,
    Col_Red,
    Col_Blue,
    Col_Green,
    Col_Yellow,
    Col_Total
};

struct BLOCK {

    // x,y���W,�F
    int x;
    int y;
    int c;
};

// �F�����肷��֐�
unsigned int Color(int c) {

    // �F���
    switch (c) {
        // ��
    case e_Color::Col_No:
        c = GetColor(255, 255, 255);
        break;
        // ��
    case e_Color::Col_Red:
        c = GetColor(255, 0, 0);
        break;
        // ��
    case e_Color::Col_Blue:
        c = GetColor(0, 0, 255);
        break;
        // ��
    case e_Color::Col_Green:
        c = GetColor(0, 0, 255);
        break;
        // ���F
    case e_Color::Col_Yellow:
        c = GetColor(0, 0, 255);
        break;
    }

    return c;
}

/*** Key�N���X ***/
class
{
public:
    int input[256];									// �L�[�{�[�h���͏��

    int GetKey()
    {
        char allkey[256];
        GetHitKeyStateAll(allkey);
        for (int i = 0; i < 256; i++)
        {
            if (allkey[i] == 1)						// ����̃L�[�͉�����Ă��邩
            {
                if (input[i] < DEF_KEY_PRESS_TIME)	// ����������܂ŉ�����Ă��邩�ǂ���
                {
                    input[i] = input[i] + 1;		// �ۑ�
                }
            }
            else if (allkey[i] == 0)				// ����̃L�[�͉�����Ă��Ȃ���
            {
                input[i] = 0;
            }
        }
        return 0;
    }
private:

}Key;


// �Q�[���J�n���̏������s���֐�
void Game_Ini(BLOCK* p) {

    for (int y = 0; y < BLOCK_NUM_Y; y++) {
        for (int x = 0; x < BLOCK_NUM_X; x++) {
            p->x = x;
            p->y = y;
            p->c = e_Color::Col_No;
        }
    }
}

// �Q�[���I�����̏������s���֐�
void Game_End() {

}

// �Q�[���̌v�Z�������s���֐�
void Game_Cal() {

}

// �Q�[���̕`�揈�����s���֐�
void Game_Draw(BLOCK* p) {

    // �t���[��X
    for (int x = 0; x < BLOCK_NUM_X + 3; x = x + 1) {
        DrawBox(x * BLOCK_EDGE,
            BLOCK_EDGE * BLOCK_NUM_Y,
            BLOCK_EDGE + BLOCK_EDGE,
            BLOCK_EDGE * BLOCK_NUM_Y + BLOCK_EDGE,
            GetColor(100, 100, 100),
            TRUE);
    }

    // �t���[��Y
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

    // �`��p�V�t�g���̍��W
    const int shi_x = BLOCK_EDGE;

    // �u���b�N
    for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
            DrawBox(
                // ���㒸�_��X���W
                shi_x + p->x * BLOCK_EDGE + BLOCK_EDGE - p->x,
                // ���㒸�_��Y���W
                p->y * BLOCK_EDGE + BLOCK_EDGE,
                // �E�����_��X���W
                shi_x + p->x - BLOCK_EDGE + BLOCK_EDGE,
                // �E�����_��Y���W
                p->y + BLOCK_EDGE,
                Color(p->c),
                TRUE);
        }
    }

    // �Ԗ�
    for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
            // �Ԗ�
            DrawBox(
                x * BLOCK_EDGE + BLOCK_EDGE,
                y * BLOCK_EDGE,
                x * BLOCK_EDGE + 2 * BLOCK_EDGE,
                y * BLOCK_EDGE + BLOCK_EDGE,
                GetColor(0, 0, 0),
                FALSE);
        }
    }
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance,
    _In_opt_  HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd) {

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
    SetBackgroundColor(0, 0, 0);				    // �E�B���h�E�̔w�i�F
    SetDrawScreen(DX_SCREEN_BACK);					// �`����ʂ𗠉�ʂɂ���
    SetAlwaysRunFlag(TRUE);			                // �E�C���h�E��A�N�e�B�u��Ԃł������𑱍s����

    for (int y = 0; y < BLOCK_NUM_Y; y++) {
        for (int x = 0; x < BLOCK_NUM_X; x++) {
            Game_Ini(&block[x][y]);
        };
    }


    /*** ���[�v���� ***/
    while (ScreenFlip() == 0 &&		                // ����ʂ̓��e��\��ʂɔ��f
        ClearDrawScreen() == 0 &&	                // ��ʂ�������
        Key.GetKey() == 0 &&						// �L�[�{�[�h���͏��擾
        ProcessMessage() == 0)		                // �E�C���h�E�̃��b�Z�[�W������
    {
        Game_Cal();
        for (int y = 0; y < BLOCK_NUM_Y; y++) {
            for (int x = 0; x < BLOCK_NUM_X; x++) {
                Game_Draw(&block[x][y]);
            };
        }
    }

    DxLib_End();					                // �c�w���C�u�����g�p�̏I������

    return 0;						                // �\�t�g�̏I�� 
}