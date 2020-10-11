#include "GameVisual.h"
#include "Replay.h"
#include <Siv3D.hpp>

// TODO: �J�E���g�_�E���̒ǉ�

void Main(void)
{
	Scene::SetBackground(Palette::Chocolate);
	const Font font(20);
	const double LapTime = 0.5;
	double time = 0.0;

	Replay replay("D:/replay.txt");
	replay.load_game();

	bool stop_flag = false;
	bool finish_flag = false;

	BoardStatus winner;

	while (System::Update())
	{
		replay.show_board();
		replay.print_first_turn(font);
		replay.print_info(font);
		replay.print_status(font);

		// �X�y�[�X�������Ă���Ԃ����Đ��𒆎~����
		if (!KeySpace.pressed())
		{
			time += Scene::DeltaTime();

			if (time >= LapTime)
			{
				replay.update_board();

				time = 0.0;
			}
		}
	}
}