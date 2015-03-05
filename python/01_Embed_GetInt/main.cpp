#include <boost/python.hpp>
#include <QDebug>

namespace bp = boost::python;

int main()
{
    // start interpreter
    Py_Initialize();

    // get main
    bp::object main_module = bp::import("__main__");
    bp::object main_namespace = main_module.attr("__dict__");

    // get namespace
    bp::dict g_namespace;
    bp::dict l_namespace;
    g_namespace["__builtins__"] = main_namespace["__builtins__"];
    l_namespace['y'] = 1;

    // run script
    try
    {
        bp::exec_file("main.py", g_namespace, l_namespace);
    }
    catch (std::invalid_argument)
    {
        qFatal("missing file: main.py");
    }
    catch (bp::error_already_set const &)
    {
        if (PyErr_ExceptionMatches(PyExc_NameError))
        {
            qFatal("NameError");
        }
        else
        {
            PyErr_Print();
            qFatal("PythonFailure");
        }
    }

    // extract result
    try
    {
        int x = bp::extract<double>(l_namespace["x"]);
        qDebug() << x;
    }
    catch (bp::error_already_set const &)
    {
        if (PyErr_ExceptionMatches(PyExc_KeyError))
        {
            qFatal("KeyError");
        }
        if (PyErr_ExceptionMatches(PyExc_TypeError))
        {
            qFatal("TypeError");
        }
        else
        {
            PyErr_Print();
            qFatal("PythonFailure");
        }
    }

    // clear namespace
    g_namespace.clear();
    l_namespace.clear();
    g_namespace["__builtins__"] = main_namespace["__builtins__"];

    return 0;
}
