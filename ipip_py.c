/**
 *   author       :   丁雪峰
 *   time         :   2016-05-18 07:13:04
 *   email        :   fengidri@yeah.net
 *   version      :   1.0.1
 *   description  :
 */
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <Python.h>


static PyObject *
api_init(PyObject *self, PyObject *args)
{
    char* str = NULL;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        return NULL;
    }

    init(str);
    Py_RETURN_NONE;
}

static PyObject *
api_destroy(PyObject *self)
{
    destroy();
    Py_RETURN_NONE;
}

static PyObject *
api_find(PyObject *self,  PyObject *args)
{
    char *ip;
    char *addr;
    size_t addr_n;
    if (!PyArg_ParseTuple(args, "s", &ip)) {
        Py_RETURN_NONE;
    }

    if (find(ip, &addr, &addr_n))
        return Py_BuildValue("s#", addr, addr_n);
    Py_RETURN_NONE;

}

static PyMethodDef methods[] = {
    {"init", api_init, METH_VARARGS, NULL},
    {"destroy", api_destroy, METH_VARARGS, NULL},
    {"find", api_find, METH_VARARGS, NULL},
    {NULL, NULL}
};

PyMODINIT_FUNC
initipip(void)
{
    Py_InitModule("ipip", methods);
}

