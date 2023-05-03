#include <iostream>
#include "Ogre.h"
#include "ogre-13.6.4/Components/Bites/include/OgreApplicationContext.h"

// test main stuff doesn't work so can change whatever
int main() {
    OgreBites::ApplicationContext appContext;
    appContext.initApp();

    // create a new Ogre root object
    Ogre::Root* root = Ogre::Root::getSingletonPtr();
    if (!root)
    {
        root = new Ogre::Root();
    }

    // create a new Ogre window
    Ogre::RenderWindow* window = appContext.getRenderWindow();

    // start the Ogre main loop
    appContext.getRoot()->startRendering();

    // cleanup
    appContext.closeApp();
    delete root;

    return 0;
}




