#include <cstdint>
#include <string>
#include <string_view>

#include "type-lists.hxx"
#include "arguments.hxx"

#include "tests.hxx"

namespace tl = pi::type_lists;
namespace arg = pi::arguments;

namespace pi::test::type_lists::nth_type
{
    auto constexpr test_that_the_first_type_in_a_list_is_the_expected_one() noexcept
    {
        static_assert(std::is_same_v<tl::nth_type<1ULL, int>, int>, "First type is not int.");
        static_assert(!std::is_same_v<tl::nth_type<1ULL, double>, int>, "First type is int instead of double.");
        static_assert(std::is_same_v<tl::nth_type<1ULL, double>, double>, "First type is not double.");
        static_assert(std::is_same_v<tl::nth_type<1ULL, int const>, int const>, "First type is not int.");
        static_assert(std::is_same_v<tl::nth_type<1ULL, struct s1>, struct s1>, "First type is not struct s1.");
        static_assert(!std::is_same_v<tl::nth_type<1ULL, struct s1>, struct s2>, "First type is struct s1 instead of s2.");
    }

    auto constexpr test_that_the_nth_type_in_a_list_is_the_expected_one() noexcept
    {
        static_assert(std::is_same_v<tl::nth_type<2ULL, double, int>, int>, "second type is not int.");
        static_assert(std::is_same_v<tl::nth_type<2ULL, double, volatile int>, volatile int>, "second type is not volatile int.");
        static_assert(std::is_same_v<tl::nth_type<5ULL, int const, double, int volatile, double, int>, int>, "fifth type is not int.");
    }
} // pi::test::type_lists::nth_type

namespace pi::test::type_lists::count
{
    auto constexpr test_that_a_type_is_found_once_in_a_list_with_unique_types_containing_that_type() noexcept
    {
        static_assert(tl::count_v<char, char, bool, short, int, unsigned, long, float, double> == 1
            , "char is not found once in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<bool, char, bool, short, int, unsigned, long, float, double> == 1
            , "bool is not found once in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<short, char, bool, short, int, unsigned, long, float, double> == 1
            , "short is not found once in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<int, char, bool, short, int, unsigned, long, float, double> == 1
            , "int is not found once in { int, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<unsigned, char, bool, short, int, unsigned, long, float, double> == 1
            , "unsigned is not found once in { unsigned, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<long, char, bool, short, int, unsigned, long, float, double> == 1
            , "long is not found once in { long, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<float, char, bool, short, int, unsigned, long, float, double> == 1
            , "float is not found once in { float, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<double, char, bool, short, int, unsigned, long, float, double> == 1
            , "double is not found once in { double, bool, short, int, unsigned, long, float, double }");
    }

    auto constexpr test_that_a_type_is_not_found_in_a_list_with_types_other_than_itself() noexcept
    {
        static_assert(tl::count_v<char, bool, unsigned char, signed char, int8_t, uint8_t> == 0
            , "char is found in { bool, unsigned char, signed char, int8_t, uint8_t }");
        static_assert(tl::count_v<bool, int, uint32_t, uint8_t, int32_t, int8_t> == 0
            , "bool is found in { int, uint32_t, uint8_t, int32_t, int8_t }");
        static_assert(tl::count_v<int, unsigned, uint32_t> == 0
            , "int is found in { unsigned, uint32_t }");
    }

    auto constexpr test_that_a_type_is_found_for_as_many_times_it_appears_in_the_list() noexcept
    {
        static_assert(tl::count_v<int, int, int> == 2
            , "int is not found twice in { int, int }");
        static_assert(tl::count_v<int, int, int, int, int, int> == 5
            , "int is not found five times in { int, int, int, int, int }");
    }

    auto constexpr test_that_a_type_is_found_in_a_list_with_non_const_cont_references_only_if_is_identical_with_one_of_the_other_with_strict_matching() noexcept
    {
        static_assert(tl::count<tl::matching::strict, int, int const, int &, int &&, int const &>() == 0
            , "int is found in { int const, int &, int &&, int const & }");
        static_assert(tl::count<tl::matching::strict, int const, int const, int &, int &&, int const &>() == 1
            , "'int const' is not found in { int const, int &, int &&, int const & }");
        static_assert(tl::count<tl::matching::strict, int &, int const, int &, int &&, int const &>() == 1
            , "'int &' is not found in { int const, int &, int &&, int const & }");
        static_assert(tl::count<tl::matching::strict, int &&, int const, int &, int &&, int const &>() == 1
            , "'int &&' is not found in { int const, int &, int &&, int const & }");
        static_assert(tl::count<tl::matching::strict, int const &, int const, int &, int &&, int const &>() == 1
            , "'int const &' is not found in { int const, int &, int &&, int const & }");
    }

    auto constexpr test_that_a_type_is_found_four_times_in_a_list_with_itself_as_const_and_reference_and_const_reference_if_relaxed_matching_is_used() noexcept
    {
        static_assert(tl::count<tl::matching::relaxed, int, int const, int &, int &&, int const &>() == 4
            , "'int' is not found four times in { int, int, int, int }");
    }

    auto constexpr test_that_a_pointer_to_a_type_is_found_once_in_a_list_with_pointer_to_type_and_pointer_to_const_type_and_const_to_pointer_to_const_pointer_with_strict_matching() noexcept
    {
        static_assert(tl::count<tl::matching::strict, int *, int *, int *const, int const *, int const *const>() == 1
            , "'int *' is not found once in { int *, int *const, int const *, int const *const }");
        static_assert(tl::count<tl::matching::strict, int *const, int *, int *const, int const *, int const *const>() == 1
            , "'int *const' is not found once in { int *, int *const, int const *, int const *const }");
        static_assert(tl::count<tl::matching::strict, int const *, int *, int *const, int const *, int const *const>() == 1
            , "'int const *' is not found once in { int *, int *const, int const *, int const *const }");
        static_assert(tl::count<tl::matching::strict, int const *const, int *, int *const, int const *, int const *const>() == 1
            , "'int const *const' is not found once in { int *, int *const, int const *, int const *const }");
    }
} // namespace pi::test::type_lists::count

namespace pi::test::type_lists::find
{
    auto constexpr test_that_the_index_of_each_type_in_a_list_is_as_expected() noexcept
    {
        static_assert(tl::find_v < char, char, bool, short, int, unsigned, long, float, double > == 0,
                      "char is not found at position 0 in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v < bool, char, bool, short, int, unsigned, long, float, double > == 1,
                      "bool is not found at position 1 in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v < short, char, bool, short, int, unsigned, long, float, double > == 2,
                      "short is not found at position 2 in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v < int, char, bool, short, int, unsigned, long, float, double > == 3,
                      "int is not found at position 3 in { int, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v < unsigned, char, bool, short, int, unsigned, long, float, double > == 4,
                      "unsigned is not found at position 4 in { unsigned, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v < long, char, bool, short, int, unsigned, long, float, double > == 5,
                      "long is not found at position 5 in { long, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v < float, char, bool, short, int, unsigned, long, float, double > == 6,
                      "float is not found at position 6 in { float, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v < double, char, bool, short, int, unsigned, long, float, double > == 7,
                      "double is not found at position 7 in { double, bool, short, int, unsigned, long, float, double }");
    }

    auto constexpr
    test_that_the_index_of_a_type_with_modifiers_reference_or_pointer_is_correctly_detected_in_a_list_with_some_of_its_variants_and_strict_matching() noexcept
    {
        static_assert(tl::find < tl::matching::strict, int, int, int const, int & , int const &, int &&, int *,
            int *const, int const *, int const *const>() == 0,
            "int is not at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find < tl::matching::strict, int const, int, int const, int & , int const &, int &&, int *,
            int *const, int const *, int const *const>() == 1,
            "'int const' is not at index 1 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find < tl::matching::strict, int & , int, int const, int & , int const &, int &&, int *,
            int *const, int const *, int const *const>() == 2,
            "'int &' is not at index 2 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find < tl::matching::strict, int const &, int, int const, int & , int const &, int &&, int *,
            int *const, int const *, int const *const>() == 3,
            "'int const &' is not at index 3 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find < tl::matching::strict, int && , int, int const, int & , int const &, int &&, int *,
            int *const, int const *, int const *const>() == 4,
            "'int &&' is not at index 4 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find < tl::matching::strict, int * , int, int const, int & , int const &, int &&, int *,
            int *const, int const *, int const *const>() == 5,
            "'int *' is not at index 5 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find < tl::matching::strict, int *const, int, int const, int & , int const &, int &&, int *,
            int *const, int const *, int const *const>() == 6,
            "'int *const' is not at index 6 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find < tl::matching::strict, int const *, int, int const, int & , int const &, int &&, int *,
            int *const, int const *, int const *const>() == 7,
            "'int const *' is not at index 7 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find < tl::matching::strict, int const *const, int, int const, int & , int const &, int &&,
            int *, int *const, int const *, int const *const>() == 8,
            "'int const *const' is not at index 8 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
    }

    auto constexpr test_that_the_result_of_find_is_the_index_of_the_first_matching_type_according_to_the_strategy() noexcept
    {
        static_assert(tl::find < tl::matching::strict, int, int && , int & , int const &, int const>() == -1
            , "int is not found in { int &&, int &, int const &, int const }");
        static_assert(tl::find < tl::matching::relaxed, int, int && , int & , int const &, int const>() == 0
            , "int is not found at 0 in { int &&, int &, int const &, int const } with ignore const and reference policy");
        static_assert(tl::find < tl::matching::strict, int *const, int *, int const *, int *const, int const *const>
        () == 2
            , "'int *const' is not found at 2 in { int *, int const *, int *const, int const *const }");
        static_assert(tl::find < tl::matching::strict,
                      int const *const, int *, int const *, int *const, int const *const>() == 3
            , "'int const *const' is not found at 3 in { int *, int const *, int *const, int const *const }");
    }
} // namespace pi::test::type_lists::find

namespace pi::test::type_lists::find_nth
{
    auto constexpr test_that_find_nth_returns_as_find_for_nth_equal_to_1() noexcept
    {
        static_assert(tl::find_nth_of_type_v<1ULL, int, double, int > == tl::find_v < int, double, int >
            , "find_nth_of_type_v and find_v give different results for nth=1 and the same type list.");
        static_assert(tl::find_nth_of_type<tl::matching::strict, 1ULL, int, double, int>() == tl::find<tl::matching::strict, int, double, int>()
            , "find_nth_of_type and find give different results for nth=1 and the same type list.");
        static_assert(tl::find_nth_of_type<tl::matching::strict, 1ULL, int const, double, int > () == tl::npos
            , "find_nth_of_type finds a int const in a list without int const.");
        static_assert(tl::find_nth_of_type<tl::matching::strict, 1ULL, int const, double, int > () == tl::find < tl::matching::strict, int const, double, int > ()
            , "find_nth_of_type and find give different results for nth=1 and the same type list.");
    }

    auto constexpr test_that_find_nth_returns_the_expected_indices() noexcept
    {
        static_assert(tl::find_nth_of_type_v<1ULL, int, double, int> == 1
            , "the first int is not found at index 1");
        static_assert(tl::find_nth_of_type_v<2ULL, int, double, int, float, int> == 3
            , "the second int is not found at index 3");
        static_assert(tl::find_nth_of_type<tl::matching::relaxed, 2ULL, int, double, int, float, int>() == 3
            , "the second int is not found at index 3");
        static_assert(tl::find_nth_of_type<tl::matching::strict, 1ULL, int const, double, int, float, int const>() == 3
            , "the first int is not found at index 1");
    }
} // namespace pi::test::type_lists::find_nth_of_type

namespace pi::test::arguments::get_first_of_type_or_default
{
    auto constexpr test_that_if_the_type_of_an_argument_is_not_found_the_default_is_assigned() noexcept
    {
        using namespace std::string_view_literals;

        static_assert(arg::get_first_of_type_or_default(1, 'a', 10.0, 12.1f) == 1
            , "an int is found in { 'a', 10.0, 12.1f } and the default '1' is returned");
        static_assert(arg::get_first_of_type_or_default("(null)"sv, 'a', 10.0, 12.1f) == "(null)"sv
            , "a 'string_view' is found in { 'a', 10.0, 12.1f }, so the default '(null)' is returned");
        static_assert(arg::get_first_of_type_or_default(1, 'a', 10.0, 12.1f) == 1
            , "an int is found in { 'a', 10.0, 12.1f } and the default '1' is returned");
        auto constexpr x = 42;
        static_assert(arg::get_first_of_type_or_default<tl::matching::strict>(1, 'a', 10.0, 12.1f, x) == 1
            , "an int is found in { 'a', 10.0, 12.1f, x }, where x is a constexpr int, and the default '1' is returned");
    }

    auto constexpr test_that_if_the_type_of_an_argument_is_found_the_argument_of_that_type_is_returned() noexcept
    {
        using namespace std::string_view_literals;

        static_assert(arg::get_first_of_type_or_default("x"sv, "y"sv) == "y"sv
            , "a string_view is not found");
    }
} // namespace pi::test::arguments::get_first_of_type_or_default

namespace pi::test::arguments::get_nth_of_type_or_default
{
    auto constexpr test_that_if_the_type_of_an_argument_is_not_found_the_default_is_assigned() noexcept
    {
        using namespace std::string_view_literals;

        static_assert(arg::get_nth_of_type_or_default<1ULL>(1, 'a', 10.0, 12.1f) == 1
            , "an int is found in { 'a', 10.0, 12.1f } and the default '1' is returned");
        static_assert(arg::get_nth_of_type_or_default<1ULL>("(null)"sv, 'a', 10.0, 12.1f) == "(null)"sv
            , "a 'string_view' is found in { 'a', 10.0, 12.1f }, so the default '(null)' is returned");
        static_assert(arg::get_nth_of_type_or_default<1ULL>(1, 'a', 10.0, 12.1f) == 1
            , "an int is found in { 'a', 10.0, 12.1f } and the default '1' is returned");
        auto constexpr x = 42;
        static_assert(arg::get_nth_of_type_or_default<tl::matching::strict, 1ULL>(1, 'a', 10.0, 12.1f, x) == 1
            , "an int is found in { 'a', 10.0, 12.1f, x }, where x is a constexpr int, and the default '1' is returned");
        static_assert(arg::get_nth_of_type_or_default<tl::matching::strict, 2ULL>(1, 'a', 10.0, x, 2) == 1);
    }

    auto constexpr test_that_if_the_type_of_an_argument_is_found_the_argument_of_that_type_is_returned() noexcept
    {
        using namespace std::string_view_literals;

        static_assert(arg::get_nth_of_type_or_default<1ULL>("x"sv, "y"sv) == "y"sv
            , "The first string_view is not found");
        static_assert(arg::get_nth_of_type_or_default<2ULL>("x"sv, "y"sv, "z"sv) == "z"sv
            , "The first string_view is not found");
    }
} // namespace pi::test::arguments::get_nth_of_type_or_default

void pi::test::run()
{
    { // type_list::nth_type tests
        using namespace pi::test::type_lists::nth_type;

        test_that_the_first_type_in_a_list_is_the_expected_one();
        test_that_the_nth_type_in_a_list_is_the_expected_one();
    }
    { // type_list::count tests
        using namespace pi::test::type_lists::count;

        test_that_a_type_is_found_once_in_a_list_with_unique_types_containing_that_type();
        test_that_a_type_is_found_for_as_many_times_it_appears_in_the_list();
        test_that_a_type_is_not_found_in_a_list_with_types_other_than_itself();
        test_that_a_type_is_found_in_a_list_with_non_const_cont_references_only_if_is_identical_with_one_of_the_other_with_strict_matching();
        test_that_a_type_is_found_four_times_in_a_list_with_itself_as_const_and_reference_and_const_reference_if_relaxed_matching_is_used();
        test_that_a_pointer_to_a_type_is_found_once_in_a_list_with_pointer_to_type_and_pointer_to_const_type_and_const_to_pointer_to_const_pointer_with_strict_matching();
    } // type_list::count tests

    { // type_list::find tests
        using namespace pi::test::type_lists::find;

        test_that_the_index_of_each_type_in_a_list_is_as_expected();
        test_that_the_index_of_a_type_with_modifiers_reference_or_pointer_is_correctly_detected_in_a_list_with_some_of_its_variants_and_strict_matching();
        test_that_the_result_of_find_is_the_index_of_the_first_matching_type_according_to_the_strategy();
    } // type_list::find tests

    { // type_list::find_mth tests
        using namespace pi::test::type_lists::find_nth;

        test_that_find_nth_returns_as_find_for_nth_equal_to_1();
        test_that_find_nth_returns_the_expected_indices();
    } // type_list::find_mth tests

    { // type_list::get_first_of_type_or_default tests
        using namespace pi::test::arguments::get_first_of_type_or_default;

        test_that_if_the_type_of_an_argument_is_not_found_the_default_is_assigned();
        test_that_if_the_type_of_an_argument_is_found_the_argument_of_that_type_is_returned();
    } // type_list::get_first_of_type_or_default tests

    { // type_list::get_nth_of_type_or_default tests
        using namespace pi::test::arguments::get_nth_of_type_or_default;

        test_that_if_the_type_of_an_argument_is_not_found_the_default_is_assigned();
        test_that_if_the_type_of_an_argument_is_found_the_argument_of_that_type_is_returned();
    } // type_list::get_nth_of_type_or_default tests
}
