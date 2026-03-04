/*
** EPITECH PROJECT, 2026
** COMPONENT4008
** File description:
** nanotekspice
*/

#ifndef COMPONENT4008
  #define COMPONENT4008
  #include "AComponent.hpp"
  #include "Gates.hpp"
  #include "IComponent.hpp"
  #include <memory>
  #include <vector>

namespace nts {
class C4008: public AComponent {
public:
  C4008() = default;
  ~C4008() override = default;

  void simulate(std::size_t tick) override { _currentTick = tick ;}

  Tristate compute(std::size_t pin) override {
    switch (pin) {
      case 3:
        return sumBit(0);
      case 6:
        return sumBit(1);
      case 12:
        return sumBit(2);
      case 9:
        return sumBit(3);
      case 8:
        return carryOut();
      default:
        return Undefined;
    }
  }

private:
  std::vector<std::unique_ptr<IComponent>> _subGates;

  static Tristate xor3(Tristate a, Tristate b, Tristate c) {
    return Operators::ntsXor(Operators::ntsXor(a, b), c);
  }

  static Tristate carry(Tristate a, Tristate b, Tristate cin) {
    Tristate axb = Operators::ntsXor(a, b);
    return Operators::ntsOr(Operators::ntsAnd(a, b), Operators::ntsAnd(cin, axb));
  }

  Tristate getA(int i) { return getPinValue(aPins[i]); }
  Tristate getB(int i) { return getPinValue(bPins[i]); }
  Tristate getC(){ return getPinValue(15); }

  Tristate sumBit(int i) {
    Tristate c = getC();
    for (int k = 0; k < i; ++k)
      c = carry(getA(k), getB(k), c);
    return xor3(getA(i), getB(i), c);
  }

  Tristate carryOut() {
    Tristate c = getC();
    for (int i = 0; i < 4; ++i)
      c = carry(getA(i), getB(i), c);
    return c;
  }

  static constexpr std::size_t aPins[4] = {1, 4, 14, 11};
  static constexpr std::size_t bPins[4] = {2, 5, 13, 10};
};
}

#endif
