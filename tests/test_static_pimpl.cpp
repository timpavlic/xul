#include "test_static_pimpl.hpp"
#include <cstdio>

struct OnlyLookNoTouch::Private {
  Private() {
    printf("Private constructing\n");
  }
  ~Private() {
    printf("Private destructing\n");
  }
  Compound c;
  int i;
  double d;
};

OnlyLookNoTouch::OnlyLookNoTouch() {}
OnlyLookNoTouch::~OnlyLookNoTouch() = default;

auto OnlyLookNoTouch::set(Compound c) -> void { pimpl_->c = c; }
auto OnlyLookNoTouch::set(int i) -> void { pimpl_->i = i; }
auto OnlyLookNoTouch::set(double d) -> void { pimpl_->d = d; }
auto OnlyLookNoTouch::getCompound() const -> Compound { return pimpl_->c; }
auto OnlyLookNoTouch::getInt() const -> int{ return pimpl_->i; }
auto OnlyLookNoTouch::getDouble() const -> double { return pimpl_->d; }

int main()
{
  OnlyLookNoTouch olnt;
  olnt.set(7);
  olnt.set(3.14);
  olnt.set(OnlyLookNoTouch::Compound{1.618, 45l});

  printf("     int: %i\n", olnt.getInt());
  printf("  double: %g\n", olnt.getDouble());
  printf("compound: {%g, %ld}\n", olnt.getCompound().d, olnt.getCompound().l);
}
