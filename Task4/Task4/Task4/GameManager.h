#pragma once
#include "String.h"
#include "Player.h"
class GameManager
{
private:
	//Player* m_player = new Player();
	String m_inputString = "";
	bool m_isPlaying = true;
	
public:
	void Process();
};

