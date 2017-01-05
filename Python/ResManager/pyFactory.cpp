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

#include "pyResManager.h"

#include <ResManager/plFactory.h>
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW_MSG(Factory, "plFactory cannot be constructed")

PY_METHOD_STATIC_VA(Factory, ClassName,
    "Params: classIdx, [version]\n"
    "Get the name of the specified class\n"
    "If `version` is specified, the classIdx is looked up for\n"
    "that version (otherwise the global mapping is used)")
{
    int classIdx, version = PlasmaVer::pvUnknown;

    if (!PyArg_ParseTuple(args, "i|i", &classIdx, &version)) {
        PyErr_SetString(PyExc_TypeError, "ClassName expects int, int");
        return NULL;
    }
    if (version == PlasmaVer::pvUnknown)
        return pyPlasma_convert(plFactory::ClassName(classIdx));
    else
        return pyPlasma_convert(plFactory::ClassName(classIdx, (PlasmaVer)version));
}

PY_METHOD_STATIC_VA(Factory, ClassIndex,
    "Params: className\n"
    "Returns the global ClassIndex for the specified class")
{
    const char* className;

    if (!PyArg_ParseTuple(args, "s", &className)) {
        PyErr_SetString(PyExc_TypeError, "ClassIndex expects a string");
        return NULL;
    }
    return pyPlasma_convert(plFactory::ClassIndex(className));
}

PY_METHOD_STATIC_VA(Factory, ClassVersion,
    "Params: classIdx, version\n"
    "Returns the Class Version of the specified class")
{
    int classIdx, version;

    if (!PyArg_ParseTuple(args, "ii", &classIdx, &version)) {
        PyErr_SetString(PyExc_TypeError, "ClassVersion expects int, int");
        return NULL;
    }
    return pyPlasma_convert(plFactory::ClassVersion(classIdx, (PlasmaVer)version));
}

static PyMethodDef pyFactory_Methods[] = {
    pyFactory_ClassName_method,
    pyFactory_ClassIndex_method,
    pyFactory_ClassVersion_method,
    PY_METHOD_TERMINATOR
};

PyTypeObject pyFactory_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plFactory",             /* tp_name */
    0,                                  /* tp_basicsize */
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
    "Creatable Factory",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyFactory_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyFactory_new,                      /* tp_new */
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

#define ADD_CREATABLE(class) \
    PY_TYPE_ADD_CONST(Factory, #class, class)

PyObject* Init_pyFactory_Type() {
    if (PyType_Ready(&pyFactory_Type) < 0)
        return NULL;

    ADD_CREATABLE(kSceneNode);
    ADD_CREATABLE(kSceneObject);
    ADD_CREATABLE(kKeyedObject);
    ADD_CREATABLE(kBitmap);
    ADD_CREATABLE(kMipmap);
    ADD_CREATABLE(kCubicEnvironmap);
    ADD_CREATABLE(kLayer);
    ADD_CREATABLE(kGMaterial);
    ADD_CREATABLE(kParticleSystem);
    ADD_CREATABLE(kParticleEffect);
    ADD_CREATABLE(kParticleCollisionEffectBeat);
    ADD_CREATABLE(kParticleFadeVolumeEffect);
    ADD_CREATABLE(kBoundInterface);
    ADD_CREATABLE(kRenderTarget);
    ADD_CREATABLE(kCubicRenderTarget);
    ADD_CREATABLE(kCubicRenderTargetModifier);
    ADD_CREATABLE(kObjInterface);
    ADD_CREATABLE(kAudioInterface);
    ADD_CREATABLE(kAudible);
    ADD_CREATABLE(kAudibleNull);
    ADD_CREATABLE(kWinAudible);
    ADD_CREATABLE(kCoordinateInterface);
    ADD_CREATABLE(kDrawInterface);
    ADD_CREATABLE(kDrawable);
    ADD_CREATABLE(kDrawableMesh);
    ADD_CREATABLE(kDrawableIce);
    ADD_CREATABLE(kPhysical);
    ADD_CREATABLE(kPhysicalMesh);
    ADD_CREATABLE(kSimulationInterface);
    ADD_CREATABLE(kCameraModifier);
    ADD_CREATABLE(kModifier);
    ADD_CREATABLE(kSingleModifier);
    ADD_CREATABLE(kSimpleModifier);
    ADD_CREATABLE(kSimpleTMModifier);
    ADD_CREATABLE(kRandomTMModifier);
    ADD_CREATABLE(kInterestingModifier);
    ADD_CREATABLE(kDetectorModifier);
    ADD_CREATABLE(kSimplePhysicalMesh);
    ADD_CREATABLE(kCompoundPhysicalMesh);
    ADD_CREATABLE(kMultiModifier);
    ADD_CREATABLE(kSynchedObject);
    ADD_CREATABLE(kSoundBuffer);
    ADD_CREATABLE(kAliasModifier);
    ADD_CREATABLE(kPickingDetector);
    ADD_CREATABLE(kCollisionDetector);
    ADD_CREATABLE(kLogicModifier);
    ADD_CREATABLE(kConditionalObject);
    ADD_CREATABLE(kANDConditionalObject);
    ADD_CREATABLE(kORConditionalObject);
    ADD_CREATABLE(kPickedConditionalObject);
    ADD_CREATABLE(kActivatorConditionalObject);
    ADD_CREATABLE(kTimerCallbackManager);
    ADD_CREATABLE(kKeyPressConditionalObject);
    ADD_CREATABLE(kAnimationEventConditionalObject);
    ADD_CREATABLE(kControlEventConditionalObject);
    ADD_CREATABLE(kObjectInBoxConditionalObject);
    ADD_CREATABLE(kLocalPlayerInBoxConditionalObject);
    ADD_CREATABLE(kObjectIntersectPlaneConditionalObject);
    ADD_CREATABLE(kLocalPlayerIntersectPlaneConditionalObject);
    ADD_CREATABLE(kPortalDrawable);
    ADD_CREATABLE(kPortalPhysical);
    ADD_CREATABLE(kSpawnModifier);
    ADD_CREATABLE(kFacingConditionalObject);
    ADD_CREATABLE(kGenericPhysical);
    ADD_CREATABLE(kViewFaceModifier);
    ADD_CREATABLE(kLayerInterface);
    ADD_CREATABLE(kLayerWrapper);
    ADD_CREATABLE(kLayerAnimation);
    ADD_CREATABLE(kLayerDepth);
    ADD_CREATABLE(kLayerMovie);
    ADD_CREATABLE(kLayerBink);
    ADD_CREATABLE(kLayerAVI);
    ADD_CREATABLE(kSound);
    ADD_CREATABLE(kWin32Sound);
    ADD_CREATABLE(kLayerOr);
    ADD_CREATABLE(kAudioSystem);
    ADD_CREATABLE(kDrawableSpans);
    ADD_CREATABLE(kDrawablePatchSet);
    ADD_CREATABLE(kInputManager);
    ADD_CREATABLE(kLogicModBase);
    ADD_CREATABLE(kFogEnvironment);
    ADD_CREATABLE(kNetApp);
    ADD_CREATABLE(kNetClientMgr);
    ADD_CREATABLE(k2WayWinAudible);
    ADD_CREATABLE(kLightInfo);
    ADD_CREATABLE(kDirectionalLightInfo);
    ADD_CREATABLE(kOmniLightInfo);
    ADD_CREATABLE(kSpotLightInfo);
    ADD_CREATABLE(kLightSpace);
    ADD_CREATABLE(kNetClientApp);
    ADD_CREATABLE(kNetServerApp);
    ADD_CREATABLE(kClient);
    ADD_CREATABLE(kCompoundTMModifier);
    ADD_CREATABLE(kCameraBrain);
    ADD_CREATABLE(kCameraBrain_Default);
    ADD_CREATABLE(kCameraBrain_Drive);
    ADD_CREATABLE(kCameraBrain_Fixed);
    ADD_CREATABLE(kCameraBrain_FixedPan);
    ADD_CREATABLE(kGUIClickMapCtrl);
    ADD_CREATABLE(kListener);
    ADD_CREATABLE(kAvatarMod);
    ADD_CREATABLE(kAvatarAnim);
    ADD_CREATABLE(kAvatarAnimMgr);
    ADD_CREATABLE(kOccluder);
    ADD_CREATABLE(kMobileOccluder);
    ADD_CREATABLE(kLayerShadowBase);
    ADD_CREATABLE(kLimitedDirLightInfo);
    ADD_CREATABLE(kAGAnim);
    ADD_CREATABLE(kAGModifier);
    ADD_CREATABLE(kAGMasterMod);
    ADD_CREATABLE(kCameraBrain_Avatar);
    ADD_CREATABLE(kCameraRegionDetector);
    ADD_CREATABLE(kCameraBrain_FP);
    ADD_CREATABLE(kLineFollowMod);
    ADD_CREATABLE(kLightModifier);
    ADD_CREATABLE(kOmniModifier);
    ADD_CREATABLE(kSpotModifier);
    ADD_CREATABLE(kLtdDirModifier);
    ADD_CREATABLE(kSeekPointMod);
    ADD_CREATABLE(kOneShotMod);
    ADD_CREATABLE(kRandomCommandMod);
    ADD_CREATABLE(kRandomSoundMod);
    ADD_CREATABLE(kPostEffectMod);
    ADD_CREATABLE(kObjectInVolumeDetector);
    ADD_CREATABLE(kResponderModifier);
    ADD_CREATABLE(kAxisAnimModifier);
    ADD_CREATABLE(kLayerLightBase);
    ADD_CREATABLE(kFollowMod);
    ADD_CREATABLE(kTransitionMgr);
    ADD_CREATABLE(kInventoryMod);
    ADD_CREATABLE(kInventoryObjMod);
    ADD_CREATABLE(kLinkEffectsMgr);
    ADD_CREATABLE(kWin32StreamingSound);
    ADD_CREATABLE(kPythonMod);
    ADD_CREATABLE(kActivatorActivatorConditionalObject);
    ADD_CREATABLE(kSoftVolume);
    ADD_CREATABLE(kSoftVolumeSimple);
    ADD_CREATABLE(kSoftVolumeComplex);
    ADD_CREATABLE(kSoftVolumeUnion);
    ADD_CREATABLE(kSoftVolumeIntersect);
    ADD_CREATABLE(kSoftVolumeInvert);
    ADD_CREATABLE(kWin32LinkSound);
    ADD_CREATABLE(kLayerLinkAnimation);
    ADD_CREATABLE(kArmatureMod);
    ADD_CREATABLE(kCameraBrain_Freelook);
    ADD_CREATABLE(kHavokConstraintsMod);
    ADD_CREATABLE(kHingeConstraintMod);
    ADD_CREATABLE(kWheelConstraintMod);
    ADD_CREATABLE(kStrongSpringConstraintMod);
    ADD_CREATABLE(kArmatureLODMod);
    ADD_CREATABLE(kWin32StaticSound);
    ADD_CREATABLE(kGameGUIMgr);
    ADD_CREATABLE(kGUIDialogMod);
    ADD_CREATABLE(kCameraBrain1);
    ADD_CREATABLE(kVirtualCam1);
    ADD_CREATABLE(kCameraBrain1_Drive);
    ADD_CREATABLE(kCameraBrain1_POA);
    ADD_CREATABLE(kCameraBrain1_Avatar);
    ADD_CREATABLE(kCameraBrain1_Fixed);
    ADD_CREATABLE(kCameraBrain1_POAFixed);
    ADD_CREATABLE(kGUIButtonMod);
    ADD_CREATABLE(kPythonFileMod);
    ADD_CREATABLE(kGUIControlMod);
    ADD_CREATABLE(kExcludeRegionModifier);
    ADD_CREATABLE(kGUIDraggableMod);
    ADD_CREATABLE(kVolumeSensorConditionalObject);
    ADD_CREATABLE(kVolActivatorConditionalObject);
    ADD_CREATABLE(kMsgForwarder);
    ADD_CREATABLE(kBlower);
    ADD_CREATABLE(kGUIListBoxMod);
    ADD_CREATABLE(kGUITextBoxMod);
    ADD_CREATABLE(kGUIEditBoxMod);
    ADD_CREATABLE(kDynamicTextMap);
    ADD_CREATABLE(kSittingModifier);
    ADD_CREATABLE(kGUIUpDownPairMod);
    ADD_CREATABLE(kGUIValueCtrl);
    ADD_CREATABLE(kGUIKnobCtrl);
    ADD_CREATABLE(kAvLadderMod);
    ADD_CREATABLE(kCameraBrain1_FirstPerson);
    ADD_CREATABLE(kCloneSpawnModifier);
    ADD_CREATABLE(kClothingItem);
    ADD_CREATABLE(kClothingOutfit);
    ADD_CREATABLE(kClothingBase);
    ADD_CREATABLE(kClothingMgr);
    ADD_CREATABLE(kGUIDragBarCtrl);
    ADD_CREATABLE(kGUICheckBoxCtrl);
    ADD_CREATABLE(kGUIRadioGroupCtrl);
    ADD_CREATABLE(kPlayerBookMod);
    ADD_CREATABLE(kGUIDynDisplayCtrl);
    ADD_CREATABLE(kLayerProject);
    ADD_CREATABLE(kInputInterfaceMgr);
    ADD_CREATABLE(kRailCameraMod);
    ADD_CREATABLE(kMultistageBehMod);
    ADD_CREATABLE(kCameraBrain1_Circle);
    ADD_CREATABLE(kParticleWindEffect);
    ADD_CREATABLE(kAnimEventModifier);
    ADD_CREATABLE(kAutoProfile);
    ADD_CREATABLE(kGUISkin);
    ADD_CREATABLE(kAVIWriter);
    ADD_CREATABLE(kParticleCollisionEffect);
    ADD_CREATABLE(kParticleCollisionEffectDie);
    ADD_CREATABLE(kParticleCollisionEffectBounce);
    ADD_CREATABLE(kInterfaceInfoModifier);
    ADD_CREATABLE(kSharedMesh);
    ADD_CREATABLE(kArmatureEffectsMgr);
    ADD_CREATABLE(kMarkerMgr);
    ADD_CREATABLE(kVehicleModifier);
    ADD_CREATABLE(kParticleLocalWind);
    ADD_CREATABLE(kParticleUniformWind);
    ADD_CREATABLE(kInstanceDrawInterface);
    ADD_CREATABLE(kShadowMaster);
    ADD_CREATABLE(kShadowCaster);
    ADD_CREATABLE(kPointShadowMaster);
    ADD_CREATABLE(kDirectShadowMaster);
    ADD_CREATABLE(kSDLModifier);
    ADD_CREATABLE(kPhysicalSDLModifier);
    ADD_CREATABLE(kClothingSDLModifier);
    ADD_CREATABLE(kAvatarSDLModifier);
    ADD_CREATABLE(kAGMasterSDLModifier);
    ADD_CREATABLE(kPythonSDLModifier);
    ADD_CREATABLE(kLayerSDLModifier);
    ADD_CREATABLE(kAnimTimeConvertSDLModifier);
    ADD_CREATABLE(kResponderSDLModifier);
    ADD_CREATABLE(kSoundSDLModifier);
    ADD_CREATABLE(kResManagerHelper);
    ADD_CREATABLE(kHKSubWorld);
    ADD_CREATABLE(kArmatureEffect);
    ADD_CREATABLE(kArmatureEffectFootSound);
    ADD_CREATABLE(kEAXListenerMod);
    ADD_CREATABLE(kDynaDecalMgr);
    ADD_CREATABLE(kObjectInVolumeAndFacingDetector);
    ADD_CREATABLE(kDynaFootMgr);
    ADD_CREATABLE(kDynaRippleMgr);
    ADD_CREATABLE(kDynaBulletMgr);
    ADD_CREATABLE(kDecalEnableMod);
    ADD_CREATABLE(kPrintShape);
    ADD_CREATABLE(kDynaPuddleMgr);
    ADD_CREATABLE(kGUIMultiLineEditCtrl);
    ADD_CREATABLE(kLayerAnimationBase);
    ADD_CREATABLE(kLayerSDLAnimation);
    ADD_CREATABLE(kATCAnim);
    ADD_CREATABLE(kAgeGlobalAnim);
    ADD_CREATABLE(kSubworldRegionDetector);
    ADD_CREATABLE(kAvatarMgr);
    ADD_CREATABLE(kNPCSpawnMod);
    ADD_CREATABLE(kActivePrintShape);
    ADD_CREATABLE(kExcludeRegionSDLModifier);
    ADD_CREATABLE(kLOSDispatch);
    ADD_CREATABLE(kDynaWakeMgr);
    ADD_CREATABLE(kSimulationMgr);
    ADD_CREATABLE(kWaveSet7);
    ADD_CREATABLE(kPanicLinkRegion);
    ADD_CREATABLE(kWin32GroupedSound);
    ADD_CREATABLE(kFilterCoordInterface);
    ADD_CREATABLE(kStereizer);
    ADD_CREATABLE(kCCRMgr);
    ADD_CREATABLE(kCCRSpecialist);
    ADD_CREATABLE(kCCRSeniorSpecialist);
    ADD_CREATABLE(kCCRShiftSupervisor);
    ADD_CREATABLE(kCCRGameOperator);
    ADD_CREATABLE(kShader);
    ADD_CREATABLE(kDynamicEnvMap);
    ADD_CREATABLE(kSimpleRegionSensor);
    ADD_CREATABLE(kMorphSequence);
    ADD_CREATABLE(kEmoteAnim);
    ADD_CREATABLE(kDynaRippleVSMgr);
    ADD_CREATABLE(kWaveSet6);
    ADD_CREATABLE(kGUIProgressCtrl);
    ADD_CREATABLE(kMaintainersMarkerModifier);
    ADD_CREATABLE(kMorphSequenceSDLMod);
    ADD_CREATABLE(kMorphDataSet);
    ADD_CREATABLE(kHardRegion);
    ADD_CREATABLE(kHardRegionPlanes);
    ADD_CREATABLE(kHardRegionComplex);
    ADD_CREATABLE(kHardRegionUnion);
    ADD_CREATABLE(kHardRegionIntersect);
    ADD_CREATABLE(kHardRegionInvert);
    ADD_CREATABLE(kVisRegion);
    ADD_CREATABLE(kVisMgr);
    ADD_CREATABLE(kRegionBase);
    ADD_CREATABLE(kGUIPopUpMenu);
    ADD_CREATABLE(kGUIMenuItem);
    ADD_CREATABLE(kCoopCoordinator);
    ADD_CREATABLE(kFont);
    ADD_CREATABLE(kFontCache);
    ADD_CREATABLE(kRelevanceRegion);
    ADD_CREATABLE(kRelevanceMgr);
    ADD_CREATABLE(kJournalBook);
    ADD_CREATABLE(kLayerTargetContainer);
    ADD_CREATABLE(kImageLibMod);
    ADD_CREATABLE(kParticleFlockEffect);
    ADD_CREATABLE(kParticleSDLMod);
    ADD_CREATABLE(kAgeLoader);
    ADD_CREATABLE(kWaveSetBase);
    ADD_CREATABLE(kPhysicalSndGroup);
    ADD_CREATABLE(kBookData);
    ADD_CREATABLE(kDynaTorpedoMgr);
    ADD_CREATABLE(kDynaTorpedoVSMgr);
    ADD_CREATABLE(kClusterGroup);
    ADD_CREATABLE(kGameMarkerModifier);
    ADD_CREATABLE(kLODMipmap);
    ADD_CREATABLE(kSwimDetector);
    ADD_CREATABLE(kFadeOpacityMod);
    ADD_CREATABLE(kFadeOpacityLay);
    ADD_CREATABLE(kDistOpacityMod);
    ADD_CREATABLE(kArmatureModBase);
    ADD_CREATABLE(kSwimRegionInterface);
    ADD_CREATABLE(kSwimCircularCurrentRegion);
    ADD_CREATABLE(kParticleFollowSystemEffect);
    ADD_CREATABLE(kSwimStraightCurrentRegion);
    ADD_CREATABLE(kObjectFlocker);
    ADD_CREATABLE(kGrassShaderMod);
    ADD_CREATABLE(kDynamicCamMap);
    ADD_CREATABLE(kAutoWalkRegion);
    ADD_CREATABLE(kCrossfade);
    ADD_CREATABLE(kParticleFadeOutEffect);
    ADD_CREATABLE(kSecurePreloader);
    ADD_CREATABLE(kWindBoneMod);
    ADD_CREATABLE(kCameraBrain_NovicePlus);
    ADD_CREATABLE(kSubtitleMgr);
    ADD_CREATABLE(kPythonFileModConditionalObject);
    ADD_CREATABLE(kLayerTransform);
    ADD_CREATABLE(kBubbleShaderMod);
    ADD_CREATABLE(kLineFollowModBase);
    ADD_CREATABLE(kClientApp);
    ADD_CREATABLE(kGUICreditsCtrl);
    ADD_CREATABLE(kCameraBrainUru);
    ADD_CREATABLE(kVirtualCamera);
    ADD_CREATABLE(kCameraBrainUru_Drive);
    ADD_CREATABLE(kCameraBrainUru_Follow);
    ADD_CREATABLE(kCameraBrainUru_Fixed);
    ADD_CREATABLE(kGUISketchCtrl);
    ADD_CREATABLE(kLadderModifier);
    ADD_CREATABLE(kCameraBrainUru_FirstPerson);
    ADD_CREATABLE(kCameraBrainUru_Circle);
    ADD_CREATABLE(kEAXReverbEffect);
    ADD_CREATABLE(kSpawnMod);
    ADD_CREATABLE(kCameraBrain_Novice);
    ADD_CREATABLE(kAvatarPhysicalSDLModifier);
    ADD_CREATABLE(kDirectMusicSound);
    ADD_CREATABLE(kClientSessionMgr);
    ADD_CREATABLE(kSDLVarChangeNotifier);
    ADD_CREATABLE(kInterestWellModifier);
    ADD_CREATABLE(kElevatorModifier);
    ADD_CREATABLE(kCameraBrain_Expert);
    ADD_CREATABLE(kPagingRegionModifier);
    ADD_CREATABLE(kGuidepathModifier);
    ADD_CREATABLE(kNodeMgr);
    ADD_CREATABLE(kEAXEffect);
    ADD_CREATABLE(kEAXPitchShifter);
    ADD_CREATABLE(kIKModifier);
    ADD_CREATABLE(kCameraBrain_M5);
    ADD_CREATABLE(kAGAnimBink);
    ADD_CREATABLE(kTreeShader);
    ADD_CREATABLE(kNodeRegionModifier);
    ADD_CREATABLE(kPiranhaRegionModifier);
    ADD_CREATABLE(kRidingAnimatedPhysicalDetector);
    ADD_CREATABLE(kVolumeSensorConditionalObjectNoArbitration);
    ADD_CREATABLE(kFXMaterial);
    ADD_CREATABLE(kMovableMod);
    ADD_CREATABLE(kMaterial);
    ADD_CREATABLE(kEffect);
    ADD_CREATABLE(kParticleBulletEffect);
    ADD_CREATABLE(kCameraBrain_Ground);
    ADD_CREATABLE(kCameraBrain_Flight);

    ADD_CREATABLE(kObjRefMsg);
    ADD_CREATABLE(kNodeRefMsg);
    ADD_CREATABLE(kMessage);
    ADD_CREATABLE(kRefMsg);
    ADD_CREATABLE(kGenRefMsg);
    ADD_CREATABLE(kTimeMsg);
    ADD_CREATABLE(kAnimCmdMsg);
    ADD_CREATABLE(kParticleUpdateMsg);
    ADD_CREATABLE(kLayRefMsg);
    ADD_CREATABLE(kMatRefMsg);
    ADD_CREATABLE(kCameraMsg);
    ADD_CREATABLE(kInputEventMsg);
    ADD_CREATABLE(kKeyEventMsg);
    ADD_CREATABLE(kMouseEventMsg);
    ADD_CREATABLE(kEvalMsg);
    ADD_CREATABLE(kTransformMsg);
    ADD_CREATABLE(kControlEventMsg);
    ADD_CREATABLE(kVaultCCRNode);
    ADD_CREATABLE(kLOSRequestMsg);
    ADD_CREATABLE(kLOSHitMsg);
    ADD_CREATABLE(kSingleModMsg);
    ADD_CREATABLE(kMultiModMsg);
    ADD_CREATABLE(kAvatarPhysicsEnableCallbackMsg);
    ADD_CREATABLE(kMemberUpdateMsg);
    ADD_CREATABLE(kNetMsgPagingRoom);
    ADD_CREATABLE(kActivatorMsg);
    ADD_CREATABLE(kDispatch);
    ADD_CREATABLE(kReceiver);
    ADD_CREATABLE(kMeshRefMsg);
    ADD_CREATABLE(kGRenderProcs);
    ADD_CREATABLE(kSfxAngleFade);
    ADD_CREATABLE(kSfxDistFade);
    ADD_CREATABLE(kSfxDistShade);
    ADD_CREATABLE(kSfxGlobalShade);
    ADD_CREATABLE(kSfxIntenseAlpha);
    ADD_CREATABLE(kSfxObjDistFade);
    ADD_CREATABLE(kSfxObjDistShade);
    ADD_CREATABLE(kDynamicValue);
    ADD_CREATABLE(kDynamicScalar);
    ADD_CREATABLE(kDynamicColorRGBA);
    ADD_CREATABLE(kDynamicMatrix33);
    ADD_CREATABLE(kDynamicMatrix44);
    ADD_CREATABLE(kController);
    ADD_CREATABLE(kLeafController);
    ADD_CREATABLE(kScaleController);
    ADD_CREATABLE(kRotController);
    ADD_CREATABLE(kPosController);
    ADD_CREATABLE(kScalarController);
    ADD_CREATABLE(kPoint3Controller);
    ADD_CREATABLE(kScaleValueController);
    ADD_CREATABLE(kQuatController);
    ADD_CREATABLE(kMatrix33Controller);
    ADD_CREATABLE(kMatrix44Controller);
    ADD_CREATABLE(kEaseController);
    ADD_CREATABLE(kSimpleScaleController);
    ADD_CREATABLE(kSimpleRotController);
    ADD_CREATABLE(kCompoundRotController);
    ADD_CREATABLE(kSimplePosController);
    ADD_CREATABLE(kCompoundPosController);
    ADD_CREATABLE(kTMController);
    ADD_CREATABLE(kFogControl);
    ADD_CREATABLE(kIntRefMsg);
    ADD_CREATABLE(kCollisionReactor);
    ADD_CREATABLE(kCorrectionMsg);
    ADD_CREATABLE(kPhysicalModifier);
    ADD_CREATABLE(kPickedMsg);
    ADD_CREATABLE(kCollideMsg);
    ADD_CREATABLE(kTriggerMsg);
    ADD_CREATABLE(kInterestingModMsg);
    ADD_CREATABLE(kDebugKeyEventMsg);
    ADD_CREATABLE(kPhysicalProperties);
    ADD_CREATABLE(kSimplePhys);
    ADD_CREATABLE(kMatrixUpdateMsg);
    ADD_CREATABLE(kCondRefMsg);
    ADD_CREATABLE(kTimerCallbackMsg);
    ADD_CREATABLE(kEventCallbackMsg);
    ADD_CREATABLE(kSpawnModMsg);
    ADD_CREATABLE(kSpawnRequestMsg);
    ADD_CREATABLE(kLoadCloneMsg);
    ADD_CREATABLE(kEnableMsg);
    ADD_CREATABLE(kWarpMsg);
    ADD_CREATABLE(kAttachMsg);
    ADD_CREATABLE(kConsole);
    ADD_CREATABLE(kRenderMsg);
    ADD_CREATABLE(kAnimTimeConvert);
    ADD_CREATABLE(kSoundMsg);
    ADD_CREATABLE(kInterestingPing);
    ADD_CREATABLE(kNodeCleanupMsg);
    ADD_CREATABLE(kSpaceTree);
    ADD_CREATABLE(kNetMessage);
    ADD_CREATABLE(kNetMsgJoinReq);
    ADD_CREATABLE(kNetMsgJoinAck);
    ADD_CREATABLE(kNetMsgLeave);
    ADD_CREATABLE(kNetMsgPing);
    ADD_CREATABLE(kNetMsgRoomsList);
    ADD_CREATABLE(kNetMsgGroupOwner);
    ADD_CREATABLE(kNetMsgGameStateRequest);
    ADD_CREATABLE(kNetMsgSessionReset);
    ADD_CREATABLE(kNetMsgOmnibus);
    ADD_CREATABLE(kNetMsgObject);
    ADD_CREATABLE(kCCRInvisibleMsg);
    ADD_CREATABLE(kLinkInDoneMsg);
    ADD_CREATABLE(kNetMsgGameMessage);
    ADD_CREATABLE(kNetMsgStream);
    ADD_CREATABLE(kAudioSysMsg);
    ADD_CREATABLE(kDispatchBase);
    ADD_CREATABLE(kServerReplyMsg);
    ADD_CREATABLE(kDeviceRecreateMsg);
    ADD_CREATABLE(kNetMsgStreamHelper);
    ADD_CREATABLE(kNetMsgObjectHelper);
    ADD_CREATABLE(kIMouseXEventMsg);
    ADD_CREATABLE(kIMouseYEventMsg);
    ADD_CREATABLE(kIMouseBEventMsg);
    ADD_CREATABLE(kLogicTriggerMsg);
    ADD_CREATABLE(kPipeline);
    ADD_CREATABLE(kDX8Pipeline);
    ADD_CREATABLE(kNetMsgVoice);
    ADD_CREATABLE(kLightRefMsg);
    ADD_CREATABLE(kNetMsgStreamedObject);
    ADD_CREATABLE(kNetMsgSharedState);
    ADD_CREATABLE(kNetMsgTestAndSet);
    ADD_CREATABLE(kNetMsgGetSharedState);
    ADD_CREATABLE(kSharedStateMsg);
    ADD_CREATABLE(kNetGenericServerTask);
    ADD_CREATABLE(kNetLookupServerGetAgeInfoFromVaultTask);
    ADD_CREATABLE(kLoadAgeMsg);
    ADD_CREATABLE(kMessageWithCallbacks);
    ADD_CREATABLE(kClientMsg);
    ADD_CREATABLE(kClientRefMsg);
    ADD_CREATABLE(kNetMsgObjStateRequest);
    ADD_CREATABLE(kCCRPetitionMsg);
    ADD_CREATABLE(kVaultCCRInitializationTask);
    ADD_CREATABLE(kNetServerMsg);
    ADD_CREATABLE(kNetServerMsgWithContext);
    ADD_CREATABLE(kNetServerMsgRegisterServer);
    ADD_CREATABLE(kNetServerMsgUnregisterServer);
    ADD_CREATABLE(kNetServerMsgStartProcess);
    ADD_CREATABLE(kNetServerMsgRegisterProcess);
    ADD_CREATABLE(kNetServerMsgUnregisterProcess);
    ADD_CREATABLE(kNetServerMsgFindProcess);
    ADD_CREATABLE(kNetServerMsgProcessFound);
    ADD_CREATABLE(kNetMsgRoutingInfo);
    ADD_CREATABLE(kNetServerSessionInfo);
    ADD_CREATABLE(kSimulationMsg);
    ADD_CREATABLE(kSimulationSynchMsg);
    ADD_CREATABLE(kHKSimulationSynchMsg);
    ADD_CREATABLE(kAvatarMsg);
    ADD_CREATABLE(kAvTaskMsg);
    ADD_CREATABLE(kAvSeekMsg);
    ADD_CREATABLE(kAvOneShotMsg);
    ADD_CREATABLE(kSatisfiedMsg);
    ADD_CREATABLE(kNetMsgObjectListHelper);
    ADD_CREATABLE(kNetMsgObjectUpdateFilter);
    ADD_CREATABLE(kProxyDrawMsg);
    ADD_CREATABLE(kSelfDestructMsg);
    ADD_CREATABLE(kSimInfluenceMsg);
    ADD_CREATABLE(kForceMsg);
    ADD_CREATABLE(kOffsetForceMsg);
    ADD_CREATABLE(kTorqueMsg);
    ADD_CREATABLE(kImpulseMsg);
    ADD_CREATABLE(kOffsetImpulseMsg);
    ADD_CREATABLE(kAngularImpulseMsg);
    ADD_CREATABLE(kDampMsg);
    ADD_CREATABLE(kShiftMassMsg);
    ADD_CREATABLE(kSimStateMsg);
    ADD_CREATABLE(kFreezeMsg);
    ADD_CREATABLE(kEventGroupMsg);
    ADD_CREATABLE(kSuspendEventMsg);
    ADD_CREATABLE(kNetMsgMembersListReq);
    ADD_CREATABLE(kNetMsgMembersList);
    ADD_CREATABLE(kNetMsgMemberInfoHelper);
    ADD_CREATABLE(kNetMsgMemberListHelper);
    ADD_CREATABLE(kNetMsgMemberUpdate);
    ADD_CREATABLE(kNetMsgServerToClient);
    ADD_CREATABLE(kNetMsgCreatePlayer);
    ADD_CREATABLE(kNetMsgAuthenticateHello);
    ADD_CREATABLE(kNetMsgAuthenticateChallenge);
    ADD_CREATABLE(kConnectedToVaultMsg);
    ADD_CREATABLE(kCCRCommunicationMsg);
    ADD_CREATABLE(kNetMsgInitialAgeStateSent);
    ADD_CREATABLE(kInitialAgeStateLoadedMsg);
    ADD_CREATABLE(kNetServerMsgFindServerBase);
    ADD_CREATABLE(kNetServerMsgFindServerReplyBase);
    ADD_CREATABLE(kNetServerMsgFindAuthServer);
    ADD_CREATABLE(kNetServerMsgFindAuthServerReply);
    ADD_CREATABLE(kNetServerMsgFindVaultServer);
    ADD_CREATABLE(kNetServerMsgFindVaultServerReply);
    ADD_CREATABLE(kAvTaskSeekDoneMsg);
    ADD_CREATABLE(kAvatarSpawnNotifyMsg);
    ADD_CREATABLE(kNetServerMsgVaultTask);
    ADD_CREATABLE(kNetMsgVaultTask);
    ADD_CREATABLE(kAgeLinkStruct);
    ADD_CREATABLE(kVaultAgeInfoNode);
    ADD_CREATABLE(kNetMsgStreamableHelper);
    ADD_CREATABLE(kNetMsgReceiversListHelper);
    ADD_CREATABLE(kNetMsgListenListUpdate);
    ADD_CREATABLE(kNetServerMsgPing);
    ADD_CREATABLE(kNetMsgAlive);
    ADD_CREATABLE(kNetMsgTerminated);
    ADD_CREATABLE(kSDLModifierMsg);
    ADD_CREATABLE(kNetMsgSDLState);
    ADD_CREATABLE(kNetServerMsgSessionReset);
    ADD_CREATABLE(kCCRBanLinkingMsg);
    ADD_CREATABLE(kCCRSilencePlayerMsg);
    ADD_CREATABLE(kRenderRequestMsg);
    ADD_CREATABLE(kRenderRequestAck);
    ADD_CREATABLE(kNetMember);
    ADD_CREATABLE(kNetGameMember);
    ADD_CREATABLE(kNetTransportMember);
    ADD_CREATABLE(kConvexVolume);
    ADD_CREATABLE(kParticleGenerator);
    ADD_CREATABLE(kSimpleParticleGenerator);
    ADD_CREATABLE(kParticleEmitter);
    ADD_CREATABLE(kAGChannel);
    ADD_CREATABLE(kMatrixChannel);
    ADD_CREATABLE(kMatrixTimeScale);
    ADD_CREATABLE(kMatrixBlend);
    ADD_CREATABLE(kMatrixControllerChannel);
    ADD_CREATABLE(kQuatPointCombine);
    ADD_CREATABLE(kPointChannel);
    ADD_CREATABLE(kPointConstant);
    ADD_CREATABLE(kPointBlend);
    ADD_CREATABLE(kQuatChannel);
    ADD_CREATABLE(kQuatConstant);
    ADD_CREATABLE(kQuatBlend);
    ADD_CREATABLE(kLinkToAgeMsg);
    ADD_CREATABLE(kPlayerPageMsg);
    ADD_CREATABLE(kCmdIfaceModMsg);
    ADD_CREATABLE(kNetServerMsgPlsUpdatePlayer);
    ADD_CREATABLE(kListenerMsg);
    ADD_CREATABLE(kAnimPath);
    ADD_CREATABLE(kClothingUpdateBCMsg);
    ADD_CREATABLE(kNotifyMsg);
    ADD_CREATABLE(kFakeOutMsg);
    ADD_CREATABLE(kCursorChangeMsg);
    ADD_CREATABLE(kNodeChangeMsg);
    ADD_CREATABLE(kAvEnableMsg);
    ADD_CREATABLE(kLinkCallbackMsg);
    ADD_CREATABLE(kTransitionMsg);
    ADD_CREATABLE(kConsoleMsg);
    ADD_CREATABLE(kVolumeIsect);
    ADD_CREATABLE(kSphereIsect);
    ADD_CREATABLE(kConeIsect);
    ADD_CREATABLE(kCylinderIsect);
    ADD_CREATABLE(kParallelIsect);
    ADD_CREATABLE(kConvexIsect);
    ADD_CREATABLE(kComplexIsect);
    ADD_CREATABLE(kUnionIsect);
    ADD_CREATABLE(kIntersectionIsect);
    ADD_CREATABLE(kModulator);
    ADD_CREATABLE(kInventoryMsg);
    ADD_CREATABLE(kLinkEffectsTriggerMsg);
    ADD_CREATABLE(kLinkEffectBCMsg);
    ADD_CREATABLE(kResponderEnableMsg);
    ADD_CREATABLE(kNetServerMsgHello);
    ADD_CREATABLE(kNetServerMsgHelloReply);
    ADD_CREATABLE(kNetServerMember);
    ADD_CREATABLE(kResponderMsg);
    ADD_CREATABLE(kOneShotMsg);
    ADD_CREATABLE(kVaultAgeInfoListNode);
    ADD_CREATABLE(kNetServerMsgServerRegistered);
    ADD_CREATABLE(kPointTimeScale);
    ADD_CREATABLE(kPointControllerChannel);
    ADD_CREATABLE(kQuatTimeScale);
    ADD_CREATABLE(kAGApplicator);
    ADD_CREATABLE(kMatrixChannelApplicator);
    ADD_CREATABLE(kPointChannelApplicator);
    ADD_CREATABLE(kLightDiffuseApplicator);
    ADD_CREATABLE(kLightAmbientApplicator);
    ADD_CREATABLE(kLightSpecularApplicator);
    ADD_CREATABLE(kOmniApplicator);
    ADD_CREATABLE(kQuatChannelApplicator);
    ADD_CREATABLE(kScalarChannel);
    ADD_CREATABLE(kScalarTimeScale);
    ADD_CREATABLE(kScalarBlend);
    ADD_CREATABLE(kScalarControllerChannel);
    ADD_CREATABLE(kScalarChannelApplicator);
    ADD_CREATABLE(kSpotInnerApplicator);
    ADD_CREATABLE(kSpotOuterApplicator);
    ADD_CREATABLE(kNetServerMsgPlsRoutableMsg);
    ADD_CREATABLE(kPuppetBrainMsg);
    ADD_CREATABLE(kATCEaseCurve);
    ADD_CREATABLE(kConstAccelEaseCurve);
    ADD_CREATABLE(kSplineEaseCurve);
    ADD_CREATABLE(kVaultAgeInfoInitializationTask);
    ADD_CREATABLE(kGameGUIMsg);
    ADD_CREATABLE(kNetServerMsgVaultRequestGameState);
    ADD_CREATABLE(kNetServerMsgVaultGameState);
    ADD_CREATABLE(kNetServerMsgVaultGameStateSave);
    ADD_CREATABLE(kNetServerMsgVaultGameStateSaved);
    ADD_CREATABLE(kNetServerMsgVaultGameStateLoad);
    ADD_CREATABLE(kNetClientTask);
    ADD_CREATABLE(kNetMsgSDLStateBCast);
    ADD_CREATABLE(kReplaceGeometryMsg);
    ADD_CREATABLE(kNetServerMsgExitProcess);
    ADD_CREATABLE(kNetServerMsgSaveGameState);
    ADD_CREATABLE(kDniCoordinateInfo);
    ADD_CREATABLE(kNetMsgGameMessageDirected);
    ADD_CREATABLE(kLinkOutUnloadMsg);
    ADD_CREATABLE(kScalarConstant);
    ADD_CREATABLE(kMatrixConstant);
    ADD_CREATABLE(kAGCmdMsg);
    ADD_CREATABLE(kParticleTransferMsg);
    ADD_CREATABLE(kParticleKillMsg);
    ADD_CREATABLE(kExcludeRegionMsg);
    ADD_CREATABLE(kOneTimeParticleGenerator);
    ADD_CREATABLE(kParticleApplicator);
    ADD_CREATABLE(kParticleLifeMinApplicator);
    ADD_CREATABLE(kParticleLifeMaxApplicator);
    ADD_CREATABLE(kParticlePPSApplicator);
    ADD_CREATABLE(kParticleAngleApplicator);
    ADD_CREATABLE(kParticleVelMinApplicator);
    ADD_CREATABLE(kParticleVelMaxApplicator);
    ADD_CREATABLE(kParticleScaleMinApplicator);
    ADD_CREATABLE(kParticleScaleMaxApplicator);
    ADD_CREATABLE(kDynamicTextMsg);
    ADD_CREATABLE(kCameraTargetFadeMsg);
    ADD_CREATABLE(kAgeLoadedMsg);
    ADD_CREATABLE(kPointControllerCacheChannel);
    ADD_CREATABLE(kScalarControllerCacheChannel);
    ADD_CREATABLE(kLinkEffectsTriggerPrepMsg);
    ADD_CREATABLE(kLinkEffectPrepBCMsg);
    ADD_CREATABLE(kAvatarInputStateMsg);
    ADD_CREATABLE(kAgeInfoStruct);
    ADD_CREATABLE(kSDLNotificationMsg);
    ADD_CREATABLE(kNetClientConnectAgeVaultTask);
    ADD_CREATABLE(kLinkingMgrMsg);
    ADD_CREATABLE(kVaultNotifyMsg);
    ADD_CREATABLE(kPlayerInfo);
    ADD_CREATABLE(kSwapSpansRefMsg);
    ADD_CREATABLE(kKI);
    ADD_CREATABLE(kDISpansMsg);
    ADD_CREATABLE(kNetMsgCreatableHelper);
    ADD_CREATABLE(kServerGuid);
    ADD_CREATABLE(kNetMsgRequestMyVaultPlayerList);
    ADD_CREATABLE(kDelayedTransformMsg);
    ADD_CREATABLE(kSuperVNodeMgrInitTask);
    ADD_CREATABLE(kElementRefMsg);
    ADD_CREATABLE(kClothingMsg);
    ADD_CREATABLE(kEventGroupEnableMsg);
    ADD_CREATABLE(kGUINotifyMsg);
    ADD_CREATABLE(kAvBrain);
    ADD_CREATABLE(kArmatureBrain);
    ADD_CREATABLE(kAvBrainHuman);
    ADD_CREATABLE(kAvBrainCritter);
    ADD_CREATABLE(kAvBrainDrive);
    ADD_CREATABLE(kAvBrainSample);
    ADD_CREATABLE(kAvBrainGeneric);
    ADD_CREATABLE(kAvBrainPuppet);
    ADD_CREATABLE(kAvBrainLadder);
    ADD_CREATABLE(kInputIfaceMgrMsg);
    ADD_CREATABLE(kKIMsg);
    ADD_CREATABLE(kRemoteAvatarInfoMsg);
    ADD_CREATABLE(kMatrixDelayedCorrectionApplicator);
    ADD_CREATABLE(kAvPushBrainMsg);
    ADD_CREATABLE(kAvPopBrainMsg);
    ADD_CREATABLE(kRoomLoadNotifyMsg);
    ADD_CREATABLE(kAvTask);
    ADD_CREATABLE(kAvAnimTask);
    ADD_CREATABLE(kAvSeekTask);
    ADD_CREATABLE(kAvBlendedSeekTask);
    ADD_CREATABLE(kAvOneShotTask);
    ADD_CREATABLE(kAvEnableTask);
    ADD_CREATABLE(kAvTaskBrain);
    ADD_CREATABLE(kAnimStage);
    ADD_CREATABLE(kNetClientMember);
    ADD_CREATABLE(kNetClientCommTask);
    ADD_CREATABLE(kNetServerMsgAuthRequest);
    ADD_CREATABLE(kNetServerMsgAuthReply);
    ADD_CREATABLE(kNetClientCommAuthTask);
    ADD_CREATABLE(kClientGuid);
    ADD_CREATABLE(kNetMsgVaultPlayerList);
    ADD_CREATABLE(kNetMsgSetMyActivePlayer);
    ADD_CREATABLE(kNetServerMsgRequestAccountPlayerList);
    ADD_CREATABLE(kNetServerMsgAccountPlayerList);
    ADD_CREATABLE(kNetMsgPlayerCreated);
    ADD_CREATABLE(kNetServerMsgVaultCreatePlayer);
    ADD_CREATABLE(kNetServerMsgVaultPlayerCreated);
    ADD_CREATABLE(kNetMsgFindAge);
    ADD_CREATABLE(kNetMsgFindAgeReply);
    ADD_CREATABLE(kNetClientConnectPrepTask);
    ADD_CREATABLE(kNetClientAuthTask);
    ADD_CREATABLE(kNetClientGetPlayerVaultTask);
    ADD_CREATABLE(kNetClientSetActivePlayerTask);
    ADD_CREATABLE(kNetClientFindAgeTask);
    ADD_CREATABLE(kNetClientLeaveTask);
    ADD_CREATABLE(kNetClientJoinTask);
    ADD_CREATABLE(kNetClientCalibrateTask);
    ADD_CREATABLE(kNetMsgDeletePlayer);
    ADD_CREATABLE(kNetServerMsgVaultDeletePlayer);
    ADD_CREATABLE(kNetCoreStatsSummary);
    ADD_CREATABLE(kCreatableGenericValue);
    ADD_CREATABLE(kCreatableListHelper);
    ADD_CREATABLE(kCreatableStream);
    ADD_CREATABLE(kAvBrainGenericMsg);
    ADD_CREATABLE(kAvTaskSeek);
    ADD_CREATABLE(kAGInstanceCallbackMsg);
    ADD_CREATABLE(kArmatureEffectMsg);
    ADD_CREATABLE(kArmatureEffectStateMsg);
    ADD_CREATABLE(kShadowCastMsg);
    ADD_CREATABLE(kBoundsIsect);
    ADD_CREATABLE(kNetClientCommLeaveTask);
    ADD_CREATABLE(kResMgrHelperMsg);
    ADD_CREATABLE(kNetMsgAuthenticateResponse);
    ADD_CREATABLE(kNetMsgAccountAuthenticated);
    ADD_CREATABLE(kNetClientCommSendPeriodicAliveTask);
    ADD_CREATABLE(kNetClientCommCheckServerSilenceTask);
    ADD_CREATABLE(kNetClientCommPingTask);
    ADD_CREATABLE(kNetClientCommFindAgeTask);
    ADD_CREATABLE(kNetClientCommSetActivePlayerTask);
    ADD_CREATABLE(kNetClientCommGetPlayerListTask);
    ADD_CREATABLE(kNetClientCommCreatePlayerTask);
    ADD_CREATABLE(kNetClientCommJoinAgeTask);
    ADD_CREATABLE(kVaultAdminInitializationTask);
    ADD_CREATABLE(kMultistageModMsg);
    ADD_CREATABLE(kSoundVolumeApplicator);
    ADD_CREATABLE(kCutter);
    ADD_CREATABLE(kBulletMsg);
    ADD_CREATABLE(kDynaDecalEnableMsg);
    ADD_CREATABLE(kOmniCutoffApplicator);
    ADD_CREATABLE(kArmatureUpdateMsg);
    ADD_CREATABLE(kAvatarFootMsg);
    ADD_CREATABLE(kNetOwnershipMsg);
    ADD_CREATABLE(kNetMsgRelevanceRegions);
    ADD_CREATABLE(kParticleFlockMsg);
    ADD_CREATABLE(kAvatarBehaviorNotifyMsg);
    ADD_CREATABLE(kATCChannel);
    ADD_CREATABLE(kScalarSDLChannel);
    ADD_CREATABLE(kLoadAvatarMsg);
    ADD_CREATABLE(kAvatarSetTypeMsg);
    ADD_CREATABLE(kNetMsgLoadClone);
    ADD_CREATABLE(kNetMsgPlayerPage);
    ADD_CREATABLE(kVNodeInitTask);
    ADD_CREATABLE(kRippleShapeMsg);
    ADD_CREATABLE(kEventManager);
    ADD_CREATABLE(kVaultNeighborhoodInitializationTask);
    ADD_CREATABLE(kNetServerMsgAgentRecoveryRequest);
    ADD_CREATABLE(kNetServerMsgFrontendRecoveryRequest);
    ADD_CREATABLE(kNetServerMsgBackendRecoveryRequest);
    ADD_CREATABLE(kNetServerMsgAgentRecoveryData);
    ADD_CREATABLE(kNetServerMsgFrontendRecoveryData);
    ADD_CREATABLE(kNetServerMsgBackendRecoveryData);
    ADD_CREATABLE(kSubWorldMsg);
    ADD_CREATABLE(kMatrixDifferenceApp);
    ADD_CREATABLE(kAvBrainUser);
    ADD_CREATABLE(kDX9Pipeline);
    ADD_CREATABLE(kDXPipeline);
    ADD_CREATABLE(kPlayerMsg);
    ADD_CREATABLE(kAvBrainPirahna);
    ADD_CREATABLE(kAxisEventMsg);
    ADD_CREATABLE(kCrossfadeMsg);
    ADD_CREATABLE(kSubtitleMsg);
    ADD_CREATABLE(kSDLStoreMsg);
    ADD_CREATABLE(kOmniSqApplicator);
    ADD_CREATABLE(kPreResourceMsg);
    ADD_CREATABLE(kUNUSED_DynamicColorRGB);
    ADD_CREATABLE(kUNUSED_DynamicMatrix33);
    ADD_CREATABLE(kUNUSED_DynamicMatrix44);
    ADD_CREATABLE(kCompoundController);
    ADD_CREATABLE(kNetClientMgrMsg);
    ADD_CREATABLE(kAgeLoaderMsg);
    ADD_CREATABLE(kAvBrainAvatar);
    ADD_CREATABLE(kPythonNotifyMsg);
    ADD_CREATABLE(kNCAgeJoinerMsg);
    ADD_CREATABLE(kAvTaskDumbSeek);
    ADD_CREATABLE(kAvTaskSmartSeek);
    ADD_CREATABLE(kCreatableUuid);
    ADD_CREATABLE(kPreloaderMsg);
    ADD_CREATABLE(kNetCommAuthConnectedMsg);
    ADD_CREATABLE(kNetCommAuthMsg);
    ADD_CREATABLE(kNetCommFileListMsg);
    ADD_CREATABLE(kNetCommFileDownloadMsg);
    ADD_CREATABLE(kNetCommLinkToAgeMsg);
    ADD_CREATABLE(kNetCommPlayerListMsg);
    ADD_CREATABLE(kNetCommActivePlayerMsg);
    ADD_CREATABLE(kNetCommCreatePlayerMsg);
    ADD_CREATABLE(kNetCommDeletePlayerMsg);
    ADD_CREATABLE(kNetCommPublicAgeListMsg);
    ADD_CREATABLE(kNetCommPublicAgeMsg);
    ADD_CREATABLE(kNetCommRegisterAgeMsg);
    ADD_CREATABLE(kAnimEvalMsg);
    ADD_CREATABLE(kAvBrainFlight);
    ADD_CREATABLE(kAvBrainNPC);
    ADD_CREATABLE(kAvBrainBlimp);
    ADD_CREATABLE(kAvBrainFlightNPC);
    ADD_CREATABLE(kParticleBulletHitMsg);
    ADD_CREATABLE(kPanicLinkMsg);
    ADD_CREATABLE(kAvTaskOneShot);

    ADD_CREATABLE(kVaultGameServerInitializationTask);
    ADD_CREATABLE(kNetClientFindDefaultAgeTask);
    ADD_CREATABLE(kVaultAgeNode);
    ADD_CREATABLE(kVaultAgeInitializationTask);
    ADD_CREATABLE(kSetListenerMsg);
    ADD_CREATABLE(kVaultSystemNode);
    ADD_CREATABLE(kAvBrainSwim);
    ADD_CREATABLE(kNetMsgVault);
    ADD_CREATABLE(kNetServerMsgVault);
    ADD_CREATABLE(kVaultTask);
    ADD_CREATABLE(kVaultConnectTask);
    ADD_CREATABLE(kVaultNegotiateManifestTask);
    ADD_CREATABLE(kVaultFetchNodesTask);
    ADD_CREATABLE(kVaultSaveNodeTask);
    ADD_CREATABLE(kVaultFindNodeTask);
    ADD_CREATABLE(kVaultAddNodeRefTask);
    ADD_CREATABLE(kVaultRemoveNodeRefTask);
    ADD_CREATABLE(kVaultSendNodeTask);
    ADD_CREATABLE(kVaultNotifyOperationCallbackTask);
    ADD_CREATABLE(kVNodeMgrInitializationTask);
    ADD_CREATABLE(kVaultPlayerInitializationTask);
    ADD_CREATABLE(kNetVaultServerInitializationTask);
    ADD_CREATABLE(kCommonNeighborhoodsInitTask);
    ADD_CREATABLE(kVaultNodeRef);
    ADD_CREATABLE(kVaultNode);
    ADD_CREATABLE(kVaultFolderNode);
    ADD_CREATABLE(kVaultImageNode);
    ADD_CREATABLE(kVaultTextNoteNode);
    ADD_CREATABLE(kVaultSDLNode);
    ADD_CREATABLE(kVaultAgeLinkNode);
    ADD_CREATABLE(kVaultChronicleNode);
    ADD_CREATABLE(kVaultPlayerInfoNode);
    ADD_CREATABLE(kVaultMgrNode);
    ADD_CREATABLE(kVaultPlayerNode);
    ADD_CREATABLE(kSynchEnableMsg);
    ADD_CREATABLE(kNetVaultServerNode);
    ADD_CREATABLE(kVaultAdminNode);
    ADD_CREATABLE(kVaultGameServerNode);
    ADD_CREATABLE(kVaultPlayerInfoListNode);
    ADD_CREATABLE(kAvatarStealthModeMsg);
    ADD_CREATABLE(kEventCallbackInterceptMsg);
    ADD_CREATABLE(kDynamicEnvMapMsg);
    ADD_CREATABLE(kClimbMsg);
    ADD_CREATABLE(kIfaceFadeAvatarMsg);
    ADD_CREATABLE(kAvBrainClimb);
    ADD_CREATABLE(kSharedMeshBCMsg);
    ADD_CREATABLE(kNetVoiceListMsg);
    ADD_CREATABLE(kSwimMsg);
    ADD_CREATABLE(kMorphDelta);
    ADD_CREATABLE(kMatrixControllerCacheChannel);
    ADD_CREATABLE(kVaultMarkerNode);
    ADD_CREATABLE(kMarkerMsg);
    ADD_CREATABLE(kPipeResMakeMsg);
    ADD_CREATABLE(kPipeRTMakeMsg);
    ADD_CREATABLE(kPipeGeoMakeMsg);
    ADD_CREATABLE(kAvCoopMsg);
    ADD_CREATABLE(kAvBrainCoop);
    ADD_CREATABLE(kSimSuppressMsg);
    ADD_CREATABLE(kVaultMarkerListNode);
    ADD_CREATABLE(kAvTaskOrient);
    ADD_CREATABLE(kAgeBeginLoadingMsg);
    ADD_CREATABLE(kSetNetGroupIDMsg);
    ADD_CREATABLE(kBackdoorMsg);
    ADD_CREATABLE(kNetMsgPython);
    ADD_CREATABLE(kPythonMsg);
    ADD_CREATABLE(kStateDataRecord);
    ADD_CREATABLE(kNetClientCommDeletePlayerTask);
    ADD_CREATABLE(kNetMsgSetTimeout);
    ADD_CREATABLE(kNetMsgActivePlayerSet);
    ADD_CREATABLE(kNetClientCommSetTimeoutTask);
    ADD_CREATABLE(kNetRoutableMsgOmnibus);
    ADD_CREATABLE(kNetMsgGetPublicAgeList);
    ADD_CREATABLE(kNetMsgPublicAgeList);
    ADD_CREATABLE(kNetMsgCreatePublicAge);
    ADD_CREATABLE(kNetMsgPublicAgeCreated);
    ADD_CREATABLE(kNetServerMsgEnvelope);
    ADD_CREATABLE(kNetClientCommGetPublicAgeListTask);
    ADD_CREATABLE(kNetClientCommCreatePublicAgeTask);
    ADD_CREATABLE(kNetServerMsgPendingMsgs);
    ADD_CREATABLE(kNetServerMsgRequestPendingMsgs);
    ADD_CREATABLE(kDbInterface);
    ADD_CREATABLE(kDbProxyInterface);
    ADD_CREATABLE(kDBGenericSQLDB);
    ADD_CREATABLE(kMySqlDB);
    ADD_CREATABLE(kNetGenericDatabase);
    ADD_CREATABLE(kNetVaultDatabase);
    ADD_CREATABLE(kNetServerMsgPlsUpdatePlayerReply);
    ADD_CREATABLE(kVaultDisconnectTask);
    ADD_CREATABLE(kNetClientCommSetAgePublicTask);
    ADD_CREATABLE(kNetClientCommRegisterOwnedAge);
    ADD_CREATABLE(kNetClientCommUnregisterOwnerAge);
    ADD_CREATABLE(kNetClientCommRegisterVisitAge);
    ADD_CREATABLE(kNetClientCommUnregisterVisitAge);
    ADD_CREATABLE(kNetMsgRemovePublicAge);
    ADD_CREATABLE(kNetMsgPublicAgeRemoved);
    ADD_CREATABLE(kNetClientCommRemovePublicAgeTask);
    ADD_CREATABLE(kCCRMessage);
    ADD_CREATABLE(kAvOneShotLinkTask);
    ADD_CREATABLE(kNetAuthDatabase);
    ADD_CREATABLE(kAvatarOpacityCallbackMsg);
    ADD_CREATABLE(kAGDetachCallbackMsg);
    ADD_CREATABLE(kMovieEventMsg);
    ADD_CREATABLE(kMovieMsg);
    ADD_CREATABLE(kPipeTexMakeMsg);
    ADD_CREATABLE(kEventLog);
    ADD_CREATABLE(kDbEventLog);
    ADD_CREATABLE(kSyslogEventLog);
    ADD_CREATABLE(kCaptureRenderMsg);
    ADD_CREATABLE(kAgeLoaded2Msg);
    ADD_CREATABLE(kPseudoLinkEffectMsg);
    ADD_CREATABLE(kPseudoLinkAnimTriggerMsg);
    ADD_CREATABLE(kPseudoLinkAnimCallbackMsg);
    ADD_CREATABLE(kClimbingWallMsg);
    ADD_CREATABLE(kClimbEventMsg);
    ADD_CREATABLE(kAvBrainQuab);
    ADD_CREATABLE(kSDLGameTimeElapsedVar);
    ADD_CREATABLE(kLinkEffectsDoneMsg);
    ADD_CREATABLE(kSDLVar);
    ADD_CREATABLE(kSDLStructVar);
    ADD_CREATABLE(kSDLBoolVar);
    ADD_CREATABLE(kSDLCharVar);
    ADD_CREATABLE(kSDLByteVar);
    ADD_CREATABLE(kSDLIntVar);
    ADD_CREATABLE(kSDLUIntVar);
    ADD_CREATABLE(kSDLFloatVar);
    ADD_CREATABLE(kSDLDoubleVar);
    ADD_CREATABLE(kSDLStringVar);
    ADD_CREATABLE(kSDLTimeVar);
    ADD_CREATABLE(kSDLUoidVar);
    ADD_CREATABLE(kSDLVector3Var);
    ADD_CREATABLE(kSDLPoint3Var);
    ADD_CREATABLE(kSDLQuaternionVar);
    ADD_CREATABLE(kSDLMatrix44Var);
    ADD_CREATABLE(kSDLRGBAVar);
    ADD_CREATABLE(kSDLAgeTimeOfDayVar);
    ADD_CREATABLE(kSDLAgeTimeElapsedVar);
    ADD_CREATABLE(kSDLMetaDoubleVar);
    ADD_CREATABLE(kSDLFixedArrayStructVar);
    ADD_CREATABLE(kSDLFixedArrayBoolVar);
    ADD_CREATABLE(kSDLFixedArrayCharVar);
    ADD_CREATABLE(kSDLFixedArrayByteVar);
    ADD_CREATABLE(kSDLFixedArrayIntVar);
    ADD_CREATABLE(kSDLFixedArrayUIntVar);
    ADD_CREATABLE(kSDLFixedArrayFloatVar);
    ADD_CREATABLE(kSDLFixedArrayDoubleVar);
    ADD_CREATABLE(kSDLFixedArrayStringVar);
    ADD_CREATABLE(kSDLFixedArrayTimeVar);
    ADD_CREATABLE(kSDLFixedArrayUoidVar);
    ADD_CREATABLE(kSDLFixedArrayVector3Var);
    ADD_CREATABLE(kSDLFixedArrayPoint3Var);
    ADD_CREATABLE(kSDLFixedArrayQuaternionVar);
    ADD_CREATABLE(kSDLFixedArrayMatrix44Var);
    ADD_CREATABLE(kSDLFixedArrayRGBAVar);
    ADD_CREATABLE(kSDLDynArrayStructVar);
    ADD_CREATABLE(kSDLDynArrayBoolVar);
    ADD_CREATABLE(kSDLDynArrayCharVar);
    ADD_CREATABLE(kSDLDynArrayByteVar);
    ADD_CREATABLE(kSDLDynArrayIntVar);
    ADD_CREATABLE(kSDLDynArrayUIntVar);
    ADD_CREATABLE(kSDLDynArrayFloatVar);
    ADD_CREATABLE(kSDLDynArrayDoubleVar);
    ADD_CREATABLE(kSDLDynArrayStringVar);
    ADD_CREATABLE(kSDLDynArrayTimeVar);
    ADD_CREATABLE(kSDLDynArrayUoidVar);
    ADD_CREATABLE(kSDLDynArrayVector3Var);
    ADD_CREATABLE(kSDLDynArrayPoint3Var);
    ADD_CREATABLE(kSDLDynArrayQuaternionVar);
    ADD_CREATABLE(kSDLDynArrayMatrix44Var);
    ADD_CREATABLE(kSDLDynArrayRGBAVar);
    ADD_CREATABLE(kSDLArrayVar);
    ADD_CREATABLE(kSDLVarChangeMsg);
    ADD_CREATABLE(kAvBrainPath);
    ADD_CREATABLE(kSDLBufferVar);
    ADD_CREATABLE(kSDLFixedArrayBufferVar);
    ADD_CREATABLE(kSDLDynArrayBufferVar);
    ADD_CREATABLE(kMatrixBorrowedChannel);
    ADD_CREATABLE(kNodeRegionMsg);
    ADD_CREATABLE(kEventCallbackSetupMsg);
    ADD_CREATABLE(kRelativeMatrixChannelApplicator);
    ADD_CREATABLE(kPiranhaRegionMsg);
    ADD_CREATABLE(kGameMgrMsg);
    ADD_CREATABLE(kGameCliMsg);
    ADD_CREATABLE(kGameCli);
    ADD_CREATABLE(kGmTicTacToe);
    ADD_CREATABLE(kGmHeek);
    ADD_CREATABLE(kGmMarker);
    ADD_CREATABLE(kGmBlueSpiral);
    ADD_CREATABLE(kAccountUpdateMsg);
    ADD_CREATABLE(kAIMsg);
    ADD_CREATABLE(kAIBrainCreatedMsg);
    ADD_CREATABLE(kGmClimbingWall);
    ADD_CREATABLE(kAIArrivedAtGoalMsg);
    ADD_CREATABLE(kGmVarSync);
    ADD_CREATABLE(kLinearVelocityMsg);
    ADD_CREATABLE(kAngularVelocityMsg);
    ADD_CREATABLE(kRideAnimatedPhysMsg);
    ADD_CREATABLE(kAvBrainRideAnimatedPhysical);

    Py_INCREF(&pyFactory_Type);
    return (PyObject*)&pyFactory_Type;
}

}
