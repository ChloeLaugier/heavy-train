#include "Level.hpp"
/*Level Constructor */
Level::Level(b2World * world, unsigned int level, unsigned int island) 
: m_world (world)
, m_departureTime(NULL)
, m_position(NULL)
, m_islandNum(island)
, m_levelNum(level)
{
    //All the blocks of the level
	//m_blocks.push_back(new Block(GROUND, 2048, 0, 0));

    //m_backgroundImages = ;
    //m_idStations= ...;
	
	//m_backgroundImages.push_back(new Sprite("../img/niveau2/sky.png",  0, 0, 1024, 768));
	//m_backgroundImages.push_back(new Sprite("../img/niveau2/moutains.png", 0, 350, 1024, 350));
	//m_backgroundImages.push_back(new Sprite("../img/niveau2/tree.png", 0, 0, 1024, 768));

	loadAndBuild();
	buildBlocks();
}

Level::~Level() 
{
	for(unsigned int i = 0; i < m_blocks.size(); ++i)
	{
		delete m_blocks[i];
	}

	for(unsigned int i = 0; i < m_backgroundImages.size(); ++i)
	{
		delete m_backgroundImages[i];
	}

	delete m_position;
}

Block * Level::getBlock(unsigned int i)
{
	if(i < m_blocks.size() )
	{
		return m_blocks.at(i);
	}
	return NULL;

}

/*
 * R�initialise les valeurs des PhysicalObjects apr�s un smooth pour coller au framerate
 */
void Level::clearAllSmoothAngleAndPosition()
{

}


/*
 * Move the level horizontally
 */
void Level::scrollLevel(const int & x)
{
	//Blocks
	for(unsigned int i = 0; i < m_blocks.size(); ++i)
	{
		m_blocks[i]->scroll(x);
	}

	//Backgrounds
	for(unsigned int i = 1; i < m_backgroundImages.size(); ++i)
	{
		int newX = (int) ( x + ( double(x) * i * 0.25) );
		m_backgroundImages[i]->setPositionX(m_backgroundImages[i]->getPositionX() + newX);
	}
}

/*
 * Load and build the level n�lvl of the island n�isle
 */
void Level::loadAndBuild()
{
	TiXmlDocument doc("../levels/levels.xml");
	int num, sizeX, speed = -1;
	Block * vBlock;
	Station * vStation;

	if(!doc.LoadFile())
	{
		std::cerr << "erreur lors du chargement du XML block" << std::endl;
		std::cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
		exit(0);
	}
	else
	{
		//permet de s�curiser le pacours des noeud (dans le cas ou l'un des noeuds n'existerait pas)
		TiXmlHandle hdl(&doc);
		std::cerr << "Level.cpp : apr�s TiXmlHandle hdl(&doc) " << std::endl;
		TiXmlElement *island = hdl.FirstChildElement().FirstChildElement().Element();
		TiXmlElement *contenuBlock = hdl.FirstChildElement().FirstChildElement().FirstChildElement().FirstChildElement().FirstChildElement().Element();
		
		while (island)
		{
			//si l'id du level correspond � m_islandNum, on entre dans le if
			if(atoi(island->Attribute("id")) == m_islandNum)
			{
				TiXmlElement *level = island->FirstChildElement();
				//on entre dans la balise island et on check toutes les balises level
				while (level)
				{
					//si l'id du level correspond � m_levelNum, on entre dans le if pour pouvoir checker toutes les balises du level choisi
					if(atoi(level->Attribute("id")) == m_levelNum)
					{
						TiXmlElement *contenuLevel = level->FirstChildElement();
						while (contenuLevel)
						{
							//si la balise dans level correspond a la balise block on entre dans ce if
							if (strcmp(contenuLevel->Value(),"block")==0)
							{
								//on est dans une balise block !
								num = atoi(contenuLevel->Attribute("num") );
								sizeX = atoi(contenuLevel->Attribute("size") );
								if(contenuLevel->Attribute("speed"))
								{
									speed = atoi(contenuLevel->Attribute("speed") );
								}

								vBlock = new Block(sizeX, num, speed);

								if (strcmp(contenuLevel->Attribute("type"),"GROUND")==0)
								{
									vBlock->setBlockType(GROUND); // smartpointer

									//variable element qui check les balises contenu dans block
									TiXmlElement *contenuBlock = contenuLevel->FirstChildElement();
									while (contenuBlock)
									{
										if (strcmp(contenuBlock->Value(),"obstacle")==0)
										{
											if (strcmp(contenuBlock->Attribute("type"),"animal") == 0)
											{
												vBlock->setAnimal(contenuBlock->Attribute("nom"), atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
											}
											else if (strcmp(contenuBlock->Attribute("type"),"bonus") == 0)
											{
												if (strcmp(contenuBlock->Attribute("nom"),"etoile") == 0)
												{
													vBlock->setBonus(STAR_DUST, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
												}
												else if (strcmp(contenuBlock->Attribute("nom"),"accelerateur") == 0)
												{
													vBlock->setBonus(ACCELERATOR, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
												}
											}
										}
										else if (strcmp(contenuBlock->Value(),"point")==0)
										{
											vBlock->addPoint(atoi(contenuBlock->Attribute("x")), atoi(contenuBlock->Attribute("y")));
										}
										contenuBlock = contenuBlock->NextSiblingElement();
									}// fin du while dans le block
								}
								else if (strcmp(contenuLevel->Attribute("type"),"PRECIPICE")==0)
								{
									vBlock->setBlockType(PRECIPICE);
									
									//variable element qui check les balises contenu dans block
									TiXmlElement *contenuBlock = contenuLevel->FirstChildElement();
									while (contenuBlock)
									{
										if (strcmp(contenuBlock->Value(),"obstacle")==0)
										{
											if (strcmp(contenuBlock->Attribute("type"),"bonus") == 0)
											{
												if (strcmp(contenuBlock->Attribute("nom"),"STAR_DUST") == 0)
												{
													vBlock->setBonus(STAR_DUST, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
												}
												else if (strcmp(contenuBlock->Attribute("nom"),"ACCELERATOR") == 0)
												{
													vBlock->setBonus(ACCELERATOR, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
												}
											}
										}
										contenuBlock = contenuBlock->NextSiblingElement();
									}// fin du while dans le block
								}
								else if (strcmp(contenuLevel->Attribute("type"),"TUNNEL")==0)
								{
									vBlock->setBlockType(TUNNEL);
									
									//variable element qui check les balises contenu dans block
									TiXmlElement *contenuBlock = contenuLevel->FirstChildElement();
									while (contenuBlock)
									{
										if (strcmp(contenuBlock->Value(),"obstacle")==0)
										{
											if (strcmp(contenuBlock->Attribute("type"),"animal") == 0)
											{
												vBlock->setAnimal(contenuBlock->Attribute("nom"), atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
											}
											else if (strcmp(contenuBlock->Attribute("type"),"bonus") == 0)
											{
												if (strcmp(contenuBlock->Attribute("nom"),"STAR_DUST") == 0)
												{
													vBlock->setBonus(STAR_DUST, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
												}
												else if (strcmp(contenuBlock->Attribute("nom"),"ACCELERATOR") == 0)
												{
													vBlock->setBonus(ACCELERATOR, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
												}
											}
										}
										contenuBlock = contenuBlock->NextSiblingElement();
									}// fin du while dans le block
								}
								else if (strcmp(contenuLevel->Attribute("type"),"JUNCTION_UP")==0 || strcmp(contenuLevel->Attribute("type"),"JUNCTION_DOWN")==0)
								{
									if (strcmp(contenuLevel->Attribute("type"),"JUNCTION_UP")==0)
									{
										vBlock->setBlockType(JUNCTION_UP);
									}
									else if (strcmp(contenuLevel->Attribute("type"),"JUNCTION_DOWN")==0)
									{
										vBlock->setBlockType(JUNCTION_DOWN);
									}
								}
								m_blocks.push_back(vBlock);
							}
							else if (strcmp(contenuLevel->Value(),"station")==0)
							{
								//on est dans la balise station / gare
								num = atoi(contenuLevel->Attribute("num"));
								sizeX = atoi(contenuLevel->Attribute("size"));

								vStation = new Station(sizeX, num); // smartpointer

								//variable element qui check les balises contenu dans block
								TiXmlElement *contenuStation = contenuLevel->FirstChildElement();
								while (contenuStation)
								{
									if (strcmp(contenuStation->Value(),"option")==0)
									{
										vStation->setTime(atoi(contenuStation->Attribute("hours")), atoi(contenuStation->Attribute("minutes")));
										vStation->setLeaving(atoi(contenuStation->Attribute("leaving")));
										vStation->setEnter(atoi(contenuStation->Attribute("entering")));
									}
									contenuStation = contenuStation->NextSiblingElement();
								}
								m_blocks.push_back(vStation);
								
							}
							else if (strcmp(contenuLevel->Value(),"infobulle")==0)
							{
								//on est dans la balise infobulle
								if (strcmp(contenuLevel->Attribute("type"),"standard") == 0)
								{
									/*StandardTip * infoStandard = new StandardTip();
									infoStandard->setAction(contenuLevel->Attribute("action"));
									infoStandard->setDeclenche(contenuLevel->Attribute("declenche"));
									TiXmlElement *contenuBulle = contenuLevel->FirstChildElement();
									while (contenuBulle){
										if (strcmp(contenuBulle->Value(),"sprite")==0){
											infoStandard->setSprite(contenuBulle->Attribute("img"));
										}
										contenuBulle = contenuBulle->NextSiblingElement();
									}*/
								}
								else if (strcmp(contenuLevel->Attribute("type"),"aide") == 0)
								{
									/*HelpTip * infoAide = new HelpTip();
									infoAide->setNumBlock(contenuLevel->Attribute("numBlock"));
									infoAide->setDeclenche(contenuLevel->Attribute("declenche"));
									TiXmlElement *contenuBulle = contenuLevel->FirstChildElement();
									while (contenuBulle){
										if (strcmp(contenuBulle->Value(),"sprite")==0){
											infoAide->setSprite(contenuBulle->Attribute("img"));
										}
										contenuBulle = contenuBulle->NextSiblingElement();
									}*/
								}
							}

							//}
							contenuLevel = contenuLevel->NextSiblingElement(); // iteration 
			
						} //fin while contenuLevel

					} //fin if level
					level = level->NextSiblingElement(); // iteration 
				} //fin while level
			} //fin if island
			island = island->NextSiblingElement(); // iteration 
		} //fin while island
	}
}

//Construit tous les blocs
void Level::buildBlocks()
{
	int posX = 0;
	for(unsigned int i = 0; i < m_blocks.size(); ++i)
	{
		m_blocks[i]->setPosX(posX);
		posX += m_blocks[i]->build(m_world);
	}
}

void Level::render(SDL_Surface * screen, int w, int h)
{
	drawBackgrounds(screen,  w,  h);
	drawBlocks(screen, w, h);
}

/*
 * Level dessine tous les blocs du vector
 */
void Level::drawBlocks(SDL_Surface * screen, int w, int h)
{
	for (unsigned int i=0; i<m_blocks.size(); i++) 
	{
		m_blocks.at(i)->draw( screen, w, h);
	}
}


/*
 * Level dessine les fonds d'�cran
 */
void Level::drawBackgrounds(SDL_Surface * screen, int w, int h)
{
	for(int i = 0; i < m_backgroundImages.size(); ++i)
	{
		m_backgroundImages[i]->draw(screen, w, h); 
	}
}
