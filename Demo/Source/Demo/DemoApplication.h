#ifndef DEMO_APPLICATION_H_
#define DEMO_APPLICATION_H_

// Library includes

// External includes

// Engine includes
#include "Application/GLApplication.h"

class DemoApplication : public engine::application::GLApplication
{
public:
    DemoApplication() = default;
    virtual ~DemoApplication() = default;

    // ApplicationInterface implementation
public:
    bool Init(int argc, char** argv) override;
    bool Shutdown() override;

    void Update() override;
    void Render() override;

    void ReceiveKeyboardInput(unsigned char key, int x, int y) override;

}; // class DemoApplication

#endif // DEMO_APPLICATION_H_
