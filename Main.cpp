#include "DxLib.h"
/*** �L�[�{�[�h�ݒ� ***/
#define DEF_KEY_PRESS_TIME (100)					// �L�[�{�[�h��������

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
void Game_Ini() {

}

// �Q�[���I�����̏������s���֐�
void Game_End() {

}

// �Q�[���̌v�Z�������s���֐�
void Game_Cal() {

}

// �Q�[���̕`�揈�����s���֐�
void Game_Draw() {

}

// �v���O������ WinMain ����n�܂�܂�
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
    SetBackgroundColor(0, 0, 0);				    // �E�B���h�E�̔w�i�F
    SetDrawScreen(DX_SCREEN_BACK);					// �`����ʂ𗠉�ʂɂ���
    SetAlwaysRunFlag(TRUE);							// �E�C���h�E��A�N�e�B�u��Ԃł������𑱍s����


    /*** ���[�v���� ***/
    while (ScreenFlip() == 0 &&		                // ����ʂ̓��e��\��ʂɔ��f
        ClearDrawScreen() == 0 &&	                // ��ʂ�������
        Key.GetKey() == 0 &&						// �L�[�{�[�h���͏��擾
        ProcessMessage() == 0)		                // �E�C���h�E�̃��b�Z�[�W������
    {
    }

    DxLib_End();					                // �c�w���C�u�����g�p�̏I������

    return 0;						                // �\�t�g�̏I�� 
}