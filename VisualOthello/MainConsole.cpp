#include "GameConsole.h"
#include "PersonPlayer.h"
#include "RandomAI.h"
#include "MaxAI.h"
#include <windows.h>

// TODO: ���v���C�@�\�̒ǉ�

int main(void)
{
	RandomAI player1(std::string("Left Top AI"));
	MaxAI player2(std::string("Max AI"));
	Game game(&player1, &player2);

	game.start();

	BoardStatus now_turn_player = game.get_first_player();

	while (!game.is_finished())
	{
		Sleep(0.5 * 1000);
		game.print_board(now_turn_player);

		// ���̃^�[����now_turn_player���u���邩�̔���
		bool can_put_flag = false;
		for (int y = 1; !can_put_flag && y <= 8; y++)
		{
			for (int x = 1; !can_put_flag && x <= 8; x++)
			{
				if (game.can_put(Coordinate{ x, y }, now_turn_player))
				{
					can_put_flag = true;
				}
			}
		}

		if (can_put_flag)
		{
			Coordinate input = game.calc(now_turn_player);

			if (game.set_stone(input, now_turn_player))
			{
				std::cout << "�u���܂���" << std::endl;
			}
			else
			{
				std::cout << "�u���܂���ł���" << std::endl;
			}
		}
		else
		{
			std::cout << "�p�X���܂���" << std::endl;
		}

		now_turn_player = game.get_enemy(now_turn_player);
	}

	game.print_board(now_turn_player);

	game.game_over();
}