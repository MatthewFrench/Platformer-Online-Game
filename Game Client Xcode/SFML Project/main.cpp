#include <SFML/Graphics.hpp>

#include "Global.h"
#include "ClientController.h"

int FullSendBytes=0;
int FullRecBytes=0;

int main (int argc, const char * argv[])
{
	
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "SFML Client");
	
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	
	ClientController clientController;
	
	// Start the game loop
	while (window.isOpen()) {
		clientController.logic();
		
	    // Process events
	    sf::Event event;
	    while (window.pollEvent(event)) {
	        // Close window : exit
	        if (event.type == sf::Event::Closed) {
	            window.close();
	        }
	        // Escape pressed : exit
	        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
	            window.close();
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)) {
				clientController.pressedLeft();
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)) {
				clientController.pressedRight();
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)) {
				clientController.pressedUp();
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)) {
				clientController.pressedDown();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				clientController.pressedSpace();
			}
			if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)) {
				clientController.releasedLeft();
			}
			if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)) {
				clientController.releasedRight();
			}
			if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)) {
				clientController.releasedUp();
			}
			if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)) {
				clientController.releasedDown();
			}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
				clientController.releasedSpace();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				clientController.pressedMouse(sf::Mouse::getPosition(window).x,
											  sf::Mouse::getPosition(window).y);
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				clientController.releasedMouse();
			}
			if (event.type == sf::Event::MouseMoved) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					clientController.draggedMouse(sf::Mouse::getPosition(window).x,
												  sf::Mouse::getPosition(window).y);
				}
			}
		}
		
		clientController.draw(&window);
		
	    // Update the window
	    window.display();
	}
	
    return EXIT_SUCCESS;
}