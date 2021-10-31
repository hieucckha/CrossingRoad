#include "SpritesModel.h"

char** SpritesModel::CarLeft_ = nullptr, ** SpritesModel::CarRight_ = nullptr;
char** SpritesModel::TruckLeft_ = nullptr, ** SpritesModel::TruckRight_ = nullptr;
char** SpritesModel::BirdLeft_ = nullptr, ** SpritesModel::BirdRight_ = nullptr;
char** SpritesModel::DinosaurLeft_ = nullptr, ** SpritesModel::DinosaurRight_ = nullptr;
char** SpritesModel::PlayerMiddle_ = nullptr;

SpritesModel::SpritesModel()
{
	initCar();
	initTruck();
	initBird();
	initDinosaur();
	initPlayer();
}

SpritesModel::~SpritesModel()
{
	deleteCar();
	deleteTruck();
	deleteBird();
	deleteDinosaur();
	deletePlayer();
}

void SpritesModel::initCar()
{
	this->CarRight_ = new char* [4];
	for (int i = 0; i < 4; ++i)
		CarRight_[i] = new char[12];

	/* [4][12]
	@  _____
	 _/__|__\__
	|    |     |
	 `(o)----(o)
	*/

	// Row 1
	CarRight_[0][0] = ' ';
	CarRight_[0][1] = ' ';
	CarRight_[0][2] = ' ';
	CarRight_[0][3] = '_';
	CarRight_[0][4] = '_';
	CarRight_[0][5] = '_';
	CarRight_[0][6] = '_';
	CarRight_[0][7] = '_';
	CarRight_[0][8] = ' ';
	CarRight_[0][9] = ' ';
	CarRight_[0][10] = ' ';
	CarRight_[0][11] = ' ';
	// Row 2
	CarRight_[1][0] = ' ';
	CarRight_[1][1] = '_';
	CarRight_[1][2] = '/';
	CarRight_[1][3] = '_';
	CarRight_[1][4] = '_';
	CarRight_[1][5] = '|';
	CarRight_[1][6] = '_';
	CarRight_[1][7] = '_';
	CarRight_[1][8] = '\\';
	CarRight_[1][9] = '_';
	CarRight_[1][10] = '_';
	CarRight_[1][11] = ' ';
	// Row 3
	CarRight_[2][0] = '|';
	CarRight_[2][1] = ' ';
	CarRight_[2][2] = ' ';
	CarRight_[2][3] = ' ';
	CarRight_[2][4] = ' ';
	CarRight_[2][5] = '|';
	CarRight_[2][6] = ' ';
	CarRight_[2][7] = ' ';
	CarRight_[2][8] = ' ';
	CarRight_[2][9] = ' ';
	CarRight_[2][10] = ' ';
	CarRight_[2][11] = '|';
	// Row 4
	CarRight_[3][0] = ' ';
	CarRight_[3][1] = '`';
	CarRight_[3][2] = '(';
	CarRight_[3][3] = 'o';
	CarRight_[3][4] = ')';
	CarRight_[3][5] = '-';
	CarRight_[3][6] = '-';
	CarRight_[3][7] = '-';
	CarRight_[3][8] = '-';
	CarRight_[3][9] = '(';
	CarRight_[3][10] = 'o';
	CarRight_[3][11] = ')';

	this->CarLeft_ = new char* [4];
	for (int i = 0; i < 4; ++i)
		CarLeft_[i] = new char[12];

	/* [4][12]
	@   _____
	 __/__|__\_
	|     |    |
	(o)----(o)`
	*/

	// Row 1
	CarLeft_[0][0] = ' ';
	CarLeft_[0][1] = ' ';
	CarLeft_[0][2] = ' ';
	CarLeft_[0][3] = ' ';
	CarLeft_[0][4] = '_';
	CarLeft_[0][5] = '_';
	CarLeft_[0][6] = '_';
	CarLeft_[0][7] = '_';
	CarLeft_[0][8] = '_';
	CarLeft_[0][9] = ' ';
	CarLeft_[0][10] = ' ';
	CarLeft_[0][11] = ' ';
	// Row 2
	CarLeft_[1][0] = ' ';
	CarLeft_[1][1] = '_';
	CarLeft_[1][2] = '_';
	CarLeft_[1][3] = '/';
	CarLeft_[1][4] = '_';
	CarLeft_[1][5] = '_';
	CarLeft_[1][6] = '|';
	CarLeft_[1][7] = '_';
	CarLeft_[1][8] = '_';
	CarLeft_[1][9] = '\\';
	CarLeft_[1][10] = '_';
	CarLeft_[1][11] = ' ';
	// Row 3
	CarLeft_[2][0] = '|';
	CarLeft_[2][1] = ' ';
	CarLeft_[2][2] = ' ';
	CarLeft_[2][3] = ' ';
	CarLeft_[2][4] = ' ';
	CarLeft_[2][5] = ' ';
	CarLeft_[2][6] = '|';
	CarLeft_[2][7] = ' ';
	CarLeft_[2][8] = ' ';
	CarLeft_[2][9] = ' ';
	CarLeft_[2][10] = ' ';
	CarLeft_[2][11] = '|';
	// Row 4
	CarLeft_[3][0] = '(';
	CarLeft_[3][1] = 'o';
	CarLeft_[3][2] = ')';
	CarLeft_[3][3] = '-';
	CarLeft_[3][4] = '-';
	CarLeft_[3][5] = '-';
	CarLeft_[3][6] = '-';
	CarLeft_[3][7] = '(';
	CarLeft_[3][8] = 'o';
	CarLeft_[3][9] = ')';
	CarLeft_[3][10] = '`';
	CarLeft_[3][11] = ' ';
}

void SpritesModel::initTruck()
{
	this->TruckRight_ = new char* [4];
	for (int i = 0; i < 4; ++i)
		TruckRight_[i] = new char[12];

	/* [4][12]
	@\\   ___
	 _\\_/___\_
	|          |
	 `(o)----(o)
	*/

	// Row 1
	TruckRight_[0][0] = ' ';
	TruckRight_[0][1] = '\\';
	TruckRight_[0][2] = '\\';
	TruckRight_[0][3] = ' ';
	TruckRight_[0][4] = ' ';
	TruckRight_[0][5] = ' ';
	TruckRight_[0][6] = '_';
	TruckRight_[0][7] = '_';
	TruckRight_[0][8] = '_';
	TruckRight_[0][9] = ' ';
	TruckRight_[0][10] = ' ';
	TruckRight_[0][11] = ' ';
	// Row 2
	TruckRight_[1][0] = ' ';
	TruckRight_[1][1] = '_';
	TruckRight_[1][2] = '\\';
	TruckRight_[1][3] = '\\';
	TruckRight_[1][4] = '_';
	TruckRight_[1][5] = '/';
	TruckRight_[1][6] = '_';
	TruckRight_[1][7] = '_';
	TruckRight_[1][8] = '_';
	TruckRight_[1][9] = '\\';
	TruckRight_[1][10] = '_';
	TruckRight_[1][11] = ' ';
	// Row 3
	TruckRight_[2][0] = '|';
	TruckRight_[2][1] = ' ';
	TruckRight_[2][2] = ' ';
	TruckRight_[2][3] = ' ';
	TruckRight_[2][4] = ' ';
	TruckRight_[2][5] = ' ';
	TruckRight_[2][6] = ' ';
	TruckRight_[2][7] = ' ';
	TruckRight_[2][8] = ' ';
	TruckRight_[2][9] = ' ';
	TruckRight_[2][10] = ' ';
	TruckRight_[2][11] = '|';
	// Row 4
	TruckRight_[3][0] = ' ';
	TruckRight_[3][1] = '`';
	TruckRight_[3][2] = '(';
	TruckRight_[3][3] = 'o';
	TruckRight_[3][4] = ')';
	TruckRight_[3][5] = '-';
	TruckRight_[3][6] = '-';
	TruckRight_[3][7] = '-';
	TruckRight_[3][8] = '-';
	TruckRight_[3][9] = '(';
	TruckRight_[3][10] = 'o';
	TruckRight_[3][11] = ')';

	this->TruckLeft_ = new char* [4];
	for (int i = 0; i < 4; ++i)
		TruckLeft_[i] = new char[12];

	/* [4][12]
	@  ___   //
	 _/___\ //_
	|          |
	(o)----(o)`
	*/

	// Row 1
	TruckLeft_[0][0] = ' ';
	TruckLeft_[0][1] = ' ';
	TruckLeft_[0][2] = ' ';
	TruckLeft_[0][3] = '_';
	TruckLeft_[0][4] = '_';
	TruckLeft_[0][5] = '_';
	TruckLeft_[0][6] = ' ';
	TruckLeft_[0][7] = ' ';
	TruckLeft_[0][8] = ' ';
	TruckLeft_[0][9] = '/';
	TruckLeft_[0][10] = '/';
	TruckLeft_[0][11] = ' ';
	// Row 2
	TruckLeft_[1][0] = ' ';
	TruckLeft_[1][1] = '_';
	TruckLeft_[1][2] = '/';
	TruckLeft_[1][3] = '_';
	TruckLeft_[1][4] = '_';
	TruckLeft_[1][5] = '_';
	TruckLeft_[1][6] = '\\';
	TruckLeft_[1][7] = ' ';
	TruckLeft_[1][8] = '/';
	TruckLeft_[1][9] = '/';
	TruckLeft_[1][10] = '_';
	TruckLeft_[1][11] = ' ';
	// Row 3
	TruckLeft_[2][0] = '|';
	TruckLeft_[2][1] = ' ';
	TruckLeft_[2][2] = ' ';
	TruckLeft_[2][3] = ' ';
	TruckLeft_[2][4] = ' ';
	TruckLeft_[2][5] = ' ';
	TruckLeft_[2][6] = ' ';
	TruckLeft_[2][7] = ' ';
	TruckLeft_[2][8] = ' ';
	TruckLeft_[2][9] = ' ';
	TruckLeft_[2][10] = ' ';
	TruckLeft_[2][11] = '|';
	// Row 4
	TruckLeft_[3][0] = '(';
	TruckLeft_[3][1] = 'o';
	TruckLeft_[3][2] = ')';
	TruckLeft_[3][3] = '-';
	TruckLeft_[3][4] = '-';
	TruckLeft_[3][5] = '-';
	TruckLeft_[3][6] = '-';
	TruckLeft_[3][7] = '(';
	TruckLeft_[3][8] = 'o';
	TruckLeft_[3][9] = ')';
	TruckLeft_[3][10] = '`';
	TruckLeft_[3][11] = ' ';
}

void SpritesModel::initBird()
{
	this->BirdRight_ = new char* [4];
	for (int i = 0; i < 4; ++i)
		BirdRight_[i] = new char[5];

	/* [4][5]
	 __
	( o>
	///\
	\V_/_
	*/

	// Row 1
	BirdRight_[0][0] = ' ';
	BirdRight_[0][1] = '_';
	BirdRight_[0][2] = '_';
	BirdRight_[0][3] = ' ';
	BirdRight_[0][4] = ' ';

	// Row 2
	BirdRight_[1][0] = '(';
	BirdRight_[1][1] = ' ';
	BirdRight_[1][2] = 'o';
	BirdRight_[1][3] = '>';
	BirdRight_[1][4] = ' ';
	// Row 3
	BirdRight_[2][0] = '/';
	BirdRight_[2][1] = '/';
	BirdRight_[2][2] = '/';
	BirdRight_[2][3] = '\\';
	BirdRight_[2][4] = ' ';
	// Row 4
	BirdRight_[3][0] = '\\';
	BirdRight_[3][1] = 'V';
	BirdRight_[3][2] = '_';
	BirdRight_[3][3] = '/';
	BirdRight_[3][4] = '_';

	this->BirdLeft_ = new char* [4];
	for (int i = 0; i < 4; ++i)
		BirdLeft_[i] = new char[5];

	/* [4][5]
	  __
	 <o )
	 /\\\
	_\_V/
	*/

	// Row 1
	BirdLeft_[0][0] = ' ';
	BirdLeft_[0][1] = ' ';
	BirdLeft_[0][2] = '_';
	BirdLeft_[0][3] = '_';
	BirdLeft_[0][4] = ' ';

	// Row 2
	BirdLeft_[1][0] = ' ';
	BirdLeft_[1][1] = '<';
	BirdLeft_[1][2] = 'o';
	BirdLeft_[1][3] = ' ';
	BirdLeft_[1][4] = ')';
	// Row 3
	BirdLeft_[2][0] = ' ';
	BirdLeft_[2][1] = '/';
	BirdLeft_[2][2] = '\\';
	BirdLeft_[2][3] = '\\';
	BirdLeft_[2][4] = '\\';
	// Row 4
	BirdLeft_[3][0] = '_';
	BirdLeft_[3][1] = '\\';
	BirdLeft_[3][2] = '_';
	BirdLeft_[3][3] = 'V';
	BirdLeft_[3][4] = '/';
}

void SpritesModel::initDinosaur()
{
	this->DinosaurRight_ = new char* [4];
	for (int i = 0; i < 4; ++i)
		DinosaurRight_[i] = new char[12];

	/* [4][12]
			 __
	  _/\/\_/ _)
	 /   _   /
	/-|_| |_|
	*/

	// Row 1
	DinosaurRight_[0][0] = ' ';
	DinosaurRight_[0][1] = ' ';
	DinosaurRight_[0][2] = ' ';
	DinosaurRight_[0][3] = ' ';
	DinosaurRight_[0][4] = ' ';
	DinosaurRight_[0][5] = ' ';
	DinosaurRight_[0][6] = ' ';
	DinosaurRight_[0][7] = ' ';
	DinosaurRight_[0][8] = ' ';
	DinosaurRight_[0][9] = '_';
	DinosaurRight_[0][10] = '_';
	DinosaurRight_[0][11] = ' ';
	// Row 2
	DinosaurRight_[1][0] = ' ';
	DinosaurRight_[1][1] = ' ';
	DinosaurRight_[1][2] = '_';
	DinosaurRight_[1][3] = '/';
	DinosaurRight_[1][4] = '\\';
	DinosaurRight_[1][5] = '/';
	DinosaurRight_[1][6] = '\\';
	DinosaurRight_[1][7] = '_';
	DinosaurRight_[1][8] = '/';
	DinosaurRight_[1][9] = ' ';
	DinosaurRight_[1][10] = '_';
	DinosaurRight_[1][11] = ')';
	// Row 3
	DinosaurRight_[2][0] = ' ';
	DinosaurRight_[2][1] = '/';
	DinosaurRight_[2][2] = ' ';
	DinosaurRight_[2][3] = ' ';
	DinosaurRight_[2][4] = ' ';
	DinosaurRight_[2][5] = '_';
	DinosaurRight_[2][6] = ' ';
	DinosaurRight_[2][7] = ' ';
	DinosaurRight_[2][8] = ' ';
	DinosaurRight_[2][9] = '/';
	DinosaurRight_[2][10] = ' ';
	DinosaurRight_[2][11] = ' ';
	// Row 4
	DinosaurRight_[3][0] = '/';
	DinosaurRight_[3][1] = '-';
	DinosaurRight_[3][2] = '|';
	DinosaurRight_[3][3] = '_';
	DinosaurRight_[3][4] = '|';
	DinosaurRight_[3][5] = ' ';
	DinosaurRight_[3][6] = '|';
	DinosaurRight_[3][7] = '_';
	DinosaurRight_[3][8] = '|';
	DinosaurRight_[3][9] = ' ';
	DinosaurRight_[3][10] = ' ';
	DinosaurRight_[3][11] = ' ';

	this->DinosaurLeft_ = new char* [4];
	for (int i = 0; i < 4; ++i)
		DinosaurLeft_[i] = new char[12];

	/* [4][12]
	 __
	(_ \_/\/\_
	  \   _   \
	   |_| |_|-\
	*/

	// Row 1
	DinosaurLeft_[0][0] = ' ';
	DinosaurLeft_[0][1] = '_';
	DinosaurLeft_[0][2] = '_';
	DinosaurLeft_[0][3] = ' ';
	DinosaurLeft_[0][4] = ' ';
	DinosaurLeft_[0][5] = ' ';
	DinosaurLeft_[0][6] = ' ';
	DinosaurLeft_[0][7] = ' ';
	DinosaurLeft_[0][8] = ' ';
	DinosaurLeft_[0][9] = ' ';
	DinosaurLeft_[0][10] = ' ';
	DinosaurLeft_[0][11] = ' ';
	// Row 2
	DinosaurLeft_[1][0] = '(';
	DinosaurLeft_[1][1] = '_';
	DinosaurLeft_[1][2] = ' ';
	DinosaurLeft_[1][3] = '\\';
	DinosaurLeft_[1][4] = '_';
	DinosaurLeft_[1][5] = '/';
	DinosaurLeft_[1][6] = '\\';
	DinosaurLeft_[1][7] = '/';
	DinosaurLeft_[1][8] = '\\';
	DinosaurLeft_[1][9] = '_';
	DinosaurLeft_[1][10] = ' ';
	DinosaurLeft_[1][11] = ' ';
	// Row 3
	DinosaurLeft_[2][0] = ' ';
	DinosaurLeft_[2][1] = ' ';
	DinosaurLeft_[2][2] = '\\';
	DinosaurLeft_[2][3] = ' ';
	DinosaurLeft_[2][4] = ' ';
	DinosaurLeft_[2][5] = ' ';
	DinosaurLeft_[2][6] = '_';
	DinosaurLeft_[2][7] = ' ';
	DinosaurLeft_[2][8] = ' ';
	DinosaurLeft_[2][9] = ' ';
	DinosaurLeft_[2][10] = '\\';
	DinosaurLeft_[2][11] = ' ';
	// Row 4
	DinosaurLeft_[3][0] = ' ';
	DinosaurLeft_[3][1] = ' ';
	DinosaurLeft_[3][2] = ' ';
	DinosaurLeft_[3][3] = '|';
	DinosaurLeft_[3][4] = '_';
	DinosaurLeft_[3][5] = '|';
	DinosaurLeft_[3][6] = ' ';
	DinosaurLeft_[3][7] = '|';
	DinosaurLeft_[3][8] = '_';
	DinosaurLeft_[3][9] = '|';
	DinosaurLeft_[3][10] = '-';
	DinosaurLeft_[3][11] = '\\';
}

void SpritesModel::initPlayer()
{
	this->PlayerMiddle_ = new char* [4];
	for (int i = 0; i < 4; ++i)
		PlayerMiddle_[i] = new char[5];

	/* [4][5]
	 _0_
	/| |\
	 \_/
	 / \
	*/

	// Row 1
	PlayerMiddle_[0][0] = ' ';
	PlayerMiddle_[0][1] = '_';
	PlayerMiddle_[0][2] = '0';
	PlayerMiddle_[0][3] = '_';
	PlayerMiddle_[0][4] = ' ';
	// Row 2
	PlayerMiddle_[1][0] = '/';
	PlayerMiddle_[1][1] = '|';
	PlayerMiddle_[1][2] = ' ';
	PlayerMiddle_[1][3] = '|';
	PlayerMiddle_[1][4] = '\\';
	// Row 3
	PlayerMiddle_[2][0] = ' ';
	PlayerMiddle_[2][1] = '\\';
	PlayerMiddle_[2][2] = '_';
	PlayerMiddle_[2][3] = '/';
	PlayerMiddle_[2][4] = ' ';
	// Row 4
	PlayerMiddle_[3][0] = ' ';
	PlayerMiddle_[3][1] = '/';
	PlayerMiddle_[3][2] = ' ';
	PlayerMiddle_[3][3] = '\\';
	PlayerMiddle_[3][4] = ' ';
}

void SpritesModel::deleteCar()
{
	for (int i = 0; i < 4; ++i)
	{
		delete[] CarLeft_[i];
		delete[] CarRight_[i];
	}
	delete[] CarLeft_;
	delete[] CarRight_;
}

void SpritesModel::deleteTruck()
{
	for (int i = 0; i < 4; ++i)
	{
		delete[] TruckLeft_[i];
		delete[] TruckRight_[i];
	}
	delete[] TruckLeft_;
	delete[] TruckRight_;
}

void SpritesModel::deleteBird()
{
	for (int i = 0; i < 4; ++i)
	{
		delete[] BirdLeft_[i];
		delete[] BirdRight_[i];
	}
	delete[] BirdLeft_;
	delete[] BirdRight_;
}

void SpritesModel::deleteDinosaur()
{
	for (int i = 0; i < 4; ++i)
	{
		delete[] DinosaurLeft_[i];
		delete[] DinosaurRight_[i];
	}
	delete[] DinosaurLeft_;
	delete[] DinosaurRight_;
}

void SpritesModel::deletePlayer()
{
	for (int i = 0; i < 4; ++i)
		delete[] PlayerMiddle_[i];

	delete[] PlayerMiddle_;
}
