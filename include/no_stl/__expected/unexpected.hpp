#pragma once

#include <type_traits>
#include <utility>

namespace no_stl
{

namespace detail
{

template <typename T>
struct is_unexpected;

template <typename E>
concept unexpected_eligible =
  (!std::is_array_v<E>) && std::is_object_v<E> && (!detail::is_unexpected<E>::value) &&
  std::is_same_v<E, std::remove_cv_t<E>>;

}  // namespace detail

template <typename E>
  requires detail::unexpected_eligible<E>
class unexpected
{
  E val_;

public:
  // constructors
  template <typename Err = E>
  constexpr explicit unexpected(Err && e)
    requires(!std::is_same_v<std::remove_cvref_t<Err>, unexpected>) &&
            (!std::is_same_v<std::remove_cvref_t<Err>, std::in_place_t>) &&
            std::is_constructible_v<E, Err>
  : val_(std::forward<Err>(e))
  {
  }
  template <typename... Args>
  constexpr explicit unexpected(std::in_place_t, Args &&... args)
    requires std::is_constructible_v<E, Args...>
  : val_(std::forward<Args>(args)...)
  {
  }
  template <typename U, typename... Args>
  constexpr explicit unexpected(std::in_place_t, std::initializer_list<U> ilist, Args &&... args)
    requires std::is_constructible_v<E, std::initializer_list<U>, Args...>
  : val_(ilist, std::forward<Args>(args)...)
  {
  }

  // observers
  constexpr const E & error() const & noexcept { return val_; }
  constexpr E & error() & noexcept { return val_; }
  constexpr const E && error() const && noexcept = delete;
  constexpr E && error() && noexcept { return std::move(val_); }

  // swap
  constexpr void swap(unexpected & other) noexcept(std::is_nothrow_swappable_v<E>)
    requires std::is_swappable_v<E>
  {
    std::swap(val_, other.val_);
  }

  // non-member functions
  template <typename Err>
  friend constexpr bool operator==(unexpected & x, unexpected<Err> & y)
  {
    return x.error() == y.error();
  }

  friend constexpr void swap(unexpected & x, unexpected & y) noexcept(noexcept(x.swap(y)))
    requires std::is_swappable_v<E>
  {
    x.swap(y);
  }
};

// deduction guide
template <typename E>
unexpected(E) -> unexpected<E>;

namespace detail
{

template <typename T>
struct is_unexpected : std::false_type
{
};
template <typename E>
struct is_unexpected<unexpected<E>> : std::true_type
{
};
template <typename T>
inline constexpr bool is_unexpected_v = is_unexpected<T>::value;

};  // namespace detail

}  // namespace no_stl
