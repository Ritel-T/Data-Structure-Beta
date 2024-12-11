// DataStruct-Iterator.ixx

export module DataStruct:Iterator;

import std;

#define func auto
#define nomodify const

namespace ds
{
	// Iterator
	export template <typename Container, bool IsConst>
	class Iterator {
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = std::conditional_t<IsConst, const typename Container::value_type, typename Container::value_type>;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;

		explicit Iterator(pointer ptr) : m_ptr(ptr) {}

		func operator*() nomodify -> reference { return *m_ptr; }

		func operator->() nomodify -> pointer { return m_ptr; }

		func operator++() -> Iterator& {
			++m_ptr;
			return *this;
		}
		func operator++(int) -> Iterator {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		func operator<=>(const Iterator& other) nomodify -> std::strong_ordering = default;

	protected:
		pointer m_ptr;
	}; // class Iterator

	// IteratorReverse
	export template <typename Container, bool IsConst>
	class IteratorReverse : public Iterator<Container, IsConst> {
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = typename Iterator<Container, IsConst>::value_type;
		using difference_type = std::ptrdiff_t;
		using pointer = typename Iterator<Container, IsConst>::pointer;
		using reference = typename Iterator<Container, IsConst>::reference;

		explicit IteratorReverse(pointer ptr) : Iterator<Container, IsConst>(ptr) {}

		func operator++() -> IteratorReverse&  override {
			--this->m_ptr;
			return *this;
		}
		func operator++(int) -> IteratorReverse  override {
			IteratorReverse tmp = *this;
			++(*this);
			return tmp;
		}

		func operator<=>(const IteratorReverse& other) nomodify->std::strong_ordering = default;

	}; // class IteratorReverse

	// Iterable
	export template <typename Container>
	class Iterable {
	public:
		using iterator = Iterator<Container, false>;
		using const_iterator = Iterator<Container, true>;
		using reverse_iterator = IteratorReverse<Container, false>;
		using reverse_const_iterator = IteratorReverse<Container, true>;

		func begin()			-> iterator			{ return iterator(static_cast<Container*>(this)->data()); }
		func begin() nomodify	-> const_iterator	{ return cbegin(); }
		func end()				-> iterator			{ return iterator(static_cast<Container*>(this)->data() + static_cast<Container*>(this)->size()); }
		func end() nomodify		-> const_iterator	{ return cend(); }

		func cbegin() nomodify	-> const_iterator	{ return const_iterator(static_cast<Container*>(this)->data()); }
		func cend() nomodify	-> const_iterator	{ return const_iterator(static_cast<Container*>(this)->data() + static_cast<Container*>(this)->size()); }

		func rbegin()			-> reverse_iterator { return reverse_iterator(std::make_reverse_iterator(end())); }
		func rbegin() nomodify	-> reverse_const_iterator	{ return crbegin(); }
		func rend()				-> reverse_iterator { return reverse_iterator(std::make_reverse_iterator(begin())); }
		func rend() nomodify	-> reverse_const_iterator	{ return crend(); }

		func crbegin() nomodify -> reverse_const_iterator	{ return reverse_const_iterator(std::make_reverse_iterator(cend())); }
		func crend() nomodify	-> reverse_const_iterator	{ return reverse_const_iterator(std::make_reverse_iterator(cbegin())); }

	}; // class Iterable

} // namespace ds