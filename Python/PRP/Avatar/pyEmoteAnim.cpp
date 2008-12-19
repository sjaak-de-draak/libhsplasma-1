#include <Python.h>
#include <PRP/Avatar/plATCAnim.h>
#include "pyATCAnim.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyEmoteAnim_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyEmoteAnim* self = (pyEmoteAnim*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plEmoteAnim();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyEmoteAnim_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyEmoteAnim_FromEmoteAnim(plEmoteAnim::Convert(cre->fThis));
}

static PyObject* pyEmoteAnim_getBodyUsage(pyEmoteAnim* self, void*) {
    return PyInt_FromLong(self->fThis->getBodyUsage());
}

static PyObject* pyEmoteAnim_getFadeIn(pyEmoteAnim* self, void*) {
    return PyFloat_FromDouble(self->fThis->getFadeIn());
}

static PyObject* pyEmoteAnim_getFadeOut(pyEmoteAnim* self, void*) {
    return PyFloat_FromDouble(self->fThis->getFadeOut());
}

static int pyEmoteAnim_setBodyUsage(pyEmoteAnim* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "bodyUsage should be an int");
        return -1;
    }
    self->fThis->setBodyUsage((plAGAnim::BodyUsage)PyInt_AsLong(value));
    return 0;
}

static int pyEmoteAnim_setFadeIn(pyEmoteAnim* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "fadeIn should be a float");
        return -1;
    }
    self->fThis->setFadeIn(PyFloat_AsDouble(value));
    return 0;
}

static int pyEmoteAnim_setFadeOut(pyEmoteAnim* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "fadeOut should be a float");
        return -1;
    }
    self->fThis->setFadeOut(PyFloat_AsDouble(value));
    return 0;
}

static PyMethodDef pyEmoteAnim_Methods[] = {
    { "Convert", (PyCFunction)pyEmoteAnim_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plEmoteAnim" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyEmoteAnim_GetSet[] = {
    { "bodyUsage", (getter)pyEmoteAnim_getBodyUsage, (setter)pyEmoteAnim_setBodyUsage, NULL, NULL },
    { "fadeIn", (getter)pyEmoteAnim_getFadeIn, (setter)pyEmoteAnim_setFadeIn, NULL, NULL },
    { "fadeOut", (getter)pyEmoteAnim_getFadeOut, (setter)pyEmoteAnim_setFadeOut, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyEmoteAnim_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plEmoteAnim",             /* tp_name */
    sizeof(pyEmoteAnim),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plEmoteAnim wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyEmoteAnim_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pyEmoteAnim_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyEmoteAnim_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyEmoteAnim_Type() {
    pyEmoteAnim_Type.tp_base = &pyATCAnim_Type;
    if (PyType_Ready(&pyEmoteAnim_Type) < 0)
        return NULL;

    Py_INCREF(&pyEmoteAnim_Type);
    return (PyObject*)&pyEmoteAnim_Type;
}

int pyEmoteAnim_Check(PyObject* obj) {
    if (obj->ob_type == &pyEmoteAnim_Type
        || PyType_IsSubtype(obj->ob_type, &pyEmoteAnim_Type))
        return 1;
    return 0;
}

PyObject* pyEmoteAnim_FromEmoteAnim(class plEmoteAnim* anim) {
    if (anim == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyEmoteAnim* pyobj = PyObject_New(pyEmoteAnim, &pyEmoteAnim_Type);
    pyobj->fThis = anim;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}