#ifndef ENGINE_H_
#define ENGINE_H_

// Forward declarations
union SDL_Event;
struct SDL_Window;

namespace engine {

bool Init(SDL_Window* i_window);
void Update();
void Render();

void RequestShutdown();
bool WasShutdownRequested();

void Shutdown();

} // namespace engine

#endif // ENGINE_H_
