//
// Created by ionut on 25.09.2021.
//

#ifndef TYPE_LISTS_TYPE_LISTS_HXX
#define TYPE_LISTS_TYPE_LISTS_HXX

#include <type_traits>

namespace pi::type_list
{
    /**
     * @brief Count the number of appearances of the first template parameter into the list of types which follows it.
     * @tparam TypeToCount The type for which we want to count the number of appearances in the rest of the types.
     * @tparam FirstTypeInTheTypeList The first type of the type list in which we search for appearances of TypeToCount.
     * @tparam RestOfTheTypeList The rest of the list of types in which we look to count the number of appearances of TypeToCount.
     * @return The number of types identical to the one to be counted.
     */
    template <typename TypeToCount, typename FirstTypeInTheTypeList, typename ...RestOfTheTypeList>
    auto constexpr count() noexcept
    {
        if constexpr (sizeof...(RestOfTheTypeList) == 0)
            return std::is_same_v<TypeToCount, FirstTypeInTheTypeList>;
        else
            return std::is_same_v<TypeToCount, FirstTypeInTheTypeList>
                 + count<TypeToCount, RestOfTheTypeList...>();
    }

    /**
     * @brief Find the first appearance of the first template parameter into the list of types which follows it.
     * @tparam TypeToFind The type for which we want to count the number of appearances in the rest of the types.
     * @tparam FirstTypeInTheTypeList The first type of the type list in which we search for appearances of TypeToCount.
     * @tparam RestOfTheTypeList The rest of the list of types in which we look to count the number of appearances of TypeToCount.
     * @return The index of the type in the list of types. If the type does not exist, the function returns -1.
     */
    template <typename TypeToFind, typename FirstTypeInTheTypeList, typename ...RestOfTheTypeList>
    auto constexpr find() noexcept
    {
        if constexpr (count<TypeToFind, FirstTypeInTheTypeList, RestOfTheTypeList...>() == 0)
            return -1;

        if constexpr (sizeof...(RestOfTheTypeList) == 0)
            return static_cast<int>(std::is_same_v<TypeToFind, FirstTypeInTheTypeList>) - 1;
        else
            return !static_cast<int>(std::is_same_v<TypeToFind, FirstTypeInTheTypeList>) * (1 + find<TypeToFind, RestOfTheTypeList...>());
    }

    template <typename T>
    using remove_cv_ref_t = std::remove_cv_t<std::remove_reference_t<T>>;

    template <typename T>
    using remove_cv_from_reference_t = std::conditional_t<std::is_lvalue_reference_v<T>, std::add_lvalue_reference_t<remove_cv_ref_t<T>>, std::remove_cv_t<T>>;

    template <typename T>
    using remove_cv_from_pointer_t = std::conditional_t<std::is_pointer_v<T>, std::add_pointer_t<std::remove_cv_t<std::remove_pointer_t<T>>>, std::remove_cv_t<T>>;

    template <typename T>
    using remove_cv_from_reference_or_pointer_t = std::conditional_t<std::is_pointer_v<T>, remove_cv_from_pointer_t<T>, remove_cv_from_reference_t<T>>;

    /**
     * @brief Search policies are used for counting or finding types in type lists.
     * @enum exact Matches the types if they have exactly the same modifiers (including none) and are the same type of pointers or references (including none).
     * @enum ignore_const Matches the types only if the type to search for is identical to one from the list without const modifier.
     * @enum ignore_reference Matches the types only of the type to search for is identical to one from the list without references.
     * @enum ignore_const_and_reference Matches the type only if the type to search for is identical to one from the list without references or const modifier.
     */
    enum class search_policy
    {
        exact
      , ignore_const
      , ignore_reference
      , ignore_const_and_reference
    };

    template <search_policy SearchPolicy, typename TypeToCount, typename FirstTypeInTheTypeList, typename ...RestOfTheTypeList>
    struct search_policy_t
    {
        static auto constexpr count() noexcept
        {
            if constexpr (SearchPolicy == search_policy::ignore_const)
                return pi::type_list::count<TypeToCount
                                          , std::remove_cv_t<remove_cv_from_reference_or_pointer_t<FirstTypeInTheTypeList>>
                                          , std::remove_cv_t<remove_cv_from_reference_or_pointer_t<RestOfTheTypeList>>...>();
            else if constexpr (SearchPolicy == search_policy::ignore_reference)
                return pi::type_list::count<TypeToCount
                                          , std::remove_reference_t<FirstTypeInTheTypeList>
                                          , std::remove_reference_t<RestOfTheTypeList>...>();
            else if constexpr (SearchPolicy == search_policy::ignore_const_and_reference)
                return pi::type_list::count<TypeToCount
                                          , std::remove_cv_t<std::remove_reference_t<remove_cv_from_reference_or_pointer_t<FirstTypeInTheTypeList>>>
                                          , std::remove_cv_t<std::remove_reference_t<remove_cv_from_reference_or_pointer_t<RestOfTheTypeList>>>...>();

            return pi::type_list::count<TypeToCount, FirstTypeInTheTypeList, RestOfTheTypeList...>();
        }

        static auto constexpr find() noexcept
        {
            if constexpr (SearchPolicy == search_policy::ignore_const)
                return pi::type_list::find<TypeToCount
                                         , std::remove_cv_t<remove_cv_from_reference_or_pointer_t<FirstTypeInTheTypeList>>
                                         , std::remove_cv_t<remove_cv_from_reference_or_pointer_t<RestOfTheTypeList>>...>();
            else if constexpr (SearchPolicy == search_policy::ignore_reference)
                return pi::type_list::find<TypeToCount
                                         , std::remove_reference_t<FirstTypeInTheTypeList>
                                         , std::remove_reference_t<RestOfTheTypeList>...>();
            else if constexpr (SearchPolicy == search_policy::ignore_const_and_reference)
                return pi::type_list::find<TypeToCount
                                         , std::remove_cv_t<std::remove_reference_t<remove_cv_from_reference_or_pointer_t<FirstTypeInTheTypeList>>>
                                         , std::remove_cv_t<std::remove_reference_t<remove_cv_from_reference_or_pointer_t<RestOfTheTypeList>>>...>();

            return pi::type_list::find<TypeToCount, FirstTypeInTheTypeList, RestOfTheTypeList...>();
        }
    };

    /**
     * @brief Count the number of appearances of the first template parameter into the list of types which follows it.
     * @tparam SearchPolicy The searching policy (search for exactly the same type or ignore const, reference or const and reference on types from the list.
     * @tparam TypeToCount The type for which we want to count the number of appearances in the rest of the types.
     * @tparam FirstTypeInTheTypeList The first type of the type list in which we search for appearances of TypeToCount.
     * @tparam RestOfTheTypeList The rest of the list of types in which we look to count the number of appearances of TypeToCount.
     * @return The number of types that corresponding to the searching policy.
     */
    template <search_policy SearchPolicy, typename TypeToCount, typename FirstTypeInTheTypeList, typename ...RestOfTheTypeList>
    auto constexpr count() noexcept
    {
        return pi::type_list::search_policy_t<SearchPolicy, TypeToCount, FirstTypeInTheTypeList, RestOfTheTypeList...>::count();
    }

    /**
     * @brief Find the first appearance of the first template parameter into the list of types which follows it.
     * @tparam SearchPolicy The searching policy (search for exactly the same type or ignore const, reference or const and reference on types from the list.
     * @tparam TypeToFind The type for which we want to count the number of appearances in the rest of the types.
     * @tparam FirstTypeInTheTypeList The first type of the type list in which we search for appearances of TypeToCount.
     * @tparam RestOfTheTypeList The rest of the list of types in which we look to count the number of appearances of TypeToCount.
     * @return The index of the type (corresponding to the search policy) in the list of types. If the type does not exist, the function returns -1.
     */
    template <search_policy SearchPolicy, typename TypeToCount, typename FirstTypeInTheTypeList, typename ...RestOfTheTypeList>
    auto constexpr find() noexcept
    {
        return pi::type_list::search_policy_t<SearchPolicy, TypeToCount, FirstTypeInTheTypeList, RestOfTheTypeList...>::find();
    }
}

#endif //TYPE_LISTS_TYPE_LISTS_HXX
