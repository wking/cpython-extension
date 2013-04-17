#include <Python.h>
#include <stdlib.h>
#include <time.h>

static PyObject *
spam_busy(PyObject *self, PyObject *args)
{
	int seconds;
	time_t start;
	long int i = 0;

	if (!PyArg_ParseTuple(args, "i", &seconds))
		return NULL;
	Py_BEGIN_ALLOW_THREADS
	start = time(NULL);
	while (time(NULL) < start + seconds)
		i++;
	Py_END_ALLOW_THREADS
	return PyLong_FromLong(i);
}

static PyMethodDef SpamMethods[] = {
	{"busy",  spam_busy, METH_VARARGS,
	 "Drop the GIL and run a busy wait for a few seconds."},
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
