/** \file shaderDataType.h */
#pragma once

#include<cstdint>

namespace Engine
{
	/** \class ShaderDataType
	**  \brief Data type which can be used by a shader
	*/

	enum class ShaderDataType
	{
		None = 0,	/** Unknown datatype*/
		Float,		/** 4 byte float*/
		Float2,		/** 8 byte float[2]*/
		Float3,		/** 24 byte float[3]*/
		Float4,		/** 16 byte float[4]*/
		Int,		/** 4 byte unsigned int*/
		Mat4,		/** 64 byte float[4][4]*/
		FlatInt,	/** 4 byte unsigned int - not to be reinterpreted as floats by the shader*/
		FlatByte,	/** 1 byte unsigned char - not to be reinterpreted as floats by the shader*/
		Byte4		/** 1 byte unsigned char[4] - to be reinterpreted as float[4] by the shader*/
	};

	namespace SDT
	{
		static uint32_t size(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Byte4: return 1 * 4;
			case ShaderDataType::FlatByte: return 1;
			case ShaderDataType::FlatInt: return 4;
			case ShaderDataType::Int: return 4;
			case ShaderDataType::Float: return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4;
			case ShaderDataType::Mat4: return 4 * 4 * 4;
			default: return 0;
			}
		}

		static uint32_t componentCount(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Byte4: return 4;
			case ShaderDataType::FlatByte: return 1;
			case ShaderDataType::FlatInt: return 1;
			case ShaderDataType::Int: return 1;
			case ShaderDataType::Float: return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat4: return 4;
			default: return 0;
			}
		}

		static uint32_t STD140Alignment(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Byte4:	  return 4;
			case ShaderDataType::FlatByte:return 4; //?
			case ShaderDataType::FlatInt: return 4;
			case ShaderDataType::Int:     return 4;
			case ShaderDataType::Float:   return 4;
			case ShaderDataType::Float2:  return 8;
			case ShaderDataType::Float3:  return 16;
			case ShaderDataType::Float4:  return 16;
			case ShaderDataType::Mat4:    return 16 * 4;
			}
			return 0;
		}
	}
}
