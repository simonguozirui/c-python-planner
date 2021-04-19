#include <Python.h>
#include <iostream>

#include "AnytimeFrenetPlanner.h"

class MyClass {
public:
    MyClass(int v) {
        this->value = v;
        this->fot = NULL;
    }
    ~MyClass() {
        std::cout << "Destroying class" << std::endl;
    }
    int get_value() {
        return this->value;
    }
    void set_value(int v) {
        this->value = v;
    }
private:
    int value;
    AnytimeFrenetPlanner *fot;
};

PyObject *MyClass_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    MyClass *self = (MyClass*) type->tp_alloc(type, 1);
   //  self->fot = NULL; // set fot = nullptr
    printf("Module: myclass new\n");
    return (PyObject *) self;
}

// need to modify it to work with initial conditions later
static int MyClass_init(PyObject *self, PyObject *args, PyObject *kwds) {
    ((MyClass *) self)->set_value(5);

    printf("Module: myclass init\n");
    return 0;
}

static void MyClass_dealloc(MyClass *self) {
    printf("Module: myclass dealloc\n");
    // delete self->fot;
    Py_TYPE(self)->tp_free(self);
}

static PyObject *MyClass_get_value(PyObject *self, PyObject *args) {
    MyClass *my_class = (MyClass *) self;
    return PyFloat_FromDouble((double) my_class->get_value());
}

/*
static PyObject *method_async_plan(PyObject *self, PyObject *args) {
    ((FotPlanner *) self)->fot->asyncPlan();
    printf("Module: Async Plan\n");
    // return self;
    return Py_None;
}

// for ease for testin for now,
// we just return a float representing the cost of it
static PyObject *method_get_path(PyObject *self, PyObject *args) {
    printf("Module: Get Path\n");
    return PyFloat_FromDouble(((FotPlanner *) self)->fot->getBestPath());
}

static PyObject *method_stop_plan(PyObject *self, PyObject *args) {
    ((FotPlanner *) self)->fot->stopPlanning();
    printf("Module: Stop Plan\n");
    return Py_None;
}
*/

static PyMethodDef MyClass_methods[] = {
    {"get_value", MyClass_get_value, METH_VARARGS, "Get value"},
        /*
    {"async_plan", method_async_plan, METH_VARARGS, "Start Async Planning"}, 
    {"get_path", method_get_path, METH_VARARGS, "Get Best Path"},
    {"stop_plan", method_stop_plan, METH_VARARGS, "Stop Planning, Shut Down all Workers"},
    */
    {NULL, NULL, 0, NULL},
};


PyTypeObject MyClassType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "my_package.MyClass",
    .tp_basicsize = sizeof(MyClass),
    .tp_dealloc = (destructor)MyClass_dealloc,
    // .tp_repr = (reprfunc)FotPlanner_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT |
    Py_TPFLAGS_BASETYPE,
    .tp_doc = "my_class.MyClass objects",
    .tp_methods = MyClass_methods,
    // .tp_members = FotPlanner_members,
    // .tp_as_mapping
    .tp_init = (initproc)MyClass_init,
    .tp_new = MyClass_new
};


static struct PyModuleDef fot_planner_module = {
    PyModuleDef_HEAD_INIT,
    "my_package",
    "My package with a C++ class",
    -1,
    //FotPlanner_methods
};

/* Initialize the fot_planner module */
PyMODINIT_FUNC PyInit_my_package(void) {
    PyObject* m;

     if (PyType_Ready(&MyClassType) < 0)
        return NULL;
        
    m = PyModule_Create(&fot_planner_module);
    if (m == NULL)
        return NULL;
    // do we need reference count?
    // Py_INCREF(&FotPlannerType);

    PyModule_AddObject(m, "MyClass", (PyObject *)&MyClassType);
    printf("my package imported!\n");
    fflush(stdout);
    return m;
}
