#ifndef XUL_STATIC_PIMPL_HPP
#define XUL_STATIC_PIMPL_HPP
/// @file
/// @copyright Copyright Tim Pavlic 2019
/// Distributed under the Boost Software License, Version 1.0.
/// See http://www.boost.org/LICENSE_1_0.txt

#include <new>

namespace xul {

template <typename Private, std::size_t Size, std::size_t Alignment>
class StaticPimpl
{
public:
  template <typename Klass = Private, typename... Args>
  StaticPimpl(Args&&... args)
  {
    static_assert(alignof(Private) == Alignment, "Supplied raw alignment of 'Private' class does not match actual alignof()");
    static_assert(sizeof(Private) == Size, "Supplied raw size of 'Private' class does not match actual sizeof()");

    new(data_) Klass(std::forward<Args>(args)...);
  }

  ~StaticPimpl()
  {
    std::launder(reinterpret_cast<Private*>(data_))->~Private();
  }

  const Private* operator-> () const {
    return std::launder(reinterpret_cast<const Private*>(data_));
  }

  Private* operator-> () {
    return std::launder(reinterpret_cast<Private*>(data_));
  }

private:
  alignas(Alignment) unsigned char data_[Size];
};

} // namespace xul

#endif
