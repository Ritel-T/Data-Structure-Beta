export module test;

import std;

export
struct struct1
{
	int a, b;

	auto test(this auto&& self) -> void {
		std::println("{} ", &self);
	}
};