#include <iostream>
#include <cstdarg>
#include <pfs/test.hpp>
#include <pfs/string.hpp>
#include <pfs/lexical_cast/parse_number.hpp>

static bool parse_digits_helper (char const * s
    , int radix
    , int sign
    , int leading_zeros
    , ptrdiff_t badpos_offset
    , uint8_t first_digit
    , ...)
{
    typedef pfs::string::const_iterator char_iterator_type;

    pfs::digits_parser<char_iterator_type> parser;

    pfs::string str(s);
    bool result = parser.parse(str.cbegin(), str.cend(), radix);
    bool r = true;

    va_list ap;
    va_start(ap, first_digit);

    uint8_t digit = first_digit;

    while (digit != 0xFF) {

        digit = va_arg(ap, uint8_t);
    }

    va_end(ap);
//     char_iterator_type badpos;
//     char_iterator_type badpos_sample;
//     pfs::error_code ec;
//     pfs::string str(s);
//
//     IntT result = pfs::string_to_int<IntT, char_iterator_type>(str.cbegin()
//         , str.cend()
//         , & badpos
//         , radix
//         , ec);
//
//     if (result != result_sample) {
//         std::cout << "***ERROR: result = " << result
//                 << ", but expected " << result_sample << std::endl;
//         r = false;
//     }
//
//     badpos_sample = str.cbegin();
//     pfs::advance(badpos_sample, badpos_offset);
//
//     if (badpos != badpos_sample) {
//         std::cout << "***ERROR: badpos does not match, result="
//             << pfs::distance(str.cbegin(), badpos)
//             << ", but expected " << badpos_offset << std::endl;
//         r = false;
//     }
//
    return r;
}

void test_parse_digits ()
{
//     ADD_TESTS(15);
//
    TEST_OK(parse_digits_helper("0", 10, { 0 }));
//     TEST_OK(test_int_helper<int32_t>("+0", 10, 0, 2));
//     TEST_OK(test_int_helper<int32_t>("-0", 10, 0, 2));
//     TEST_OK(test_int_helper<int32_t>("1", 10, 1, 1));
//     TEST_OK(test_int_helper<int32_t>("+1", 10, 1, 2));
//     TEST_OK(test_int_helper<int32_t>("-1", 10, -1, 2));
//     TEST_OK(test_int_helper<int32_t>("2147483647", 10, 2147483647L, 10));
//     TEST_OK(test_int_helper<int32_t>("+2147483647", 10, 2147483647L, 11));
//     TEST_OK(test_int_helper<int32_t>("-2147483648", 10, -2147483647L - 1, 11)); // use the substract instead of -2147483648L to avoid warning: this decimal constant is unsigned only in ISO C90 [enabled by default]
//     TEST_OK(test_int_helper<int32_t>("-2147483649", 10, -214748364L, 10));
//     TEST_OK(test_int_helper<int32_t>("2147483648", 10, 214748364L, 9));
//     TEST_OK(test_int_helper<int32_t>("7FFFFFFF", 16,  0x7FFFFFFFL, 8));
//     TEST_OK(test_int_helper<int32_t>("80000000", 16, 0x80000000/16, 7));
//     TEST_OK(test_int_helper<int32_t>("FFFFFFFF", 16, 0xFFFFFFFF/16, 7));
//     TEST_OK(test_int_helper<int32_t>("-FFFFFFFF", 16, -1 * 0xFFFFFFF, 8));
//
// #if PFS_HAVE_INT64
//     ADD_TESTS(10);
//
//     TEST_OK(test_int_helper<int64_t>("0", 10, 0, 1));
//     TEST_OK(test_int_helper<int64_t>("+0", 10, 0, 2));
//     TEST_OK(test_int_helper<int64_t>("-0", 10, 0, 2));
//     TEST_OK(test_int_helper<int64_t>("1", 10, 1, 1));
//     TEST_OK(test_int_helper<int64_t>("+1", 10, 1, 2));
//     TEST_OK(test_int_helper<int64_t>("-1", 10, -1, 2));
//     TEST_OK(test_int_helper<int64_t>("9223372036854775807", 10, 9223372036854775807LL, 19));
//     TEST_OK(test_int_helper<int64_t>("-9223372036854775808", 10, -9223372036854775807LL - 1LL, 20));
//     TEST_OK(test_int_helper<int64_t>("9223372036854775808", 10, 922337203685477580LL, 18));
//     TEST_OK(test_int_helper<int64_t>("-9223372036854775809", 10, -922337203685477580LL, 19));
// #endif
}

