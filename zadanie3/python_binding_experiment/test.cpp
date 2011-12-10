#include <boost/python.hpp>
#include <iostream>

using namespace boost::python;

const char * hello(){
  return "hello\n";
}


class Base{
  public:
    int getMagicNumber(){
      return 666;
    }
};


class Foo : public Base{
  public:
    Foo(int initial_value){
      m_counter = initial_value;
    }

    void inc(){
      m_counter++;
    }

    int get(){
      return m_counter;
    }

    const Foo operator+ (const Foo& other) const{
      return Foo(other.m_counter + m_counter);
    }

    tuple getPair() const{
      return make_tuple(1,"aa");
    }

  private:
    int m_counter;
};


std::ostream& operator << (std::ostream& out, Foo f){
  out << "counter value is " << f.get();
  return out;
}


BOOST_PYTHON_MODULE(test){
  using namespace boost::python;
  def("hello", hello);
  class_<Foo>("Foo", init<int>())
    .def("get", &Foo::get)
    .def("magic", &Foo::getMagicNumber)
    .def("inc", &Foo::inc)
    .def("getPair", &Foo::getPair)
    .def(self + self)
    .def(self_ns::str(self));
}
