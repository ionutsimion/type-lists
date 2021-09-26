#include <iostream>

#include "type-lists.hxx"

namespace
{
    void print_title(std::string const &title);
    void print_separator(std::string const &title, bool is_last = false);
}

auto test_count_without_policy()
{
    using pi::type_list::count;
    using pi::type_list::search_policy;

    std::string const title{ "Testing count() function without a policy" };

    print_title(title);
    std::cout << "| count<int, int8_t>()                        = " << count<int, int8_t>() << '\n';
    std::cout << "| count<int, int16_t>()                       = " << count<int, int16_t>() << '\n';
    std::cout << "| count<int, int32_t>()                       = " << count<int, int32_t>() << '\n';
    std::cout << "| count<int, int64_t>()                       = " << count<int, int64_t>() << '\n';
    std::cout << "| count<int, int>()                           = " << count<int, int>() << '\n';
    std::cout << "| count<int, int const>()                     = " << count<int, int const>() << '\n';
    std::cout << "| count<int, int volatile>()                  = " << count<int, int volatile>() << '\n';
    std::cout << "| count<int, int &>()                         = " << count<int, int &>() << '\n';
    std::cout << "| count<int, int &&>()                        = " << count<int, int &&>() << '\n';
    std::cout << "| count<int, int const &>()                   = " << count<int, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int &, int &>()                       = " << count<int &, int &>() << '\n';
    std::cout << "| count<int &, int &&>()                      = " << count<int &, int &&>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<int &, int const &>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<int &&, int &&>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<int &&, int const &>() << '\n';
    std::cout << "| count<int &&, int &&>()                     = " << count<int &&, int &&>() << '\n';
    print_separator(title);
    std::cout << "| count<int *, int *>()                       = " << count<int *, int *>() << '\n';
    std::cout << "| count<int *, int const *>()                 = " << count<int *, int const *>() << '\n';
    std::cout << "| count<int *, int *const>()                  = " << count<int *, int *const>() << '\n';
    std::cout << "| count<int *, int const *const>()            = " << count<int *, int const *const>() << '\n';
    print_separator(title);
    std::cout << "| count<int const, int>()                     = " << count<int const, int>() << '\n';
    std::cout << "| count<int &, int>()                         = " << count<int &, int>() << '\n';
    std::cout << "| count<int const &, int>()                   = " << count<int const &, int>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<int &, int const &>() << '\n';
    std::cout << "| count<int &&, int>()                        = " << count<int &&, int>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<int &&, int &>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<int &&, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int *const, int *>()                  = " << count<int *const, int *>() << '\n';
    std::cout << "| count<int *const, int const *>()            = " << count<int *const, int const *>() << '\n';
    std::cout << "| count<int *const, int const *const>()       = " << count<int *const, int const *const>() << '\n';
    std::cout << "| count<int const *, int *>()                 = " << count<int const *, int *>() << '\n';
    std::cout << "| count<int const *, int *const>()            = " << count<int const *, int *const>() << '\n';
    std::cout << "| count<int const *, int const *const>()      = " << count<int const *, int const *const>() << '\n';
    std::cout << "| count<int const *const, int *>()            = " << count<int const *const, int *>() << '\n';
    std::cout << "| count<int const *const, int *const>()       = " << count<int const *const, int *const>() << '\n';
    std::cout << "| count<int const *const, int const *>()      = " << count<int const *const, int const *>() << '\n';
    print_separator(title, true);
}

auto test_count_with_exact_policy()
{
    using pi::type_list::count;
    using pi::type_list::search_policy;

    std::string const title{ "Testing count() function with exact policy (identical with no policy)" };

    print_title(title);
    std::cout << "| count<int, int8_t>()                        = " << count<search_policy::exact, int, int8_t>() << '\n';
    std::cout << "| count<int, int16_t>()                       = " << count<search_policy::exact, int, int16_t>() << '\n';
    std::cout << "| count<int, int32_t>()                       = " << count<search_policy::exact, int, int32_t>() << '\n';
    std::cout << "| count<int, int64_t>()                       = " << count<search_policy::exact, int, int64_t>() << '\n';
    std::cout << "| count<int, int>()                           = " << count<search_policy::exact, int, int>() << '\n';
    std::cout << "| count<int, int const>()                     = " << count<search_policy::exact, int, int const>() << '\n';
    std::cout << "| count<int, int volatile>()                  = " << count<search_policy::exact, int, int volatile>() << '\n';
    std::cout << "| count<int, int &>()                         = " << count<search_policy::exact, int, int &>() << '\n';
    std::cout << "| count<int, int &&>()                        = " << count<search_policy::exact, int, int &&>() << '\n';
    std::cout << "| count<int, int const &>()                   = " << count<search_policy::exact, int, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int &, int &>()                       = " << count<search_policy::exact, int &, int &>() << '\n';
    std::cout << "| count<int &, int &&>()                      = " << count<search_policy::exact, int &, int &&>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::exact, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::exact, int &&, int &&>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::exact, int &&, int const &>() << '\n';
    std::cout << "| count<int &&, int &&>()                     = " << count<search_policy::exact, int &&, int &&>() << '\n';
    print_separator(title);
    std::cout << "| count<int *, int *>()                       = " << count<search_policy::exact, int *, int *>() << '\n';
    std::cout << "| count<int *, int const *>()                 = " << count<search_policy::exact, int *, int const *>() << '\n';
    std::cout << "| count<int *, int *const>()                  = " << count<search_policy::exact, int *, int *const>() << '\n';
    std::cout << "| count<int *, int const *const>()            = " << count<search_policy::exact, int *, int const *const>() << '\n';
    print_separator(title);
    std::cout << "| count<int const, int>()                     = " << count<search_policy::exact, int const, int>() << '\n';
    std::cout << "| count<int &, int>()                         = " << count<search_policy::exact, int &, int>() << '\n';
    std::cout << "| count<int const &, int>()                   = " << count<search_policy::exact, int const &, int>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::exact, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int>()                        = " << count<search_policy::exact, int &&, int>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::exact, int &&, int &>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::exact, int &&, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int *const, int *>()                  = " << count<search_policy::exact, int *const, int *>() << '\n';
    std::cout << "| count<int *const, int const *>()            = " << count<search_policy::exact, int *const, int const *>() << '\n';
    std::cout << "| count<int *const, int const *const>()       = " << count<search_policy::exact, int *const, int const *const>() << '\n';
    std::cout << "| count<int const *, int *>()                 = " << count<search_policy::exact, int const *, int *>() << '\n';
    std::cout << "| count<int const *, int *const>()            = " << count<search_policy::exact, int const *, int *const>() << '\n';
    std::cout << "| count<int const *, int const *const>()      = " << count<search_policy::exact, int const *, int const *const>() << '\n';
    std::cout << "| count<int const *const, int *>()            = " << count<search_policy::exact, int const *const, int *>() << '\n';
    std::cout << "| count<int const *const, int *const>()       = " << count<search_policy::exact, int const *const, int *const>() << '\n';
    std::cout << "| count<int const *const, int const *>()      = " << count<search_policy::exact, int const *const, int const *>() << '\n';
    print_separator(title, true);
}

auto test_count_with_ignore_list_cv_policy()
{
    using pi::type_list::count;
    using pi::type_list::search_policy;

    std::string const title{ "Testing count() function with ignore const and volatile policy for list types" };

    print_title(title);
    std::cout << "| count<int, int8_t>()                        = " << count<search_policy::ignore_list_cv, int, int8_t>() << '\n';
    std::cout << "| count<int, int16_t>()                       = " << count<search_policy::ignore_list_cv, int, int16_t>() << '\n';
    std::cout << "| count<int, int32_t>()                       = " << count<search_policy::ignore_list_cv, int, int32_t>() << '\n';
    std::cout << "| count<int, int64_t>()                       = " << count<search_policy::ignore_list_cv, int, int64_t>() << '\n';
    std::cout << "| count<int, int>()                           = " << count<search_policy::ignore_list_cv, int, int>() << '\n';
    std::cout << "| count<int, int const>()                     = " << count<search_policy::ignore_list_cv, int, int const>() << '\n';
    std::cout << "| count<int, int volatile>()                  = " << count<search_policy::ignore_list_cv, int, int volatile>() << '\n';
    std::cout << "| count<int, int &>()                         = " << count<search_policy::ignore_list_cv, int, int &>() << '\n';
    std::cout << "| count<int, int &&>()                        = " << count<search_policy::ignore_list_cv, int, int &&>() << '\n';
    std::cout << "| count<int, int const &>()                   = " << count<search_policy::ignore_list_cv, int, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int &, int &>()                       = " << count<search_policy::ignore_list_cv, int &, int &>() << '\n';
    std::cout << "| count<int &, int &&>()                      = " << count<search_policy::ignore_list_cv, int &, int &&>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::ignore_list_cv, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::ignore_list_cv, int &&, int &&>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::ignore_list_cv, int &&, int const &>() << '\n';
    std::cout << "| count<int &&, int &&>()                     = " << count<search_policy::ignore_list_cv, int &&, int &&>() << '\n';
    print_separator(title);
    std::cout << "| count<int *, int *>()                       = " << count<search_policy::ignore_list_cv, int *, int *>() << '\n';
    std::cout << "| count<int *, int const *>()                 = " << count<search_policy::ignore_list_cv, int *, int const *>() << '\n';
    std::cout << "| count<int *, int *const>()                  = " << count<search_policy::ignore_list_cv, int *, int *const>() << '\n';
    std::cout << "| count<int *, int const *const>()            = " << count<search_policy::ignore_list_cv, int *, int const *const>() << '\n';
    print_separator(title);
    std::cout << "| count<int const, int>()                     = " << count<search_policy::ignore_list_cv, int const, int>() << '\n';
    std::cout << "| count<int &, int>()                         = " << count<search_policy::ignore_list_cv, int &, int>() << '\n';
    std::cout << "| count<int const &, int>()                   = " << count<search_policy::ignore_list_cv, int const &, int>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::ignore_list_cv, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int>()                        = " << count<search_policy::ignore_list_cv, int &&, int>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::ignore_list_cv, int &&, int &>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::ignore_list_cv, int &&, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int *const, int *>()                  = " << count<search_policy::ignore_list_cv, int *const, int *>() << '\n';
    std::cout << "| count<int *const, int const *>()            = " << count<search_policy::ignore_list_cv, int *const, int const *>() << '\n';
    std::cout << "| count<int *const, int const *const>()       = " << count<search_policy::ignore_list_cv, int *const, int const *const>() << '\n';
    std::cout << "| count<int const *, int *>()                 = " << count<search_policy::ignore_list_cv, int const *, int *>() << '\n';
    std::cout << "| count<int const *, int *const>()            = " << count<search_policy::ignore_list_cv, int const *, int *const>() << '\n';
    std::cout << "| count<int const *, int const *const>()      = " << count<search_policy::ignore_list_cv, int const *, int const *const>() << '\n';
    std::cout << "| count<int const *const, int *>()            = " << count<search_policy::ignore_list_cv, int const *const, int *>() << '\n';
    std::cout << "| count<int const *const, int *const>()       = " << count<search_policy::ignore_list_cv, int const *const, int *const>() << '\n';
    std::cout << "| count<int const *const, int const *>()      = " << count<search_policy::ignore_list_cv, int const *const, int const *>() << '\n';
    print_separator(title, true);
}

auto test_count_with_ignore_list_ref_policy()
{
    using pi::type_list::count;
    using pi::type_list::search_policy;

    std::string const title{ "Testing count() function with ignore reference policy for list types" };

    print_title(title);
    std::cout << "| count<int, int8_t>()                        = " << count<search_policy::ignore_list_ref, int, int8_t>() << '\n';
    std::cout << "| count<int, int16_t>()                       = " << count<search_policy::ignore_list_ref, int, int16_t>() << '\n';
    std::cout << "| count<int, int32_t>()                       = " << count<search_policy::ignore_list_ref, int, int32_t>() << '\n';
    std::cout << "| count<int, int64_t>()                       = " << count<search_policy::ignore_list_ref, int, int64_t>() << '\n';
    std::cout << "| count<int, int>()                           = " << count<search_policy::ignore_list_ref, int, int>() << '\n';
    std::cout << "| count<int, int const>()                     = " << count<search_policy::ignore_list_ref, int, int const>() << '\n';
    std::cout << "| count<int, int volatile>()                  = " << count<search_policy::ignore_list_ref, int, int volatile>() << '\n';
    std::cout << "| count<int, int &>()                         = " << count<search_policy::ignore_list_ref, int, int &>() << '\n';
    std::cout << "| count<int, int &&>()                        = " << count<search_policy::ignore_list_ref, int, int &&>() << '\n';
    std::cout << "| count<int, int const &>()                   = " << count<search_policy::ignore_list_ref, int, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int &, int &>()                       = " << count<search_policy::ignore_list_ref, int &, int &>() << '\n';
    std::cout << "| count<int &, int &&>()                      = " << count<search_policy::ignore_list_ref, int &, int &&>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::ignore_list_ref, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::ignore_list_ref, int &&, int &&>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::ignore_list_ref, int &&, int const &>() << '\n';
    std::cout << "| count<int &&, int &&>()                     = " << count<search_policy::ignore_list_ref, int &&, int &&>() << '\n';
    print_separator(title);
    std::cout << "| count<int *, int *>()                       = " << count<search_policy::ignore_list_ref, int *, int *>() << '\n';
    std::cout << "| count<int *, int const *>()                 = " << count<search_policy::ignore_list_ref, int *, int const *>() << '\n';
    std::cout << "| count<int *, int *const>()                  = " << count<search_policy::ignore_list_ref, int *, int *const>() << '\n';
    std::cout << "| count<int *, int const *const>()            = " << count<search_policy::ignore_list_ref, int *, int const *const>() << '\n';
    print_separator(title);
    std::cout << "| count<int const, int>()                     = " << count<search_policy::ignore_list_ref, int const, int>() << '\n';
    std::cout << "| count<int &, int>()                         = " << count<search_policy::ignore_list_ref, int &, int>() << '\n';
    std::cout << "| count<int const &, int>()                   = " << count<search_policy::ignore_list_ref, int const &, int>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::ignore_list_ref, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int>()                        = " << count<search_policy::ignore_list_ref, int &&, int>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::ignore_list_ref, int &&, int &>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::ignore_list_ref, int &&, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int *const, int *>()                  = " << count<search_policy::ignore_list_ref, int *const, int *>() << '\n';
    std::cout << "| count<int *const, int const *>()            = " << count<search_policy::ignore_list_ref, int *const, int const *>() << '\n';
    std::cout << "| count<int *const, int const *const>()       = " << count<search_policy::ignore_list_ref, int *const, int const *const>() << '\n';
    std::cout << "| count<int const *, int *>()                 = " << count<search_policy::ignore_list_ref, int const *, int *>() << '\n';
    std::cout << "| count<int const *, int *const>()            = " << count<search_policy::ignore_list_ref, int const *, int *const>() << '\n';
    std::cout << "| count<int const *, int const *const>()      = " << count<search_policy::ignore_list_ref, int const *, int const *const>() << '\n';
    std::cout << "| count<int const *const, int *>()            = " << count<search_policy::ignore_list_ref, int const *const, int *>() << '\n';
    std::cout << "| count<int const *const, int *const>()       = " << count<search_policy::ignore_list_ref, int const *const, int *const>() << '\n';
    std::cout << "| count<int const *const, int const *>()      = " << count<search_policy::ignore_list_ref, int const *const, int const *>() << '\n';
    print_separator(title, true);
}

auto test_count_with_ignore_list_cv_ref_policy()
{
    using pi::type_list::count;
    using pi::type_list::search_policy;

    std::string const title{ "Testing count() function with ignore const, volatile and reference policy for list types" };

    print_title(title);
    std::cout << "| count<int, int8_t>()                        = " << count<search_policy::ignore_list_cv_ref, int, int8_t>() << '\n';
    std::cout << "| count<int, int16_t>()                       = " << count<search_policy::ignore_list_cv_ref, int, int16_t>() << '\n';
    std::cout << "| count<int, int32_t>()                       = " << count<search_policy::ignore_list_cv_ref, int, int32_t>() << '\n';
    std::cout << "| count<int, int64_t>()                       = " << count<search_policy::ignore_list_cv_ref, int, int64_t>() << '\n';
    std::cout << "| count<int, int>()                           = " << count<search_policy::ignore_list_cv_ref, int, int>() << '\n';
    std::cout << "| count<int, int const>()                     = " << count<search_policy::ignore_list_cv_ref, int, int const>() << '\n';
    std::cout << "| count<int, int volatile>()                  = " << count<search_policy::ignore_list_cv_ref, int, int volatile>() << '\n';
    std::cout << "| count<int, int &>()                         = " << count<search_policy::ignore_list_cv_ref, int, int &>() << '\n';
    std::cout << "| count<int, int &&>()                        = " << count<search_policy::ignore_list_cv_ref, int, int &&>() << '\n';
    std::cout << "| count<int, int const &>()                   = " << count<search_policy::ignore_list_cv_ref, int, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int &, int &>()                       = " << count<search_policy::ignore_list_cv_ref, int &, int &>() << '\n';
    std::cout << "| count<int &, int &&>()                      = " << count<search_policy::ignore_list_cv_ref, int &, int &&>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::ignore_list_cv_ref, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::ignore_list_cv_ref, int &&, int &&>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::ignore_list_cv_ref, int &&, int const &>() << '\n';
    std::cout << "| count<int &&, int &&>()                     = " << count<search_policy::ignore_list_cv_ref, int &&, int &&>() << '\n';
    print_separator(title);
    std::cout << "| count<int *, int *>()                       = " << count<search_policy::ignore_list_cv_ref, int *, int *>() << '\n';
    std::cout << "| count<int *, int const *>()                 = " << count<search_policy::ignore_list_cv_ref, int *, int const *>() << '\n';
    std::cout << "| count<int *, int *const>()                  = " << count<search_policy::ignore_list_cv_ref, int *, int *const>() << '\n';
    std::cout << "| count<int *, int const *const>()            = " << count<search_policy::ignore_list_cv_ref, int *, int const *const>() << '\n';
    print_separator(title);
    std::cout << "| count<int const, int>()                     = " << count<search_policy::ignore_list_cv_ref, int const, int>() << '\n';
    std::cout << "| count<int &, int>()                         = " << count<search_policy::ignore_list_cv_ref, int &, int>() << '\n';
    std::cout << "| count<int const &, int>()                   = " << count<search_policy::ignore_list_cv_ref, int const &, int>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::ignore_list_cv_ref, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int>()                        = " << count<search_policy::ignore_list_cv_ref, int &&, int>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::ignore_list_cv_ref, int &&, int &>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::ignore_list_cv_ref, int &&, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int *const, int *>()                  = " << count<search_policy::ignore_list_cv_ref, int *const, int *>() << '\n';
    std::cout << "| count<int *const, int const *>()            = " << count<search_policy::ignore_list_cv_ref, int *const, int const *>() << '\n';
    std::cout << "| count<int *const, int const *const>()       = " << count<search_policy::ignore_list_cv_ref, int *const, int const *const>() << '\n';
    std::cout << "| count<int const *, int *>()                 = " << count<search_policy::ignore_list_cv_ref, int const *, int *>() << '\n';
    std::cout << "| count<int const *, int const *>()           = " << count<search_policy::ignore_list_cv_ref, int const *, int const *>() << '\n';
    std::cout << "| count<int const *, int const *const>()      = " << count<search_policy::ignore_list_cv_ref, int const *, int const *const>() << '\n';
    std::cout << "| count<int const *const, int *>()            = " << count<search_policy::ignore_list_cv_ref, int const *const, int *>() << '\n';
    std::cout << "| count<int const *const, int *const>()       = " << count<search_policy::ignore_list_cv_ref, int const *const, int *const>() << '\n';
    std::cout << "| count<int const *const, int const *>()      = " << count<search_policy::ignore_list_cv_ref, int const *const, int const *>() << '\n';
    print_separator(title, true);
}

auto test_count_with_ignore_all_cv_policy()
{
    using pi::type_list::count;
    using pi::type_list::search_policy;

    std::string const title{ "Testing count() function with ignore const and volatile policy for all types" };

    print_title(title);
    std::cout << "| count<int, int8_t>()                        = " << count<search_policy::ignore_all_cv, int, int8_t>() << '\n';
    std::cout << "| count<int, int16_t>()                       = " << count<search_policy::ignore_all_cv, int, int16_t>() << '\n';
    std::cout << "| count<int, int32_t>()                       = " << count<search_policy::ignore_all_cv, int, int32_t>() << '\n';
    std::cout << "| count<int, int64_t>()                       = " << count<search_policy::ignore_all_cv, int, int64_t>() << '\n';
    std::cout << "| count<int, int>()                           = " << count<search_policy::ignore_all_cv, int, int>() << '\n';
    std::cout << "| count<int, int const>()                     = " << count<search_policy::ignore_all_cv, int, int const>() << '\n';
    std::cout << "| count<int, int volatile>()                  = " << count<search_policy::ignore_all_cv, int, int volatile>() << '\n';
    std::cout << "| count<int, int &>()                         = " << count<search_policy::ignore_all_cv, int, int &>() << '\n';
    std::cout << "| count<int, int &&>()                        = " << count<search_policy::ignore_all_cv, int, int &&>() << '\n';
    std::cout << "| count<int, int const &>()                   = " << count<search_policy::ignore_all_cv, int, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int &, int &>()                       = " << count<search_policy::ignore_all_cv, int &, int &>() << '\n';
    std::cout << "| count<int &, int &&>()                      = " << count<search_policy::ignore_all_cv, int &, int &&>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::ignore_all_cv, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::ignore_all_cv, int &&, int &&>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::ignore_all_cv, int &&, int const &>() << '\n';
    std::cout << "| count<int &&, int &&>()                     = " << count<search_policy::ignore_all_cv, int &&, int &&>() << '\n';
    print_separator(title);
    std::cout << "| count<int *, int *>()                       = " << count<search_policy::ignore_all_cv, int *, int *>() << '\n';
    std::cout << "| count<int *, int const *>()                 = " << count<search_policy::ignore_all_cv, int *, int const *>() << '\n';
    std::cout << "| count<int *, int *const>()                  = " << count<search_policy::ignore_all_cv, int *, int *const>() << '\n';
    std::cout << "| count<int *, int const *const>()            = " << count<search_policy::ignore_all_cv, int *, int const *const>() << '\n';
    print_separator(title);
    std::cout << "| count<int const, int>()                     = " << count<search_policy::ignore_all_cv, int const, int>() << '\n';
    std::cout << "| count<int &, int>()                         = " << count<search_policy::ignore_all_cv, int &, int>() << '\n';
    std::cout << "| count<int const &, int>()                   = " << count<search_policy::ignore_all_cv, int const &, int>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::ignore_all_cv, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int>()                        = " << count<search_policy::ignore_all_cv, int &&, int>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::ignore_all_cv, int &&, int &>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::ignore_all_cv, int &&, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int *const, int *>()                  = " << count<search_policy::ignore_all_cv, int *const, int *>() << '\n';
    std::cout << "| count<int *const, int const *>()            = " << count<search_policy::ignore_all_cv, int *const, int const *>() << '\n';
    std::cout << "| count<int *const, int const *const>()       = " << count<search_policy::ignore_all_cv, int *const, int const *const>() << '\n';
    std::cout << "| count<int const *, int *>()                 = " << count<search_policy::ignore_all_cv, int const *, int *>() << '\n';
    std::cout << "| count<int const *, int *const>()            = " << count<search_policy::ignore_all_cv, int const *, int *const>() << '\n';
    std::cout << "| count<int const *, int const *const>()      = " << count<search_policy::ignore_all_cv, int const *, int const *const>() << '\n';
    std::cout << "| count<int const *const, int *>()            = " << count<search_policy::ignore_all_cv, int const *const, int *>() << '\n';
    std::cout << "| count<int const *const, int *const>()       = " << count<search_policy::ignore_all_cv, int const *const, int *const>() << '\n';
    std::cout << "| count<int const *const, int const *>()      = " << count<search_policy::ignore_all_cv, int const *const, int const *>() << '\n';
    print_separator(title, true);
}

auto test_count_with_ignore_all_ref_policy()
{
    using pi::type_list::count;
    using pi::type_list::search_policy;

    std::string const title{ "Testing count() function with ignore reference policy for all types" };

    print_title(title);
    std::cout << "| count<int, int8_t>()                        = " << count<search_policy::ignore_all_ref, int, int8_t>() << '\n';
    std::cout << "| count<int, int16_t>()                       = " << count<search_policy::ignore_all_ref, int, int16_t>() << '\n';
    std::cout << "| count<int, int32_t>()                       = " << count<search_policy::ignore_all_ref, int, int32_t>() << '\n';
    std::cout << "| count<int, int64_t>()                       = " << count<search_policy::ignore_all_ref, int, int64_t>() << '\n';
    std::cout << "| count<int, int>()                           = " << count<search_policy::ignore_all_ref, int, int>() << '\n';
    std::cout << "| count<int, int const>()                     = " << count<search_policy::ignore_all_ref, int, int const>() << '\n';
    std::cout << "| count<int, int volatile>()                  = " << count<search_policy::ignore_all_ref, int, int volatile>() << '\n';
    std::cout << "| count<int, int &>()                         = " << count<search_policy::ignore_all_ref, int, int &>() << '\n';
    std::cout << "| count<int, int &&>()                        = " << count<search_policy::ignore_all_ref, int, int &&>() << '\n';
    std::cout << "| count<int, int const &>()                   = " << count<search_policy::ignore_all_ref, int, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int &, int &>()                       = " << count<search_policy::ignore_all_ref, int &, int &>() << '\n';
    std::cout << "| count<int &, int &&>()                      = " << count<search_policy::ignore_all_ref, int &, int &&>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::ignore_all_ref, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::ignore_all_ref, int &&, int &&>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::ignore_all_ref, int &&, int const &>() << '\n';
    std::cout << "| count<int &&, int &&>()                     = " << count<search_policy::ignore_all_ref, int &&, int &&>() << '\n';
    print_separator(title);
    std::cout << "| count<int *, int *>()                       = " << count<search_policy::ignore_all_ref, int *, int *>() << '\n';
    std::cout << "| count<int *, int const *>()                 = " << count<search_policy::ignore_all_ref, int *, int const *>() << '\n';
    std::cout << "| count<int *, int *const>()                  = " << count<search_policy::ignore_all_ref, int *, int *const>() << '\n';
    std::cout << "| count<int *, int const *const>()            = " << count<search_policy::ignore_all_ref, int *, int const *const>() << '\n';
    print_separator(title);
    std::cout << "| count<int const, int>()                     = " << count<search_policy::ignore_all_ref, int const, int>() << '\n';
    std::cout << "| count<int &, int>()                         = " << count<search_policy::ignore_all_ref, int &, int>() << '\n';
    std::cout << "| count<int const &, int>()                   = " << count<search_policy::ignore_all_ref, int const &, int>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::ignore_all_ref, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int>()                        = " << count<search_policy::ignore_all_ref, int &&, int>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::ignore_all_ref, int &&, int &>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::ignore_all_ref, int &&, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int *const, int *>()                  = " << count<search_policy::ignore_all_ref, int *const, int *>() << '\n';
    std::cout << "| count<int *const, int const *>()            = " << count<search_policy::ignore_all_ref, int *const, int const *>() << '\n';
    std::cout << "| count<int *const, int const *const>()       = " << count<search_policy::ignore_all_ref, int *const, int const *const>() << '\n';
    std::cout << "| count<int const *, int *>()                 = " << count<search_policy::ignore_all_ref, int const *, int *>() << '\n';
    std::cout << "| count<int const *, int *const>()            = " << count<search_policy::ignore_all_ref, int const *, int *const>() << '\n';
    std::cout << "| count<int const *, int const *const>()      = " << count<search_policy::ignore_all_ref, int const *, int const *const>() << '\n';
    std::cout << "| count<int const *const, int *>()            = " << count<search_policy::ignore_all_ref, int const *const, int *>() << '\n';
    std::cout << "| count<int const *const, int *const>()       = " << count<search_policy::ignore_all_ref, int const *const, int *const>() << '\n';
    std::cout << "| count<int const *const, int const *>()      = " << count<search_policy::ignore_all_ref, int const *const, int const *>() << '\n';
    print_separator(title, true);
}

auto test_count_with_ignore_all_cv_ref_policy()
{
    using pi::type_list::count;
    using pi::type_list::search_policy;

    std::string const title{ "Testing count() function with ignore const, volatile and reference policy for all types" };

    print_title(title);
    std::cout << "| count<int, int8_t>()                        = " << count<search_policy::ignore_all_cv_ref, int, int8_t>() << '\n';
    std::cout << "| count<int, int16_t>()                       = " << count<search_policy::ignore_all_cv_ref, int, int16_t>() << '\n';
    std::cout << "| count<int, int32_t>()                       = " << count<search_policy::ignore_all_cv_ref, int, int32_t>() << '\n';
    std::cout << "| count<int, int64_t>()                       = " << count<search_policy::ignore_all_cv_ref, int, int64_t>() << '\n';
    std::cout << "| count<int, int>()                           = " << count<search_policy::ignore_all_cv_ref, int, int>() << '\n';
    std::cout << "| count<int, int const>()                     = " << count<search_policy::ignore_all_cv_ref, int, int const>() << '\n';
    std::cout << "| count<int, int volatile>()                  = " << count<search_policy::ignore_all_cv_ref, int, int volatile>() << '\n';
    std::cout << "| count<int, int &>()                         = " << count<search_policy::ignore_all_cv_ref, int, int &>() << '\n';
    std::cout << "| count<int, int &&>()                        = " << count<search_policy::ignore_all_cv_ref, int, int &&>() << '\n';
    std::cout << "| count<int, int const &>()                   = " << count<search_policy::ignore_all_cv_ref, int, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int &, int &>()                       = " << count<search_policy::ignore_all_cv_ref, int &, int &>() << '\n';
    std::cout << "| count<int &, int &&>()                      = " << count<search_policy::ignore_all_cv_ref, int &, int &&>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::ignore_all_cv_ref, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::ignore_all_cv_ref, int &&, int &&>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::ignore_all_cv_ref, int &&, int const &>() << '\n';
    std::cout << "| count<int &&, int &&>()                     = " << count<search_policy::ignore_all_cv_ref, int &&, int &&>() << '\n';
    print_separator(title);
    std::cout << "| count<int *, int *>()                       = " << count<search_policy::ignore_all_cv_ref, int *, int *>() << '\n';
    std::cout << "| count<int *, int const *>()                 = " << count<search_policy::ignore_all_cv_ref, int *, int const *>() << '\n';
    std::cout << "| count<int *, int *const>()                  = " << count<search_policy::ignore_all_cv_ref, int *, int *const>() << '\n';
    std::cout << "| count<int *, int const *const>()            = " << count<search_policy::ignore_all_cv_ref, int *, int const *const>() << '\n';
    print_separator(title);
    std::cout << "| count<int const, int>()                     = " << count<search_policy::ignore_all_cv_ref, int const, int>() << '\n';
    std::cout << "| count<int &, int>()                         = " << count<search_policy::ignore_all_cv_ref, int &, int>() << '\n';
    std::cout << "| count<int const &, int>()                   = " << count<search_policy::ignore_all_cv_ref, int const &, int>() << '\n';
    std::cout << "| count<int &, int const &>()                 = " << count<search_policy::ignore_all_cv_ref, int &, int const &>() << '\n';
    std::cout << "| count<int &&, int>()                        = " << count<search_policy::ignore_all_cv_ref, int &&, int>() << '\n';
    std::cout << "| count<int &&, int &>()                      = " << count<search_policy::ignore_all_cv_ref, int &&, int &>() << '\n';
    std::cout << "| count<int &&, int const &>()                = " << count<search_policy::ignore_all_cv_ref, int &&, int const &>() << '\n';
    print_separator(title);
    std::cout << "| count<int *const, int *>()                  = " << count<search_policy::ignore_all_cv_ref, int *const, int *>() << '\n';
    std::cout << "| count<int *const, int const *>()            = " << count<search_policy::ignore_all_cv_ref, int *const, int const *>() << '\n';
    std::cout << "| count<int *const, int const *const>()       = " << count<search_policy::ignore_all_cv_ref, int *const, int const *const>() << '\n';
    std::cout << "| count<int const *, int *>()                 = " << count<search_policy::ignore_all_cv_ref, int const *, int *>() << '\n';
    std::cout << "| count<int const *, int *const>()            = " << count<search_policy::ignore_all_cv_ref, int const *, int *const>() << '\n';
    std::cout << "| count<int const *, int const *const>()      = " << count<search_policy::ignore_all_cv_ref, int const *, int const *const>() << '\n';
    std::cout << "| count<int const *const, int *>()            = " << count<search_policy::ignore_all_cv_ref, int const *const, int *>() << '\n';
    std::cout << "| count<int const *const, int *const>()       = " << count<search_policy::ignore_all_cv_ref, int const *const, int *const>() << '\n';
    std::cout << "| count<int const *const, int const *>()      = " << count<search_policy::ignore_all_cv_ref, int const *const, int const *>() << '\n';
    print_separator(title, true);
}

int main()
{
    test_count_without_policy();
    test_count_with_exact_policy();
    test_count_with_ignore_list_cv_policy();
    test_count_with_ignore_list_ref_policy();
    test_count_with_ignore_list_cv_ref_policy();
    test_count_with_ignore_all_cv_policy();
    test_count_with_ignore_all_ref_policy();
    test_count_with_ignore_all_cv_ref_policy();

    return 0;
}

namespace
{
    void print_title(std::string const &title)
    {
        std::cout << ' ' << std::string(title.size() + 2, '-') << '\n';
        std::cout << "| " << title << " |\n";
        std::cout << '+' << std::string(title.size() + 2, '-') << '\n';
    }

    void print_separator(std::string const &title, bool const is_last)
    {
        std::cout << (is_last ? ' ' : '+') << std::string(title.size() + 2, '-') << (is_last ? "\n\n" : "\n");
    }
}
