//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#ifndef GXADJACENTCELL_H
#define GXADJACENTCELL_H

typedef struct
{
		/**
	    * Four byte cell ID.
	    */
	unsigned long m_CellId;
		/**
	    * Signal quality.
	    */
	unsigned char m_SignalQuality;

}GXAdjacentCell;

	/**
    * @return Four byte cell ID.
    */
    extern unsigned long GXAdjacentCell_GetCellId(GXAdjacentCell *p);

    /**
    * @param value
    *            Four byte cell ID.
    */
    extern void GXAdjacentCell_SetCellId(GXAdjacentCell *p, unsigned long value);

    /**
    * @return Signal quality.
    */
    extern unsigned char GXAdjacentCell_GetSignalQuality(GXAdjacentCell *p);

    /**
    * @param value
    *            Signal quality.
    */
    extern void GXAdjacentCell_SetSignalQuality(GXAdjacentCell *p, unsigned char value);

#endif //GXADJACENTCELL_H
