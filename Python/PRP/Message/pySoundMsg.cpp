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

#include "pySoundMsg.h"

#include <PRP/Message/plSoundMsg.h>
#include "pyMessageWithCallbacks.h"

extern "C" {

PY_PLASMA_NEW(SoundMsg, plSoundMsg)

PY_METHOD_VA(SoundMsg, getCmd,
    "Params: cmd\n"
    "Returns whether or not the command is set")
{
    int cmd;
    if (!PyArg_ParseTuple(args, "i", &cmd)) {
        PyErr_SetString(PyExc_TypeError, "getCmd expects an int");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->getCmd(cmd));
}

PY_METHOD_VA(SoundMsg, setCmd,
    "Params: cmd, value\n"
    "Sets the specified command")
{
    int cmd;
    int value = 1;
    if (!PyArg_ParseTuple(args, "i|i", &cmd, &value)) {
        PyErr_SetString(PyExc_TypeError, "setCmd expects an int and an optional int");
        return NULL;
    }
    self->fThis->setCmd(cmd, value != 0);
    Py_RETURN_NONE;
}

static PyMethodDef pySoundMsg_Methods[] = {
    pySoundMsg_getCmd_method,
    pySoundMsg_setCmd_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(double, SoundMsg, begin, getBegin, setBegin)
PY_PROPERTY(double, SoundMsg, end, getEnd, setEnd)
PY_PROPERTY(bool, SoundMsg, loop, getLoop, setLoop)
PY_PROPERTY(bool, SoundMsg, playing, getPlaying, setPlaying)
PY_PROPERTY(float, SoundMsg, speed, getSpeed, setSpeed)
PY_PROPERTY(double, SoundMsg, time, getTime, setTime)
PY_PROPERTY(int, SoundMsg, index, getIndex, setIndex)
PY_PROPERTY(int, SoundMsg, repeats, getRepeats, setRepeats)
PY_PROPERTY(float, SoundMsg, volume, getVolume, setVolume)
PY_PROPERTY(plSoundMsg::FadeType, SoundMsg, fadeType, getFadeType, setFadeType)

static PyGetSetDef pySoundMsg_GetSet[] = {
    pySoundMsg_begin_getset,
    pySoundMsg_end_getset,
    pySoundMsg_loop_getset,
    pySoundMsg_playing_getset,
    pySoundMsg_speed_getset,
    pySoundMsg_time_getset,
    pySoundMsg_index_getset,
    pySoundMsg_repeats_getset,
    pySoundMsg_volume_getset,
    pySoundMsg_fadeType_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pySoundMsg_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSoundMsg",            /* tp_name */
    sizeof(pySoundMsg),                 /* tp_basicsize */
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
    "plSoundMsg wrapper",                     /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySoundMsg_Methods,                 /* tp_methods */
    NULL,                               /* tp_members */
    pySoundMsg_GetSet,                  /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySoundMsg_new,                     /* tp_new */
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

PyObject* Init_pySoundMsg_Type() {
    pySoundMsg_Type.tp_base = &pyMessageWithCallbacks_Type;
    if (PyType_Ready(&pySoundMsg_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(SoundMsg, "kPlay", plSoundMsg::kPlay);
    PY_TYPE_ADD_CONST(SoundMsg, "kStop", plSoundMsg::kStop);
    PY_TYPE_ADD_CONST(SoundMsg, "kSetLooping", plSoundMsg::kSetLooping);
    PY_TYPE_ADD_CONST(SoundMsg, "kUnSetLooping", plSoundMsg::kUnSetLooping);
    PY_TYPE_ADD_CONST(SoundMsg, "kSetBegin", plSoundMsg::kSetBegin);
    PY_TYPE_ADD_CONST(SoundMsg, "kToggleState", plSoundMsg::kToggleState);
    PY_TYPE_ADD_CONST(SoundMsg, "kAddCallbacks", plSoundMsg::kAddCallbacks);
    PY_TYPE_ADD_CONST(SoundMsg, "kRemoveCallbacks", plSoundMsg::kRemoveCallbacks);
    PY_TYPE_ADD_CONST(SoundMsg, "kGetStatus", plSoundMsg::kGetStatus);
    PY_TYPE_ADD_CONST(SoundMsg, "kNumSounds", plSoundMsg::kNumSounds);
    PY_TYPE_ADD_CONST(SoundMsg, "kStatusReply", plSoundMsg::kStatusReply);
    PY_TYPE_ADD_CONST(SoundMsg, "kGoToTime", plSoundMsg::kGoToTime);
    PY_TYPE_ADD_CONST(SoundMsg, "kSetVolume", plSoundMsg::kSetVolume);
    PY_TYPE_ADD_CONST(SoundMsg, "kSetTalkIcon", plSoundMsg::kSetTalkIcon);
    PY_TYPE_ADD_CONST(SoundMsg, "kClearTalkIcon", plSoundMsg::kClearTalkIcon);
    PY_TYPE_ADD_CONST(SoundMsg, "kSetFadeIn", plSoundMsg::kSetFadeIn);
    PY_TYPE_ADD_CONST(SoundMsg, "kSetFadeOut", plSoundMsg::kSetFadeOut);
    PY_TYPE_ADD_CONST(SoundMsg, "kIsLocalOnly", plSoundMsg::kIsLocalOnly);
    PY_TYPE_ADD_CONST(SoundMsg, "kSelectFromGroup", plSoundMsg::kSelectFromGroup);
    PY_TYPE_ADD_CONST(SoundMsg, "kNumCmds", plSoundMsg::kNumCmds);
    PY_TYPE_ADD_CONST(SoundMsg, "kFastForwardPlay", plSoundMsg::kFastForwardPlay);
    PY_TYPE_ADD_CONST(SoundMsg, "kFastForwardToggle", plSoundMsg::kFastForwardToggle);

    PY_TYPE_ADD_CONST(SoundMsg, "kLinear", plSoundMsg::kLinear);
    PY_TYPE_ADD_CONST(SoundMsg, "kLogarithmic", plSoundMsg::kLogarithmic);
    PY_TYPE_ADD_CONST(SoundMsg, "kExponential", plSoundMsg::kExponential);

    Py_INCREF(&pySoundMsg_Type);
    return (PyObject*)&pySoundMsg_Type;
}

PY_PLASMA_IFC_METHODS(SoundMsg, plSoundMsg)

};
