#include "Interface.hpp"
#include "GameEngine.hpp"

/*
 * Constructeur
 */
Interface::Interface()
: m_buttonSelected(-1)
{}

/*
 * Destructeur
 */
Interface::~Interface()
{
	for(unsigned int i = 0; i < m_buttonsImages.size(); ++i)
	{
		delete m_backgroundImages[i];
	}

	for(unsigned int i = 0; i < m_buttonsImages.size(); ++i)
	{
		delete m_buttonsImages[i];
	}
}

/*
 * Charge et stocke les images de l'interface
 * screen : enum correspondant au type d'interface
 */
void Interface::loadImages(const GameScreen & screen)
{
	Sprite * background;
	switch(screen)
	{
		case TITLE :
			background = new Sprite("../img/screens/title_screen.png", 0, 0, 1024, 768);
			assert(background);
			m_backgroundImages.push_back(background);
			break;
		case PAUSE :
			background = new Sprite("../img/screens/ecran1_test3.png", 0, 0, 800, 600);
			assert(background);
			m_backgroundImages.push_back(background);
			break;
	}
}

/*
 * G�re les op�rations de l'interface
 */
void Interface::update()
{
}

/*
 * G�re l'affichage de l'interface
 * screen : fen�tre SDL
 * width : largeur de l'�cran
 * height : hauteur de l'�cran
 */
void Interface::render(SDL_Surface * screen, const int & width, const int & height)
{
	for(unsigned int i = 0; i < m_backgroundImages.size(); ++i)
	{
		Sprite * img = m_backgroundImages[i];
		assert(img);
		img->draw(screen, width, height);
	}
}

/*
 * G�re les �v�nements de mouvement de la souris
 */
void Interface::checkMouseMotionEvent(const SDL_MouseMotionEvent *event)
{

}

/*
 * G�re les �v�nements de la souris
 */
void Interface::checkMouseEvent(GameEngine * gameEngine, const SDL_MouseButtonEvent *event)
{
	if( event->button == int(SDL_BUTTON_LEFT) && event->state == int(SDL_PRESSED) )
	{
		/*m_iMousePositionX = event->x;
		m_iMousePositionY = event->y;
		m_bButtonPressed = true;*/
	}

	if( event->button == int(SDL_BUTTON_LEFT) && event->state == int(SDL_RELEASED) )
	{
		//m_bButtonPressed = false;
		gameEngine->changeScreen(GAME);
	}
}

/*
 * G�re les �v�nements clavier
 */
void Interface::checkKeyboardEvent(const SDL_KeyboardEvent *event)
{
	switch(event->keysym.sym)
	{
		case SDLK_UP :
			std::cout<<"UP arrow"<<std::endl;
			break;
		default:
			break;
	}
}



