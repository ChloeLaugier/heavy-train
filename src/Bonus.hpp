#ifndef __BONUS_HPP__
#define __BONUS_HPP__

#include "Sprite.hpp"
#include "PhysicalObject.hpp"

enum BonusType
{
	STAR_DUST = 0,
	ACCELERATOR
};

class Bonus : public PhysicalObject
{
	public :
		Bonus(BonusType type, int posX, int posY);
		~Bonus();
		//Return the type of the Bonus
		BonusType getType();
		//Return m_used
		bool isUsed();
		void build(b2World * world);
		void setIsUsed(bool b);
		void draw(SDL_Surface * screen, const int & width, const int & height);
		void scroll(const int & x);
	private :
		int m_posX;
		int m_posY;
		// Bonus type
		BonusType m_type;
		// False if the bonus is not used yet
		bool m_isUsed;
		//Acceleration value if accelerator is used
		static int m_speedAccelerator;
};
#endif