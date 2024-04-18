#pragma once

#include <memory>

class DynamicPayoffInstance {
public:
  template <class ConcreteT>
  explicit DynamicPayoffInstance(ConcreteT&& concrete) : mAbstract(new ConcreteInstance(std::move(concrete))) {}
  void test() const { mAbstract->test(); }
  
private:
  
  class Interface {
  public:
    virtual void test() const = 0;
    virtual ~Interface() = default;
  };

  template <class ConcreteT>
  class ConcreteInstance : public Interface {
  public:
    ConcreteInstance(ConcreteT&& concrete) : mConcrete(std::move(concrete)) {}
    void test() const override { mConcrete.test(); }

  private:
    ConcreteT mConcrete;
  };

  std::shared_ptr<Interface> mAbstract;

};