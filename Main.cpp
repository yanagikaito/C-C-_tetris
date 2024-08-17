#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
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
    SetBackgroundColor(0, 0, 0);				    // �E�B���h�E�̔w�i�F
    SetDrawScreen(DX_SCREEN_BACK);					// �`����ʂ𗠉�ʂɂ���
    SetAlwaysRunFlag(TRUE);							// �E�C���h�E��A�N�e�B�u��Ԃł������𑱍s����


    /*** ���[�v���� ***/
    while (ScreenFlip() == 0 &&		                // ����ʂ̓��e��\��ʂɔ��f
        ClearDrawScreen() == 0 &&	                // ��ʂ�������
        ProcessMessage() == 0)		                // �E�C���h�E�̃��b�Z�[�W������
    {
    }

    DxLib_End();					                // �c�w���C�u�����g�p�̏I������

    return 0;						                // �\�t�g�̏I�� 
}