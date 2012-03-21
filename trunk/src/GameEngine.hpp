#ifndef __GAME_ENGINE_HPP__
#define __GAME_ENGINE_HPP__

#include "Interface.hpp"
#include "ActualGame.hpp"

#ifdef _WIN32
#include "SDL/SDL.h"
#include "tinyXML/tinyxml.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_framerate.h"
#else
#include <SDL/SDL.h>
#include <tinyxml.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_framerate.h>
#endif

#include <map>

/*
* Classe principale du jeu. Contient les fonctions principale et la boucle de jeu
*/
class GameEngine
{
	public :
		//Contructeur
		GameEngine();
		//Destructeur
		virtual ~GameEngine();

		//Initialise la fen�tre SDL, SDl_ttf et SDL_mixer
		void initSDL();
		//Cr�e les �crans de jeu
		void loadInterfaces();
		//Chargement du XML des scores et des niveaux d�bloqu�s
		void loadXML();
		
		//Contient la boucle principale du jeu
		void run();
		//G�re les op�rations du jeu
		void update();
		//G�re l'affichage du jeu
		void render();

		//Change l'interface actuellement affich�e
		void changeScreen(const GameScreen & previousScreen, const GameScreen & screen, int level = -1, int island = -1);
		//Renvoie l'�num de l'interface actuellement affich�e
		GameScreen getActualGameScreen();

		//Lance une partie
		void startGame();
		//Met en pause le jeu
		void pauseGame();
		//Quitte le jeu
		void quit();

		//Joue une musique
		void playMusic(const int & num);
		//Stoppe la musique actuellement jou�e
		void stopMusic();

	private : 
		//Enum de l'interface actuellement affich�e
		GameScreen					m_actualGameScreen;
		//Toutes les interfaces du jeu
		std::vector<Interface*>		m_interfaces;

		//Nombre de niveaux d�bloqu�s
		unsigned int				m_nbAvailableLevels;
		//Nombre d'�les d�bloqu�es
		unsigned int				m_nbAvailableIslands;
		
		//Ecran SDL 
		SDL_Surface*				m_screen;
		//Gestionnaire de framerate SDL
		FPSmanager					m_FPSManager;
		//Largeur de l'�cran
		int							m_windowsWidth;
		//Hauteur de l'�cran
		int							m_windowsHeight;

		//Quand le jeu est en cours, m_isRunning = true
		bool						m_isRunning;
		//Quand le jeu est en plein �cran, m_isFullScreen = true
		bool						m_isFullScreen;

		//Partie de jeu actuellement jou�e
		ActualGame*					m_actualGame;
		
		//Musique
		Mix_Music *					m_musique;
};

#endif
