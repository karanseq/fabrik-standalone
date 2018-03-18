#ifndef APPLICATION_H_
#define APPLICATION_H_

// Library includes

// External includes

namespace engine {
namespace application {

    class ApplicationInterface
    {
    public:
        ApplicationInterface() = default;
        virtual ~ApplicationInterface() = default;

    public:
        virtual bool Init(int argc, char** argv) = 0;
        virtual void Run() = 0;
        virtual bool Shutdown() = 0;

        virtual void Update() = 0;
        virtual void Render() = 0;

        virtual void ReceiveKeyboardInput(unsigned char key, int x, int y) = 0;

    protected:
        static ApplicationInterface* g_application;

        friend void ApplicationUpdateFunc();
        friend void ApplicationRenderFunc();
        friend void ApplicationKeyboardFunc(unsigned char key, int x, int y);

    }; // ApplicationInterface

    void ApplicationUpdateFunc();
    void ApplicationRenderFunc();
    void ApplicationKeyboardFunc(unsigned char key, int x, int y);

} // namespace application
} // namespace engine

#endif // APPLICATION_H_
