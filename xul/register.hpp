#ifndef XUL_REGISTER_HPP
#define XUL_REGISTER_HPP
/// @file
/// @copyright Copyright Tim Pavlic 2019
/// Distributed under the Boost Software License, Version 1.0.
/// See http://www.boost.org/LICENSE_1_0.txt

namespace xul {

/// Provides an encapsulation around a pointer to memory that is a register,
/// typically at a known memory address on a microcontroller, or mmap'd into
/// user space.
template <typename T, typename Derived>
class Register
{
  class Value;
  class Bit;
public:


  Register& operator|=(Value val) {
    *reg_ |= val.get();
    return *this;
  }

  Register& operator&=(Value val) {
    *reg_ &= val.get();
    return *this;
  }

  Register& operator=(Value val) {
    *reg_ = val.get();
    return *this;
  }

  operator Value() { return *reg_; }


private:
  /// The CRTP _Derived_ type is a friend, allowing it, and only it, to define
  /// constant `Bit`s.
  friend Derived;

  class Bit
  {
  public:
    /// Templated, named constructor for Bit, which allows the bit to be static
    /// asserted for validity.
    template <int BitNo>
    static constexpr Bit at() {
      static_assert(BitNo < sizeof(T)*8, "Bit position is outside of valid range for the register's data type");
      static_assert(BitNo >=0, "Bit position must be positive");
      return Bit{BitNo};
    }

    /// Get this bit's position
    constexpr int pos() const { return pos_; }

    /// Or this bit with another, resulting in a value assignable to a register.
    constexpr Value operator|(Bit bit) const { return Value{*this} | bit; }

    /// Convert this bit into a value, by negating its shifted into position value.
    constexpr Value operator~() const { return ~Value{*this}; }

  private:
    constexpr Bit(int pos) : pos_{pos} {}
    int pos_;
  };


  /// Represents the value a register holds, or can be assigned.
  class Value
  {
  public:
    /// Create a Value from a single bit, by setting the bit in the value, at
    /// the bit's that bit to 1.
    Value(Bit b) : val_{static_cast<T>(1 << b.pos())} {}


    /// Get the underlying data of the register value.
    constexpr T get() const { return val_; }
    constexpr Value operator|=(Value other) { return val_ | other.val_; }
    constexpr Value operator|(Value other) { return val_| other.val_; }
    constexpr Value operator&=(Value other) { return val_ | other.val_; }
    constexpr Value operator~() { return ~val_; }
    explicit constexpr operator bool() const { return val_ != 0; }

  private:
    friend class Bit;
    friend class Register;

    // Create a register value representation from a raw value of the register
    // data type (_T_). This is used by the friend Register class, and when
    // performing Value bit wise operations.
    constexpr Value(T val) : val_{val} {}
    T val_;
  };

  /// Create a register encapsualtion for the register at the supplied pointer.
  Register(volatile T* reg) : reg_{reg} {}

  volatile T* reg_;
};

}

#endif
