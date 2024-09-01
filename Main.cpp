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

struct GATHER {

    // �u���b�N4���
    BLOCK block[4];
    // �`��
    int t;
    // ��]
    int r;
};

// �u���b�N�̏W�܂�̃^�C�v��񋓑̂Œ�`
enum e_Type {

    // �l�p�`
    Typ_squ,

    // �X�g���[�g
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

// �u���b�N�̏W�܂��`
GATHER move;

// ���Ɍ����u���b�N�̏W�܂�̒�`
GATHER next[5];


// �u���b�N�̏W�܂�Ɋւ���ϐ����
GATHER Move_Sub(GATHER m, int x, int y) {

    // �`��ƐF����
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

// �u���b�N�̏W�܂��������
void Move_Ini(int n) {

    // �F�������_���Ō���
    unsigned int c =
        GetRand(e_Color::Col_Total - e_Color::Col_Red - 1)
        + e_Color::Col_Red;

    // �F����
    for (int i = 0; i < 4; i = i + 1) {

        next[n].block[i].c = c;
    }

    // �`��������_���Ō���
    next[n].t = GetRand(e_Type::Typ_Total - 1);

    // ��]�������_���Ō���
    next[n].t = GetRand(4 - 1);

    // next���
    next[n] = Move_Sub(
        next[n],
        BLOCK_EDGE * 4,
        BLOCK_EDGE * 0);

    // move���
    move = next[0];
}

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
        c = GetColor(124, 252, 0);
        break;
        // ���F
    case e_Color::Col_Yellow:
        c = GetColor(255, 255, 0);
        break;
    }

    return c;
}

// �J�E���^
int Cou;

/*** Key�N���X ***/
class
{
public:
    int input[256];									// �L�[�{�[�h���͏��

    int GetKey()
    {
        GetHitKeyStateAll(allKey);
        for (int i = 0; i < 256; i++)
        {
            if (allKey[i] == 1)						// ����̃L�[�͉�����Ă��邩
            {
                if (input[i] < DEF_KEY_PRESS_TIME)	// ����������܂ŉ�����Ă��邩�ǂ���
                {
                    input[i] = input[i] + 1;		// �ۑ�
                }
            }
            else if (allKey[i] == 0)				// ����̃L�[�͉�����Ă��Ȃ���
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

    // �u���b�N�̏W�܂�̏�����
    for (int i = 0; i < 5; i = i + 1) {
        Move_Ini(i);
    }

    // next���炷
    for (int i = 0; i < 5 - 1; i = i + 1) {
        next[i] = next[i + 1];
    }

    // �J�E���g������
    Cou = 0;
}

// �u���b�N�̏W�܂�͈̔͗񋓑̒�`
enum e_Move_Lim {

    e_�͈͓�,
    e_x��0����,
    e_x��300�ȏ�,
    e_y��600�ȏ�,
};

// �ǂ��̃��~�b�g��Ԃ��֐�
int Move_Lim() {

    for (int i = 0; i < 4; i = i + 1) {

        // �ǂ̍����ɐڐG�����ꍇ
        if (move.block[i].x < 0) {
            return e_Move_Lim::e_x��0����;
        }
        // �ǂ̉E���ɐڐG�����ꍇ
        if (move.block[i].x >= 300) {
            return e_Move_Lim::e_x��300�ȏ�;
        }
        // ��ɐڐG�����ꍇ
        if (move.block[i].y >= 600) {
            return e_Move_Lim::e_y��600�ȏ�;
        }
    }
    return e_Move_Lim::e_�͈͓�;
}

// �u���b�N�ƃu���b�N�̐ڐG����
bool HitJudg(BLOCK* p, int xs, int ys) {

    for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
            for (int i = 0; i < 4; i = i + 1) {

                // �z��O�͒T���s�\�Ȃ��ߊ֐��I��(x����)
                if (x - xs < 0 ||
                    x + xs == BLOCK_NUM_X ||
                    y + ys == BLOCK_NUM_Y) {

                    // ��ڐG
                    return FALSE;
                }

                // �������W�̎w�肵���ꏊ�Ƀu���b�N�����݂���ꍇ
                if (move.block[i].x == p->x &&
                    move.block[i].y == p->y &&
                    move.block[i].c != e_Color::Col_No &&
                    (p + x + xs)[y + ys].c != e_Color::Col_No) {

                    // �ڐG
                    return TRUE;
                }
            }
        }
    }

    // ��ڐG
    return FALSE;
}

// moveY�����v�Z
bool Move_Ycal(BLOCK* p) {

    Cou = Cou + 1;

    // ���W�X�V
    move = Move_Sub(
        move,
        move.block[0].x,

        // 1�b�Ԃ�1��Y�����Ɉړ�����
        BLOCK_EDGE * (int)(Cou / 60));

    // �u���b�Ny���W�͈̔͐���
    if (Move_Lim() == e_Move_Lim::e_y��600�ȏ� ||
        HitJudg(p, 0, 0) == TRUE) {

        // ���W�O�̏�Ԃɖ߂�
        move = Move_Sub(
            move,
            move.block[0].x,
            move.block[0].y - BLOCK_EDGE);

        // move��block�ɑ��
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

        // �J�E���g������
        Cou = 0;

        // �u���b�N�������f
        bool del = TRUE;

        // ���������
        int del_row = 0;

        // ����������W
        int del_y = 0;

        for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {

            // ������
            del = TRUE;

            for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {

                // ��1���1�ł��󔒂����݂���ꍇ
                if (p->c == e_Color::Col_No) {

                    // �������~
                    del = FALSE;
                }
            }

            if (del == TRUE) {

                // �����񐔃J�E���g
                del_row = del_row + 1;

                // ���������Ō�̗����
                del_y = y;

                //��1��̃u���b�N��S�ď���
                for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
                    p->c = e_Color::Col_No;
                }
            }
        }

        // ���������񐔕��̃u���b�N�̈ʒu�ړ�
        if (del_row != 0) {

            for (int y = BLOCK_NUM_Y - 1; y > 0; y = y - 1) {

                // ���������Ō�̗�̏ꍇ,�񐔕��u���b�N�̈ʒu�ړ�
                if (y == del_y) {

                    // �u���b�N�ꂩ�烋�[�v
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

        // �u���b�N�̏W�܂�̏�����
        Move_Ini(5 - 1);

        // next���炷
        for (int i = 0; i < 5 - 1; i = i + 1) {
            next[i] = next[i + 1];
        }

        // �ڐG
        return TRUE;
    }

    // ��ڐG
    return FALSE;
}

// �Q�[���I�����̏������s���֐�
bool Game_End(BLOCK* p) {

    for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {

        // 1�ԏ�̗�Ƀu���b�N�����݂��Ă��邩���f
        if (p->c != e_Color::Col_No) {

            // �Q�[���I��
            return TRUE;
        }
    }

    // �Q�[�����s
    return FALSE;
}

// �Q�[���̌v�Z�������s���֐�
void Game_Cal(BLOCK* p) {

    // �u���b�N��]
    // ����](�����v���)
    if (allKey[KEY_INPUT_L] == 1) {

        move.r = move.r + 1;
    }

    // �E��](���v���)
    else if (allKey[KEY_INPUT_R] == 1) {

        move.r = move.r - 1;
    }

    // �u���b�N��]�͈�
    if (move.r < 0) {

        move.r = 3;
    }

    else if (move.r > 3) {

        move.r = 0;
    }

    // �u���b�N�W�܂�E�����ւ̈ړ�
    if (allKey[KEY_INPUT_D] == 1) {

        // �u���b�N�X�V
        move = Move_Sub(
            move,
            move.block[0].x + BLOCK_EDGE,
            move.block[0].y);

        // �u���b�N�̍��W����
        if (HitJudg(p, +1, 0) == TRUE || Move_Lim() == e_Move_Lim::e_x��300�ȏ�) {


            move = Move_Sub(
                move,
                move.block[0].x - BLOCK_EDGE,
                move.block[0].y);
        }
    }

    // �u���b�N�W�܂荶�����ւ̈ړ�
    if (allKey[KEY_INPUT_A] == 1) {


        // �u���b�N�X�V
        move = Move_Sub(
            move,
            move.block[0].x - BLOCK_EDGE,
            move.block[0].y);

        // �u���b�N�̍��W����
        if (HitJudg(p, +1, 0) == TRUE || Move_Lim() == e_Move_Lim::e_x��0����) {

            move = Move_Sub(
                move,
                move.block[0].x + BLOCK_EDGE,
                move.block[0].y);
        }
    }

    bool y_fla = FALSE;

    // �u���b�N�W�܂艺�����ւ̈ړ�
    if (allKey[KEY_INPUT_S] == 1) {

        while (1) {

            if (Move_Ycal(p) == TRUE) {

                // �������[�v����
                break;
            }
        }
    }

    // �u���b�NY�����ړ��v�Z(����)
    Move_Ycal(p);

    // �Q�[���I�[�o�[���ۂ����f
    if (Game_End(p) == TRUE) {

        // �Q�[��������
        Game_Ini(p);
    }
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
                shi_x + p->x * BLOCK_EDGE + BLOCK_EDGE,
                // ���㒸�_��Y���W
                p->y = y * BLOCK_EDGE + BLOCK_EDGE,
                // �E�����_��X���W
                shi_x + p->x - BLOCK_EDGE + p->x * 3 - p->x + 5,
                // �E�����_��Y���W
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

// �v���O������ WinMain ����n�܂�܂�
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
        BLOCK* p;

        p = &block[0][0];

        Game_Cal(p);

        for (int y = 0; y < BLOCK_NUM_Y; y++) {
            for (int x = 0; x < BLOCK_NUM_X; x++) {
                Game_Draw(&block[x][y]);
            };
        }
    }

    DxLib_End();					                // �c�w���C�u�����g�p�̏I������

    return 0;						                // �\�t�g�̏I�� 
}