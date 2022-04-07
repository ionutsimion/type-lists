#pragma once

#include <type_traits>

namespace pi::type_lists
{
    /**
     * @brief Search policies are used for counting or finding types in type lists.
     * @enum strict Matches the types if they have exactly the same modifiers (including none) and are the same type of pointers or references (including none).
     * @enum ignore_const Matches the types only if the type to search for is identical to one from the list without const modifier.
     * @enum ignore_reference Matches the types only of the type to search for is identical to one from the list without references.
     * @enum relaxed Matches the type only if the type to search for is identical to one from the list without references or const modifier.
     */
    enum class matching
    {
        strict
      , relaxed
    };

    template <typename Type, matching Matching>
    using adjust_for_matching_t = std::conditional_t<Matching == matching::strict, Type, std::decay_t<Type>>;

    /**
     * @brief Count the number of appearances of the first template parameter into the list of types which follows it.
     * @tparam Matching The searching policy (search for exactly the same type or ignore const, reference or const and reference on types from the list.
     * @tparam TypeToCount The type for which we want to count the number of appearances in the rest of the types.
     * @tparam FirstTypeInTheTypeList The first type of the type list in which we search for appearances of TypeToCount.
     * @tparam RestOfTheTypeList The rest of the list of types in which we look to count the number of appearances of TypeToCount.
     * @return The number of types that corresponding to the searching policy.
     */
    template <matching Matching, typename Type, typename ...TypeList>
    auto constexpr count()
    {
        return (... + std::is_same_v<Type, adjust_for_matching_t<TypeList, Matching>>);
    }

    /**
     * @brief Find the first appearance of the first template parameter into the list of types which follows it.
     * @tparam Matching The searching policy (search for exactly the same type or ignore const, reference or const and reference on types from the list.
     * @tparam TypeToFind The type for which we want to count the number of appearances in the rest of the types.
     * @tparam FirstTypeInTheTypeList The first type of the type list in which we search for appearances of TypeToFind.
     * @tparam RestOfTheTypeList The rest of the list of types in which we look to count the number of appearances of TypeToFind.
     * @return The index of the type (corresponding to the search policy) in the list of types. If the type does not exist, the function returns -1.
     */
    template <matching Matching, typename TypeToFind, typename FirstTypeInTheTypeList, typename ...RestOfTheTypeList>
    auto constexpr find() noexcept
    {
        if constexpr (count<Matching, TypeToFind, adjust_for_matching_t<FirstTypeInTheTypeList, Matching>, adjust_for_matching_t<RestOfTheTypeList, Matching>...>() == 0)
        {
            return -1;
        }

        if constexpr (sizeof...(RestOfTheTypeList) == 0)
            return static_cast<int>(std::is_same_v<TypeToFind, adjust_for_matching_t<FirstTypeInTheTypeList, Matching>>) - 1;
        else
            return !static_cast<int>(std::is_same_v<TypeToFind, adjust_for_matching_t<FirstTypeInTheTypeList, Matching>>) * (1 + find<Matching, TypeToFind, RestOfTheTypeList...>());
    }

    /**
     * @brief Count the number of appearances of a type in a list of types.
     * @tparam Type The type which appearances we want to count the number of appearances in the list of types.
     * @tparam TypeList The list of types in which to look for Type.
     * @return The number of types identical to the one to be counted.
     */
    template <typename Type, typename ...TypeList>
    auto constexpr count_v = count<matching::relaxed, Type, TypeList...>();

    /**
     * @brief Find the first appearance of the first template parameter into the list of types which follows it.
     * @tparam Type The type we want to find.
     * @tparam TypeList The list of types in which to look for Type.
     * @return The index of the type in the list of types. If the type does not exist, the function returns -1.
     */
    template <typename Type, typename ...TypeList>
    auto constexpr find_v = find<matching::relaxed, Type, TypeList...>();
} // namespace pi::type_list
