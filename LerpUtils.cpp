/**
 * Includes lerp/easing methods.
 * All in static format for easy access.
 */

#include "LerpUtils.h"

float LerpUtils::CalculateEasingPosition(eEASING_LOGIC easingLogic, float startPos, float endPos, float currentTime, float maxTime)
{
	float deltaOriginal = currentTime / maxTime;
	float deltaEasing = 0.0f;

	switch (easingLogic)
	{
	case eEASING_LOGIC::EaseDirect:
		deltaEasing = deltaOriginal;
		break;
	case eEASING_LOGIC::EaseOutSine:
		deltaEasing = GetEaseOutSine(deltaOriginal);
		break;
	case eEASING_LOGIC::EaseOutQuad:
		deltaEasing = GetEaseOutQuad(deltaOriginal);
		break;
	case eEASING_LOGIC::EaseOutCubic:
		deltaEasing = GetEaseOutCubic(deltaOriginal);
		break;
	case eEASING_LOGIC::EaseOutQuart:
		deltaEasing = GetEaseOutQuart(deltaOriginal);
		break;
	case eEASING_LOGIC::EaseOutBack:
		deltaEasing = GetEaseOutBack(deltaOriginal);
		break;
	case eEASING_LOGIC::EaseInSine:
		deltaEasing = GetEaseInSine(deltaOriginal);
		break;
	case eEASING_LOGIC::EaseInQuad:
		deltaEasing = GetEaseInQuad(deltaOriginal);
		break;
	case eEASING_LOGIC::EaseInCubic:
		deltaEasing = GetEaseInCubic(deltaOriginal);
		break;
	case eEASING_LOGIC::EaseInQuart:
		deltaEasing = GetEaseInQuart(deltaOriginal);
		break;
	case eEASING_LOGIC::EaseInBack:
		deltaEasing = GetEaseInBack(deltaOriginal);
		break;
	}

	float maxDistance = abs(startPos - endPos);
	float currentDistance = deltaEasing * maxDistance;

	if (startPos < endPos)
	{
		return (startPos + currentDistance);
	}
	else
	{
		return (startPos - currentDistance);
	}
}

double LerpUtils::GetEaseOutSine(float x)
{
	return sin((x * std::numbers::pi) / 2.0);
}

double LerpUtils::GetEaseOutQuad(float x)
{
	return 1.0 - (1.0 - x) * (1.0 - x);
}

double LerpUtils::GetEaseOutCubic(float x)
{
	return 1.0 - pow(1.0 - x, 3.0);
}

double LerpUtils::GetEaseOutQuart(float x)
{
	return 1.0 - pow(1.0 - x, 4.0);
}

double LerpUtils::GetEaseOutBack(float x)
{
	const double c1 = 1.70158;
	const double c3 = c1 + 1.0;

	return 1.0 + c3 * pow(x - 1.0, 3.0) + c1 * pow(x - 1.0, 2.0);
}

double LerpUtils::GetEaseInSine(float x)
{
	return 1.0 - cos((x * std::numbers::pi) / 2.0);
}

double LerpUtils::GetEaseInQuad(float x)
{
	return x * x;
}

double LerpUtils::GetEaseInCubic(float x)
{
	return x * x * x;
}

double LerpUtils::GetEaseInQuart(float x)
{
	return x * x * x * x;
}

double LerpUtils::GetEaseInBack(float x)
{
	const double c1 = 1.70158;
	const double c3 = c1 + 1.0;

	return c3 * x * x * x - c1 * x * x;
}