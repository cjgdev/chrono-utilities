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

#include <chrono>
#include <string>

namespace chrono { namespace utility {

    /*
     * chrono::utility::to_duration
     *
     * Convert a string of the format ([+-]?\d+(ns|us|ms|s|m|h))* to a std::chrono::duration type.
     *
     * (1) template <class BidirectionalIterator, class Duration>
     *     Duration to_duration(const BidirectionalIterator& first, const BidirectionalIterator& last);
     * (2) template <class Char, class Duration>
     *     Duration to_duration(const std::basic_string<Char>& str);
     * (3) template <class Duration>
     *     Duration to_duration(const std::string& str);
     * (4) template <class Duration>
     *     Duration to_duration(const std::wstring& str);
     * (5) template <class Char, class Duration>
     *     Duration to_duration(const Char* str);
     * (6) template <class Duration>
     *     Duration to_duration(const char* str);
     * (7) template <class Duration>
     *     Duration to_duration(const wchar_t* str);
     *
     * Parameters
     * ---
     * first, last
     * Bidirectional iterators to the initial and final positions of the sequence to be parsed. The range used is
     * [first,last), which contains all the elements between first and last, including the element pointed by first
     * but not the element pointed by last.
     *
     * str
     * String containing the sequence to be parsed.
     *
     * Return value
     * ---
     * Duration representing the parsed sequence cast to the type of std::chrono::duration specified by Duration.
     *
     * Example
     * ---
     * #include <iostream>
     * #include "chrono/utilities/to_duration.hpp>
     *
     * int main() {
     *     auto d = chrono::utilities::to_duration<std::chrono::seconds>("1h33m7s");
     *     std::cout << d.count() << "s in 1h 33m 7s" << std::endl;
     *     return 0;
     * }
     *
     * Output: 5587s in 1h 33m 7s
     *
     * Complexity
     * ---
     * Linear (O(n)) in the distance between first and last.
     *
     * Exceptions
     * ---
     * Throws std::invalid_argument if the input string is malformed and cannot be parsed.
     */

    template<class BidirectionalIterator, class Duration>
    Duration to_duration(const BidirectionalIterator& first, const BidirectionalIterator& last) {
        using duration_type = Duration;
        duration_type tmp(0);
        BidirectionalIterator it(first);
        while (it != last) {
            bool neg = (*it == '-');
            if (*it == '+' || *it == '-') ++it;
            typename duration_type::rep n = 0;
            while(it != last) {
                if (*it >= '0' && *it <= '9') {
                    n = n * 10  - (*it - '0');
                } else {
                    break;
                }
                it++;
            }
            n = neg ? n : -n;
            switch (*it) {
                case 'n': { // ns
                    if (*(++it) == 's') {
                        tmp += std::chrono::duration_cast<duration_type>(
                                std::chrono::nanoseconds(n));
                    } else {
                        throw std::invalid_argument("invalid input string");
                    }
                    break;
                }
                case 'u': { // us
                    if (*(++it) == 's') {
                        tmp += std::chrono::duration_cast<duration_type>(
                                std::chrono::microseconds(n));
                    } else {
                        throw std::invalid_argument("invalid input string");
                    }
                    break;
                }
                case 'm': { // m / ms
                    if (*(++it) == 's') {
                        tmp += std::chrono::duration_cast<duration_type>(
                                std::chrono::milliseconds(n));
                    } else {
                        tmp += std::chrono::duration_cast<duration_type>(
                                std::chrono::minutes(n));
                        it--;
                    }
                    break;
                }
                case 's': { // s
                    tmp += std::chrono::duration_cast<duration_type>(
                            std::chrono::seconds(n));
                    break;
                }
                case 'h': { // h
                    tmp += std::chrono::duration_cast<duration_type>(
                            std::chrono::hours(n));
                    break;
                }
                default: {
                    throw std::invalid_argument("invalid input string");
                }
            }
            it++;
        }
        return duration_type(tmp);
    }

    template <class Char, class Duration>
    Duration to_duration(const std::basic_string<Char>& str) {
        return to_duration<typename std::basic_string<Char>::const_iterator, Duration>(str.cbegin(), str.cend());
    }

    template <class Duration>
    Duration to_duration(const std::string& str) {
        return to_duration<typename std::string::const_iterator, Duration>(str.cbegin(), str.cend());
    }

    template <class Duration>
    Duration to_duration(const std::wstring& str) {
        return to_duration<typename std::wstring::const_iterator, Duration>(str.cbegin(), str.cend());
    }

    template <class Char, class Duration>
    Duration to_duration(const Char* str) {
        std::basic_string<Char> tmp(str);
        return to_duration<Char, Duration>(tmp);
    }

    template <class Duration>
    Duration to_duration(const char* str) {
        return to_duration<char, Duration>(str);
    }

    template <class Duration>
    Duration to_duration(const wchar_t* str) {
        return to_duration<wchar_t, Duration>(str);
    }

} }