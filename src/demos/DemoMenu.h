#pragma once

#include "Demo.h"
#include <functional>
#include <iostream>
#include <vector>
#include <string>

namespace Demo {
	class DemoMenu : public Demo {
	public:
		DemoMenu(Demo*& currentDemo);

		void onImGuiRender() override;

		template<typename T>
			void registerDemo(const std::string& name) {
			std::cout << "Registering demo: " << name << std::endl;
			m_demos.push_back(std::make_pair(name, []() { return new T(); }));
		}
	private:
		Demo*& m_currentDemo;
		std::vector<std::pair<std::string, std::function<Demo*()>>> m_demos;
	};
}
