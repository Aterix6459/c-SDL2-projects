#include <SDL2/SDL_events.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
using namespace std;


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    const int screen_width = 800;
    const int screen_height = 600;

    // create window
    SDL_Window* window = SDL_CreateWindow("my window", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,\
         screen_width, screen_height, SDL_WINDOW_SHOWN);

    // create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // create rects
    std::vector<SDL_Rect> rects;

    bool isRunning = true;
    SDL_Event event;
    

    while(isRunning){
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: isRunning = false; break;
                case SDL_MOUSEMOTION:
                    if(event.button.button == SDL_BUTTON_LEFT){
                        SDL_Rect rect = {event.button.x - rect.w / 2, event.button.y - rect.h / 2, 10, 10};
                        rects.push_back(rect);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT){
                        SDL_Rect rect = {event.button.x - rect.w / 2, event.button.y - rect.h / 2, 10, 10};
                        rects.push_back(rect);
                    }
                    break;                   
            }
        }
        // window color
        SDL_SetRenderDrawColor(renderer, 13, 213,13,255);
        SDL_RenderClear(renderer);

        // rects color
        SDL_SetRenderDrawColor(renderer, 35,65,24,255);

            rects.erase(std::remove_if(rects.begin(), rects.end(),\
            [](SDL_Rect &rectt) {

                return rectt.x > screen_width || rectt.y > screen_height;
            }
        ), rects.end());

        for(SDL_Rect &rectt : rects){
            // cout << &rectt << endl;
            // rectt.y += 10;
            SDL_RenderFillRect(renderer, &rectt);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    return 1;
}

// run in linux
// g++ many_rects.cpp -o rects -lSDL2  && ./rects
