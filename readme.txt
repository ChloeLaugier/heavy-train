==== INSTALLATION =====
Tout d'abord, j'esp�re que vous n'avez pas plac� le dossier SVN HeavyTrain � un endroit o� le chemin est constitu� d'un accent (ex : Document/C�line/HeavyTrain) Si c'est le cas, changez son emplacement, car Cmake n'aime pas les accents.

Sous Linux, vous avez besoin des biblioth�ques suivantes :
SDL
SDL_image
SDL_ttf
SDL_mixer
SDL_gfx
smpeg
tinyXML

Sous Windows :
1. Installer Cmake : http://www.cmake.org/cmake/resources/software.html et Visual C++ Express 2010 : http://www.microsoft.com/visualstudio/en-us/products/2010-editions/visual-cpp-express
2. Lancez cmake-gui
3. Compl�tez les deux champs du haut avec :
 - Where is the source code : [chemin du SVN]
 - Where to build the binaries : [chemin du SVN]/windows
4. Cliquez sur "Configure" puis choisissez "Visual Studio 10" puis cliquez sur OK
5. Cliquez une seconde fois sur "Configure" puis ensuite sur "Generate"
6. C'est fini ! Lancez le projet Visual Studio "HeavyTrain.vcproj" du r�pertoire "windows", puis clic droit sur le projet dans Visual Studio et choisissez "D�finir le projet comme projet de d�marrage". Heavy Train devrait maintenant �tre �crit en gras. Faites F7 pour compiler et F5 pour compiler puis lancez le programme.

Sous Linux
1. Avec des apt-get ou avec l'installeur Synaptic, installez Cmake et tinyXml.
2. Installez Box2D en t�l�chargeant l'archive suivante (http://code.google.com/p/box2d/downloads/detail?name=Box2D_v2.2.1.zip&can=2&q=) et suivez les indications du fichier build.txt
3. Lancez cmake-gui
4. Compl�tez les deux champs du haut avec :
 - Where is the source code : [chemin du SVN]
 - Where to build the binaries : [chemin du SVN]/linux
5. Cliquez sur "Configure" puis choisissez "Unix Makefile" puis cliquez sur OK
6. Cliquez une seconde fois sur "Configure" puis ensuite sur "Generate"
7. C'est fini ! Le makefile se situe dans le r�pertoire "linux"

==== CREER SES NIVEAUX =====
Vous voulez cr�er votre propre niveau ?
Aucun probl�me, notre jeu le permet et m�me l'encourage !
(je le finirais demain promis)