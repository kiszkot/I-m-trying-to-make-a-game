#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"

GameObject * player;
Map * map;

SDL_Renderer * Game::renderer = nullptr;

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

    player = new GameObject("assets/spriteTable.png", 0, 0);
    map = new Map();

}

/**
 * Handles various game event
 * **/

void Game::handleEvents() {
    SDL_Event event;
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

    player -> Update();

}

/**
 * Renders sprites on screen from back to front
 * **/

void Game::render() {
    SDL_RenderClear(renderer);

    // Add your render crap here
    // Background first, stuff on top last

    //map -> DrawMap();
    player -> Render();

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