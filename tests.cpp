#include <cassert>
#include <cstdint>
#include <string>
#include <string_view>

#include "type-lists.hxx"
#include "arguments.hxx"

#include "tests.hxx"

namespace tl = pi::type_lists;
namespace arg = pi::arguments;

namespace pi::test::type_lists::count
{
    auto test_that_several_fundamental_types_against_a_list_of_all_tested_fundamental_types()
    {
        static_assert(tl::count_v<char, char, bool, short, int, unsigned, long, float, double> == 1
            , "char is found in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<bool, char, bool, short, int, unsigned, long, float, double> == 1
            , "bool is found in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<short, char, bool, short, int, unsigned, long, float, double> == 1
            , "short is found in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<int, char, bool, short, int, unsigned, long, float, double> == 1
            , "int is found in { int, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<unsigned, char, bool, short, int, unsigned, long, float, double> == 1
            , "unsigned is found in { unsigned, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<long, char, bool, short, int, unsigned, long, float, double> == 1
            , "long is found in { long, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<float, char, bool, short, int, unsigned, long, float, double> == 1
            , "float is found in { float, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count_v<double, char, bool, short, int, unsigned, long, float, double> == 1
            , "double is found in { double, bool, short, int, unsigned, long, float, double }");
    }

    auto test_that_a_type_is_not_found_in_a_type_list_without_itself()
    {
        static_assert(tl::count_v<char, bool, unsigned char, signed char, int8_t, uint8_t> == 0
            , "char is not found in { bool, unsigned char, signed char, int8_t, uint8_t }");
        static_assert(tl::count_v<bool, int, uint32_t, uint8_t, int32_t, int8_t> == 0
            , "bool is not found in { int, uint32_t, uint8_t, int32_t, int8_t }");
        static_assert(tl::count_v<int, unsigned, uint32_t> == 0
            , "int is not found in { unsigned, uint32_t }");
    }

    auto test_that_a_type_is_found_for_as_many_times_it_appears_in_the_list()
    {
        static_assert(tl::count_v<int, int, int> == 2
            , "int is found twice in { int, int }");
        static_assert(tl::count_v<int, int, int, int, int, int> == 5
            , "int is found twice in { int, int, int, int, int }");
    }

    auto test_that_a_type_is_found_in_a_list_with_itself_as_const_or_reference_or_const_reference_only_if_it_is_identical_to_one_in_the_list()
    {
        static_assert(tl::count<tl::matching::strict, int, int const, int &, int &&, int const &>() == 0
            , "int is not found in { int const, int &, int &&, int const & }");
        static_assert(tl::count<tl::matching::strict, int const, int const, int &, int &&, int const &>() == 1
            , "int is not found in { int const, int &, int &&, int const & }");
        static_assert(tl::count<tl::matching::strict, int &, int const, int &, int &&, int const &>() == 1
            , "int is not found in { int const, int &, int &&, int const & }");
        static_assert(tl::count<tl::matching::strict, int &&, int const, int &, int &&, int const &>() == 1
            , "int is not found in { int const, int &, int &&, int const & }");
        static_assert(tl::count<tl::matching::strict, int const &, int const, int &, int &&, int const &>() == 1
            , "int is not found in { int const, int &, int &&, int const & }");
    }

    auto test_that_a_type_is_found_four_times_in_a_list_with_itself_as_const_and_reference_and_const_reference_if_ignore_const_and_reference_policy_is_used()
    {
        static_assert(tl::count<tl::matching::relaxed, int, int const, int &, int &&, int const &>() == 4
            , "'int' is found four times in { int, int, int, int }");
    }

    auto test_that_a_const_type_is_not_found_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_const_and_reference_policy_is_used()
    {
        static_assert(tl::count<tl::matching::relaxed, int const, int, int const, int &, int &&, int const &>() == 0
            , "'int const' is not found in { int, int, int, int, int }");
    }

    auto test_that_a_lreference_type_is_not_found_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_const_and_reference_policy_is_used()
    {
        static_assert(tl::count<tl::matching::relaxed, int &, int, int const, int &, int &&, int const &>() == 0
            , "'int &' is found five times in { int, int, int, int, int }");
    }

    auto test_that_a_rreference_type_is_not_found_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_const_and_reference_policy_is_used()
    {
        static_assert(tl::count<tl::matching::relaxed, int &&, int, int const, int &, int &&, int const &>() == 0
            , "'int &&' is found five times in { int, int, int, int, int }");
    }

    auto test_that_a_pointer_to_a_type_is_found_once_in_a_list_with_pointer_to_type_and_pointer_to_const_type_and_const_to_pointer_to_const_pointer_without_policies()
    {
        static_assert(tl::count<tl::matching::strict, int *, int *, int *const, int const *, int const *const>() == 1
            , "'int *' is found once in { int *, int *const, int const *, int const *const }");
        static_assert(tl::count<tl::matching::strict, int *const, int *, int *const, int const *, int const *const>() == 1
            , "'int *const' is found once in { int *, int *const, int const *, int const *const }");
        static_assert(tl::count<tl::matching::strict, int const *, int *, int *const, int const *, int const *const>() == 1
            , "'int const *' is found once in { int *, int *const, int const *, int const *const }");
        static_assert(tl::count<tl::matching::strict, int const *const, int *, int *const, int const *, int const *const>() == 1
            , "'int const *const' is found once in { int *, int *const, int const *, int const *const }");
    }
} // namespace pi::test::type_lists::count

namespace pi::test::type_lists::find
{
    auto test_that_the_index_of_several_fundamental_types_against_a_list_of_all_tested_fundamental_types_is_as_expected()
    {
        static_assert(tl::find_v<char, char, bool, short, int, unsigned, long, float, double> == 0
            , "char is found at position 0 in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v<bool, char, bool, short, int, unsigned, long, float, double> == 1
            , "bool is found at position 1 in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v<short, char, bool, short, int, unsigned, long, float, double> == 2
            , "short is found at position 2 in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v<int, char, bool, short, int, unsigned, long, float, double> == 3
            , "int is found at position 4 in { int, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v<unsigned, char, bool, short, int, unsigned, long, float, double> == 4
            , "unsigned is found at position 5 in { unsigned, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v<long, char, bool, short, int, unsigned, long, float, double> == 5
            , "long is found at position 6 in { long, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v<float, char, bool, short, int, unsigned, long, float, double> == 6
            , "float is found at position 7 in { float, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find_v<double, char, bool, short, int, unsigned, long, float, double> == 7
            , "double is found at position 8 in { double, bool, short, int, unsigned, long, float, double }");
    }

    auto test_that_the_index_of_a_type_with_modifiers_reference_or_pointer_is_correctly_detected_in_a_list_with_all_of_its_forms()
    {
        static_assert(tl::find<tl::matching::strict, int, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 0,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<tl::matching::strict, int const, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 1,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<tl::matching::strict, int &, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 2,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<tl::matching::strict, int const &, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 3,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<tl::matching::strict, int &&, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 4,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<tl::matching::strict, int *, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 5,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<tl::matching::strict, int *const, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 6,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<tl::matching::strict, int const *, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 7,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<tl::matching::strict, int const *const, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 8,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
    }

    auto test_that_the_result_of_find_is_the_index_of_the_first_matching_type_according_to_the_search_policy()
    {
        static_assert(tl::find<tl::matching::strict, int, int &&, int &, int const &, int const>() == -1
            , "int is not found in { int &&, int &, int const &, int const }");
        static_assert(tl::find<tl::matching::relaxed, int, int &&, int &, int const &, int const>() == 0
            , "int is found at 0 in { int &&, int &, int const &, int const } with ignore const and reference policy");
        static_assert(tl::find<tl::matching::strict, int *const, int *, int const *, int *const, int const *const>() == 2
            , "'int *const' is found at 2 in { int *, int const *, int *const, int const *const }");
        static_assert(tl::find<tl::matching::strict, int const *const, int *, int const *, int *const, int const *const>() == 3
            , "'int const *const' is found at 3 in { int *, int const *, int *const, int const *const }");
    }
}

namespace pi::test::arguments::default_or_argument
{
    auto constexpr test_that_if_the_type_of_an_argument_is_not_found_the_default_is_assigned() noexcept
    {
        using namespace std::string_view_literals;

        static_assert(arg::default_or_argument(1, 'a', 10.0, 12.1f) == 1
            , "an int is not found in { 'a', 10.0, 12.1f } and the default '1' is returned");
        static_assert(arg::default_or_argument("(null)"sv, 'a', 10.0, 12.1f) == "(null)"sv
            , "a 'string_view' is not found in { 'a', 10.0, 12.1f }, so the default '(null)' is returned");
        static_assert(arg::default_or_argument(1, 'a', 10.0, 12.1f) == 1
            , "an int is not found in { 'a', 10.0, 12.1f } and the default '1' is returned");
        auto constexpr x = 42;
        static_assert(arg::default_or_argument<tl::matching::strict>(1, 'a', 10.0, 12.1f, x) == 1
            , "an int is not found in { 'a', 10.0, 12.1f, x }, where x is a constexpr int, and the default '1' is returned");
    }
}

void pi::test::run()
{
    { // type_list::count tests
        using namespace pi::test::type_lists::count;

        test_that_several_fundamental_types_against_a_list_of_all_tested_fundamental_types();
        test_that_a_type_is_found_for_as_many_times_it_appears_in_the_list();
        test_that_a_type_is_not_found_in_a_type_list_without_itself();
        test_that_a_type_is_found_in_a_list_with_itself_as_const_or_reference_or_const_reference_only_if_it_is_identical_to_one_in_the_list();
        test_that_a_type_is_found_four_times_in_a_list_with_itself_as_const_and_reference_and_const_reference_if_ignore_const_and_reference_policy_is_used();
        test_that_a_const_type_is_not_found_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_const_and_reference_policy_is_used();
        test_that_a_lreference_type_is_not_found_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_const_and_reference_policy_is_used();
        test_that_a_rreference_type_is_not_found_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_const_and_reference_policy_is_used();
        test_that_a_pointer_to_a_type_is_found_once_in_a_list_with_pointer_to_type_and_pointer_to_const_type_and_const_to_pointer_to_const_pointer_without_policies();
    } // type_list::count tests

    { // type_list::find tests
        using namespace pi::test::type_lists::find;

        test_that_the_index_of_several_fundamental_types_against_a_list_of_all_tested_fundamental_types_is_as_expected();
        test_that_the_index_of_a_type_with_modifiers_reference_or_pointer_is_correctly_detected_in_a_list_with_all_of_its_forms();
        test_that_the_result_of_find_is_the_index_of_the_first_matching_type_according_to_the_search_policy();
    } // type_list::find tests

    { // pi::test::arguments::default_or_argument tests
        using namespace pi::test::arguments::default_or_argument;

        test_that_if_the_type_of_an_argument_is_not_found_the_default_is_assigned();
    } // pi::test::arguments::default_or_argument tests

    using namespace std::string_view_literals;

    assert(arg::default_or_argument("x"sv, "y"sv) == "y"sv);
}
