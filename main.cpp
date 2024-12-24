// main.cpp

import std;
import DataStruct;

auto incr_prt(std::ranges::range auto&& rng)
	requires requires { ++*rng.begin(); }
{
	std::print("Addable: ");
	for (auto& elem : rng) {
		++elem;
		std::print("{} ", elem);
	}
	std::println("");
}

auto incr_prt(std::ranges::range auto&& rng)
{
	std::print("Readable: ");
    for (auto const& elem : rng) {
        std::print("{} ", elem);
    }
    std::println("");
}

int main() {
	ds::Vector<int> v{ 1,2,3,4,5,6,7,8,9,10,11,12,13 };
	const ds::Vector<int> cv{ 1,2,3,4,5 };

	auto subv = v
		| std::views::transform([](auto const& elem) { return elem * elem; })
		| std::views::filter([](auto const& elem) { return elem % 2 == 0; });

	ds::println(subv);
}

void test0()
{
	auto s1 = std::chrono::high_resolution_clock::now();

	ds::Vector<int> v;
	for (int i = 0; i < 100000; ++i) v.push_back(i);
	v.println();
	
	auto e1 = std::chrono::high_resolution_clock::now();
	auto d1 = std::chrono::duration_cast<std::chrono::milliseconds>(e1 - s1);


	auto s2 = std::chrono::high_resolution_clock::now();

	std::vector<int> v2;
	for (int i = 0; i < 100000; ++i) v2.push_back(i);
	for (auto& elem : v2) { std::print("{} ", elem); } std::println();

	auto e2 = std::chrono::high_resolution_clock::now();
	auto d2 = std::chrono::duration_cast<std::chrono::milliseconds>(e2 - s2);

	std::println("");
	std::println("ds::Vector  time: {} ms", d1.count());
	std::println("std::vector time: {} ms", d2.count());
}

void test1() {
	ds::Vector<int> v{ 1,2,3,4,5 };
	const ds::Vector<int> cv{ 1,2,3,4,5 };

	v.println();
	cv.println();
	for (auto it = v.begin(); it != v.end(); ++it) {
		++*it;
		std::print("{} ", *it);
	}
	std::println("");
	for (auto it = cv.begin(); it != cv.end(); ++it) {
		//++*it;
		std::print("{} ", *it);
	}
	std::println("");

	for (auto it = v.rbegin(); it != v.rend(); ++it) {
		std::print("{} ", *it);
	}
	std::println("");
	for (auto it = cv.rbegin(); it != cv.rend(); ++it) {
		std::print("{} ", *it);
	}
}

void test2() {
	ds::Vector<int> v{ 1,2,3,4,5 };
	const ds::Vector<int> cv{ 1,2,3,4,5 };

	auto subr1 = v.range();
	incr_prt(subr1);

	auto subr2 = v.subrange(1, 3);
	incr_prt(subr2);

	auto subr3 = cv.range();
	incr_prt(subr3);

	auto subr4 = cv.subrange(1, 3);
	incr_prt(subr4);

	for (auto& elem : v) {
		std::print("{} ", elem);
	}
	for (auto& elem : cv) {
		std::print("{} ", elem);
	}
	for (auto const& elem : v) {
		std::print("{} ", elem);
	}
	for (auto const& elem : cv) {
		std::print("{} ", elem);
	}
}
