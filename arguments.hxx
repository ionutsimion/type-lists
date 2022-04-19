#pragma once

#include "type-lists.hxx"

namespace pi::arguments
{
    namespace internal
    {
        template <int Index, typename Head, typename ...Tail>
        [[nodiscard]] auto constexpr get([[maybe_unused]] Head &&first_argument, [[maybe_unused]] Tail &&...rest_of_arguments)
        {
            if constexpr (Index > 0)
            {
                return get<Index - 1>(std::forward<Tail>(rest_of_arguments)...);
            }

            return std::forward<Head>(first_argument);
        }
    } // namespace internal

    /**
     * Either get the @a Nth argument of type @a Type or the desired @a default_value, using a matching strategy.
     * @tparam Matching The matching strategy (see @a type_list::matching).
     * @tparam Nth 1-based index of the argument of type @a Type.
     * @tparam Type Type of the @a default_value and the desired argument.
     * @tparam TypeList List of argument types.
     * @param default_value Value to return in case there is no @a Nth argument.
     * @param arguments List of arguments
     * @return The @Nth argument of type @a Type or @a default_value
     */
    template <type_lists::matching Matching, size_t Nth, typename Type, typename ...TypeList>
    [[nodiscard]] auto constexpr default_or_nth_argument([[maybe_unused]] Type &&default_value, [[maybe_unused]] TypeList &&...arguments) noexcept
    {
        if constexpr (auto constexpr index = type_lists::find_nth<Matching, Type, Nth, TypeList...>(); index != type_lists::npos)
        {
            return internal::get<index>(std::forward<TypeList>(arguments)...);
        }

        return std::forward<Type>(default_value);
    }

    /**
     * Either get the @a Nth argument of type @a Type or the desired @a default_value.
     * @tparam Nth 1-based index of the argument of type @a Type.
     * @tparam Type Type of the @a default_value and the desired argument.
     * @tparam TypeList List of argument types.
     * @param default_value Value to return in case there is no @a Nth argument.
     * @param arguments List of arguments
     * @return The @Nth argument of type @a Type or @a default_value
     * @note Calls @a default_or_nth_argument with relaxed @a type_list::matching strategy
     */
    template <size_t Nth, typename Type, typename ...TypeList>
    [[nodiscard]] auto constexpr default_or_nth_argument(Type &&default_value, TypeList &&...arguments) noexcept
    {
        return default_or_nth_argument<type_lists::matching::relaxed, Nth, Type, TypeList...>(
            std::forward<Type>(default_value)
          , std::forward<TypeList>(arguments)...);
    }

    /**
     * @brief Returns either the first argument matching the type of @a default_value, or the default_value.
     * @tparam Matching The matching strategy (see @a type_list::matching).
     * @tparam Type The type to search for.
     * @tparam TypeList The list of types in which to look for Type.
     * @param default_value The fall-back value in case not argument of the same type is found.
     * @param arguments A list of arguments of any type and number.
     * @return The @a default_value or the argument of the same type as the default.
     */
    template <type_lists::matching Matching, typename Type, typename ...TypeList>
    [[nodiscard]] auto constexpr default_or_argument(Type &&default_value, TypeList &&...arguments) noexcept
    {
        return default_or_nth_argument<Matching, 1ULL, Type, TypeList...>(
            std::forward<Type>(default_value)
          , std::forward<TypeList>(arguments)...);
    }

    /**
     * @brief Returns either the first argument matching the type of @a default_value, or the default_value.
     * @tparam Type The type to search for.
     * @tparam TypeList The list of types in which to look for Type.
     * @param default_value The fall-back value in case not argument of the same type is found.
     * @param arguments A list of arguments of any type and number.
     * @return The @a default_value or the argument of the same type as the default.
     * @note Effectively calls @a default_or_argument with @a matching::strict strategy.
     */
    template <typename Type, typename ...TypeList>
    [[nodiscard]] auto constexpr default_or_argument(Type &&default_value, TypeList &&...arguments) noexcept
    {
        return default_or_argument<type_lists::matching::relaxed>(std::forward<Type>(default_value), std::forward<TypeList>(arguments)...);
    }
} // namespace pi::arguments
