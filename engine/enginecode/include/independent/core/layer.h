/* \file layer.h */
#pragma once

#include <string>
#include "window.h"

namespace Engine {
	/**
	\class Layer
	A convient abstraction of rending and eventrs into a layer which can be placed in a stack.
	Intended for use as a base class.
	*/
	class Layer
	{
	public:
		Layer(const char * name) : m_name(name) {}; //!< Constructor

		virtual void onAttach() {} //!< Runs when layer is attached
		virtual void onDetach() {}//!< Runs when layer is detached
		virtual void onRender() {} //!< Runs when layer is renderered
		virtual void onUpdate(float timestep) {}//!< Runs every frame
		virtual void onResize(WindowResizeEvent& e) {} //!< Runs when layers window is resized

		inline const char * getName() const { return m_name; } //!< Get layer name
		inline void setDisplayed(bool displayStatus) { m_isDisplayed = displayStatus; } //!< Set layer display status
		inline void setActive(bool activeStatus) { m_isActive = activeStatus; }  //!< Set layer active status
		inline void setFocused(bool focusedStatus)  { m_isFocused = focusedStatus; } //!< Set layer focus status
		inline const bool isDisplayed() const { return m_isDisplayed; } //!< Get layer display status
		inline const bool isActive() const { return m_isActive; } //!< Get layer active status
		inline const bool isFocused() const { return m_isFocused; } //!< Get layer focus status

		virtual void onKeyPressed(KeyPressedEvent & e) { e.handle(false); } //!< On key press event
	protected:
		const char * m_name; //!< Name, useful for debugging
		bool m_isDisplayed = true; //!< Should this layer be rendered
		bool m_isActive = true; //!< Should this layer be updated
		bool m_isFocused = true; //!< Should this layer be getting events;
	};
}