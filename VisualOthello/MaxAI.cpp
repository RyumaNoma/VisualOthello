#include "MaxAI.h"

MaxAI::MaxAI(std::string name) : Player::Player(name)
{
}

Coordinate MaxAI::calc(std::vector<std::vector<BoardStatus>> board)
{
	int max = 0;
	Coordinate max_coordinate;

	for (int y = 1; y <= 8; y++)
	{
		for (int x = 1; x <= 8; x++)
		{
			// �u����Ȃ�
			if (Player::can_put(Coordinate{ x, y }, player_num, board))
			{
				// ���W(x, y)�ɒu�����Ƃ��ɗ��Ԃ���R�}�̐�
				int now = Player::can_get_num(Coordinate{ x, y }, this->player_num, board);

				// ���݂�max�����������
				if (now > max)
				{
					// max���X�V����
					max = now;
					// max�̍��W���X�V����
					max_coordinate = Coordinate{ x, y };
				}
			}
		}
	}

	return max_coordinate;
}