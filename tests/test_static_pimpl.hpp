#ifndef XUL_TEST_STATIC_PIMPL_HPP
#define XUL_TEST_STATIC_PIMPL_HPP

#include "../xul/static_pimpl.hpp"

struct OnlyLookNoTouch
{
  OnlyLookNoTouch();
  ~OnlyLookNoTouch();

  struct Compound {
    double d;
    long l;
  };

  void set(int);
  void set(double);
  void set(Compound);

  int getInt() const;
  double getDouble() const;
  Compound getCompound() const;

private:
  struct Private;
  xul::StaticPimpl<Private, 32, alignof(double)> pimpl_;
};

#endif
