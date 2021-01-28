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

#include "pyAudible.h"

#include <PRP/Audio/plAudible.h>
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(Audible, plAudible)

PY_PLASMA_TYPE(Audible, plAudible, "plAudible wrapper")

PY_PLASMA_TYPE_INIT(Audible)
{
    pyAudible_Type.tp_new = pyAudible_new;
    pyAudible_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pyAudible_Type) < 0)
        return nullptr;

    Py_INCREF(&pyAudible_Type);
    return (PyObject*)&pyAudible_Type;
}

PY_PLASMA_IFC_METHODS(Audible, plAudible)
