#pragma once
#include <cstdint>
#include <vector>

namespace dbf
{
	class InputSystem
	{
	public:
		enum State
		{
			Idle,
			Pressed,
			Held,
			Released
		};


	public:
		InputSystem() = default;
		~InputSystem() = default;

		void Initialize();
		void Shutdown();

		void Update();

		bool GetKeyDown(int key) { return m_keyboardState[key]; }

	private:
		int m_numKeys;

		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyboardState;
	};

	extern const uint32_t key_space;
	extern const uint32_t key_up;
	extern const uint32_t key_down;
	extern const uint32_t key_left;
	extern const uint32_t key_right;
	extern const uint32_t key_escape;
}
