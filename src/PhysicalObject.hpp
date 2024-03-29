#ifndef __PHYSICAL_OBJECT_HPP__
#define __PHYSICAL_OBJECT_HPP__

#ifdef _WIN32
#include "Box2D/Box2D.h"
#include "SDL/SDL_mixer.h"
#else
#include <Box2D/Box2D.h>
#include <SDL/SDL_mixer.h>
#endif

#include "Sprite.hpp"

#define INFINITE 999999.0

enum _entityCategory 
{
    TRAIN =				0x0001,
    PASSENGER =		    0x0002,
    OBSTACLE_SENSOR =	0x0004,
};

class PhysicalObject
{
	public :
		PhysicalObject();
		PhysicalObject(Sprite * sprite);
		virtual ~PhysicalObject();

		//Retourne m_body
		b2Body * getBody();
		//Attribue un body
		void setBody(b2Body * body);
		//Retourne le m_sprite
		Sprite * getSprite();

		//Mets � jour les positions et angle actuelle et de la derni�re frame
		void updatePositions(b2Vec2 pos, double angle);
		void updatePreviousPositions(b2Vec2 pos, double angle);

		//Pointeur vers le m_world de ActualGame
		static b2World * m_world;
		//Ratio calcul� en fonction du framerate
		static double fixedTimestepAccumulatorRatio;

		//Retourne la position du body
		b2Vec2 getPosition();
		//Retourne l'angle du body
		double getAngle();
		b2Vec2 getPreviousPosition();
		double getPreviousAngle();
	protected :
		//Body of the physical object
		b2Body * m_body;
		//Sprite of the physical Object
		Sprite * m_sprite;

		//Position de m_body smooth�e
		b2Vec2 m_smoothedPosition;
		//Position de m_body au dernier pas de simulation
		b2Vec2 m_previousPosition;
		//Position de m_body au dernier pas de simulation
		b2Vec2 m_previousPosition2;
		//Angle de m_body smooth�e
		double m_smoothedAngle;
		//Angle de m_body au dernier pas de simulation
		float m_previousAngle;
};
#endif