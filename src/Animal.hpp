#ifndef __ANIMAL_HPP__
#define __ANIMAL_HPP__

#include "PhysicalObject.hpp"
#include "Sprite.hpp"
#include <sstream>

/*
* Animal qui est un obstacle.
*/
class Animal : public PhysicalObject
{
	public :
		//Constructeur
		Animal(const char * type, int x, int y);
		//Destructeur
		virtual ~Animal();
		//When the animal gets in contact with the train, change the displayed image of the animal then delete it
		void die();
		//When the train whistles next to the animal, change the displayed image of the animal then delete it
		void flee();

		void build(b2World * world);
		void draw(SDL_Surface * screen, const int & width, const int & height);
		void scroll(int x);
		bool isDie();
		void keyboard( const SDL_KeyboardEvent *event);
	private :
		double m_posX;
		double m_posY;
		const char * m_type;
		bool m_die;//Pour dire quand le train est mort à Bloc
		bool m_tchou;// Pour signaler quand le train a tchou
		bool m_hasEscape;//Il est parti ?
};
#endif
