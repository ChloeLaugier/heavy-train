#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include "Sprite.hpp"

#include <map>

class GameEngine;

/*
* Type d'interface
*/
enum GameScreen
{
	TITLE = 0,
	PAUSE,
	SCORE,
	HELP,
	WORLD,
	ISLAND,
	ENDGAME,
	GAME,
	NB_SCREENS
};

/*
* Ecran de jeu
*/
class Interface
{
	public :
		//Constructeur
		Interface(GameScreen type);
		//Destructeur
		virtual ~Interface();
 
		//Charge et stocke les images de l'interface
		void loadImages();

		//G�re les op�rations de l'interface
		void update(GameEngine * gameEngine);
		//G�re l'affichage de l'interface
		void render(SDL_Surface * screen, const int & width, const int & height);

		//G�re les �v�nements de mouvement de la souris
		void checkMouseMotionEvent(const SDL_MouseMotionEvent *event);
		//G�re les �v�nements de la souris
		void checkMouseEvent(const SDL_MouseButtonEvent *event);
		//G�re les �v�nements clavier
		void checkKeyboardEvent(const SDL_KeyboardEvent *event);

		//Affiche du texte � l'�cran
		void displayText(SDL_Surface * screen, const SDL_Rect * position, const std::string & text);
		
		//Charge le niveau n�level de l'�le n�island
		std::multimap<std::string, int> loadScores(const int & island, const int & level);
		//Renvoie le nombre d'�les d�bloqu�es
		unsigned int getNbAvailableIslands();
		//Renvoie le nombre de niveaux d�bloqu�s pour la derni�re �le d�bloqu�e
		unsigned int getNbAvailableLevels();

	private :

		//Sprites des images de fond de l'interface
		std::vector<Sprite*>		m_backgroundImages;
		//Sprites des boutons de l'interface
		std::vector<Sprite*>		m_buttonsImages;
		//Type de l'interface
		GameScreen					m_type;
		//Informations souris
		int							m_mousePositionX;
		int							m_mousePositionY;
		int							m_clic;
};

#endif