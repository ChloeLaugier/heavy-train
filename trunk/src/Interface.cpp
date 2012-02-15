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
	//TODO : voir si tout est bien delete
	SDL_Rect * position = new SDL_Rect;
	SDL_Rect * size = new SDL_Rect;
	Sprite * background;
	switch(screen)
	{
		case TITLE :
			assert(position);
			position->x = 0;
			position->y = 0;
			assert(size);
			size->x = 1024;
			size->y = 768;
			background = new Sprite("../img/screens/title_screen.png", position, size);
			assert(background);
			m_backgroundImages.push_back(background);
			break;
		case PAUSE :
			assert(position);
			position->x = 0;
			position->y = 0;
			assert(size);
			size->x = 800;
			size->y = 600;
			background = new Sprite("../img/screens/ecran1_test3.png", position, size);
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
		gameEngine->changeScreen(PAUSE);
	}
}

/*
 * G�re les �v�nements clavier
 */
void Interface::checkKeyboardEvent(const SDL_KeyboardEvent *event)
{
	switch(event->keysym.sym)
	{
		case SDLK_UP : {
			std::cout<<"UP arrow"<<std::endl;

			break;
		}
		default:
			break;
	}
}



