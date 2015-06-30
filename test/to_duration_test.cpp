/*
 * Copyright (C) 2015 Christopher Gilbert.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define CATCH_CONFIG_MAIN
#include "../test/catch.hpp"

#include "chrono/utility/to_duration.hpp"

namespace cu = chrono::utility;

TEST_CASE("to_duration works as required", "[to_duration]") {
	SECTION("std::string") {
		std::string str("1s");
		auto d = cu::to_duration<std::chrono::seconds>(str);
		REQUIRE(d.count() == 1);
	}
	SECTION("std::wstring") {
		std::wstring str(L"1s");
		auto d = cu::to_duration<std::chrono::seconds>(str);
		REQUIRE(d.count() == 1);
	}
	SECTION("char*") {
		auto d = cu::to_duration<std::chrono::seconds>("1s");
		REQUIRE(d.count() == 1);
	}
	SECTION("wchar_t*") {
		std::string str("1s");
		auto d = cu::to_duration<std::chrono::seconds>(L"1s");
		REQUIRE(d.count() == 1);
	}
	SECTION("throws std::invalid_argument") {
		REQUIRE_NOTHROW(cu::to_duration<std::chrono::seconds>(""));
		REQUIRE_THROWS(cu::to_duration<std::chrono::seconds>("invalid"));
		REQUIRE_THROWS(cu::to_duration<std::chrono::seconds>("12z"));
	}
	SECTION("nanoseconds") {
		auto d = cu::to_duration<std::chrono::nanoseconds>("1ns");
		REQUIRE(d.count() == 1);
	}
	SECTION("microseconds") {
		auto d = cu::to_duration<std::chrono::microseconds>("1us");
		REQUIRE(d.count() == 1);
	}
	SECTION("milliseconds") {
		auto d = cu::to_duration<std::chrono::milliseconds>("1ms");
		REQUIRE(d.count() == 1);
	}
	SECTION("seconds") {
		auto d = cu::to_duration<std::chrono::seconds>("1s");
		REQUIRE(d.count() == 1);
	}
	SECTION("minutes") {
		auto d = cu::to_duration<std::chrono::minutes>("1m");
		REQUIRE(d.count() == 1);
	}
	SECTION("hours") {
		auto d = cu::to_duration<std::chrono::hours>("1h");
		REQUIRE(d.count() == 1);
	}
	SECTION("combination") {
		auto ns = cu::to_duration<std::chrono::nanoseconds>("1ns");
		auto us = cu::to_duration<std::chrono::nanoseconds>("1us");
		auto ms = cu::to_duration<std::chrono::nanoseconds>("1ms");
		auto s = cu::to_duration<std::chrono::nanoseconds>("1s");
		auto m = cu::to_duration<std::chrono::nanoseconds>("1m");
		auto h = cu::to_duration<std::chrono::nanoseconds>("1h");
		auto d = cu::to_duration<std::chrono::nanoseconds>("1h1m1s1ms1us1ns");
		REQUIRE(d.count() == ns.count() + us.count() + ms.count() + s.count() + m.count() + h.count());
	}
}