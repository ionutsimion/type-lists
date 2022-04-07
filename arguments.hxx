#pragma once

#include "type-lists.hxx"

namespace pi::arguments
{
    template <int Index, typename FirstArgument, typename ...RestOfArguments>
    auto constexpr get(FirstArgument &&first_argument, RestOfArguments &&...rest_of_arguments)
    {
        if constexpr (Index == 0)
        {
            return std::forward<FirstArgument>(first_argument);
        }

        return get<Index - 1, RestOfArguments...>(std::forward<RestOfArguments>(rest_of_arguments)...);
    }

    using pi::type_lists::matching;

    template <matching Matching, typename TypeToFind, typename ...Arguments>
    auto constexpr default_or_argument(TypeToFind &&default_value, Arguments &&...arguments) noexcept
    {
        static_assert(sizeof...(Arguments) > 0, "At least one argument must be provided");

        if constexpr (auto constexpr index = pi::type_lists::find<Matching, TypeToFind, Arguments...>(); index == -1)
            return std::forward<TypeToFind>(default_value);
        else
            return get<index>(std::forward<Arguments>(arguments)...);
    }

    template <typename TypeToFind, typename ...Arguments>
    auto constexpr default_or_argument(TypeToFind &&default_value, Arguments &&...arguments) noexcept
    {
        return default_or_argument<matching::relaxed, TypeToFind, Arguments...>(std::forward<TypeToFind>(default_value), std::forward<Arguments>(arguments)...);
    }
}
