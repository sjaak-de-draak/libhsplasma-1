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

#include "pyGUIControlHandlers.h"

#include <PRP/GUI/pfGUIControlHandlers.h>
#include <typeinfo>

PyObject* ICreateGUIControlHandler(pfGUICtrlProcObject* proc)
{
    if (proc == nullptr)
        Py_RETURN_NONE;
    else if (typeid(*proc) == typeid(pfGUIConsoleCmdProc))
        return pyGUIConsoleCmdProc_FromGUIConsoleCmdProc((pfGUIConsoleCmdProc*)proc);
    else if (typeid(*proc) == typeid(pfGUIPythonScriptProc))
        return pyGUIPythonScriptProc_FromGUIPythonScriptProc((pfGUIPythonScriptProc*)proc);
    else if (typeid(*proc) == typeid(pfGUICloseDlgProc))
        return pyGUICloseDlgProc_FromGUICloseDlgProc((pfGUICloseDlgProc*)proc);
    return pyGUICtrlProcObject_FromGUICtrlProcObject(proc);
}
