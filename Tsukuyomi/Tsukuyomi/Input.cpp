#include "stdafx.h"

#include "Input.h"

Input::Input()
{
	for(int i = 0; i < 256; ++i)
		m_keys[i] = false;
}

Input::Input(const Input& input)
{

}

Input::~Input()
{

}

void Input::pushDown(const unsigned& n)
{
	m_keys[n] = true;
}

void Input::pullUp(const unsigned& n)
{
	m_keys[n] = false;
}

bool Input::isDown(const unsigned& n)
{
	return m_keys[n];
}

void Input::setFunctionOnKeyDown(std::function<void(void)> f, const unsigned& n)
{
	Command tmp;
	tmp.setFunction(f);
	auto it = m_keyDown.find(n);

	if(it != m_keyDown.end())
	{
		m_keyDown.erase(it);
	}

	m_keyDown.insert(std::pair<unsigned, Command>(n, tmp));

}

void Input::execKeysDown()
{
	for(auto& it : m_keyDown)
	{
		if(m_keys[it.first])
			it.second.execute();
	}
}