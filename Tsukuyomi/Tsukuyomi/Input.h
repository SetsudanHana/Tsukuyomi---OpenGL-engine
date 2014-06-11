#pragma once

#include "Command.h"

class Input
{
public:

	Input();
	Input(const Input&);
	~Input();

	void pushDown(const unsigned&);
	void pullUp(const unsigned&);
	bool isDown(const unsigned&);

	void setFunctionOnKeyDown(std::function<void(void)>,const unsigned&);

	void execKeysDown();

private:
	bool m_keys[282];
	std::map<unsigned, Command> m_keyDown;
};