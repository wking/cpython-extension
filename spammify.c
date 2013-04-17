#include <Python.h>
#include <stdlib.h>

static PyObject *
spam_busy(PyObject *self, PyObject *args)
{
	long int count, i;

	if (!PyArg_ParseTuple(args, "l", &count))
		return NULL;
	Py_BEGIN_ALLOW_THREADS
	for (i = 0; i < count; i++)
		;
	Py_END_ALLOW_THREADS
	return PyLong_FromLong(i);
}

static PyMethodDef SpamMethods[] = {
	{"busy",  spam_busy, METH_VARARGS,
	 "Drop the GIL and run a busy wait until you count to `count`."},
	{NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef spammodule = {
	PyModuleDef_HEAD_INIT,
	"spam",   /* name of module */
	NULL,     /* module documentation, may be NULL */
	0,        /* size of per-interpreter state of the module */
	SpamMethods
};

PyMODINIT_FUNC
PyInit_spam(void)
{
	return PyModule_Create(&spammodule);
}
