#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Demo {

    struct Settings {
        Settings() = default;

        Settings(const std::string &name, const glm::uvec2 &viewPortSize) : name(name), viewPortSize(viewPortSize) {}

        std::string name;
        glm::uvec2 viewPortSize;

    };

    class Demo {

    public:

        Demo() = default;

        Demo(Settings settings) : m_settings(settings) {};

        virtual ~Demo() {};

        virtual void init() {};

        virtual void onUpdate(float deltaTime) {};

        virtual void onRender() {};

        virtual void onImGuiRender() {};

    protected:

        Settings m_settings;

    };
}
