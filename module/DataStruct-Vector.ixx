module; // DataStruct-Vector.ixx

#include "ds-mod-preheader.h"

export module DataStruct:Vector;

import std;

import :Iterator;
import :Print;

namespace ds {
	// Vector
	export template <typename T>
	_DS_Container class Vector : public Printable<T>
	{
	public:
		Vector() : m_data(nullptr), m_size(0), m_cap(0) {}
		Vector(size_t size) : m_data(new T[size]), m_size(size), m_cap(size) {}
		Vector(size_t size, T const& val) : m_data(new T[size]), m_size(size), m_cap(size) {
			std::fill(m_data, m_data + size, val);
		}
		Vector(std::initializer_list<T> il) : m_data(new T[il.size()]), m_size(il.size()), m_cap(il.size()) {
			std::copy(il.begin(), il.end(), m_data);
		}
		Vector(Vector const& other) : m_data(new T[other.m_cap]), m_size(other.m_size), m_cap(other.m_cap) {
			std::copy(other.m_data, other.m_data + other.m_size, m_data);
		}
		Vector(Vector&& other) noexcept :
			m_data(std::exchange(other.m_data, nullptr)),
			m_size(std::exchange(other.m_size, 0)),
			m_cap(std::exchange(other.m_cap, 0)) {};
		~Vector() { delete[] m_data; }

		func operator=(const Vector& other) -> Vector& {
			if (this == &other) return *this;
			delete[] m_data;
			m_data = new T[other.m_cap];
			m_size = other.m_size;
			m_cap  = other.m_cap;
			std::copy(other.m_data, other.m_data + other.m_size, m_data);
			return *this;
		}
		func operator=(Vector&& other) noexcept -> Vector& {
			if (this == &other) return *this;
			delete[] m_data;
			m_data = std::exchange(other.m_data, nullptr);
			m_size = std::exchange(other.m_size, 0);
			m_cap  = std::exchange(other.m_cap , 0);
			return *this;
		}

		func push_back(T const& val) -> void {
			if (m_size >= m_cap)
				reserve(m_cap == 0 ? 1 : m_cap * 2);
			m_data[m_size++] = val;
		}
		func pop_back() -> void { if (m_size > 0) --m_size; }

		func back()				-> T&		 { return m_data[m_size - 1]; }
		func back() nomodify	-> T const& { return m_data[m_size - 1]; }

		func front()			-> T&       { return m_data[0]; }
		func front() nomodify	-> T const& { return m_data[0]; }

		func data()				-> T*		 { return m_data; }
		func data() nomodify	-> T const* { return m_data; }

		func size() nomodify	-> size_t { return m_size; }

		func capacity() nomodify -> size_t { return m_cap; }

		func empty() nomodify	-> bool { return m_size == 0; }

		func clear() -> void { m_size = 0; }

		func reserve(size_t new_cap) -> void {
			if (new_cap <= m_cap) return;

			T* new_data = new T[new_cap];
			std::copy(m_data, m_data + m_size, new_data);
			delete[] m_data;
			m_data = new_data;
			m_cap = new_cap;
		}

		func resize(size_t new_size, T const& val = T()) -> void {
			if (new_size == m_size) return;
			if (new_size < m_size) {
				m_size = new_size;
				return;
			}
			reserve(new_size);
			std::fill(m_data + m_size, m_data + new_size, val);
			m_size = new_size;
		}

		func shrink_to_fit() -> void {
			if (m_size == m_cap) return;
			T* new_data = new T[m_size];
			std::copy(m_data, m_data + m_size, new_data);
			delete[] m_data;
			m_data = new_data;
			m_cap = m_size;
		}

		func operator[](size_t idx)			 -> T&		 { return m_data[idx]; }
		func operator[](size_t idx) nomodify -> const T& { return m_data[idx]; }

	private:
		T* m_data;
		size_t m_size;
		size_t m_cap;

		func __begin_ptr()			 -> T*		  override { return m_data; }
		func __end_ptr()			 -> T*		  override { return m_data + m_size; }
		func __begin_ptr()	nomodify -> T const*  override { return m_data; }
		func __end_ptr()	nomodify -> T const*  override { return m_data + m_size; }

	}; // class Vector

} // namespace ds