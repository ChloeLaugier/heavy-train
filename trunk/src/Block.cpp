#include "Block.hpp"


/*
 * Block Constructor
 * sizeX est la dimension du bloc en pixel
 * posX est la position du bloc en pixels dans l'espace
 */

Block::Block(int sizeX, int id, int speed)
: m_type(NOTHING)
, m_posX(-1)
, m_sizeX(sizeX)
, m_id(id)
, m_maxSpeed(speed)
, m_hillSegmentWidth(10)
, m_sizeXMin(256)
, m_sizeXMax(2048)
, m_sizeYMin(384)
, m_y (668)
, m_tunnelHeight (200)
{
	/*SDL_Rect * p1, *p01, *p2, *p3, *p4, *p5, *p6;
	switch(type)
	{
		case GROUND :
			p1 = new SDL_Rect;
			p1->x = posX;
			p1->y = m_y;
			p01 = new SDL_Rect;
			p01->x = 10;
			p01->y = 404;
			p2 = new SDL_Rect;
			p2->x = 256;
			p2->y = 550;
			p3 = new SDL_Rect;
			p3->x = 512;
			p3->y = 600;
			p4 = new SDL_Rect;
			p4->x = 768;
			p4->y = 450;
			p5 = new SDL_Rect;
			p5->x = 1024;
			p5->y = m_y;
			p6 = new SDL_Rect;
			p6->x = posX+sizeX;
			p6->y = m_y;
			m_points.push_back(p1);
			m_points.push_back(p01);
			m_points.push_back(p2);
			m_points.push_back(p3);
			m_points.push_back(p4);
			m_points.push_back(p5);
			m_points.push_back(p6);
			break;
		case PRECIPICE :
			break;
		case STATION :
			break;
		case TUNNEL :
			break;
		default:
			m_sizeX = sizeX;
			break;

	}*/
	m_sprite = NULL;
	SDL_Rect * pos = new SDL_Rect; pos->x = 0; pos->y = m_y;
	m_points.push_back(pos);
	
}

/*
 * Block Constructor
 * sizeX est la dimension du bloc en pixel
 * posX est la position du bloc en pixels dans l'espace
 */

Block::Block(BlockType type, int sizeX, int id, int speed)
: m_type(NOTHING)
, m_posX(-1)
, m_sizeX(sizeX)
, m_id(id)
, m_maxSpeed(speed)
, m_hillSegmentWidth(10)
, m_sizeXMin(256)
, m_sizeXMax(2048)
, m_sizeYMin(384)
, m_y (668)
, m_tunnelHeight (200)
{
	m_sprite = NULL;
	SDL_Rect * pos = new SDL_Rect; pos->x = 0; pos->y = m_y;
	m_points.push_back(pos);
	
}

Block::~Block() 
{
	for( unsigned int i = 0; i < m_points.size(); ++i)
	{
		delete m_points[i];
	}
	for( unsigned int i = 0; i < m_bonus.size(); ++i)
	{
		delete m_bonus[i];
	}
	for( unsigned int i = 0; i < m_animals.size(); ++i)
	{
		delete m_animals[i];
	}

	delete m_sprite;
}

//Attribue un type au bloc
void Block::setBlockType(BlockType type)
{
	if(type > -1 && type < NB_BLOCK_TYPES)
		m_type = type;
}


b2Body * Block::getBody() 
{
	return m_body;
} 

void Block::setBody(b2Body * body) 
{
	m_body = body;
}

//Attribue une posX au bloc
void Block::setPosX(const int & x)
{
	m_posX = x;
}

void Block::addPoint(int x, int y) 
{
	SDL_Rect * pts = new SDL_Rect;
	pts->x = x;
	pts->y = y;
	m_points.push_back(pts);
} 

void Block::setBonus(BonusType type, int x, int y) 
{
	Bonus * bonus = new Bonus(type, x, y);
	m_bonus.push_back(bonus);
}

void Block::setAnimal(const char * type, int x, int y) 
{
	std::cout << "setanimal" << std::endl;
	Animal * animal = new Animal(type, x, y);
	m_animals.push_back(animal);
}

//Retourne l'identifiant du point � l'ordonn�e la plus basse
int Block::getYMinPoint()
{
	int min = 9999999;
	int idMin = -1;
	for(unsigned int i = 0; i < m_points.size(); ++i)
	{
		if(m_points[i]->y < min)
		{
			min = m_points[i]->y;
			idMin = i;
		}
	}

	return idMin;
}
//Retourne l'identifiant du point � l'ordonn�e la plus grande
int Block::getYMaxPoint()
{
	int max = -9999999;
	int idMax = -1;
	for(unsigned int i = 0; i < m_points.size(); ++i)
	{
		if(m_points[i]->y > max)
		{
			max = m_points[i]->y;
			idMax = i;
		}
	}

	return idMax;
}

void Block::createImage()
{
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 rmask = 0xff000000;
		Uint32 gmask = 0x00ff0000;
		Uint32 bmask = 0x0000ff00;
		Uint32 amask = 0x000000ff;
	#else
		Uint32 rmask = 0x000000ff;
		Uint32 gmask = 0x0000ff00;
		Uint32 bmask = 0x00ff0000;
		Uint32 amask = 0xff000000;
	#endif

	switch(m_type)
	{
		case GROUND :
		{
			//Cr�ation du masque
			SDL_Surface * mask = SDL_CreateRGBSurface(SDL_HWSURFACE, m_sizeX, (int) m_sizeYMin, 32, rmask, gmask, bmask, amask);
	
			for(int x = 0; x < m_sizeX; ++x)
			{
				for(int y = 0; y < m_sizeYMin; ++y)
				{
					Sprite::putpixel(mask, x, y, 0xffffffff);
				}
			}
			double x1, y1, x2, y2;
			for(unsigned int i = 1; i < m_groundPoints.size(); ++i)
			{
				//Conversion en m�tre
				x1 = m_groundPoints[i-1].x;
				y1 = m_groundPoints[i-1].y;
				x2 = m_groundPoints[i].x;
				y2 = m_groundPoints[i].y;
				Sprite::convertMetersToPixels(&x1, &y1, WINDOWS_W, WINDOWS_H);
				Sprite::convertMetersToPixels(&x2, &y2, WINDOWS_W, WINDOWS_H);

				//Pour l'image, on retire posX
				x1 -= m_posX;
				x2 -= m_posX;

				//Remplissage du haut de l'�cran par du noir
				int nbSide = 4;
				Sint16 * xPolygon = new Sint16[nbSide];
				Sint16 * yPolygon = new Sint16[nbSide];
				xPolygon[0] = (Sint16) x1; yPolygon[0] = 0;
				xPolygon[1] = (Sint16) x2; yPolygon[1] = 0;
				xPolygon[2] = (Sint16) x2; yPolygon[2] = (Sint16) (y2 - m_sizeYMin);
				xPolygon[3] = (Sint16) x1; yPolygon[3] = (Sint16) (y1 - m_sizeYMin);
				filledPolygonRGBA(mask, xPolygon, yPolygon, nbSide, 0, 0, 0, 255);
				delete [] xPolygon;
				delete [] yPolygon;
			}
	
			//SDL_SaveBMP(mask, "masque.bmp");

			//Chargement de l'image ground
			SDL_Surface * ground = IMG_Load("../img/levels/ground.png");
			if(!ground)
			{
				std::cout<<std::endl;
			}
			//Changement de la taille pour correspondre � la taille du bloc
			ground->w = m_sizeX;
			//SDL_SaveBMP(ground, "ground2.bmp");

			//Construction de l'image du bloc
			SDL_Surface * imageTest = SDL_CreateRGBSurface(SDL_HWSURFACE, m_sizeX, (int) m_sizeYMin, 32, rmask, gmask, bmask, amask);
			Uint32 actualPixel;
			for(int x = 0; x < m_sizeX; ++x)
			{
				for(int y = 0; y < m_sizeYMin; ++y)
				{
					if( Sprite::getpixel(mask, x, y) == 0xff000000)
					{
						actualPixel = 0x00000000;
					}
					else if( Sprite::getpixel(mask, x, y) == 0xffffffff)
					{
						actualPixel = Sprite::getpixel(mask, x, y) & Sprite::getpixel(ground, x, y);
					}
					Sprite::putpixel(imageTest, x, y, actualPixel);
				}
			}

			//SDL_SaveBMP(imageTest, "bloc.bmp");

			m_sprite = new Sprite(imageTest, m_posX, (Sint16) m_sizeYMin, m_sizeX, m_sizeYMin);

			SDL_FreeSurface(mask);
			SDL_FreeSurface(ground);
		}
		break;

		case STATION :
		{
			//Cr�er une image avec du plat et la gare au milieu ?
		}
		break;

		case TUNNEL :
		{
			//Cr�er une image avec les bords du tunnel aux extr�mit�s ?
		}
		break;

		case PRECIPICE :
		{
			//Cr�er une image avec les bords du pr�cipice aux extr�mit�s ?
		}
		break;
	}

	

	
}

void Block::scroll(const int & x)
{
	if(m_sprite)
		m_sprite->setPositionX(m_sprite->getPositionX() + x);

	for (int i=0; i< m_animals.size(); i++) {
		m_animals[i]->scroll(x);
	}
}


void Block::draw(SDL_Surface * screen, const int & width, const int & height)
{
	if(m_sprite)
		m_sprite->draw(screen, width, height);
	
	for (int i=0; i< m_animals.size(); i++) {
		if (m_animals[i]->isDie()) {
			delete m_animals[i];
			 m_animals.erase(m_animals.begin()+i);
			
		}
		else {
			
			m_animals[i]->draw(screen, width, height);
		}
	}

}


void Block::keyboard(const SDL_KeyboardEvent *event){
	for (int i=0; i<m_animals.size(); i++) {
		m_animals[i]->keyboard(event);
	}

}

/*
 * Block construction
 */
int Block::build(b2World * world)
{
	//Taille en m�tre
	/*double size = m_sizeX;
	Sprite::convertPixelsToMeters(&size, NULL, WINDOWS_W, WINDOWS_H);
	//PosX en m�tre
	double pos = m_posX;
	Sprite::convertPixelsToMeters(&pos, NULL, WINDOWS_W, WINDOWS_H);*/



	//construction des animaux
	for (int i=0; i< m_animals.size(); i++) {	
		m_animals[i]->build(world);
	}


	switch(m_type)
	{
		case GROUND:
		{
			//V�rification taille de la future spline
			//On suppose que les points sont dans l'ordre et que le x du premier point > 0
			if(m_points.size() > 1)
			{
				if(m_points[m_points.size() - 1]->x < m_sizeXMin)
				{
					m_points[m_points.size() - 1]->x = (Sint16) m_sizeXMin;
				}
				else if(m_points[m_points.size() - 1]->x > m_sizeXMax)
				{
					m_points[m_points.size() - 1]->x = (Sint16) m_sizeXMax;
				}

				int id = getYMinPoint();
				if( id != -1)
				{
					assert(id < m_points.size());
					if(m_points[id]->y < m_sizeYMin)
					{
						m_points[id]->y = (Sint16) m_sizeYMin;
					}
				}

				id = getYMaxPoint();
				if( id != -1 )
				{
					assert(id < m_points.size());
					if(m_points[id]->y > m_y)
					{
						m_points[id]->y = m_y;
					}
				}
			}
			//Ajout du dernier point
			SDL_Rect * last = new SDL_Rect; last->x = m_sizeX; last->y = m_y;
			m_points.push_back(last);
			
			//Smoothing de la spline et conversion des pixels en m�tres
			b2Vec2 p1, p2;
			b2Vec2 pt1, pt2;
			int hSegments;
			double dx, da, yMid, ampl;
			double x, y;

			for(unsigned int i = 1; i < m_points.size(); ++i)
			{
				p1 = b2Vec2(m_points[i-1]->x + m_posX, m_points[i-1]->y);
				p2 = b2Vec2(m_points[i]->x + m_posX, m_points[i]->y);

				hSegments = (int) floorf( (p2.x - p1.x) / m_hillSegmentWidth );
				dx = (p2.x - p1.x) / hSegments;
				da = M_PI / hSegments;
				yMid = (p1.y + p2.y) / 2.0;
				ampl = (p1.y - p2.y) / 2.0;
 
				pt1 = p1;
				//Conversion en m�tre
				x = pt1.x;
				y = pt1.y;
				Sprite::convertPixelsToMeters(&x, &y, WINDOWS_W, WINDOWS_H);
				pt1.x = (float32) x;
				pt1.y = (float32) y;
				m_groundPoints.push_back(pt1);
				for (int j = 0; j < hSegments + 1; ++j)
				{
					pt2.x = (float32) (p1.x + j*dx);
					pt2.y = (float32) (yMid + ampl * cosf( (float) da*j) );

					//Conversion en m�tre
					x = pt2.x;
					y = pt2.y;
					Sprite::convertPixelsToMeters(&x, &y, WINDOWS_W, WINDOWS_H);
					pt2.x = (float32) x;
					pt2.y = (float32) y;
					m_groundPoints.push_back(pt2);

					pt1 = pt2;
				}
			}

			//Construction du body
			b2BodyDef groundBodyDef;
			groundBodyDef.position.Set(0, 0); //Position � changer plus tard
			m_body = world->CreateBody(&groundBodyDef);

			b2EdgeShape shape;
			for (unsigned int i = 1; i < m_groundPoints.size(); ++i)
			{
				if(i > 1)
				{
					shape.m_hasVertex0 = true;
					shape.m_vertex0 = m_groundPoints[i-2];
				}
			
				if(i < m_groundPoints.size() - 1)
				{
					shape.m_hasVertex3 = true;
					shape.m_vertex3 = m_groundPoints[i+1];
				}

				p1 = m_groundPoints[i-1];
				p2 = m_groundPoints[i];
				shape.Set(p1, p2);
				m_body->CreateFixture(&shape, 0);
			}
		}

		std::cout<<"GROUND!!"<<std::endl;
		break;

		/*case STATION :
		{
			//On suppose que la taille de la gare est sup�rieure � z�ro
			b2BodyDef groundBodyDef;
			groundBodyDef.position.Set(pos, 0); //Position � changer plus tard
			m_body = world->CreateBody(&groundBodyDef);

			b2EdgeShape shape;
			//Attention aux blocs mitoyens : y'a t-il besoin de mettre shape.m_hasVertex0 et shape.m_hasVertex3 ?
			double x1 = m_posX, y1 = m_sizeYMin;
			double x2 = m_posX + m_sizeX, y2 = m_sizeYMin;
			Sprite::convertPixelsToMeters(&x1, &y1, WINDOWS_W, WINDOWS_H);
			Sprite::convertPixelsToMeters(&x2, &y2, WINDOWS_W, WINDOWS_H);
			b2Vec2 p1((float32) x1, (float32) y1);
			b2Vec2 p2((float32) x2, (float32) y2);
			shape.Set(p1, p2);
			m_body->CreateFixture(&shape, 0);
			break;
		}*/

		case TUNNEL :
		{
			//On suppose que la taille du tunnel est sup�rieure � z�ro
			b2BodyDef groundBodyDef;
			groundBodyDef.position.Set(0, 0); //Position � changer plus tard
			m_body = world->CreateBody(&groundBodyDef);

			//Attention aux blocs mitoyens : y'a t-il besoin de mettre shape.m_hasVertex0 et shape.m_hasVertex3 ?

			//Sol du tunnel
			b2EdgeShape sol;
			double x1 = m_posX, y1 = m_y;
			double x2 = m_posX + m_sizeX, y2 = m_y;
			Sprite::convertPixelsToMeters(&x1, &y1, WINDOWS_W, WINDOWS_H);
			Sprite::convertPixelsToMeters(&x2, &y2, WINDOWS_W, WINDOWS_H);
			b2Vec2 p1((float32) x1, (float32) y1);
			b2Vec2 p2((float32) x2, (float32) y2);
			sol.Set(p1, p2);
			m_body->CreateFixture(&sol, 0);

			//Sol du tunnel
			b2EdgeShape plafond;
			x1 = m_posX; y1 = m_y - m_tunnelHeight;
			x2 = m_posX + m_sizeX; y2 = m_y - m_tunnelHeight;
			Sprite::convertPixelsToMeters(&x1, &y1, WINDOWS_W, WINDOWS_H);
			Sprite::convertPixelsToMeters(&x2, &y2, WINDOWS_W, WINDOWS_H);
			p1.x = (float32) x1; p1.y = (float32) y1;
			p2.x = (float32) x2; p2.y = (float32) y2;
			plafond.Set(p1, p2);
			m_body->CreateFixture(&plafond, 0);
		}
		std::cout<<"TUNNEL!!"<<std::endl;
		break;

		case PRECIPICE :
		{
			//Pas de body
		}
		std::cout<<"TROUUUU!!"<<std::endl;
		break;
	}


	//Construction de l'image
	createImage();

	return m_sizeX;
}
