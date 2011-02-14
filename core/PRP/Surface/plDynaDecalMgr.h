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

#ifndef _PLDYNADECALMGR_H
#define _PLDYNADECALMGR_H

#include "PRP/Object/plSynchedObject.h"
#include "Math/hsGeometry3.h"

class PLASMA_DLL plDynaDecalMgr : public virtual plSynchedObject {
    CREATABLE(plDynaDecalMgr, kDynaDecalMgr, plSynchedObject)

protected:
    plKey fMatPreShade, fMatRTShade;
    hsTArray<plKey> fTargets, fPartyObjects;
    float fPartyTime;
    unsigned short fMaxNumVerts, fMaxNumIdx;
    unsigned int fWaitOnEnable;
    float fWetLength, fRampEnd, fDecayStart, fLifeSpan, fIntensity;
    float fGridSizeU, fGridSizeV;
    hsVector3 fScale;
    hsTArray<plKey> fNotifies;

public:
    plDynaDecalMgr();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plDynaBulletMgr : public virtual plDynaDecalMgr {
    CREATABLE(plDynaBulletMgr, kDynaBulletMgr, plDynaDecalMgr)
};


class PLASMA_DLL plDynaFootMgr : public virtual plDynaDecalMgr {
    CREATABLE(plDynaFootMgr, kDynaFootMgr, plDynaDecalMgr)
};

#endif
