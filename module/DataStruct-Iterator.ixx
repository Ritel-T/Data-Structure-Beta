module; // DataStruct-Iterator.ixx

#include "ds-mod-preheader.h"

export module DataStruct:Iterator;

import std;

namespace ds
{
	template <typename T>
	concept Range_c = std::ranges::range<T>;

	// exported functions
	export func range(Range_c auto&& container)		-> Range_c auto {
		return std::ranges::subrange(container.begin(), container.end());
	}
	export func subrange(Range_c auto&& container,
						 size_t start, size_t len)	-> Range_c auto {
		return container | std::views::drop(start) | std::views::take(len);
	}
		
	export func print(Range_c auto const& container, std::string const& sep = " ") -> void {
		for (auto const& e : container)
			std::print("{}{}", e, sep);
	}
	export func println(auto const&... args) -> void {
		print(args...);
		std::println("");
	}


	// Contiguous Iterator
	export template <typename T>
	class Iterator {
	public:
		using iterator_category = std::contiguous_iterator_tag;
		using value_type		= T;
		using pointer			= value_type*;
		using reference			= value_type&;
		using difference_type	= std::ptrdiff_t;

		Iterator() = default;
		Iterator(pointer ptr) : m_ptr(ptr) {}
		Iterator(Iterator const& other) : m_ptr(other.m_ptr) {}

		func operator*()  nomodify -> reference { return *m_ptr; }
		func operator->() nomodify -> pointer	{ return m_ptr; }
		func operator[](difference_type n) nomodify -> reference {
			return *(m_ptr + n);
		}

		func operator++()		-> Iterator& {
			++m_ptr;
			return *this;
		}
		func operator++(int)	-> Iterator {
			Iterator temp = *this;
			++m_ptr;
			return temp;
		}

		func operator--()		-> Iterator& {
			--m_ptr;
			return *this;
		}
		func operator--(int)	-> Iterator {
			Iterator temp = *this;
			--m_ptr;
			return temp;
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

		func operator<=>(Iterator const& other) nomodify -> std::strong_ordering = default;

		operator pointer() nomodify { return m_ptr; }

	private:
		pointer m_ptr;

	}; // class Iterator (Contiguous)

	// Iterator for List (both singly and doubly linked)
	export template <typename Node>
		requires requires(Node* n) { n->next; }
    class Iterator<Node> {
	public:
		bool static constexpr IsDLL = requires(Node* n) { n->prev; };

		using iterator_category = std::conditional_t <IsDLL,
            std::bidirectional_iterator_tag,
            std::forward_iterator_tag>;
		using value_type		= std::conditional_t<std::is_const_v<Node>,
			typename Node::value_type const,
			typename Node::value_type>;
		using pointer			= value_type*;
		using reference			= value_type&;
        using difference_type	= std::ptrdiff_t;

		Iterator() = default;
		Iterator(Node* ptr) : m_ptr(ptr) {}
		Iterator(Iterator const& other) : m_ptr(other.m_ptr) {}

		func operator*()  nomodify -> reference { return m_ptr->data; }
		func operator->() nomodify -> pointer	{ return &m_ptr->data; }

		func operator++()		-> Iterator& {
			m_ptr = m_ptr->next;
			return *this;
		}
		func operator++(int)	-> Iterator {
			Iterator temp = *this;
			m_ptr = m_ptr->next;
			return temp;
		}

		func operator--()		-> Iterator& requires IsDLL {
			m_ptr = m_ptr->prev;
			return *this;
		}
		func operator--(int)	-> Iterator  requires IsDLL {
			Iterator temp = *this;
			m_ptr = m_ptr->prev;
			return temp;
		}

		func operator+(size_t n) nomodify -> Iterator {
			Node* temp = m_ptr;
			for (size_t i = 0; i < n; ++i)
				temp = temp->next;
			return Iterator(temp);
		}
		func operator-(size_t n) nomodify -> Iterator requires IsDLL {
			Node* temp = m_ptr;
			for (size_t i = 0; i < n; ++i)
				temp = temp->prev;
			return Iterator(temp);
		}

		//func operator-(Iterator const& other) nomodify -> difference_type {
		//	Node* temp = m_ptr;
		//	difference_type count = 0;
		//	while (temp != other.m_ptr) {
		//		temp = temp->next;
		//		++count;
		//	}
		//	return count;
		//}

		//func operator==(Iterator const& other) nomodify -> bool {
		//	std::clog << "operator==(Iterator const&)" << std::endl;
		//	return m_ptr == other.m_ptr;
		//}

		func operator<=>(Iterator const& other) nomodify -> std::strong_ordering
			= default;

		operator value_type*() {
			std::clog << "operator value_type*()" << std::endl;
			return &m_ptr->data;
		}

	private:
		Node* m_ptr;

	}; // class Iterator (for List)


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

	protected:
		func virtual __begin_ptr()			-> T*		= 0;
		func virtual __end_ptr()			-> T*		= 0;
		func virtual __begin_ptr() nomodify	-> T const* = 0;
		func virtual __end_ptr()   nomodify -> T const* = 0;

	}; // class Iterable

	export template <typename T>
	_DS_Property class RangeCompatible : public Iterable<T> {
	public:
		using Iterable<T>::begin;
		using Iterable<T>::end;
		using Iterable<T>::cbegin;
		using Iterable<T>::cend;

		func range()			-> Range_c auto {
			return std::ranges::subrange(begin(), end());
		}
		func range() nomodify   -> Range_c auto {
			return std::ranges::subrange(cbegin(), cend());
		}

		func subrange(size_t start, size_t len)			 -> Range_c auto {
			return range() | std::views::drop(start) | std::views::take(len);
		}
		func subrange(size_t start, size_t len) nomodify -> Range_c auto {
			return range() | std::views::drop(start) | std::views::take(len);
		}

	}; // class RangeCompatible

	export template <typename T>
	_DS_Property class Printable : public RangeCompatible<T> {
	public:
		using RangeCompatible<T>::range;
		using RangeCompatible<T>::subrange;

		func print(std::string const& sep = " ")							nomodify -> void {
			ds::print(range(), sep);
		}
		func print(size_t start, size_t len, std::string const& sep = " ")	nomodify -> void {
			ds::print(subrange(start, len), sep);
		}
		func print(size_t len, std::string const& sep = " ")				nomodify -> void {
			print(0, len, sep);
		}
		func println(auto const&... args)									nomodify -> void {
			print(args...);
			std::println("");
		}

	}; // class Printable

} // namespace ds