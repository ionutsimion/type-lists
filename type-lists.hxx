#pragma once

#include <type_traits>

namespace pi::type_lists
{
    namespace internal
    {
        template <typename Type, std::size_t Nth, typename First, typename ...Rest>
        [[nodiscard]] auto constexpr find_nth() noexcept
        {
            if constexpr ((Nth == 1ULL && std::is_same_v<First, Type>)|| sizeof...(Rest) == 0ULL)
            {
                return 0;
            }
            else
            {
                return 1 + find_nth<Type, Nth - std::is_same_v<Type, First>, Rest...>();
            }
        }

        template <typename Type, typename First, typename ...Rest>
        [[nodiscard]] auto constexpr find() noexcept
        {
            if constexpr (std::is_same_v<First, Type> || sizeof...(Rest) == 0ULL)
            {
                return 0;
            }
            else
            {
                return 1 + find<Type, Rest...>();
            }
        }
    } // namespace internal

    /**
     * @invariant Invalid position.
     */
    auto constexpr npos = -1;

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
     * @brief Count the number of appearances of a type in a list of types using a matching strategy.
     * @tparam Matching The searching policy (search for exactly the same type or ignore const, reference or const and reference on types from the list.
     * @tparam Type The type which appearances we want to count the number of appearances in the list of types.
     * @tparam TypeList The list of types in which to look for Type.
     * @return The number of matches of Type in TypeList.
     */
    template <matching Matching, typename Type, typename ...TypeList>
    [[nodiscard]] auto constexpr count()
    {
        return (... + std::is_same_v<adjust_for_matching_t<Type, Matching>, adjust_for_matching_t<TypeList, Matching>>);
    }

    /**
     * @brief Count the number of appearances of a type in a list of types.
     * @tparam Type The type which appearances we want to count the number of appearances in the list of types.
     * @tparam TypeList The list of types in which to look for Type.
     * @return The number of matches of Type in TypeList.
     * @note Effectively calls \a count with \a matching::strict strategy.
     */
    template <typename Type, typename ...TypeList>
    [[maybe_unused]] auto constexpr count_v = count<matching::relaxed, Type, TypeList...>();

    template <matching Matching, typename Type, std::size_t Nth, typename ...TypeList>
    [[nodiscard]] auto constexpr find_nth() noexcept
    {
        static_assert(sizeof...(TypeList) > 0ULL, "At least one type is expected.");
        static_assert(Nth > 0 && Nth <= sizeof...(TypeList), "Nth is a 1-based index at most equal to the number of the type list elements.");

        if constexpr (count<Matching, Type, TypeList...>() < Nth)
        {
            return npos;
        }

        return internal::find_nth<adjust_for_matching_t<Type, Matching>, Nth, adjust_for_matching_t<TypeList, Matching>...>();
    }

    template <typename Type, std::size_t Nth, typename ...TypeList>
    [[maybe_unused]] auto constexpr find_nth_v = find_nth<matching::relaxed, Type, Nth, TypeList...>();

    /**
     * @brief Find the first appearance of the first template parameter into the list of types which follows it.
     * @tparam Matching The searching policy (search for exactly the same type or ignore const, reference or const and reference on types from the list.
     * @tparam Type The type to search for.
     * @tparam TypeList The list of types in which to look for Type.
     * @return The index of Type in TypeList. If no match is found, returns \a pi::type_list::npos.
     */
    template <matching Matching, typename Type, typename ...TypeList>
    [[nodiscard]] auto constexpr find() noexcept
    {
        if constexpr (count<Matching, Type, TypeList...>() == 0ULL)
        {
            return npos;
        }

        return internal::find<adjust_for_matching_t<Type, Matching>, adjust_for_matching_t<TypeList, Matching>...>();
    }

    /**
     * @brief Find the first appearance of the first template parameter into the list of types which follows it.
     * @tparam Type The type to search for.
     * @tparam TypeList The list of types in which to look for Type.
     * @return The index of Type in TypeList. If no match is found, returns \a pi::type_list::npos.
     * @note Effectively calls \a find with \a matching::strict strategy.
     */
    template <typename Type, typename ...TypeList>
    [[maybe_unused]] auto constexpr find_v = find<matching::relaxed, Type, TypeList...>();
} // namespace pi::type_list
