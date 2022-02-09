#include "Game.hpp"
#include "TextureManager.hpp"
//#include "GameObject.hpp"
#include "Map.hpp"
//#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

//GameObject * player;
Map * map;

SDL_Renderer * Game::renderer = nullptr;

Manager manager;
SDL_Event Game::event;

std::vector<ColliderComponent *> Game::colliders;

// auto & tile0(manager.addEntity());
// auto & tile1(manager.addEntity());

auto & player(manager.addEntity());
auto & wall(manager.addEntity());

enum groupLabels : std::size_t {
    groupMap,
    groupPlayers,
    groupColliders
};

Game::Game() {}

Game::~Game() {}

/**
 * Initialize everything needed to run SDL, creates a window and a renderer
 * **/

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

    Uint32 flags = 0;
    if(fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Subsystem Initialized ... " << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window) { std::cout << "Window Created" << std::endl; }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
            std::cout << "Renderer Created" << std::endl; 
        }

        isRunning = true;
    } else {
        std::cout << "Not Initialized" << std::endl;
        isRunning = false;
    }

    //player = new GameObject("assets/spriteTable.png", 0, 0);
    map = new Map();

    // ECS Implement
    //newPlayer.addComponent<PositionComponent>();
    //newPlayer.getComponent<PositionComponent>().init();

    /*
    tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
    tile1.addComponent<TileComponent>(250, 250, 32, 32, 1);
    tile1.addComponent<ColliderComponent>("Grass");
    */

    Map::LoadMap("assets/map1.map", 16, 16);

    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("assets/spriteTable.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    wall.addComponent<TransformComponent>(300.0, 300.0, 300, 20, 1);
    wall.addComponent<SpriteComponent>("assets/tileMap.png", 1, 0);
    wall.addComponent<ColliderComponent>("wall");
    wall.addGroup(groupMap);

}

/**
 * Handles various game event
 * **/

void Game::handleEvents() {
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

/** 
 * Updates the game to make stuff happen
 * **/

void Game::update() {

    Vector2D playerPos = player.getComponent<TransformComponent>().position;
    manager.refresh();
    manager.update();

    for(auto & cc : colliders) {
        if(Collision::AABB(player.getComponent<ColliderComponent>(), * cc) &&
            player.getComponent<ColliderComponent>() != * cc) {
        
            //player.getComponent<TransformComponent>().velocity * -2;
            player.getComponent<TransformComponent>().position = playerPos;
        }
    }

    /*
    * std::cout << newPlayer.getComponent<PositionComponent>().x() << " , " <<
    *     newPlayer.getComponent<PositionComponent>().y() << std::endl;
    * */
   
}

auto & tiles(manager.GetGroup(groupMap));
auto & players(manager.GetGroup(groupPlayers));

/**
 * Renders sprites on screen from back to front
 * **/

void Game::render() {
    SDL_RenderClear(renderer);

    // Add your render crap here
    // Background first, stuff on top last

    for(auto & t : tiles) { t -> draw(); }
    for(auto & t : players) { t -> draw(); }

    SDL_RenderPresent(renderer);
}

/**
 * Cleans the game before closing
 * **/

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

void Game::AddTile(int id, int x, int y) {
    auto & tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, id);
    tile.addGroup(groupMap);
}