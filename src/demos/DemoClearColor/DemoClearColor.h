#pragma once

#include "Demo.h"

namespace Demo {

    class DemoClearColor : public Demo {

    public:

        DemoClearColor(const Settings &settings);

        ~DemoClearColor();

        void onUpdate(float deltaTime) override;

        void onRender() override;

        void onImGuiRender() override;

    private:

        float m_clearColor[4];

    };

}
