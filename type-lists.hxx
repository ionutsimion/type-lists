//
// Created by ionut on 25.09.2021.
//

#ifndef TYPE_LISTS_TYPE_LISTS_HXX
#define TYPE_LISTS_TYPE_LISTS_HXX

namespace pi::type_list
{
    template <typename T>
    using remove_cv_ref_t = std::remove_cv_t<std::remove_reference_t<T>>;
    /**
     * @brief Count the number of appearances of the first template parameter into the list of types which follows it.
     * @tparam TypeToCount The type for which we want to count the number of appearances in the rest of the types.
     * @tparam FirstTypeInTheTypeList The first type of the type list in which we search for appearances of TypeToCount.
     * @tparam RestOfTheTypeList The rest of the list of types in which we look to count the number of appearances of TypeToCount.
     */
    template <typename TypeToCount, typename FirstTypeInTheTypeList, typename ...RestOfTheTypeList>
    auto constexpr count()
    {
        if constexpr (sizeof...(RestOfTheTypeList) == 0)
            return std::is_same_v<TypeToCount, FirstTypeInTheTypeList>;
        else
            return std::is_same_v<TypeToCount, FirstTypeInTheTypeList>
                 + count<TypeToCount, RestOfTheTypeList...>();
    }

    /**
     * @brief Search policies are used for counting or finding types in type lists.
     * @enum exact Matches the types if they have exactly the same modifiers (including none) and are the same type of pointers or references (including none).
     * @enum ignore_list_cv Matches the types only if the type to search for is identical to one from the list without const or volatile modifiers.
     * @enum ignore_list_ref Matches the types only of the type to search for is identical to one from the list without references.
     * @enum ignore_list_cv_ref Matches the type only if the type to search for is identical to one from the list without references or volatile modifiers.
     * @enum ignore_all_cv Matches the types only if the type to search for is identical to one from the list, all without const or volatile modifiers.
     * @enum ignore_all_ref Matches the types only of the type to search for is identical to one from the list, all without references.
     * @enum ignore_all_cv_ref Matches the type only if the type to search for is identical to one from the list, all without references or volatile modifiers.
     */
    enum class search_policy
    {
        exact
      , ignore_list_cv
      , ignore_list_ref
      , ignore_list_cv_ref
      , ignore_all_cv
      , ignore_all_ref
      , ignore_all_cv_ref
    };

    template <search_policy CountPolicy, typename TypeToCount, typename FirstTypeInTheTypeList, typename ...RestOfTheTypeList>
    struct count_policy_t
    {
        static auto constexpr count()
        {
            if constexpr (CountPolicy == search_policy::ignore_list_cv)
            {
                if constexpr (sizeof...(RestOfTheTypeList) == 0)
                    return std::is_same_v<TypeToCount, FirstTypeInTheTypeList> || std::is_same_v<TypeToCount, std::remove_cv_t<FirstTypeInTheTypeList>>;
                else
                    return (std::is_same_v<TypeToCount, FirstTypeInTheTypeList> || std::is_same_v<TypeToCount, std::remove_cv_t<FirstTypeInTheTypeList>>)
                         + count_policy_t<CountPolicy, TypeToCount, RestOfTheTypeList...>::count();
            }
            else if constexpr (CountPolicy == search_policy::ignore_list_ref)
            {
                if constexpr (sizeof...(RestOfTheTypeList) == 0)
                    return std::is_same_v<TypeToCount, FirstTypeInTheTypeList> || std::is_same_v<TypeToCount, std::remove_reference_t<FirstTypeInTheTypeList>>;
                else
                    return (std::is_same_v<TypeToCount, FirstTypeInTheTypeList> || std::is_same_v<TypeToCount, std::remove_reference_t<FirstTypeInTheTypeList>>)
                         + count_policy_t<CountPolicy, TypeToCount, RestOfTheTypeList...>::count();
            }
            else if constexpr (CountPolicy == search_policy::ignore_list_cv_ref)
            {
                if constexpr (sizeof...(RestOfTheTypeList) == 0)
                    return std::is_same_v<TypeToCount, FirstTypeInTheTypeList> || std::is_same_v<TypeToCount, remove_cv_ref_t<FirstTypeInTheTypeList>>;
                else
                    return (std::is_same_v<TypeToCount, FirstTypeInTheTypeList> || std::is_same_v<TypeToCount, remove_cv_ref_t<FirstTypeInTheTypeList>>)
                         + count_policy_t<CountPolicy, TypeToCount, RestOfTheTypeList...>::count();
            }
            else if constexpr (CountPolicy == search_policy::ignore_all_cv)
                return pi::type_list::count<std::remove_cv_t<TypeToCount>, std::remove_cv_t<FirstTypeInTheTypeList>, std::remove_cv_t<RestOfTheTypeList>...>();
            else if constexpr (CountPolicy == search_policy::ignore_all_ref)
                return pi::type_list::count<std::remove_reference_t<TypeToCount>, std::remove_reference_t<FirstTypeInTheTypeList>, std::remove_reference_t<RestOfTheTypeList>...>();
            else if constexpr (CountPolicy == search_policy::ignore_all_cv_ref)
                return pi::type_list::count<remove_cv_ref_t<TypeToCount>, remove_cv_ref_t<FirstTypeInTheTypeList>, remove_cv_ref_t<RestOfTheTypeList>...>();

            return pi::type_list::count<TypeToCount, FirstTypeInTheTypeList, RestOfTheTypeList...>();
        }
    };

    /**
     * @brief Count the number of appearances of the first template parameter into the list of types which follows it.
     * @tparam CountPolicy The counting policy (search for exactly the same type or ignore const and volatile, reference or all three on types from the list.
     * @tparam TypeToCount The type for which we want to count the number of appearances in the rest of the types.
     * @tparam FirstTypeInTheTypeList The first type of the type list in which we search for appearances of TypeToCount.
     * @tparam RestOfTheTypeList The rest of the list of types in which we look to count the number of appearances of TypeToCount.
     */
    template <search_policy CountPolicy, typename TypeToCount, typename FirstTypeInTheTypeList, typename ...RestOfTheTypeList>
    auto constexpr count()
    {
        return pi::type_list::count_policy_t<CountPolicy, TypeToCount, FirstTypeInTheTypeList, RestOfTheTypeList...>::count();
    }
}

#endif //TYPE_LISTS_TYPE_LISTS_HXX
