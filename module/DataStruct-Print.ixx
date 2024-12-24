module; // DataStruct-Print.ixx

#include "ds-mod-preheader.h"

export module DataStruct:Print;

import std;

namespace ds {

	export func range(std::ranges::range auto&& container) -> std::ranges::range auto {
		return std::ranges::subrange(container.begin(), container.end());
	}
	export func subrange(std::ranges::range auto&& container,
						 size_t start, size_t len)		   -> std::ranges::range auto {
		return std::ranges::subrange(
			container.begin() + start > container.end() ?
				container.end() : container.begin() + start,
			container.begin() + start + len > container.end() ?
				container.end() : container.begin() + start + len);
	}

	export func print(std::ranges::range auto&& range, std::string sep = " ") -> void {
		for (auto const& e : range)
			std::print("{}{}", e, sep);
	}
	export func println(auto... args) -> void {
		print(args...);
		std::println("");
	}

	export template<typename T>
	_DS_Property class Printable {
	public:
		func range() -> std::ranges::range auto {
			return std::ranges::subrange(__begin_ptr(), __end_ptr());
		}
		func range() nomodify -> std::ranges::range auto {
			return std::ranges::subrange(__begin_ptr(), __end_ptr());
		}

		func subrange(size_t start, size_t len) -> std::ranges::range auto {
			return std::ranges::subrange(__begin_ptr() + start,
				__begin_ptr() + start + (len > size() - start ? size() - start : len));
		}
		func subrange(size_t start, size_t len) nomodify -> std::ranges::range auto {
			return std::ranges::subrange(__begin_ptr() + start,
				__begin_ptr() + start + (len > size() - start ? size() - start : len));
		}

		func print(std::string sep = " ") nomodify -> void {
			ds::print(range(), sep);
		}
		func print(size_t start, size_t len, std::string sep = " ") nomodify -> void {
			if (start >= size()) return;
			ds::print(subrange(start, len), sep);
		}
		func print(size_t len, std::string sep = " ") nomodify -> void {
			print(0, len, sep);
		}
		func println(auto... args) nomodify -> void {
			print(args...);
			std::println("");
		}

	private:
		func virtual __begin_ptr()			-> T*		= 0;
		func virtual __end_ptr()			-> T*		= 0;
		func virtual __begin_ptr() nomodify	-> T const* = 0;
		func virtual __end_ptr()   nomodify -> T const* = 0;

		func virtual size()	nomodify -> size_t = 0;

	}; // class Printable

} // namespace ds