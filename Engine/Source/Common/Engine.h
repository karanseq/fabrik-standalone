#ifndef ENGINE_H_
#define ENGINE_H_

namespace engine {

void Init();
void Update();
void Render();

void Pause();
void Resume();
bool IsPaused();

void Shutdown();

} // namespace engine

#endif // ENGINE_H_
