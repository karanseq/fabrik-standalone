#ifndef ENGINE_H_
#define ENGINE_H_

// Forward declarations
union SDL_Event;

namespace engine {

void Init();
void Update();
void Render();
void HandleSDLEvent(const SDL_Event& i_event);

void Pause();
void Resume();
bool IsPaused();

void Shutdown();

} // namespace engine

#endif // ENGINE_H_
