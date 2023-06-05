#include <iostream>
#include "Vector2.h"

void Draw(SDL_Renderer* mRenderer, Vector2 drawPos);
void UpdatePosition(Vector2 newPosition);
bool CheckForCollision(Vector2 RoadLinesPos);

const int ROADLINES_HEIGHT = 16;
const int ROADLINES_WIDTH = 4;

class RoadLine {
    public:
        RoadLine(Vector2 position): position(position) {
            RoadLineRect.x = static_cast<int>(position.x);
            RoadLineRect.y = static_cast<int>(position.y);
            RoadLineRect.w = ROADLINES_WIDTH;
            RoadLineRect.h = ROADLINES_HEIGHT;
        }
    
        Vector2 position;
        SDL_Rect RoadLineRect;

        void Draw(SDL_Renderer* mRenderer, Vector2 drawPos);
        void UpdatePosition(Vector2 newPosition);
        bool CheckForCollision(Vector2 RoadLinesPos);
};

void RoadLine::Draw(SDL_Renderer* mRenderer, Vector2 drawPos) {
    RoadLineRect.x = static_cast<int>(drawPos.x);
    RoadLineRect.y = static_cast<int>(drawPos.y);

    if(RoadLineRect.w != ROADLINES_WIDTH) { RoadLineRect.w = ROADLINES_WIDTH; }
    if(RoadLineRect.h != ROADLINES_HEIGHT) { RoadLineRect.h = ROADLINES_HEIGHT; }
    
    SDL_RenderFillRect(mRenderer, &RoadLineRect);
}

void RoadLine::UpdatePosition(Vector2 newPosition) {
    position = newPosition;
}