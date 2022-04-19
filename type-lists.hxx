#pragma once

#include <type_traits>

namespace pi::type_lists
{
    auto static constexpr n_pos = -1;

    namespace internal
    {
        template <typename Type, typename First, typename ...Rest>
        auto constexpr find() noexcept
        {
            if constexpr (std::is_same_v<First, Type> || sizeof...(Rest) == size_t{ 0 })
            {
                return  0;
            }
            else
            {
                return 1 + internal::find<Type, Rest...>();
            }
        }
    } // namespace internal
    /**
     * @enum Matching strategies are used for counting or finding types in type list.
     */
    enum class matching
    {
        strict  ///< Matches the types if they are exactly the same (both are values or l-reference or r-reference; both are const or volatile etc.)
      , relaxed ///< Matches the types regardless of modifiers; also, values are matched to references.
    };

    /**
     * @typedef The exact type for @a matching::strict, the base (decayed) type else.
     */
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
     * @brief Count the number of appearances of a type in a list of types.
     * @tparam Type The type which appearances we want to count the number of appearances in the list of types.
     * @tparam TypeList The list of types in which to look for Type.
     * @return The number of matches of Type in TypeList.
     * @note Effectively calls count() with matching::strict strategy.
     */
    template <typename Type, typename ...TypeList>
    auto constexpr count_v = count<matching::relaxed, Type, TypeList...>();

    /**
     * @brief Find the first appearance of the first template parameter into the list of types which follows it.
     * @tparam Matching The searching policy (search for exactly the same type or ignore const, reference or const and reference on types from the list.
     * @tparam Type The type to search for.
     * @tparam TypeList The list of types in which to look for Type.
     * @return The index of Type in TypeList. If no match is found, returns pi::type_list::n_pos.
     */
    template <matching Matching, typename Type, typename ...TypeList>
    auto constexpr find() noexcept
    {
        if constexpr (count<Matching, Type, TypeList...>() == size_t{ 0 })
        {
            return n_pos;
        }

        return internal::find<Type, adjust_for_matching_t<TypeList, Matching>...>();
    }

    /**
     * @brief Find the first appearance of the first template parameter into the list of types which follows it.
     * @tparam Type The type to search for.
     * @tparam TypeList The list of types in which to look for Type.
     * @return The index of Type in TypeList. If no match is found, returns pi::type_list::n_pos.
     * @note Effectively calls find() with matching::strict strategy.
     */
    template <typename Type, typename ...TypeList>
    auto constexpr find_v = find<matching::relaxed, Type, TypeList...>();
} // namespace pi::type_list
