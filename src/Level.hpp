#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#ifdef _WIN32
#include "SDL/SDL.h"
#include "tinyXML/tinyxml.h"
#include "SDL/SDL_image.h"
#else
#include <SDL/SDL.h>
#include <tinyxml.h>
#include <SDL/SDL_image.h>
#endif

#include <map>
#include "Sprite.hpp"
#include "Block.hpp"
#include "Time.hpp"

class Level
{
	public :
		//Constructor
		Level();
		//Destructor
		//virtual ~Level();
		//Move the level horizontally
		void scrollLevel(const int & x);
		//Load and build the level n�lvl of the island n�isle
		void loadAndBuild(const int & isle, const int & lvl);
		Block * getBlock(int i);
	private :
		//All the blocks of the level
		std::vector<Block*>	m_blocks;
		//Departure time of the level
		Time* m_departureTime;
		//Position of the level at the screen (bottom-left of the first block)
		SDL_Rect*	m_position;
		//Numero of the level�s island
		int	m_islandNum;
		//Numero of the level
		int	m_levelNum;
		//Background image of the level and moving speed
		std::map<Sprite, int> m_backgroundImages;
		//Numeros of the blocks which are stations
		std::vector<int> m_idStations;
};
#endif
