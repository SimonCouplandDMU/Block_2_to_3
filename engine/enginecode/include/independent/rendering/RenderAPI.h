/* \file renderAPI.h*/
#pragma once

namespace Engine
{
	/** \class RenderAPI
	*	Render API list for switching between
	*/

	class RenderAPI {
	public:
		/** \class
		*  List of possible render APIS
		*/
		enum class API { 
			None = 0,		/**< No API - no graphics */
			OpenGL = 1,		/**< OpenGL */
			Direct3D = 2,	/**< DirectX/Direct3D */
			Vulkan = 3		/**< Vulkan */
		};
		inline static API getAPI() { return s_API; } //!< Getter for the current API
	private:
		static API s_API; //!< The current API
	};
}
