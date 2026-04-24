/**
 * @file game.cpp
 * @author Nathan, Brayden, Tristan, John
 * @brief
 * @date 11-04-2026
 *
 *
 */

#include "../header/game.h"
#include <SFML/Graphics/RenderWindow.hpp>

Game::Game(sf::RenderWindow &window) {
    mGame.initializeEnemyList(window);
    // mIsDone = false;
    //  mGameState = welcome;
}

// Handle events from input devices and the window
void Game::handleInput(sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            // Close window button clicked.
            window.close();
        }
        // switch (mGameState)
        // {
        // case welcome:
        // std::cout<<"Game::handleInput case welcome" <<std::endl;
        //  mGameState = mWelcomeScreen.handleInput(event, window);
        //  break;
        // case game:
        // std::cout<<"Game::handleInput case game" <<std::endl;
        //  mGameState = mGame.handleInput(event, window);
        //  break;
        // case results:
        // std::cout<<"Game::handleInput case result" <<std::endl;
        //  mGameState=mResults.handleInput(event, window);
        //  break;
        // case quit:
        // std::cout<<"Game::handleInput case quit" <<std::endl;
        //  window.close();
        //  break;
        // }
    }
}

// //Update objects in the scene
// void Game::update(double elapsedTime, sf::RenderWindow& window)
// {
//     switch (mGameState)
//         {
//         // case welcome:
// //std::cout<<"Game::update case welcome" <<std::endl;
//             // mWelcomeScreen.update();
//             // break;
//         case game:
// //std::cout<<"Game::update case game" <<std::endl;
//             mGame.update(elapsedTime, window);
//             break;
//         // case results:
// //std::cout<<"Game::update case result" <<std::endl;
//             // mResults.update();
//             // break;
//         case quit:
// //std::cout<<"Game::update case quit" <<std::endl;
//             window.close();
//             break;
//         }
// }

void Game::update(double elapsedTime, sf::RenderWindow &window) {
    mGame.update(elapsedTime, window);
}

void Game::render(sf::RenderWindow &window) { mGame.render(window); }

sf::Vector2f Game::getJuanPosition() const { return mGame.getJuanPosition(); }

// Render objects from the scene onto the window
//  void Game::render(sf::RenderWindow& window)
//  {
//      window.clear(sf::Color::Black);
//      //mWindow.draw(mJuan);
//      switch (mGameState)
//          {
//          // case welcome:
//          //     mWelcomeScreen.render(window);
//          //     break;
//          case game:
//              mGame.render(window);
//              break;
//          // case results:
//          //     mResults.render(window);
//          //     break;
//          case quit:
//              break;
//          }
//      window.display();
//  }
