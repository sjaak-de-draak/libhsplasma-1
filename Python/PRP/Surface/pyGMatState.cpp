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

#include "pyGMatState.h"

#include <PRP/Surface/hsGMatState.h>

extern "C" {

PY_PLASMA_NEW_MSG(GMatState, "Cannot construct hsGMatState objects")

PY_PROPERTY_MEMBER(unsigned int, GMatState, blendFlags, fBlendFlags)
PY_PROPERTY_MEMBER(unsigned int, GMatState, clampFlags, fClampFlags)
PY_PROPERTY_MEMBER(unsigned int, GMatState, shadeFlags, fShadeFlags)
PY_PROPERTY_MEMBER(unsigned int, GMatState, ZFlags, fZFlags)
PY_PROPERTY_MEMBER(unsigned int, GMatState, miscFlags, fMiscFlags)

static PyGetSetDef pyGMatState_GetSet[] = {
    pyGMatState_blendFlags_getset,
    pyGMatState_clampFlags_getset,
    pyGMatState_shadeFlags_getset,
    pyGMatState_ZFlags_getset,
    pyGMatState_miscFlags_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyGMatState_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsGMatState",           /* tp_name */
    sizeof(pyGMatState),                /* tp_basicsize */
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

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "hsGMatState wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyGMatState_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyGMatState_new,                    /* tp_new */
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

PyObject* Init_pyGMatState_Type() {
    if (PyType_Ready(&pyGMatState_Type) < 0)
        return NULL;

    /* Blend Flags */
    PY_TYPE_ADD_CONST(GMatState, "kBlendTest", hsGMatState::kBlendTest);
    PY_TYPE_ADD_CONST(GMatState, "kBlendAlpha", hsGMatState::kBlendAlpha);
    PY_TYPE_ADD_CONST(GMatState, "kBlendMult", hsGMatState::kBlendMult);
    PY_TYPE_ADD_CONST(GMatState, "kBlendAdd", hsGMatState::kBlendAdd);
    PY_TYPE_ADD_CONST(GMatState, "kBlendAddColorTimesAlpha", hsGMatState::kBlendAddColorTimesAlpha);
    PY_TYPE_ADD_CONST(GMatState, "kBlendAntiAlias", hsGMatState::kBlendAntiAlias);
    PY_TYPE_ADD_CONST(GMatState, "kBlendDetail", hsGMatState::kBlendDetail);
    PY_TYPE_ADD_CONST(GMatState, "kBlendNoColor", hsGMatState::kBlendNoColor);
    PY_TYPE_ADD_CONST(GMatState, "kBlendMADD", hsGMatState::kBlendMADD);
    PY_TYPE_ADD_CONST(GMatState, "kBlendDot3", hsGMatState::kBlendDot3);
    PY_TYPE_ADD_CONST(GMatState, "kBlendAddSigned", hsGMatState::kBlendAddSigned);
    PY_TYPE_ADD_CONST(GMatState, "kBlendAddSigned2X", hsGMatState::kBlendAddSigned2X);
    PY_TYPE_ADD_CONST(GMatState, "kBlendMask", hsGMatState::kBlendMask);
    PY_TYPE_ADD_CONST(GMatState, "kBlendInvertAlpha", hsGMatState::kBlendInvertAlpha);
    PY_TYPE_ADD_CONST(GMatState, "kBlendInvertColor", hsGMatState::kBlendInvertColor);
    PY_TYPE_ADD_CONST(GMatState, "kBlendAlphaMult", hsGMatState::kBlendAlphaMult);
    PY_TYPE_ADD_CONST(GMatState, "kBlendAlphaAdd", hsGMatState::kBlendAlphaAdd);
    PY_TYPE_ADD_CONST(GMatState, "kBlendNoVtxAlpha", hsGMatState::kBlendNoVtxAlpha);
    PY_TYPE_ADD_CONST(GMatState, "kBlendNoTexColor", hsGMatState::kBlendNoTexColor);
    PY_TYPE_ADD_CONST(GMatState, "kBlendNoTexAlpha", hsGMatState::kBlendNoTexAlpha);
    PY_TYPE_ADD_CONST(GMatState, "kBlendInvertVtxAlpha", hsGMatState::kBlendInvertVtxAlpha);
    PY_TYPE_ADD_CONST(GMatState, "kBlendAlphaAlways", hsGMatState::kBlendAlphaAlways);
    PY_TYPE_ADD_CONST(GMatState, "kBlendInvertFinalColor", hsGMatState::kBlendInvertFinalColor);
    PY_TYPE_ADD_CONST(GMatState, "kBlendInvertFinalAlpha", hsGMatState::kBlendInvertFinalAlpha);
    PY_TYPE_ADD_CONST(GMatState, "kBlendEnvBumpNext", hsGMatState::kBlendEnvBumpNext);
    PY_TYPE_ADD_CONST(GMatState, "kBlendSubtract", hsGMatState::kBlendSubtract);
    PY_TYPE_ADD_CONST(GMatState, "kBlendRevSubtract", hsGMatState::kBlendRevSubtract);
    PY_TYPE_ADD_CONST(GMatState, "kBlendAlphaTestHigh", hsGMatState::kBlendAlphaTestHigh);

    /* Clamp Flags */
    PY_TYPE_ADD_CONST(GMatState, "kClampTextureU", hsGMatState::kClampTextureU);
    PY_TYPE_ADD_CONST(GMatState, "kClampTextureV", hsGMatState::kClampTextureV);
    PY_TYPE_ADD_CONST(GMatState, "kClampTexture", hsGMatState::kClampTexture);

    /* Shade Flags */
    PY_TYPE_ADD_CONST(GMatState, "kShadeSoftShadow", hsGMatState::kShadeSoftShadow);
    PY_TYPE_ADD_CONST(GMatState, "kShadeNoProjectors", hsGMatState::kShadeNoProjectors);
    PY_TYPE_ADD_CONST(GMatState, "kShadeEnvironMap", hsGMatState::kShadeEnvironMap);
    PY_TYPE_ADD_CONST(GMatState, "kShadeVertexShade", hsGMatState::kShadeVertexShade);
    PY_TYPE_ADD_CONST(GMatState, "kShadeNoShade", hsGMatState::kShadeNoShade);
    PY_TYPE_ADD_CONST(GMatState, "kShadeBlack", hsGMatState::kShadeBlack);
    PY_TYPE_ADD_CONST(GMatState, "kShadeSpecular", hsGMatState::kShadeSpecular);
    PY_TYPE_ADD_CONST(GMatState, "kShadeNoFog", hsGMatState::kShadeNoFog);
    PY_TYPE_ADD_CONST(GMatState, "kShadeWhite", hsGMatState::kShadeWhite);
    PY_TYPE_ADD_CONST(GMatState, "kShadeSpecularAlpha", hsGMatState::kShadeSpecularAlpha);
    PY_TYPE_ADD_CONST(GMatState, "kShadeSpecularColor", hsGMatState::kShadeSpecularColor);
    PY_TYPE_ADD_CONST(GMatState, "kShadeSpecularHighlight", hsGMatState::kShadeSpecularHighlight);
    PY_TYPE_ADD_CONST(GMatState, "kShadeVertColShade", hsGMatState::kShadeVertColShade);
    PY_TYPE_ADD_CONST(GMatState, "kShadeInherit", hsGMatState::kShadeInherit);
    PY_TYPE_ADD_CONST(GMatState, "kShadeIgnoreVtxIllum", hsGMatState::kShadeIgnoreVtxIllum);
    PY_TYPE_ADD_CONST(GMatState, "kShadeEmissive", hsGMatState::kShadeEmissive);
    PY_TYPE_ADD_CONST(GMatState, "kShadeReallyNoFog", hsGMatState::kShadeReallyNoFog);

    /* Z Flags */
    PY_TYPE_ADD_CONST(GMatState, "kZIncLayer", hsGMatState::kZIncLayer);
    PY_TYPE_ADD_CONST(GMatState, "kZClearZ", hsGMatState::kZClearZ);
    PY_TYPE_ADD_CONST(GMatState, "kZNoZRead", hsGMatState::kZNoZRead);
    PY_TYPE_ADD_CONST(GMatState, "kZNoZWrite", hsGMatState::kZNoZWrite);
    PY_TYPE_ADD_CONST(GMatState, "kZMask", hsGMatState::kZMask);
    PY_TYPE_ADD_CONST(GMatState, "kZLODBias", hsGMatState::kZLODBias);

    /* Misc Flags */
    PY_TYPE_ADD_CONST(GMatState, "kMiscWireFrame", hsGMatState::kMiscWireFrame);
    PY_TYPE_ADD_CONST(GMatState, "kMiscDrawMeshOutlines", hsGMatState::kMiscDrawMeshOutlines);
    PY_TYPE_ADD_CONST(GMatState, "kMiscTwoSided", hsGMatState::kMiscTwoSided);
    PY_TYPE_ADD_CONST(GMatState, "kMiscDrawAsSplats", hsGMatState::kMiscDrawAsSplats);
    PY_TYPE_ADD_CONST(GMatState, "kMiscAdjustPlane", hsGMatState::kMiscAdjustPlane);
    PY_TYPE_ADD_CONST(GMatState, "kMiscAdjustCylinder", hsGMatState::kMiscAdjustCylinder);
    PY_TYPE_ADD_CONST(GMatState, "kMiscAdjustSphere", hsGMatState::kMiscAdjustSphere);
    PY_TYPE_ADD_CONST(GMatState, "kMiscAdjust", hsGMatState::kMiscAdjust);
    PY_TYPE_ADD_CONST(GMatState, "kMiscTroubledLoner", hsGMatState::kMiscTroubledLoner);
    PY_TYPE_ADD_CONST(GMatState, "kMiscBindSkip", hsGMatState::kMiscBindSkip);
    PY_TYPE_ADD_CONST(GMatState, "kMiscBindMask", hsGMatState::kMiscBindMask);
    PY_TYPE_ADD_CONST(GMatState, "kMiscBindNext", hsGMatState::kMiscBindNext);
    PY_TYPE_ADD_CONST(GMatState, "kMiscLightMap", hsGMatState::kMiscLightMap);
    PY_TYPE_ADD_CONST(GMatState, "kMiscUseReflectionXform", hsGMatState::kMiscUseReflectionXform);
    PY_TYPE_ADD_CONST(GMatState, "kMiscPerspProjection", hsGMatState::kMiscPerspProjection);
    PY_TYPE_ADD_CONST(GMatState, "kMiscOrthoProjection", hsGMatState::kMiscOrthoProjection);
    PY_TYPE_ADD_CONST(GMatState, "kMiscProjection", hsGMatState::kMiscProjection);
    PY_TYPE_ADD_CONST(GMatState, "kMiscRestartPassHere", hsGMatState::kMiscRestartPassHere);
    PY_TYPE_ADD_CONST(GMatState, "kMiscBumpLayer", hsGMatState::kMiscBumpLayer);
    PY_TYPE_ADD_CONST(GMatState, "kMiscBumpDu", hsGMatState::kMiscBumpDu);
    PY_TYPE_ADD_CONST(GMatState, "kMiscBumpDv", hsGMatState::kMiscBumpDv);
    PY_TYPE_ADD_CONST(GMatState, "kMiscBumpDw", hsGMatState::kMiscBumpDw);
    PY_TYPE_ADD_CONST(GMatState, "kMiscBumpChans", hsGMatState::kMiscBumpChans);
    PY_TYPE_ADD_CONST(GMatState, "kMiscNoShadowAlpha", hsGMatState::kMiscNoShadowAlpha);
    PY_TYPE_ADD_CONST(GMatState, "kMiscUseRefractionXform", hsGMatState::kMiscUseRefractionXform);
    PY_TYPE_ADD_CONST(GMatState, "kMiscCam2Screen", hsGMatState::kMiscCam2Screen);
    PY_TYPE_ADD_CONST(GMatState, "kAllMiscFlags", hsGMatState::kAllMiscFlags);

    Py_INCREF(&pyGMatState_Type);
    return (PyObject*)&pyGMatState_Type;
}

PY_PLASMA_IFC_METHODS(GMatState, hsGMatState)

}
