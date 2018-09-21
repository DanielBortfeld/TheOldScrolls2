// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef UI_H
#define UI_H

#include "UIText.h"

#include <memory>

struct UI
{
	std::weak_ptr<UIText> hitPointsText;
	std::weak_ptr<UIText> scoreText;
};

#endif // !UI_H
