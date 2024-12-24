module; // DataStruct-Iterator.ixx

#include "ds-mod-preheader.h"

export module DataStruct:Iterator;

import std;

namespace ds
{
	// Iterator
	export template <typename T>
	class Iterator {
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type		= T;
		using pointer			= T*;
		using reference			= T&;
		using difference_type	= std::ptrdiff_t;

		Iterator() : m_ptr(nullptr) {}
		Iterator(value_type* ptr) : m_ptr(ptr) {}
		Iterator(Iterator const& other) : m_ptr(other.m_ptr) {}

		func operator*()  nomodify -> reference { return *m_ptr; }
		func operator->() nomodify -> pointer	{ return m_ptr; }
		func operator[](difference_type n) nomodify -> reference { return m_ptr[n]; }

		func operator++()		-> Iterator& {
			++m_ptr;
			return *this;
		}
		func operator++(int)	-> Iterator {
			Iterator tmp = *this;
			++m_ptr;
			return tmp;
		}

		func operator--()		-> Iterator& {
			--m_ptr;
			return *this;
		}
		func operator--(int)	-> Iterator {
			Iterator tmp = *this;
			--m_ptr;
			return tmp;
		}

		func operator+=(difference_type n) -> Iterator& {
			m_ptr += n;
			return *this;
		}
		func operator-=(difference_type n) -> Iterator& {
			m_ptr -= n;
			return *this;
		}

		func operator+(difference_type n) nomodify -> Iterator { return Iterator(m_ptr + n); }
		func operator-(difference_type n) nomodify -> Iterator { return Iterator(m_ptr - n); }

		func operator-(Iterator const& other) nomodify -> difference_type {
			return m_ptr - other.m_ptr;
		}

		func operator<=>(Iterator const& other) nomodify -> std::strong_ordering {
			return m_ptr <=> other.m_ptr;
		}

		operator pointer() nomodify { return m_ptr; }

	private:
		pointer m_ptr;
	}; // class Iterator

	// Iterable
	export template <typename T>
	_DS_Property class Iterable {
	public:
		using iterator					= Iterator<T>;
		using const_iterator			= Iterator<T const>;
		using reverse_iterator			= std::reverse_iterator<iterator>;
		using const_reverse_iterator	= std::reverse_iterator<const_iterator>;

		func begin()				-> iterator				{ return __begin_ptr(); }
		func end()					-> iterator				{ return __end_ptr(); }
		func begin()	nomodify	-> const_iterator		{ return cbegin(); }
		func end()		nomodify	-> const_iterator		{ return cend(); }

		func cbegin()	nomodify	-> const_iterator		{ return __begin_ptr(); }
		func cend()		nomodify	-> const_iterator		{ return __end_ptr(); }

		func rbegin()				-> reverse_iterator		{ return std::make_reverse_iterator(end()); }
		func rend()					-> reverse_iterator		{ return std::make_reverse_iterator(begin()); }
		func rbegin()	nomodify	-> const_reverse_iterator { return crbegin(); }
		func rend()		nomodify	-> const_reverse_iterator { return crend(); }

		func crbegin()	nomodify	-> const_reverse_iterator { return std::make_reverse_iterator(cend()); }
		func crend()	nomodify	-> const_reverse_iterator { return std::make_reverse_iterator(cbegin()); }

	private:
		func virtual __begin_ptr()			-> T*		= 0;
		func virtual __end_ptr()			-> T*		= 0;
		func virtual __begin_ptr() nomodify	-> T const* = 0;
		func virtual __end_ptr()   nomodify -> T const* = 0;

	}; // class Iterable

} // namespace ds