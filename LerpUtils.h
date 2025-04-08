/**
 * Includes lerp/easing methods.
 * All in static format for easy access.
 */

#pragma once

#include <cmath>
#include <numbers>

class LerpUtils
{
public:

	enum eEASING_LOGIC
	{
		EaseDirect,
		EaseOutSine,
		EaseOutQuad,
		EaseOutCubic,
		EaseOutQuart,
		EaseOutBack,
		EaseInSine,
		EaseInQuad,
		EaseInCubic,
		EaseInQuart,
		EaseInBack
	};

	static float CalculateEasingPosition(eEASING_LOGIC easingLogic, float start, float end, float currentTime, float maxTime);

private:

	static double GetEaseOutSine(float x);
	static double GetEaseOutQuad(float x);
	static double GetEaseOutCubic(float x);
	static double GetEaseOutQuart(float x);
	static double GetEaseOutBack(float x);
	static double GetEaseInSine(float x);
	static double GetEaseInQuad(float x);
	static double GetEaseInCubic(float x);
	static double GetEaseInQuart(float x);
	static double GetEaseInBack(float x);
};