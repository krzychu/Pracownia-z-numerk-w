#include <boost/python.hpp>

const char * hello(){
  return "hello\n";
}

class Foo{
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

  private:
    int m_counter;
};


BOOST_PYTHON_MODULE(test){
  using namespace boost::python;
  def("hello", hello);
  class_<Foo>("Foo", init<int>())
    .def("get", &Foo::get)
    .def("inc", &Foo::inc);

}
