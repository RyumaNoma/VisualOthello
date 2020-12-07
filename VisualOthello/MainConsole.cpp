#include "GameConsole.h"
#include "PersonPlayer.h"
#include "RandomAI.h"
#include "MaxAI.h"
#include "ReplayConsole.h"
#include <windows.h>
#include <cstdlib>
#include <ctime>

// TODO: ���v���C�@�\�̒ǉ�

int main(void)
{
	srand((unsigned)time(NULL));
	RandomAI player1(std::string("Left Top AI"));
	MaxAI player2(std::string("Max AI"));
	Game game(&player1, &player2);

	game.start();

	Replay replay("D:/replayC.txt");
	replay.set_game_info(player1.get_name(), player2.get_name(), game.get_first_player());

	BoardStatus now_turn_player = game.get_first_player();
	GameStatus game_status = SET;

	while (!game.is_finished())
	{
		//�Ֆʂ̋L�^
		replay.record_board(game.get_board(), game_status);

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
				game_status = SET;
			}
			else
			{
				// ��@�ȏꏊ�Ƀ}�X��u���悤�ɂ��Ă�������C�����_���ȃ}�X�ɒu��
				std::vector<Coordinate> can_put_list;

				for (int y = 1; y <= 8; y++)
				{
					for (int x = 1; x <= 8; x++)
					{
						Coordinate c = { x, y };
						if (game.can_put(c, now_turn_player))
						{
							can_put_list.push_back(c);
						}
					}
				}

				int r = rand() % can_put_list.size();

				if (game.set_stone(can_put_list[r], now_turn_player))
				{
					std::cout << "�����_���ɒu���܂���" << std::endl;
					game_status = SET;
				}
				else
				{
					std::cout << "�u���܂���ł���" << std::endl;
					game_status = CANNOT_SET;
				}
			}
		}
		else
		{
			std::cout << "�p�X���܂���" << std::endl;
			game_status = PASS;
		}

		now_turn_player = game.get_enemy(now_turn_player);
	}

	game.print_board(now_turn_player);
	replay.record_board(game.get_board(), game_status);

	game.game_over();
}