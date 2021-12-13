#pragma once

class SpritesModel
{
public:
	static char** CarLeft_, ** CarRight_;
	static char** TruckLeft_, ** TruckRight_;
	static char** BirdLeft_, ** BirdRight_;
	static char** DinosaurLeft_, ** DinosaurRight_;
	static char** PlayerMiddle_;

public:
	SpritesModel();
	~SpritesModel();

	void initCar();
	void initTruck();
	void initBird();
	void initDinosaur();
	void initPlayer();

	void deleteCar();
	void deleteTruck();
	void deleteBird();
	void deleteDinosaur();
	void deletePlayer();

public:
	friend class Scene;
};

