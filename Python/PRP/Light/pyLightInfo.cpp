/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pyLightInfo.h"

#include <PRP/Light/plLightInfo.h>
#include "PRP/Object/pyObjInterface.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"
#include "Sys/pyColor.h"
#include "Math/pyMatrix.h"

extern "C" {

PY_PLASMA_NEW_MSG(LightInfo, "plLightInfo is abstract")

PY_METHOD_NOARGS(LightInfo, clearVisRegions, "Remove all VisRegions from the light") {
    self->fThis->clearVisRegions();
    Py_RETURN_NONE;
}

PY_METHOD_VA(LightInfo, addVisRegion,
    "Params: regionKey\n"
    "Add a VisRegion to the light")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key) || !pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addVisRegion expects a plKey");
        return NULL;
    }
    self->fThis->addVisRegion(*key->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyLightInfo_getVisRegions(pyLightInfo* self, void*) {
    PyObject* list = PyList_New(self->fThis->getVisRegions().size());
    for (size_t i=0; i<self->fThis->getVisRegions().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getVisRegions()[i]));
    return list;
}

static int pyLightInfo_setVisRegions(pyLightInfo* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Vis Regions, use addVisRegion()");
    return -1;
}

static PyMethodDef pyLightInfo_Methods[] = {
    pyLightInfo_clearVisRegions_method,
    pyLightInfo_addVisRegion_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(hsColorRGBA, LightInfo, ambient, getAmbient, setAmbient)
PY_PROPERTY(hsColorRGBA, LightInfo, diffuse, getDiffuse, setDiffuse)
PY_PROPERTY(hsColorRGBA, LightInfo, specular, getSpecular, setSpecular)
PY_PROPERTY(hsMatrix44, LightInfo, lightToLocal, getLightToLocal, setLightToLocal)
PY_PROPERTY(hsMatrix44, LightInfo, localToLight, getLocalToLight, setLocalToLight)
PY_PROPERTY(hsMatrix44, LightInfo, lightToWorld, getLightToWorld, setLightToWorld)
PY_PROPERTY(hsMatrix44, LightInfo, worldToLight, getWorldToLight, setWorldToLight)
PY_PROPERTY(plKey, LightInfo, projection, getProjection, setProjection)
PY_PROPERTY(plKey, LightInfo, softVolume, getSoftVolume, setSoftVolume)
PY_PROPERTY(plKey, LightInfo, sceneNode, getSceneNode, setSceneNode)

static PyGetSetDef pyLightInfo_GetSet[] = {
    pyLightInfo_ambient_getset,
    pyLightInfo_diffuse_getset,
    pyLightInfo_specular_getset,
    pyLightInfo_lightToLocal_getset,
    pyLightInfo_localToLight_getset,
    pyLightInfo_lightToWorld_getset,
    pyLightInfo_worldToLight_getset,
    pyLightInfo_projection_getset,
    pyLightInfo_softVolume_getset,
    pyLightInfo_sceneNode_getset,
    { _pycs("visRegions"), (getter)pyLightInfo_getVisRegions,
        (setter)pyLightInfo_setVisRegions, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyLightInfo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plLightInfo",           /* tp_name */
    sizeof(pyLightInfo),                /* tp_basicsize */
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
    "plLightInfo wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLightInfo_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pyLightInfo_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLightInfo_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyLightInfo_Type() {
    pyLightInfo_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pyLightInfo_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(LightInfo, "kLPObsolete", plLightInfo::kLPObsolete);
    PY_TYPE_ADD_CONST(LightInfo, "kLPCastShadows", plLightInfo::kLPCastShadows);
    PY_TYPE_ADD_CONST(LightInfo, "kLPMovable", plLightInfo::kLPMovable);
    PY_TYPE_ADD_CONST(LightInfo, "kLPHasIncludes", plLightInfo::kLPHasIncludes);
    PY_TYPE_ADD_CONST(LightInfo, "kLPIncludesChars", plLightInfo::kLPIncludesChars);
    PY_TYPE_ADD_CONST(LightInfo, "kLPOverAll", plLightInfo::kLPOverAll);
    PY_TYPE_ADD_CONST(LightInfo, "kLPHasSpecular", plLightInfo::kLPHasSpecular);
    PY_TYPE_ADD_CONST(LightInfo, "kLPShadowOnly", plLightInfo::kLPShadowOnly);
    PY_TYPE_ADD_CONST(LightInfo, "kLPShadowLightGroup", plLightInfo::kLPShadowLightGroup);
    PY_TYPE_ADD_CONST(LightInfo, "kLPForceProj", plLightInfo::kLPForceProj);

    Py_INCREF(&pyLightInfo_Type);
    return (PyObject*)&pyLightInfo_Type;
}

PY_PLASMA_IFC_METHODS(LightInfo, plLightInfo)

}
