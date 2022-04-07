#pragma once

#include "type-lists.hxx"

namespace pi::arguments
{
    namespace internal
    {
        template <int Index, typename FirstArgument, typename ...RestOfArguments>
        auto constexpr get(FirstArgument &&first_argument, RestOfArguments &&...rest_of_arguments)
        {
            if constexpr (Index > 0)
            {
                return get<Index - 1>(std::forward<RestOfArguments>(rest_of_arguments)...);
            }

            return std::forward<FirstArgument>(first_argument);
        }
    } // namespace internal

    /**
     * @brief Returns either the first argument matching the type of \a default_value, or the default_value.
     * @tparam Matching The searching policy (search for exactly the same type or ignore const, reference or const and reference on types from the list.
     * @tparam Type The type to search for.
     * @tparam ArgumentTypes The list of types in which to look for Type.
     * @param default_value The fall-back value in case not argument of the same type is found.
     * @param arguments A list of arguments of any type and number.
     * @return The \a default_value or the argument of the same type as the default.
     */
    template <type_lists::matching Matching, typename Type, typename ...ArgumentTypes>
    auto constexpr default_or_argument(Type &&default_value, ArgumentTypes &&...arguments) noexcept
    {
        if constexpr (auto constexpr index = type_lists::find<Matching, Type, ArgumentTypes...>(); index != type_lists::npos)
        {
            return internal::get<index>(std::forward<ArgumentTypes>(arguments)...);
        }

        return std::forward<Type>(default_value);
    }

    /**
     * @brief Returns either the first argument matching the type of \a default_value, or the default_value.
     * @tparam Type The type to search for.
     * @tparam ArgumentTypes The list of types in which to look for Type.
     * @param default_value The fall-back value in case not argument of the same type is found.
     * @param arguments A list of arguments of any type and number.
     * @return The \a default_value or the argument of the same type as the default.
     * @note Effectively calls \a default_or_argument with \a matching::strict strategy.
     */
    template <typename Type, typename ...ArgumentTypes>
    auto constexpr default_or_argument(Type &&default_value, ArgumentTypes &&...arguments) noexcept
    {
        return default_or_argument<type_lists::matching::relaxed>(std::forward<Type>(default_value), std::forward<ArgumentTypes>(arguments)...);
    }
} // namespace pi::arguments
