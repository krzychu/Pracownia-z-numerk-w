#include <boost/python.hpp>

const char * hello(){
  return "hello\n";
}

BOOST_PYTHON_MODULE(test){
  using namespace boost::python;
  def("hello", hello);
}
