// main.cpp
#include <iostream>
#include <vector>
#include <ranges>
#include <chrono>
#include <concepts>
#include <algorithm>
#include <iterator>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <type_traits>
#include <string>

import DataStruct;

//auto incr_prt(std::ranges::range auto&& rng)
//	requires requires { ++*rng.begin(); }
//{
//	std::println("Addable: ");
//	for (auto& elem : rng) {
//		++elem;
//		std::print("{} ", elem);
//	}
//	std::println("");
//}

auto incr_prt(std::ranges::range auto const& rng)
{
	std::print("Readable: ");
    for (auto const& elem : rng) {
        //std::print("{} ", elem);
		std::cout << elem << " ";
    }
    std::println("");
}

int main() {
	using namespace std::ranges::views;

	ds::Vector<int> myv{ 1,2,3,4,5,6,7,8,9,10 };
	ds::Vector<int> const cmyv{ 1,2,3,4,5,6,7,8,9,10 };
	static_assert(std::ranges::range<decltype(myv)>);  // OK
	static_assert(std::ranges::range<decltype(cmyv)>); // OK

	static_assert(std::input_iterator<decltype(myv.begin())>);
	static_assert(std::input_iterator<decltype(myv.cbegin())>);
	static_assert(std::ranges::range<ds::Vector<int> const>);  // All OK

	auto it = myv.begin();
	std::advance(it, 5);
	auto cit = cmyv.begin();
	std::advance(cit, 5);
	std::print("{} {}\n", *it, *cit); // OK

	auto subr = cmyv | drop(5);
	static_assert(std::ranges::range<decltype(subr)>); // OK

	auto const_subr = cmyv | drop(5);
	static_assert(std::ranges::range<decltype(const_subr)>); // Error

	auto const& subr_cref = subr;
	//static_assert(std::ranges::range<decltype(subr_cref)>); // Error

	//for (auto it = subr_cref.begin(); it != subr_cref.end(); ++it) {
	//	std::print("{} ", *it);
	//}

	//for (auto const& elem : subrc2) {
	//	std::print("{} ", elem);
	//}


	//incr_prt(subr);
	//ds::print(subr);

	//void test2();
	//test2();

	//auto subr = myv.subrange(2,5);
	//incr_prt(subr);
	//incr_prt(subr | std::views::transform([](auto& e) -> auto& {
	//	std::println("transform: {} *= 3", e);
	//	return e *= 3;
	//}));

	//for (auto it = myv.begin(); it != myv.end(); ++it) {
	//	std::print("{} ", *it);
	//}

	//auto subv = myv
	//	| std::views::transform([](auto const& elem) { return elem * elem; })
	//	| std::views::filter([](auto const& elem) { return elem % 2 == 0; });

	//ds::println(myv);
}
/*
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
*/