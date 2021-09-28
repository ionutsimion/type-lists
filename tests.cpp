#include <cstdint>

#include "type-lists.hxx"

namespace tl = pi::type_list;

namespace pi::test::type_list::count
{
    auto test_that_several_fundamental_types_against_a_list_of_all_tested_fundamental_types()
    {
        static_assert(tl::count<char, char, bool, short, int, unsigned, long, float, double>() == 1
            , "char is found in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count<bool, char, bool, short, int, unsigned, long, float, double>() == 1
            , "bool is found in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count<short, char, bool, short, int, unsigned, long, float, double>() == 1
            , "short is found in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count<int, char, bool, short, int, unsigned, long, float, double>() == 1
            , "int is found in { int, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count<unsigned, char, bool, short, int, unsigned, long, float, double>() == 1
            , "unsigned is found in { unsigned, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count<long, char, bool, short, int, unsigned, long, float, double>() == 1
            , "long is found in { long, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count<float, char, bool, short, int, unsigned, long, float, double>() == 1
            , "float is found in { float, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::count<double, char, bool, short, int, unsigned, long, float, double>() == 1
            , "double is found in { double, bool, short, int, unsigned, long, float, double }");
    }

    auto test_that_a_type_is_not_found_in_a_type_list_without_itself()
    {
        static_assert(tl::count<char, bool, unsigned char, signed char, int8_t, uint8_t>() == 0
            , "char is not found in { bool, unsigned char, signed char, int8_t, uint8_t }");
        static_assert(tl::count<bool, int, uint32_t, uint8_t, int32_t, int8_t>() == 0
            , "bool is not found in { int, uint32_t, uint8_t, int32_t, int8_t }");
        static_assert(tl::count<int, unsigned, uint32_t>() == 0
            , "int is not found in { unsigned, uint32_t }");
    }

    auto test_that_a_type_is_found_for_as_many_times_it_appears_in_the_list()
    {
        static_assert(tl::count<int, int, int>() == 2, "int is found twice in { int, int }");
        static_assert(tl::count<int, int, int, int, int, int>() == 5, "int is found twice in { int, int, int, int, int }");
    }

    auto test_that_a_type_is_found_in_a_list_with_itself_as_const_or_reference_or_const_reference_only_if_it_is_identical_to_one_in_the_list()
    {
        static_assert(tl::count<int, int const, int &, int &&, int const &>() == 0
            , "int is not found in { int const, int &, int &&, int const & }");
        static_assert(tl::count<int const, int const, int &, int &&, int const &>() == 1
            , "int is not found in { int const, int &, int &&, int const & }");
        static_assert(tl::count<int &, int const, int &, int &&, int const &>() == 1
            , "int is not found in { int const, int &, int &&, int const & }");
        static_assert(tl::count<int &&, int const, int &, int &&, int const &>() == 1
            , "int is not found in { int const, int &, int &&, int const & }");
        static_assert(tl::count<int const &, int const, int &, int &&, int const &>() == 1
            , "int is not found in { int const, int &, int &&, int const & }");
    }

    auto test_that_a_type_is_found_once_in_a_list_with_itself_as_const_and_reference_and_const_reference_if_ignore_const_policy_is_used()
    {
        static_assert(tl::count<tl::search_policy::ignore_const, int, int const, int &, int &&, int const &>() == 1
            , "'int' is found once in { int, int &, int &&, int & }");
    }

    auto test_that_a_type_is_found_twice_in_a_list_with_itself_as_const_and_reference_and_const_reference_if_ignore_reference_policy_is_used()
    {
        static_assert(tl::count<tl::search_policy::ignore_reference, int, int const, int &, int &&, int const &>() == 2
            , "'int' is found twice in { int const, int, int, int const }");
    }

    auto test_that_a_type_is_found_four_times_in_a_list_with_itself_as_const_and_reference_and_const_reference_if_ignore_const_and_reference_policy_is_used()
    {
        static_assert(tl::count<tl::search_policy::ignore_const_and_reference, int, int const, int &, int &&, int const &>() == 4
            , "'int' is found four times in { int, int, int, int }");
    }

    auto test_that_a_const_type_is_not_found_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_const_policy_is_used()
    {
        static_assert(tl::count<tl::search_policy::ignore_const, int const, int, int const, int &, int &&, int const &>() == 0
            , "'int const' is not found in { int, int, int &, int &&, int & }");
    }

    auto test_that_a_const_type_is_found_twice_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_reference_policy_is_used()
    {
        static_assert(tl::count<tl::search_policy::ignore_reference, int const, int, int const, int &, int &&, int const &>() == 2
            , "'int const' is found twice in { int, int const, int, int, int const }");
    }

    auto test_that_a_const_type_is_not_found_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_const_and_reference_policy_is_used()
    {
        static_assert(tl::count<tl::search_policy::ignore_const_and_reference, int const, int, int const, int &, int &&, int const &>() == 0
            , "'int const' is not found in { int, int, int, int, int }");
    }

    auto test_that_a_lreference_type_is_found_twice_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_const_policy_is_used()
    {
        static_assert(tl::count<tl::search_policy::ignore_const, int &, int, int const, int &, int &&, int const &>() == 2
            , "'int &' is found twice in { int, int, int &, int &&, int & }");
    }

    auto test_that_a_lreferemce_type_is_not_found_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_reference_policy_is_used()
    {
        static_assert(tl::count<tl::search_policy::ignore_reference, int &, int, int const, int, int, int const>() == 0
            , "'int &' is found twice in { int &, int const, int, int, int const }");
    }

    auto test_that_a_lreference_type_is_not_found_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_const_and_reference_policy_is_used()
    {
        static_assert(tl::count<tl::search_policy::ignore_const_and_reference, int &, int, int const, int &, int &&, int const &>() == 0
            , "'int &' is found five times in { int, int, int, int, int }");
    }

    auto test_that_a_rreference_type_is_found_once_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_const_policy_is_used()
    {
        static_assert(tl::count<tl::search_policy::ignore_const, int &&, int, int const, int &, int &&, int const &>() == 1
            , "'int &&' is found twice in { int, int, int &, int &&, int & }");
    }

    auto test_that_a_rreferemce_type_is_not_found_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_reference_policy_is_used()
    {
        static_assert(tl::count<tl::search_policy::ignore_reference, int &&, int, int const, int, int, int const>() == 0
            , "'int &&' is found twice in { int &, int const, int, int, int const }");
    }

    auto test_that_a_rreference_type_is_not_found_in_a_list_with_itself_as_non_const_and_const_and_reference_and_const_reference_if_ignore_const_and_reference_policy_is_used()
    {
        static_assert(tl::count<tl::search_policy::ignore_const_and_reference, int &&, int, int const, int &, int &&, int const &>() == 0
            , "'int &&' is found five times in { int, int, int, int, int }");
    }

    auto test_that_a_pointer_to_a_type_is_found_once_in_a_list_with_pointer_to_type_and_pointer_to_const_type_and_const_to_pointer_to_const_pointer_without_policies()
    {
        static_assert(tl::count<int *, int *, int *const, int const *, int const *const>() == 1
            , "'int *' is found once in { int *, int *const, int const *, int const *const }");
        static_assert(tl::count<int *const, int *, int *const, int const *, int const *const>() == 1
            , "'int *const' is found once in { int *, int *const, int const *, int const *const }");
        static_assert(tl::count<int const *, int *, int *const, int const *, int const *const>() == 1
            , "'int const *' is found once in { int *, int *const, int const *, int const *const }");
        static_assert(tl::count<int const *const, int *, int *const, int const *, int const *const>() == 1
            , "'int const *const' is found once in { int *, int *const, int const *, int const *const }");
    }

    auto test_that_a_pointer_to_a_type_is_found_four_times_in_a_list_with_pointer_to_type_and_pointer_to_const_type_and_const_to_pointer_to_const_pointer_if_ignore_const_policy_is_used()
    {
        static_assert(tl::count<tl::search_policy::ignore_const, int *, int *, int *const, int const *, int const *const>() == 4
            , "'int *' is found once in { int *, int *, int *, int * }");
    }
}

namespace pi::test::type_list::find
{
    auto test_that_the_index_of_several_fundamental_types_against_a_list_of_all_tested_fundamental_types_is_as_expected()
    {
        static_assert(tl::find<char, char, bool, short, int, unsigned, long, float, double>() == 0
            , "char is found at position 0 in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find<bool, char, bool, short, int, unsigned, long, float, double>() == 1
            , "bool is found at position 1 in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find<short, char, bool, short, int, unsigned, long, float, double>() == 2
            , "short is found at position 2 in { char, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find<int, char, bool, short, int, unsigned, long, float, double>() == 3
            , "int is found at position 4 in { int, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find<unsigned, char, bool, short, int, unsigned, long, float, double>() == 4
            , "unsigned is found at position 5 in { unsigned, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find<long, char, bool, short, int, unsigned, long, float, double>() == 5
            , "long is found at position 6 in { long, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find<float, char, bool, short, int, unsigned, long, float, double>() == 6
            , "float is found at position 7 in { float, bool, short, int, unsigned, long, float, double }");
        static_assert(tl::find<double, char, bool, short, int, unsigned, long, float, double>() == 7
            , "double is found at position 8 in { double, bool, short, int, unsigned, long, float, double }");
    }

    auto test_that_the_index_of_a_type_with_modifiers_reference_or_pointer_is_correctly_detected_in_a_list_with_all_of_its_forms()
    {
        static_assert(tl::find<int, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 0,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<int const, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 1,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<int &, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 2,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<int const &, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 3,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<int &&, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 4,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<int *, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 5,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<int *const, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 6,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<int const *, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 7,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
        static_assert(tl::find<int const *const, int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const>() == 8,
            "int is at index 0 in { int, int const, int &, int const &, int &&, int *, int *const, int const *, int const *const }");
    }

    auto test_that_the_result_of_find_is_the_index_of_the_first_matching_type_according_to_the_search_policy()
    {
        static_assert(tl::find<int, int &&, int &, int const &, int const>() == -1
            , "int is not found in { int &&, int &, int const &, int const }");
        static_assert(tl::find<tl::search_policy::ignore_const, int, int &&, int &, int const &, int const>() == 3
            , "int is found at 3 in { int &&, int &, int const &, int const } with ignore const policy");
        static_assert(tl::find<tl::search_policy::ignore_reference, int, int &&, int &, int const &, int const>() == 0
            , "int is found at 1 in { int &&, int &, int const &, int const } with ignore const policy");
        static_assert(tl::find<tl::search_policy::ignore_reference, int const, int &&, int &, int const &, int const>() == 2
            , "'int const' is found at 2 in { int &&, int &, int const &, int const } with ignore reference policy");
        static_assert(tl::find<tl::search_policy::ignore_const_and_reference, int, int &&, int &, int const &, int const>() == 0
            , "int is found at 0 in { int &&, int &, int const &, int const } with ignore const and reference policy");
        static_assert(tl::find<int *const, int *, int const *, int *const, int const *const>() == 2
            , "'int *const' is found at 2 in { int *, int const *, int *const, int const *const }");
        static_assert(tl::find<int const *const, int *, int const *, int *const, int const *const>() == 3
            , "'int const *const' is found at 3 in { int *, int const *, int *const, int const *const }");
        static_assert(tl::find<tl::search_policy::ignore_const, int *, int const *, int *const, int const *const>() == 0
            , "'int *const' is found at 2 in { int *, int const *, int *const, int const *const }");
    }
}
