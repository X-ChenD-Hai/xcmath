#ifndef XCMATH_TYPES_HPP
#define XCMATH_TYPES_HPP
#include <type_traits>
#include <utility>
namespace xcmath {

template <typename T>
concept TVector = requires(class _T) {
    { T::size } -> std::convertible_to<size_t>;
    { T::template has<_T> } -> std::convertible_to<bool>;
};

template <typename... Ts>
struct tvector {
    template <typename T>
    static constexpr bool has = false || (std::is_same_v<T, Ts> || ...);
    static constexpr size_t size = sizeof...(Ts);
    template <size_t I>
    using at = std::tuple_element_t<I, std::tuple<Ts...>>;
    template <typename... T>
    using push_back = tvector<Ts..., T...>;
    template <typename... T>
    using push_front = tvector<T..., Ts...>;
    using pop_front =
        std::remove_pointer<decltype([]<size_t... I>(
                                         std::index_sequence<I...>) {
            return (tvector<at<I + 1>...> *)nullptr;
        }(std::make_index_sequence<size - 1>{}))>::type;
    using pop_back =
        std::remove_pointer<decltype([]<size_t... I>(
                                         std::index_sequence<I...>) {
            return (tvector<at<I>...> *)nullptr;
        }(std::make_index_sequence<size - 1>{}))>::type;
    template <TVector T>
    using concat = std::remove_pointer<decltype([]<size_t... I>(
                                                    std::index_sequence<I...>) {
        return (tvector<Ts..., typename T::template at<I>...> *)nullptr;
    }(std::make_index_sequence<T::size>{}))>::type;

   private:
    template <typename... T>
    struct remove_all_helper {
        using Type = std::remove_pointer<decltype([]<class _T, class... _Ts>() {
            if constexpr (sizeof...(_Ts) == 0) {
                if constexpr (tvector<T...>::template has<_T>) {
                    return (tvector<> *)nullptr;
                } else {
                    return (tvector<_T> *)nullptr;
                }
            } else {
                if constexpr (tvector<T...>::template has<_T>) {
                    return (typename tvector<_Ts...>::template remove_all<T...>
                                *)nullptr;
                } else {
                    return (typename tvector<_Ts...>::template remove_all<
                            T...>::template push_front<_T> *)nullptr;
                }
            }
        }.template operator()<Ts...>())>::type;
    };
    template <>
    struct remove_all_helper<> {
        using Type = tvector<Ts...>;
    };

   public:
    template <size_t T>
        requires(T < size)
    using remove = std::remove_pointer<
        decltype([]<size_t... I, size_t... J>(std::index_sequence<I...>,
                                              std::index_sequence<J...>) {
            return (tvector<at<I>..., at<J + T + 1>...> *)nullptr;
        }(std::make_index_sequence<T>{},
                 std::make_index_sequence<size - T - 1>{}))>::type;
    template <typename... T>
    using remove_all = typename remove_all_helper<T...>::Type;
    template <TVector T>
    using remove_all_from_list =
        std::remove_pointer<decltype([]<class... _Rt>(tvector<_Rt...> *) {
            return (remove_all<_Rt...> *)nullptr;
        }((T *)nullptr))>::type;
    template <class T>
    static constexpr size_t find =
        []<size_t I, class _T, class... _Ts>(this auto &&self) {
            if constexpr (std::is_same_v<T, _T>) {
                return I;
            }
            if constexpr (sizeof...(_Ts) == 0) {
                return I + 1;
            } else {
                return self.template operator()<I + 1, _Ts...>();
            }
        }.template operator()<0, Ts...>();
    template <size_t... T>
    using subsequence = tvector<at<T>...>;
    template <size_t Start, size_t End>
    using slice = std::remove_pointer<decltype([]<size_t... I>(
                                                   std::index_sequence<I...>) {
        return (tvector<at<Start + I>...> *)nullptr;
    }(std::make_index_sequence<End - Start>{}))>::type;
};
template <>
struct tvector<> {
    static constexpr size_t size = 0;
    template <typename T>
    static constexpr bool has = false;
    template <typename... T>
    using push_back = tvector<T...>;
    template <typename... T>
    using push_front = tvector<T...>;
    template <TVector T>
    using concat = T;
    template <size_t... T>
        requires(sizeof...(T) == 0)
    using remove = tvector<>;
    template <size_t... T>
        requires(sizeof...(T) == 0)
    using remove_all = tvector<>;
    template <TVector T>
    using remove_all_from_list = tvector<>;
};

}  // namespace xcmath

#endif  // XCMATH_TYPES_HPP