#pragma once

#include <memory>

class Observables;

class DynamicPayoffInstance {
public:
  template <class ConcreteT>
  explicit DynamicPayoffInstance(ConcreteT&& concrete) : mAbstract(new ConcreteInstance(std::move(concrete))) {}
  void test() const { mAbstract->test(); }
  void evaluate(Observables const& observables) const { mAbstract->evaluate(observables); }
  
private:
  
  class Interface {
  public:
    virtual void test() const = 0;
    virtual void evaluate(Observables const& observables) const = 0;
    virtual ~Interface() = default;
  };

  template <class ConcreteT>
  class ConcreteInstance : public Interface {
  public:
    ConcreteInstance(ConcreteT&& concrete) : mConcrete(std::move(concrete)) {}
    void test() const override { mConcrete.test(); }
    void evaluate(Observables const& observables) const override { mConcrete.evaluate(observables); }

  private:
    ConcreteT mConcrete;
  };

  std::shared_ptr<Interface> mAbstract;

};