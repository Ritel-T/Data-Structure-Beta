export module DataStruct:Array;

import std;
import :Iterator;

#define func auto
#define nomodify const

namespace ds {
	// Array
	export template <typename T, size_t N>
	class Array : public Iterable<Array<T, N>>
	{
	public:
		using value_type = T;

		Array() : m_data() {}
		Array(const T& val) { std::fill(m_data, m_data + N, val); }
		Array(std::initializer_list<T> il) {
			auto it = il.begin();
			for (size_t i = 0; i < N && it != il.end(); ++i, ++it) m_data[i] = *it;
		}
		Array(const Array& other) { std::copy(other.m_data, other.m_data + N, m_data); }
		Array(Array&& other) noexcept { std::swap(m_data, other.m_data); }
		~Array() = default;

		func operator[](size_t i) -> T& { return m_data[i]; }
		func operator[](size_t i) nomodify -> const T& { return m_data[i]; }

		func data() -> T* { return m_data; }
		func data() nomodify -> const T* { return m_data; }

		func constexpr size() nomodify -> size_t { return N; }

		func fill(const T& val) -> void { std::fill(m_data, m_data + N, val); }

		func print(std::string sep = " ") nomodify -> void { print(0, N, sep); }
		func print(size_t r, std::string sep = " ") nomodify -> void { print(0, r, sep); }
		func print(size_t l, size_t r, std::string sep = " ") nomodify -> void {
			for (size_t i = l; i < r; ++i) {
				std::cout << m_data[i] << sep;
			}
		}
		func print(Iterable<Array<T, N>>::const_iterator l, Iterable<Array<T, N>>::const_iterator r, std::string sep = " ") nomodify -> void {
			print(l - Iterable<Array<T, N>>::cbegin(), r - Iterable<Array<T, N>>::cbegin(), sep);
		}
		template <typename... Args>
		func println(Args... args) nomodify -> void { print(args...); std::cout << std::endl; }
		func println() nomodify -> void { print(); std::cout << std::endl; }

	private:
		T m_data[N];

	}; // class Array

} // namespace ds