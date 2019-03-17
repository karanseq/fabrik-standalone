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
        virtual bool Init() = 0;
        virtual void Run() = 0;
        virtual void Shutdown() = 0;

    protected:
        static ApplicationInterface* g_application;

    }; // ApplicationInterface

} // namespace application
} // namespace engine

#endif // APPLICATION_H_
