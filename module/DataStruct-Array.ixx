module; // DataStruct-Array.ixx

#include "ds-mod-preheader.h"

export module DataStruct:Array;

import std;

import :Iterator;
import :Print;

namespace ds {
	// Array
	export template <typename T, size_t N>
	_DS_Container class Array : public Iterable<T>, public Printable<T>
	{
	public:
		Array() : m_data() {}
		Array(T const& val) {
			std::fill(m_data, m_data + N, val);
		}
		Array(std::initializer_list<T> il) {
			if (il.size() > N)
				throw std::out_of_range("Array initializer_list size exceeds N");
			std::copy(il.begin(), il.end(), m_data);
		}
		Array(Array const& other) {
			std::copy(other.m_data, other.m_data + N, m_data);
		}
		Array(Array&& other) noexcept : m_data(std::exchange(other.m_data, nullptr)) {}
		~Array() = default;


		func data()			 -> T*		 { return m_data; }
		func data() nomodify -> T const* { return m_data; }

		func constexpr size() nomodify -> size_t { return N; }

		func fill(T const& val) -> void {
			std::fill(m_data, m_data + N, val);
		}

		func operator[](size_t i)		   -> T&	   { return m_data[i]; }
		func operator[](size_t i) nomodify -> T const& { return m_data[i]; }

	private:
		T m_data[N];

		func __begin_ptr()			 -> T* override { return m_data; }
		func __end_ptr()			 -> T* override { return m_data + N; }
		func __begin_ptr()	nomodify -> T const* override { return m_data; }
		func __end_ptr()	nomodify -> T const* override { return m_data + N; }

	}; // class Array

} // namespace ds