#include "GameEngine.hpp"

SDL_Surface * Sprite::screen;

/*
 * Constructeur
 */

GameEngine::GameEngine()
: m_actualGameScreen(TITLE)
, m_nbAvailableIslands(1)
, m_nbAvailableLevels(1)
, m_screen(NULL)
, m_windowsWidth(WINDOWS_W)
, m_windowsHeight(WINDOWS_H)
, m_isRunning(true)
, m_isFullScreen(false)
, m_actualGame(NULL)
{
}

/*
 * Destructeur
 */
GameEngine::~GameEngine()
{
	for(unsigned int i = 0; i < m_interfaces.size(); ++i)
	{
		delete m_interfaces[i];
	}

	if(m_actualGame != NULL)
		delete m_actualGame;

	SDL_FreeSurface(m_screen);

	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}

/*
 * Initialise la fen�tre SDL, SDl_ttf et SDL_mixer
 */
void GameEngine::initSDL()
{
	//SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		std::cerr << "Can't initialize SDL : " << SDL_GetError() << std::endl;
		m_isRunning = false;
	}

	SDL_WM_SetCaption("Heavy Train", NULL);

	m_screen = SDL_SetVideoMode(m_windowsWidth, m_windowsHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	Sprite::screen = m_screen;
	assert(m_screen);

	//SDL_ttf
	TTF_Init();

	//SDL_mixer
	if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		std::cerr << "Can't initialize SDL_mixer " << std::endl;
		m_isRunning = false;
	}
	
	//Framerate
	SDL_initFramerate(&m_FPSManager);
	SDL_setFramerate(&m_FPSManager, 60);
}

/*
 * Cr�e les �crans de jeu
 */
void GameEngine::loadInterfaces()
{
	//TITLE
	Interface * titleScreen = new Interface(TITLE);
	titleScreen->load();
	m_interfaces.push_back(titleScreen);

	//PAUSE
	Interface * pauseScreen = new Interface(PAUSE);
	pauseScreen->load();
	m_interfaces.push_back(pauseScreen);

	//SCORE
	Interface * scoreScreen = new Interface(SCORE);
	scoreScreen->load();
	m_interfaces.push_back(scoreScreen);

	//HELP
	Interface * helpScreen = new Interface(HELP);
	helpScreen->load();
	m_interfaces.push_back(helpScreen);

	//WORLD
	Interface * worldScreen = new Interface(WORLD);
	worldScreen->load();
	m_interfaces.push_back(worldScreen);

	//ISLAND
	Interface * islandScreen = new Interface(ISLAND);
	islandScreen->load();
	m_interfaces.push_back(islandScreen);

	//GAMEOVER
	Interface * gameOverScreen = new Interface(GAMEOVER);
	gameOverScreen->load();
	m_interfaces.push_back(gameOverScreen);

	//ENDGAME
	Interface * endGameScreen = new Interface(ENDGAME);
	endGameScreen->load();
	m_interfaces.push_back(endGameScreen);
}

/*
 * Contient la boucle principale du jeu
 */
void GameEngine::run()
{
	std::cout << "Game Engine run" << std::endl;
	//Initialisation SDL
	initSDL();
	
	//Initialisation de l'interface
	loadInterfaces();

	while(m_isRunning)
	{
		update();
		render();
		SDL_framerateDelay(&m_FPSManager);
		//std::cout<<SDL_getFramerate(&m_FPSManager)<<std::endl;
	}
}



/*
 * G�re les op�rations du jeu
 */
void GameEngine::update()
{
	if(m_actualGameScreen != GAME)
	{
		assert(m_actualGameScreen < m_interfaces.size() );
		m_interfaces[m_actualGameScreen]->update(this);
	}
	else
	{

	}

	SDL_Event event;
	if( SDL_PollEvent(&event) )
	{
		switch (event.type)
		{
			case SDL_QUIT:
				m_isRunning = false;
				break;
			/*case SDL_VIDEORESIZE:
				m_windowsWidth = event.resize.w;
				m_windowsHeight = event.resize.h;
				m_screen = SDL_SetVideoMode(m_windowsWidth, m_windowsHeight, 32, SDL_VIDEORESIZE | SDL_DOUBLEBUF);
				break;
			*/
			case SDL_KEYDOWN:
				/*if(event.key.keysym.sym == SDLK_ESCAPE)
				{
					m_isRunning = false;
				}*/
				if(event.key.keysym.sym == SDLK_F11)
				{
					if(!m_isFullScreen)
					{
						m_screen = SDL_SetVideoMode(m_windowsWidth, m_windowsHeight, 32, SDL_FULLSCREEN | SDL_DOUBLEBUF);
						m_isFullScreen = true;
					}
					else
					{
						m_screen = SDL_SetVideoMode(m_windowsWidth, m_windowsHeight, 32,  SDL_DOUBLEBUF);
						m_isFullScreen = false;
					}

				}
				else
				{
					if(m_actualGameScreen == GAME)
					{
						assert(m_actualGame);
						m_actualGame->checkKeyboardEvent(this, &(event.key));
					}
					else
					{
						m_interfaces[m_actualGameScreen]->checkKeyboardEvent(&(event.key));
					}
				}
				break;
			case SDL_KEYUP:
				if(m_actualGameScreen == GAME)
				{
					assert(m_actualGame);
					m_actualGame->checkKeyboardEvent(this, &(event.key));
				}
				break;
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				if(m_actualGameScreen != GAME)
				{
					m_interfaces[m_actualGameScreen]->checkMouseEvent(&(event.button));
				}
				break;
			case SDL_MOUSEMOTION:
				if(m_actualGameScreen != GAME)
				{
					m_interfaces[m_actualGameScreen]->checkMouseMotionEvent(&(event.motion));
				}
				break;
		}
	}
}

/*
 * G�re l'affichage du jeu
 */
void GameEngine::render()
{
	SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
	
	if(m_actualGameScreen != GAME)
	{
		assert(m_actualGameScreen < m_interfaces.size() );
		m_interfaces[m_actualGameScreen]->render(m_screen, m_windowsWidth, m_windowsHeight);
	}
	else
	{
		m_actualGame->run(this, m_screen, m_windowsWidth, m_windowsHeight);		
	}
	// Met � jour l'affichage
	//SDL_Flip(m_screen);
	SDL_UpdateRect(m_screen, 0, 0, m_windowsWidth, m_windowsHeight);
}

/*
 * Change l'interface actuellement affich�e
 * screen : Enum du nouvel �cran de jeu
 */
void GameEngine::changeScreen(const GameScreen & previousScreen, const GameScreen & screen, int level, int island)
{
	if(screen < NB_SCREENS)
	{
		if(screen == GAME && previousScreen != PAUSE && previousScreen != GAMEOVER)
		{
			//Initialisation d'une partie
			m_actualGame = new ActualGame(level, island);

			//musique
			Mix_AllocateChannels(20);
			Mix_VolumeMusic(MIX_MAX_VOLUME/2);
			Mix_Volume(0, MIX_MAX_VOLUME);
			m_musique = Mix_LoadMUS("../musics/rednex.ogg");
			Mix_PlayMusic(m_musique, -1);

		}
		/*else if(screen == GAME && previousScreen == GAMEOVER)
		{
			m_actualGame->teleportTrainToLastStation();
		}*/

		if(screen == SCORE)
		{
			if(previousScreen == TITLE)
			{
				//On r�cup�re tous les scores du jeu
				m_interfaces[screen]->loadXML(0, 0);
			}
			else if(previousScreen == ISLAND)
			{
				//On r�cup�re les scores du niveau s�lectionn�
				m_interfaces[screen]->loadXML(level, island);
			}
		}
		else if(screen == ENDGAME)
		{
			//On r�cup�re les scores pour le niveau qu'on vient de d�bloquer
			m_interfaces[screen]->setlevelUnlockedSaved(false);
			m_interfaces[screen]->loadXML(level, island);
			m_interfaces[screen]->setActualGameForScores(m_actualGame);
			m_interfaces[screen]->setNameRegistered(false);
		}
		else if(screen == WORLD)
		{
			//On met � jour le nombre d'iles/niveaux d�bloqu�s avant d'afficher l'�cran 
			m_interfaces[screen]->loadXML(-1, -1);
		}
		else if(screen == ISLAND)
		{
			//On met � jour le nombre d'iles/niveaux d�bloqu�s avant d'afficher l'�cran 
			m_interfaces[screen]->loadXML(-1, -1);
		}
		else if( (screen == TITLE && previousScreen == PAUSE) || (screen == TITLE && previousScreen == GAMEOVER) ) 
		{
			Mix_PauseMusic();
			delete m_actualGame;
			m_actualGame = NULL;
		}
		else if(screen == HELP)
		{
			m_interfaces[screen]->setPreviousScreen(previousScreen);
		}

		//Suppression d'un niveau de jeu actuel en changeant d'�cran de jeu autre que PAUSE
		if(previousScreen == GAME && screen != PAUSE /*&& screen != GAMEOVER*/ )
		{
			Mix_PauseMusic();
			delete m_actualGame;
			m_actualGame = NULL;
		}

		m_actualGameScreen = screen;
	}
}

/*
 * Renvoie l'�num de l'interface actuellement affich�e
 */
GameScreen GameEngine::getActualGameScreen()
{
	return m_actualGameScreen;
}

/*
 * Quitte le jeu
 */
void GameEngine::quit()
{
	m_isRunning = false;
}
