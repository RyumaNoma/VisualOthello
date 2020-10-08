# 開発環境
## ツール
- Visual Studio 2019
- [Siv3D(4.3.0)](https://siv3d.github.io/ja-jp/tutorial/basic/)

## 言語
- C++

# 各プロジェクト
各プロジェクトは「スタートアッププロジェクトに設定する」をしてから実行する
## ConsoleOthello
- 開発者 VS AI が出来るデバッグ用プロジェクト
- AI VS AI も出来る
- これらはプロジェクト内の`Main.cpp`を変更する事で変更できる
## VisualOthello
- AI VS AI 用プロジェクト

## 新しいAIクラスを作る
1. ソリューションエクスプローラーのVisualOthello上で右クリック
1. 追加 > 新しい項目 でC++クラスを選択し、名前を自分のAI名にして追加を押す
1. 次の画面で基底クラスにPlayerと書き、OKを押す

1. ヘッダーファイルをこのような状態にする(MaxAIクラスの例、MaxAI.h)
	```cpp
	#pragma once
	#include "Player.h"
	class MaxAI : public Player
	{
	public:
		MaxAI();
		Coordinate calc(std::vector<std::vector<BoardStatus>> board);
	};
	```

1. C++ファイルをこのような状態にする(MaxAIクラスの例、MaxAI.cpp)

	- 返り値がCoordinate構造体のcalc関数内にプログラムを書き込むことでAIの脳を作ります
	```cpp
	#include "MaxAI.h"

	MaxAI::MaxAI(std::string name) : Player::Player(name)
	{
	}

	Coordinate MaxAI::calc(std::vector<std::vector<BoardStatus>> board)
	{
	}
	```

1. 最も沢山裏返すことが出来るマスにコマを置くAIを作ってみる
	- MaxAIクラスのcalc関数をこういう風にするだけ。簡単ですね
	```cpp
	Coordinate MaxAI::calc(std::vector<std::vector<BoardStatus>> board)
	{
		int max = 0;
		Coordinate max_coordinate;

		for (int y = 1; y <= 8; y++)
		{
			for (int x = 1; x <= 8; x++)
			{
				// 置けるなら
				if (Player::can_put(Coordinate{ x, y }, player_num, board))
				{
					// 座標(x, y)に置いたときに裏返せるコマの数
					int now = Player::can_get_num(Coordinate{ x, y }, this->player_num, board);
					// 現在のmaxよりも多ければ
					if (now > max)
					{
						// maxを更新する
						max = now;
						// maxの座標を更新する
						max_coordinate = Coordinate{ x, y };
					}
				}
			}
		}

		return max_coordinate;
	}
	```

1. main関数(Main.cpp)を書き換える
	
	VisualOthello内のmain関数を書き換える。
	- 18または19行目の宣言を以下のようにする
	```cpp
	MaxAI player2(std::string("Max AI"));
	```
	これは
	```cpp
	クラス名 player2(std::string("AIの名前"));
	```
	の形式で書く。

	- クラスのヘッダーをインクルードする
	```cpp
	#include "Max.h"
	```

1. 実行してみる
	1. VisualOthelloプロジェクトをスタートアッププロジェクトに設定する
	1. 実行する(Ctrl + F5)


## ConsoleOthelloプロジェクトで実行するには
1. main関数を変更する
	- ConsoleOthelloプロジェクト内のmain関数をVisualOthelloのmain関数と同様に変更する

1. ConsoleOthelloプロジェクトにクラスを追加する
	1. ConsoleOthelloのソースファイル上で右クリックする
	1. 追加 > 既存の項目 をクリックする
	1. VisualOthelloプロジェクトにあるMax.cppを選択し、追加を押す

	1. ConsoleOthelloのヘッダーファイル上で右クリックする
	1. 追加 > 既存の項目 をクリックする
	1. VisualOthelloプロジェクトにあるMax.hを選択し、追加を押す

1. 実行する
	1. ConsoleOthelloをスタートアッププロジェクトに設定する
	1. 実行する(Ctrl + F5)