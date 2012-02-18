#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include "Bonus.hpp"
#include "Sprite.hpp"

#ifdef _WIN32
#include "Box2D/Box2D.h"
#else
#include <Box2D/Box2D.h>
#endif

enum BlockType
{
	GROUND = 0,
	PRECIPICE,
	STATION,
	TUNNEL,
	JUNCTION_UP,
	JUNCTION_DOWN
};

class Block
{
	public :
		Block(int sizeX);
		void build();
		void scroll(int);
		b2Body * getBody();
		void setBody(b2Body * body);
	private :
		Sprite * m_sprite;
		b2Body * m_body;
		int m_sizeX;
};
#endif
