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
        PyErr_Print();
        qFatal("PythonFailure");
    }

    // extract result
    try
    {
        bp::object L = l_namespace["L"];

        // make sure it is a list
        if (PyObject_IsInstance(L.ptr(), (PyObject*)&PyList_Type)) {

            // get the size
            int size = bp::len(L);
            qDebug("len(L) = %d", size);

            // extract the items
            for (int i = 0; i < size; i++)
            {
                int j = bp::extract<int>(L[i]);
                qDebug("L[%d]   = %d", i, j);
            }
        }
    }
    catch (bp::error_already_set const &)
    {
        PyErr_Print();
        qFatal("PythonFailure");
    }

    // clear namespace
    g_namespace.clear();
    l_namespace.clear();
    g_namespace["__builtins__"] = main_namespace["__builtins__"];

    return 0;
}
