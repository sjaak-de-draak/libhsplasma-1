#ifndef _PLCAMERAMODIFIER_H
#define _PLCAMERAMODIFIER_H

#include "NucleusLib/pnModifier/plModifier.h"
#include "NucleusLib/pnMessage/plCameraMsg.h"

DllClass plCameraModifier1 : public plSingleModifier {
public:
    DllClass CamTrans {
    protected:
        plKey fTransTo;
        bool fCutPos, fCutPOA, fIgnore;
        float fAccel, fDecel, fVelocity, fPOAAccel, fPOADecel, fPOAVelocity;

    public:
        CamTrans();
        ~CamTrans();

        void read(hsStream* S, plResManager* mgr);
        void write(hsStream* S, plResManager* mgr);
        void prcWrite(pfPrcHelper* prc);
    };

protected:
    hsPoint3 fFrom, fAt;
    plKey fBrain;
    hsTArray<CamTrans*> fTrans;
    float fFOVw, fFOVh;
    hsTArray<plMessage*> fMessageQueue;
    hsTArray<plKey> fSenderQueue;
    hsTArray<plCameraMsg*> fFOVInstructions;
    bool fAnimated, fStartAnimOnPush, fStopAnimOnPop, fResetAnimOnPop;
    hsPoint3 fLastSubPos, fLastSubPOA;
    bool fInSubLastUpdate, fUpdateBrainTarget;

public:
    plCameraModifier1();
    ~plCameraModifier1();

    DECLARE_CREATABLE(plCameraModifier1)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
