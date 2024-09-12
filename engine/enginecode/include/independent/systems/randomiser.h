/** \file randomiser.h */
#pragma once

#include <random>
#include "system.h"

namespace Engine
{
	class Randomiser : public System
	{
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...) override; //!< Start the system
		virtual void stop(SystemSignal close = SystemSignal::None, ...) override; //!< Stop the system

		static int32_t uniformIntBetween(int32_t lower, int32_t upper); //!< Get an integer i such that lower <= i <= upper
		static float uniformFloatBetween(float lower, float upper); //!< Get a float i such that lower <= i <= upper
		static int32_t normalInt(float c, float sigma); //!< Get a int from the Gaussian distribution described by C and Sigma
		static float normalFloat(float c, float sigma); //!< Get a int from the Gaussian distribution described by C and Sigma
	private:
		static std::shared_ptr<std::mt19937> s_generator; //!< Random number engine
		static std::uniform_int_distribution<int32_t> s_uniformInt; //!< Uniform interger distribution
		static std::uniform_real_distribution<float> s_uniformFloat; //!< Uniform float distribution
		static float s_intRange; //!< Range of int32_t
		static float s_floatRange; //!< Range of 32bit float
	};
}