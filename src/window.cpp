#include <ctime>
#include <iostream>
#include <stdexcept>
#include "../includes/window.hpp"

// Constructeur de la classe, prend le chemin vers la texture des boids en paramètre
Window::Window(const char *path) {
    // On active l'utilisation de Wayland si possible (peut causer des erreurs sinon)
    if (getenv("WAYLAND_DISPLAY")) {
        putenv((char*) "GDK_BACKEND=wayland");
    }

    // On initialise la librairie avec l'utilisation des évènements
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(SDL_GetError());
    }

    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) != 0) {
        throw std::runtime_error(SDL_GetError());
    }

    // On crée la texture des boids à partir d'un bitmap
    if ((surface = SDL_LoadBMP(path)) == NULL) {
        throw std::runtime_error(SDL_GetError());
    }

    if ((texture = SDL_CreateTextureFromSurface(renderer, surface)) == NULL) {
        throw std::runtime_error(SDL_GetError());
    }

    // On définie la seed à partir du temps actuel pour éviter de toujours générer les mêmes nombres
    srand(time(NULL));

    // On remplie la liste de BOID_COUNT boid aléatoires (voir constructeur Boid::Boid)
    boids.reserve(BOID_COUNT);
    for (int i = 0; i < BOID_COUNT; i++) {
        boids.emplace_back();
    }
}

// Permet d'ajouter un boid aux éléments à rendre dans une frame
void Window::renderBoid(const Boid &boid) {
    rect.x = (int) boid.pos.x;
    rect.y = (int) boid.pos.y;

    // On oriente le boid correctement en fonction de sa vitesse
    double angle = atan(boid.vel.y / boid.vel.x) + M_PI_2;
    if (boid.vel.x < 0 && boid.vel.y > 0)
        angle += M_PI;
    else if (boid.vel.x < 0 && boid.vel.y < 0)
        angle -= M_PI;

    // On utilise la bonne couleur et on le rend
    SDL_SetTextureColorMod(texture, boid.r, boid.g, boid.b);
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle*TO_DEG, NULL, SDL_FLIP_NONE);
}

// Logique principale utilisée à chaque frame
void Window::update() {
    SDL_RenderClear(renderer);
    uint32_t now, nextTicks = SDL_GetTicks() + TICK_INTERVAL;

    for (int i = 0; i < boids.size(); i++) {
        Boid& boid = boids.at(i);

        boid.update(boids);
        renderBoid(boid);
    }

    SDL_RenderPresent(renderer);

    // Pour 60 FPS, TICK_INTERVAL vaut 16ms mais le rendu peut prendre moins de 16ms
    // donc on calcule s'il reste du temps à attendre pour avoir un framerate indépendant des perfomances du CPU

    now = SDL_GetTicks();
    if (now < nextTicks) {
        SDL_Delay(nextTicks - now);
    } else {
        std::cout << "Frame took too long to render" << std::endl;
    }
}

// Destructeur appelé en cas de crash ou de fin du programme
Window::~Window() {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
