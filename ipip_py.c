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

#include "ipip.h"

static PyObject *IpIpErr;

static PyObject *
api_init(PyObject *self, PyObject *args)
{
    char* str = NULL;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        return NULL;
    }

    if (init(str) < 0)
    {
        PyErr_SetString(IpIpErr, "Init failed");
    }
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
    int res;
    if (!PyArg_ParseTuple(args, "s", &ip)) {
        Py_RETURN_NONE;
    }

    res = find(ip, &addr, &addr_n);
    if (res < 0)
    {
        if (-1 == res)
            PyErr_SetString(IpIpErr, "Ip Format Error");

        if (-2 == res)
            PyErr_SetString(IpIpErr, "Not Init");

        Py_RETURN_NONE;
    }
    return Py_BuildValue("s#", addr, addr_n);

}

static PyMethodDef methods[] = {
    {"init",    api_init,    METH_VARARGS, NULL},
    {"destroy", api_destroy},
    {"find",    api_find,    METH_VARARGS, NULL},
    {NULL, NULL}
};

PyMODINIT_FUNC
initipip(void)
{
    PyObject *m;
    m = Py_InitModule("ipip", methods);
    if (m == NULL)
        return;

    IpIpErr = PyErr_NewException("ipip.error", NULL, NULL);
    Py_INCREF(IpIpErr);
    PyModule_AddObject(m, "error", IpIpErr);
}

