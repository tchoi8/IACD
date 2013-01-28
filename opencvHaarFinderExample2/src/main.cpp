#include "ofAppGlutWindow.h"
#include "testApp.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1444, 680, OF_WINDOW);
	ofRunApp(new testApp());
}
