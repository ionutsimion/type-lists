#pragma once

#include "type-lists.hxx"

namespace pi::arguments
{
    template <int index, typename FirstArgument, typename ...RestOfArguments>
    auto constexpr get(FirstArgument &&first_argument, RestOfArguments &&...rest_of_arguments)
    {
        if constexpr (index == 0)
            return std::forward<FirstArgument>(first_argument);
        else
            return get<index - 1, RestOfArguments...>(rest_of_arguments...);
    }

    template <typename TypeToFind, typename ...Arguments>
    auto constexpr default_or_argument(TypeToFind &&default_value, Arguments &&...arguments) noexcept
    {
        static_assert(sizeof...(Arguments) > 0, "At least one argument must be provided");

        if constexpr (auto constexpr index = pi::type_lists::find<TypeToFind, Arguments...>(); index == -1)
            return std::forward<TypeToFind>(default_value);
        else
            return get<index>(std::forward<Arguments>(arguments)...);
    }

    using pi::type_lists::search_policy, pi::type_lists::search_policy_t;

    template <search_policy SearchPolicy, typename TypeToFind, typename ...Arguments>
    auto constexpr default_or_argument(TypeToFind &&default_value, Arguments &&...arguments) noexcept
    {
        static_assert(sizeof...(Arguments) > 0, "At least one argument must be provided");

        if constexpr (auto constexpr index = pi::type_lists::find<SearchPolicy, TypeToFind, Arguments...>(); index == -1)
            return std::forward<TypeToFind>(default_value);
        else
            return get<index>(std::forward<Arguments>(arguments)...);
    }
}
