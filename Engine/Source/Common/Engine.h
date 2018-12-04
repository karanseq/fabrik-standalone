#ifndef ENGINE_H_
#define ENGINE_H_

// Forward declarations
union SDL_Event;

namespace engine {

bool Init();
void Update();
void Render();
void HandleSDLEvent(const SDL_Event& i_event);

void RequestShutdown();
bool WasShutdownRequested();

void Shutdown();

} // namespace engine

#endif // ENGINE_H_
