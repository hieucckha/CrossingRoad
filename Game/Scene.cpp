#include "Scene.h"

const char Scene::DeadMenu[7][33] = {
	{"################################"},
	{"#                              #"},
	{"#       Your are dead...       #"},
	{"#          Continue?           #"},
	{"#    Y: Restart  Others: End   #"},
	{"#                              #"},
	{"################################"}
};
const char Scene::LoadMenu[16][41] = {
	{"########################################"},
	{"#              LOAD GAME:              #"},
	{"#                                      #"},
	{"#                                      #"}, //Max: 10
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#  Enter load file:                    #"},
	{"########################################"}
};
const char Scene::SaveMenu[5][41] = {
	{"########################################"},
	{"#              SAVE GAME:              #"},
	{"#                                      #"},
	{"#  Name of file:                       #"},
	{"########################################"}
};
const char Scene::PauseMenu[5][41] = {
	{"########################################"},
	{"#                                      #"},
	{"#              PAUSED GAME             #"},
	{"#                                      #"},
	{"########################################"}
};

const char Scene::MainMenu[7][27] = {
	{"##########################"},
	{"#                        #"},
	{"#      N: New Game       #"},
	{"#      T: Load Game      #"},
	{"#      S: Setting        #"},
	{"#                        #"},
	{"##########################"}
};

const char Scene::Setting[7][27] = {
	{"##########################"},
	{"#                        #"},
	{"#   T: Toggle Music      #"},
	{"#                        #"},
	{"#   Others: Back         #"},
	{"#                        #"},
	{"##########################"},
};