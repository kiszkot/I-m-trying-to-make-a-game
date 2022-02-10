#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Map * map;

SDL_Renderer * Game::renderer = nullptr;

Manager manager;
SDL_Event Game::event;

std::vector<ColliderComponent *> Game::colliders;

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

    map = new Map();

    // ECS Implement

    Map::LoadMap("assets/map2.map", 16, 16);

    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("assets/spriteTable.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
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

    Vector2D playerPos = player.getComponent<TransformComponent>().previousPos;
    manager.refresh();
    manager.update();

    for(auto & cc : colliders) {
        if(Collision::AABB(player.getComponent<ColliderComponent>(), * cc) &&
            player.getComponent<ColliderComponent>() != * cc) {
        
            //player.getComponent<TransformComponent>().velocity * -2;
            player.getComponent<TransformComponent>().position = playerPos;
            player.getComponent<TransformComponent>().target = playerPos;
        }
    }

    /*
    * std::cout << newPlayer.getComponent<PositionComponent>().x() << " , " <<
    *     newPlayer.getComponent<PositionComponent>().y() << std::endl;
    * */
   
}

auto & tiles(manager.GetGroup(groupMap));
auto & players(manager.GetGroup(groupPlayers));

const char * mapFile = "assets/tileMap.png";

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

void Game::AddTile(int srcX, int srcY, int xpos, int ypos) {
    auto & tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapFile);
    tile.addGroup(groupMap);
}