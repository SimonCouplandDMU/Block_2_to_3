/** \file RenderCommands.h */

#pragma once

#include <functional>

namespace Engine
{
	class RendererCommon; //!< Advanced declaration for friendship

	/** \class RenderCommand
	*	API render command. List possible commands and holds action as a function
	*/

	class RenderCommand
	{
	public:
		enum class Commands {
			clearDepthBuffer, clearColourBuffer, clearColourAndDepthBuffer, setClearColour,
			enableDepthTesting, disableDepthTesting, enableBlending, disableBlending,
			setStandardBlendFunc, setAdditiveBlendFunc
		};
	private:
		std::function<void(void)> m_action; //!< Action of the render command
		friend class RenderCommandFactory;
		friend class RendererCommon;
	};

	/** \class RenderCommandFactory
	*	Builds API specific render commands from a command type and parameters
	*/
	class RenderCommandFactory
	{
	public:
		template<typename ...Args> static RenderCommand * createCommand(RenderCommand::Commands command, Args&& ...args) //!< Create an API specific command
		{
			RenderCommand * result = new RenderCommand;

			switch (command)
			{
			case RenderCommand::Commands::clearColourAndDepthBuffer :
				result->m_action = getClearColourAndDepthBufferCommand();
				return result;
			case RenderCommand::Commands::clearColourBuffer:
				result->m_action = getClearColourBufferCommand();
				return result;
			case RenderCommand::Commands::clearDepthBuffer:
				result->m_action = getClearDepthBufferCommand();
				return result;
			case RenderCommand::Commands::enableBlending:
				result->m_action = getEnableBlendingCommand();
				return result;
			case RenderCommand::Commands::disableBlending:
				result->m_action = getDisableBlendingCommand();
				return result;
			case RenderCommand::Commands::enableDepthTesting:
				result->m_action = getEnableDepthTestingCommand();
				return result;
			case RenderCommand::Commands::disableDepthTesting:
				result->m_action = getDisableDepthTestingCommand();
				return result;
			case RenderCommand::Commands::setStandardBlendFunc:
				result->m_action = getStandardBlendCommand();
				return result;
			case RenderCommand::Commands::setAdditiveBlendFunc:
				result->m_action = getAdditiveBlendCommand();
				return result;
			case RenderCommand::Commands::setClearColour :
				float r, g, b, a;

				auto argTuple = std::make_tuple(args...);
				
				getValue<float, 0>(r, argTuple);
				getValue<float, 1>(g, argTuple);
				getValue<float, 2>(b, argTuple);
				getValue<float, 3>(a, argTuple);

				result->m_action = getSetClearColourCommand(r,g,b,a);
				return result;
			}
		}
	private:

		static std::function<void(void)> getClearColourAndDepthBufferCommand();
		static std::function<void(void)> getClearColourBufferCommand();
		static std::function<void(void)> getClearDepthBufferCommand();
		static std::function<void(void)> getEnableBlendingCommand();
		static std::function<void(void)> getDisableBlendingCommand();
		static std::function<void(void)> getEnableDepthTestingCommand();
		static std::function<void(void)> getDisableDepthTestingCommand();
		static std::function<void(void)> getStandardBlendCommand();
		static std::function<void(void)> getAdditiveBlendCommand();
		static std::function<void(void)> getSetClearColourCommand(float r, float g, float b, float a);

		// Following code based on https://www.geeksforgeeks.org/how-to-iterate-over-the-elements-of-an-stdtuple-in-c/
		template <typename G, size_t I, typename... Ts>
		typename std::enable_if<I >= sizeof...(Ts), void>::type
		static getValue(G& result, std::tuple<Ts...> tup)
		{
			// If index is great than or equal tuple size don't do anything
		}

		template <typename G, size_t I, typename... Ts>
		typename std::enable_if<(I < sizeof...(Ts)), void>::type
		static getValue(G& result, std::tuple<Ts...> tup)
		{
			// Get the the Ith thing in the tuple
			result = std::get<I>(tup);
		}

	};
}