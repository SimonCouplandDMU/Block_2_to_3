/** \file randomiser.cpp */
#pragma once

#include "engine_pch.h"
#include "systems/randomiser.h"
#include <chrono>

namespace Engine
{
	std::shared_ptr<std::mt19937> Randomiser::s_generator = nullptr;
	std::uniform_int_distribution<int32_t> Randomiser::s_uniformInt = std::uniform_int_distribution<int32_t>(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max());
	std::uniform_real_distribution<float> Randomiser::s_uniformFloat = std::uniform_real_distribution<float>(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
	float Randomiser::s_intRange = static_cast<float>((std::numeric_limits<int32_t>::max() - (float)std::numeric_limits<int32_t>::min()));
	float Randomiser::s_floatRange = std::numeric_limits<float>::max() - std::numeric_limits<float>::min();

	void Randomiser::start(SystemSignal init, ...)
	{
		auto now = std::chrono::high_resolution_clock::now();
		s_generator.reset(new std::mt19937(now.time_since_epoch().count()));
	}

	void Randomiser::stop(SystemSignal close, ...)
	{
		s_generator.reset();
	}

	int32_t Randomiser::uniformIntBetween(int32_t lower, int32_t upper)
	{
		float t = (static_cast<float>(s_uniformInt(*s_generator)) / s_intRange) + 0.5f;
		float range = upper - lower;
		return lower + static_cast<int32_t>(t * range);
	}

	float Randomiser::uniformFloatBetween(float lower, float upper)
	{
		float t = (s_uniformFloat(*s_generator) / s_floatRange);
		float range = upper - lower;
		return lower + (t * range);
	}

	int32_t Randomiser::normalInt(float c, float sigma)
	{
		std::normal_distribution<float> distribution(c, sigma);
		return static_cast<int32_t>(distribution(*s_generator));
	}

	float Randomiser::normalFloat(float c, float sigma)
	{
		std::normal_distribution<float> distribution(c, sigma);
		return distribution(*s_generator);
	}
}