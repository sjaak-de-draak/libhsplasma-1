#include "plCameraModifier.h"

/* plCameraModifier1::CamTrans */
plCameraModifier1::CamTrans::CamTrans()
                : fCutPos(false), fCutPOA(false), fIgnore(false), fAccel(60.0f),
                  fDecel(60.0f), fVelocity(60.0f), fPOAAccel(60.0f),
                  fPOADecel(60.0f), fPOAVelocity(60.0f) { }

plCameraModifier1::CamTrans::~CamTrans() { }

void plCameraModifier1::CamTrans::read(hsStream* S, plResManager* mgr) {
    fTransTo = mgr->readKey(S);
    fCutPos = S->readBool();
    fCutPOA = S->readBool();
    fIgnore = S->readBool();
    fVelocity = S->readFloat();
    fAccel = S->readFloat();
    fDecel = S->readFloat();
    fPOAVelocity = S->readFloat();
    fPOAAccel = S->readFloat();
    fPOADecel = S->readFloat();
}

void plCameraModifier1::CamTrans::write(hsStream* S, plResManager* mgr) {
    mgr->writeKey(S, fTransTo);
    S->writeBool(fCutPos);
    S->writeBool(fCutPOA);
    S->writeBool(fIgnore);
    S->writeFloat(fVelocity);
    S->writeFloat(fAccel);
    S->writeFloat(fDecel);
    S->writeFloat(fPOAVelocity);
    S->writeFloat(fPOAAccel);
    S->writeFloat(fPOADecel);
}

void plCameraModifier1::CamTrans::prcWrite(pfPrcHelper* prc) {
    prc->startTag("CamTrans");
    prc->writeParam("CutPos", fCutPos);
    prc->writeParam("CutPOA", fCutPOA);
    prc->writeParam("Ignore", fIgnore);
    prc->writeParam("Velocity", fVelocity);
    prc->writeParam("Accel", fAccel);
    prc->writeParam("Decel", fDecel);
    prc->writeParam("POAVelocity", fPOAVelocity);
    prc->writeParam("POAAccel", fPOAAccel);
    prc->writeParam("POADecel", fPOADecel);
    prc->endTag();
      prc->writeSimpleTag("TansTo");
      fTransTo->prcWrite(prc);
      prc->closeTag();
    prc->closeTag();
}


/* plCameraModifier1 */
plCameraModifier1::plCameraModifier1()
                 : fFrom(0.0f, 0.0f, 0.0f), fAt(0.0f, 1.0f, 0.0f),
                   fFOVw(45.0f), fFOVh(33.75f), fAnimated(false),
                   fStartAnimOnPush(false), fStopAnimOnPop(false),
                   fResetAnimOnPop(false), fInSubLastUpdate(false),
                   fUpdateBrainTarget(false) { }

plCameraModifier1::~plCameraModifier1() {
    for (size_t i=0; i<fTrans.getSize(); i++)
        delete fTrans[i];
    for (size_t i=0; i<fMessageQueue.getSize(); i++)
        delete fMessageQueue[i];
    for (size_t i=0; i<fFOVInstructions.getSize(); i++)
        delete fFOVInstructions[i];
}

IMPLEMENT_CREATABLE(plCameraModifier1, kCameraModifier1, plSingleModifier)

void plCameraModifier1::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fBrain = mgr->readKey(S);
    fTrans.setSizeNull(S->readInt());
    for (size_t i=0; i<fTrans.getSize(); i++) {
        fTrans[i] = new CamTrans();
        fTrans[i]->read(S, mgr);
    }
    fFOVw = S->readFloat();
    fFOVh = S->readFloat();

    fMessageQueue.setSizeNull(S->readInt());
    fSenderQueue.setSize(fMessageQueue.getSize());
    for (size_t i=0; i<fMessageQueue.getSize(); i++)
        fMessageQueue[i] = plMessage::Convert(mgr->ReadCreatable(S));
    for (size_t i=0; i<fSenderQueue.getSize(); i++)
        fSenderQueue[i] = mgr->readKey(S);

    fFOVInstructions.setSizeNull(S->readInt());
    for (size_t i=0; i<fFOVInstructions.getSize(); i++)
        fFOVInstructions[i] = plCameraMsg::Convert(mgr->ReadCreatable(S));

    fAnimated = S->readBool();
    fStartAnimOnPush = S->readBool();
    fStopAnimOnPop = S->readBool();
    fResetAnimOnPop = S->readBool();
}

void plCameraModifier1::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    mgr->writeKey(S, fBrain);
    S->writeInt(fTrans.getSize());
    for (size_t i=0; i<fTrans.getSize(); i++)
        fTrans[i]->write(S, mgr);
    S->writeFloat(fFOVw);
    S->writeFloat(fFOVh);

    S->writeInt(fMessageQueue.getSize());
    for (size_t i=0; i<fMessageQueue.getSize(); i++)
        mgr->WriteCreatable(S, fMessageQueue[i]);
    for (size_t i=0; i<fSenderQueue.getSize(); i++)
        mgr->writeKey(S, fSenderQueue[i]);

    S->writeInt(fFOVInstructions.getSize());
    for (size_t i=0; i<fFOVInstructions.getSize(); i++)
        mgr->WriteCreatable(S, fFOVInstructions[i]);

    S->writeBool(fAnimated);
    S->writeBool(fStartAnimOnPush);
    S->writeBool(fStopAnimOnPop);
    S->writeBool(fResetAnimOnPop);
}

void plCameraModifier1::prcWrite(pfPrcHelper* prc) {
    hsKeyedObject::prcWrite(prc);

    prc->startTag("CameraModParams");
    prc->writeParam("FOVw", fFOVw);
    prc->writeParam("FOVh", fFOVh);
    prc->writeParam("Animated", fAnimated);
    prc->writeParam("StartAnimOnPush", fStartAnimOnPush);
    prc->writeParam("StopAnimOnPop", fStopAnimOnPop);
    prc->writeParam("ResetAnimOnPop", fResetAnimOnPop);
    prc->endTag(true);

    prc->writeSimpleTag("Brain");
    fBrain->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Transforms");
    for (size_t i=0; i<fTrans.getSize(); i++)
        fTrans[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("MessageQueue");
    for (size_t i=0; i<fMessageQueue.getSize(); i++) {
        prc->writeSimpleTag("Message");
        fMessageQueue[i]->prcWrite(prc);  prc->closeTag();
        prc->closeTag();
        prc->writeSimpleTag("Sender");
        fSenderQueue[i]->prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("FOVInstructions");
    for (size_t i=0; i<fFOVInstructions.getSize(); i++) {
        fFOVInstructions[i]->prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}
