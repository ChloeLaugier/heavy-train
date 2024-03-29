#ifndef __TRAIN_HPP__
#define __TRAIN_HPP__

#ifdef _WIN32
#include "Box2D/Box2D.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#else
#include <Box2D/Box2D.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#endif

#include "Sprite.hpp"
#include "Bonus.hpp"
#include "Wagon.hpp"

class GameEngine;

class Train
{
	public :

	//Constructeur
	Train();
	//Destructeur
	virtual ~Train();

	bool checkiIfTrainIsReturned();
	//Apply the force m_impetus to move the train
	void speedUp();
	//Apply the force -m_impetus to move the train
	void speedDown();
	//Apply the force m_jumpImpetus to make the train jumping
	void jump();
	//Make the train whistling
	void whistle();
	//When the train is stopped at a station, check if he is well-placed, at the center of the platform
	void checkPositionStation(Station *station);
	//When the train derail, change the displayed image of the train then the player restart at the last station reached
	void derail();
	//Use a bonus
	void useBonus(const BonusType& bonus);
	//When the train get in contact with an animal, change the displayed image of the train then the player restart at the last station reached
	void crushAnimal();
	//When the train falls in a precipice, change the displayed image of the train then the player restart at the last station reached
	void die();
	//Return the total number of passengers in the train
	int getNbPassengers();
	//Returne le nombre maximal de passagers pouvant être dans le train
	int getMaxCapacity();
	//Ejects n passengers from the wagons
	void ejectPassengers(int n);
	// Take off passengers at the Station
	void takeOffPassengers(Station *);
	// Take in at the Station
	void takeInPassengers(Station *);
	//Check if the train is shaken
	void isShaken();
	// dessiner le train
	void drawSprite(SDL_Surface * screen, const int & width, const int & height);
	// Creer la physique du train
	void build(b2World * world);

	int getPixelsDistanceBetweenSpriteAndBody();

	void keyboard(GameEngine* g, const SDL_KeyboardEvent *event);

	//Donne la position actuelle de la locomotive
	b2Vec2 getLocoBodyPosition();
	//Donne la taille actuelle de la locomotive
	b2Vec2 getBodySize() { return m_size; };

	float32 getSpeed();
	bool getIsAtStation();
	void setIsAtStation(bool b);
	b2Body * getBody(unsigned int i);
	std::vector<PhysicalObject *> getPhysicalObjects() { return m_physicalObjects; };

	std::vector<Wagon*> getWagons() {return m_wagons;};
	
	Sprite * getSprite() { return m_physicalObjects[0]->getSprite(); };
	void setUsingTimeAccelerator(int );
	void decreaseTimeAccelerator();
   private :
	//Current speed of the train
	int m_actualSpeed;
	//Maximal speed that the train is able to reach
	int m_maxSpeed;
	//Maximal backward speed that the train is able to reach
	int m_maxSpeedBack;
	//Horizontal impetus applied to move the train
	int m_impetus;
	//Vertical impetus applied to make the train jumping
	int m_jumpImpetus;
	//Above 0 if the train is currently using an accelerator bonus. Decrease at each frame
	int m_usingTimeAccelerator;
	//Increase if the train is shaken
	int m_shaken;
	// Sound of the tchoutchou
	Mix_Chunk * m_tchoutchouSound;	
	int m_channel;
	// Sounf of the scared passengers
	Mix_Chunk * m_passengerSound;

	//Physical bodies of the steam engine
	// 3 bodies -- 0: loco - 1: wheel1 - 2: wheel2
	std::vector<PhysicalObject * > m_physicalObjects;
	// joint pour la roue1 
	b2WheelJoint* m_spring1; 
	// joint pour la roue2
	b2WheelJoint* m_spring2; 
	// vitesse du wheel joint
	float32 m_speed; 
	// fréquence du wheel joint
	float32 m_hz; 
	// le saut est lancé
	bool m_isJumping;
	//Si le train est arreté en gare
	bool m_isAtStation;
	// pour joindre les wagons et le train
	b2Joint* m_joints[2];
	//The two wagons of the game
	std::vector<Wagon*> m_wagons;
	//Taille de la locomotive
	b2Vec2	m_size;
	//Nombre de wagons
	unsigned int m_nbWagons;
};
#endif
