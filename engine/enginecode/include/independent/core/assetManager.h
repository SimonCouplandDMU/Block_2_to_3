/** \file assetManager.h
*/
#pragma once

#include <memory>
#include <unordered_map>

namespace Engine {

	/**
	\class AssetManager
	A templated class which holds a parameterised type in a map. Will only accept shared pointers to each element.
	*/

	template <class G>
	class AssetManager
	{
	public:
		void reserve(uint32_t capacity); //!< Reserve capacity, use before adding stuff
		bool contains(const char * key); //!< Is this item in the container already
		void add(const char * key, std::shared_ptr<G>& element); //!< Add element to the container
		std::shared_ptr<G> get(const char * key); //!< Get a point to an asset. Return nullptr is not found 
		void clear();
	private:
		std::unordered_map <const char *, std::shared_ptr<G>> m_container; // Data structure to hold assets
	};

	template <class G>
	void AssetManager<G>::reserve(uint32_t capacity)
	{
		m_container.reserve(capacity);
	}

	template <class G>
	bool AssetManager<G>::contains(const char * key)
	{
		return m_container.find(key) != m_container.end();
	}

	template <class G>
	void AssetManager<G>::add(const char * key, std::shared_ptr<G>& element)
	{
		m_container[key] = element;
	}

	template <class G>
	std::shared_ptr<G> AssetManager<G>::get(const char * key)
	{
		if (contains(key)) return m_container[key];
		else return nullptr;
	}

	template <class G>
	void AssetManager<G>::clear()
	{
		m_container.clear();
	}
}