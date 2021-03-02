#pragma once

namespace Demo {
	class Demo {
	public:
		Demo() {};
		virtual ~Demo() {};

		virtual void onUpdate(float deltaTime) {};
		virtual void onRender() {};
		virtual void onImGuiRender() {};
	};
}
