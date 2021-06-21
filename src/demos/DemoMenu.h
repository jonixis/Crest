#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <string>

#include "Demo.h"
#include "DemoModelLoader.h"
#include "InputManager.h"

namespace Demo {

    class DemoMenu : public Demo {

    public:

        DemoMenu(Demo *&currentDemo);

        void onImGuiRender() override;

        template<typename T>
        void registerDemo(const Settings& settings) {
            std::cout << "Registering demo: " << settings.name << std::endl;
            m_demos.push_back(std::make_pair(settings.name, [settings]() { return new T(settings); }));
        }

        template<typename T>
        void registerDemo(const Settings& settings, const std::shared_ptr<InputManager>& inputManager) {
            std::cout << "Registering demo: " << settings.name << std::endl;
            m_demos.push_back(std::make_pair(settings.name, [settings, inputManager]() { return new T(settings, inputManager); }));
        }

    private:

        Demo *&m_currentDemo;
        std::vector<std::pair<std::string, std::function<Demo *()>>> m_demos;

    };
}
