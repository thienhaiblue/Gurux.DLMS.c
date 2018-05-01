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
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------
#ifndef GXDLMSPROFILEGENERIC_H
#define GXDLMSPROFILEGENERIC_H

#include "GXDLMSCaptureObject.h"
#include "GXDLMSRegister.h"

#include "String.h"
#include "Vector.h"

typedef int (*GetAttributeCount_FuncPtr)(void* p);
typedef int (*GetMethodCount_FuncPtr)(void* p);
typedef int (*GetValue_FuncPtr)(void* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);
typedef int (*SetValue_FuncPtr)(void* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);
typedef int (*Invoke_FuncPtr)(void* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

typedef void (*d_FuncPtr)(void* p);

typedef int (*SetDataType_FuncPtr)(void* p, int index, DLMS_DATA_TYPE type);
typedef int (*GetDataType_FuncPtr)(void* p, int index, DLMS_DATA_TYPE* type);

typedef int (*GetUIDataType_FuncPtr)(void* p, int index, DLMS_DATA_TYPE* type);

typedef void (*GetValues_FuncPtr)(void* p, Vector* values); // std::vector<std::string>&
typedef void (*GetAttributeIndexToRead_FuncPtr)(void* p, Vector* int_attributes);

typedef enum
{
    /**
     First in first out

     When circle buffer is full first item is removed.
    */
    DLMS_SORT_METHOD_FIFO = 1,
    /**
     Last in first out.

     When circle buffer is full last item is removed.
    */
    DLMS_SORT_METHOD_LIFO = 2,
    /**
     Largest is first.
    */
    DLMS_SORT_METHOD_LARGEST = 3,
    /**
     Smallest is first.
    */
    DLMS_SORT_METHOD_SMALLEST = 4,
    /**
     Nearst to zero is first.
    */
    DLMS_SORT_METHOD_NEAREST_TO_ZERO = 5,
    /**
     Farest from zero is first.
    */
    DLMS_SORT_METHOD_FAREST_FROM_ZERO = 6
} GX_SORT_METHOD;

typedef struct CGXDLMSProfileGeneric // class CGXDLMSProfileGeneric : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSProfileGeneric_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSProfileGeneric_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSProfileGeneric_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSProfileGeneric_SetValue
	Invoke_FuncPtr Invoke; // = CGXDLMSProfileGeneric_Invoke

    // (CGXDLMSObject)
    CGXAttributeCollection m_Attributes;
    CGXAttributeCollection m_MethodAttributes;
    String m_Description;
    DLMS_OBJECT_TYPE m_ObjectType;
    char m_AttributeIndex;
    unsigned short m_DataIndex;
    unsigned short m_Version;

    Map m_ReadTimes; // std::map<int, time_t> m_ReadTimes;
    unsigned short m_SN;
    unsigned char m_LN[6];

    // Override CGXDLMSObject
    d_FuncPtr d; // = CGXDLMSProfileGeneric_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSProfileGeneric_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSProfileGeneric_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSProfileGeneric_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    //List of non exists columns.
    Vector m_DynamicColumns; //std::vector<CGXDLMSObject*>

    Vector m_Buffer; //std::vector< std::vector<CGXDLMSVariant> >
    Vector m_CaptureObjects; //std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
    int m_CapturePeriod;
    GX_SORT_METHOD m_SortMethod;
    CGXDLMSObject* m_SortObject;
    unsigned long m_ProfileEntries;
    unsigned long m_EntriesInUse;

    int m_SortObjectAttributeIndex;
    int m_SortObjectDataIndex;

} CGXDLMSProfileGeneric;

#define CGXDLMSProfileGeneric_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSProfileGeneric_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))
#define CGXDLMSProfileGeneric_GetName(p)              CGXDLMSObject_GetName((CGXDLMSObject*) (p))

//public:

/**
* Get selected columns from parameters.
*
* @param selector
*            Is read by entry or range.
* @param parameters
*            Received parameters where columns information is found.
* @return Selected columns.
*/
extern int CGXDLMSProfileGeneric_GetSelectedColumns_2(
    CGXDLMSProfileGeneric* p,
    int selector,
    CGXDLMSVariant* parameters,
    Vector* columns); //std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >& 

/**
 Constructor.
*/
extern void CGXDLMSProfileGeneric_1(CGXDLMSProfileGeneric* p);

//SN Constructor.
extern void CGXDLMSProfileGeneric_2(CGXDLMSProfileGeneric* p, String ln, unsigned short sn);

/**
 Constructor.

    @param ln Logical Name of the object.
*/
extern void CGXDLMSProfileGeneric_3(CGXDLMSProfileGeneric* p, String ln);

/**
 Destructor.
*/
extern void CGXDLMSProfileGeneric_d(CGXDLMSProfileGeneric* p);

/**
 Data of profile generic.
*/
extern Vector* CGXDLMSProfileGeneric_GetBuffer(CGXDLMSProfileGeneric* p); //std::vector< std::vector<CGXDLMSVariant> >&

/**
 Captured Objects.
*/
extern Vector* CGXDLMSProfileGeneric_GetCaptureObjects(CGXDLMSProfileGeneric* p); //std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >&

/**
 How often values are captured.
*/
extern int CGXDLMSProfileGeneric_GetCapturePeriod(CGXDLMSProfileGeneric* p);
extern void CGXDLMSProfileGeneric_SetCapturePeriod(CGXDLMSProfileGeneric* p, int value);

/**
 How columns are sorted.
*/
extern GX_SORT_METHOD CGXDLMSProfileGeneric_GetSortMethod(CGXDLMSProfileGeneric* p);
extern void CGXDLMSProfileGeneric_SetSortMethod(CGXDLMSProfileGeneric* p, GX_SORT_METHOD value);

/**
 Column that is used for sorting.
*/
extern CGXDLMSObject* CGXDLMSProfileGeneric_GetSortObject(CGXDLMSProfileGeneric* p);
extern void CGXDLMSProfileGeneric_SetSortObject(CGXDLMSProfileGeneric* p, CGXDLMSObject* value);

/**
 Entries (rows) in Use.
*/
extern unsigned long CGXDLMSProfileGeneric_GetEntriesInUse(CGXDLMSProfileGeneric* p);
extern void CGXDLMSProfileGeneric_SetEntriesInUse(CGXDLMSProfileGeneric* p, unsigned long value);

/**
 Maximum Entries (rows) count.
*/
extern unsigned long CGXDLMSProfileGeneric_GetProfileEntries(CGXDLMSProfileGeneric* p);
extern void CGXDLMSProfileGeneric_SetProfileEntries(CGXDLMSProfileGeneric* p, unsigned long value);
/**
Attribute index of sort object.
*/
extern int CGXDLMSProfileGeneric_GetSortObjectAttributeIndex(CGXDLMSProfileGeneric* p);
extern void CGXDLMSProfileGeneric_SetSortObjectAttributeIndex(CGXDLMSProfileGeneric* p, int value);

/**
 Data index of sort object.
*/
extern int CGXDLMSProfileGeneric_GetSortObjectDataIndex(CGXDLMSProfileGeneric* p);
extern void CGXDLMSProfileGeneric_SetSortObjectDataIndex(CGXDLMSProfileGeneric* p, int value);

/**
 Clears the buffer.
*/
extern void CGXDLMSProfileGeneric_Reset_1(CGXDLMSProfileGeneric* p);

/*
* Copies the values of the objects to capture into the buffer by reading
* capture objects.
*/
extern int CGXDLMSProfileGeneric_Capture_1(CGXDLMSProfileGeneric* p, CGXDLMSServer* server);

//Get attribute values of object.
extern void CGXDLMSProfileGeneric_GetValues(CGXDLMSProfileGeneric* p, Vector* values); //std::vector<std::string>&

extern void CGXDLMSProfileGeneric_GetAttributeIndexToRead(CGXDLMSProfileGeneric* p, Vector* attributes); //std::vector<int>&

//Returns amount of attributes.
extern int CGXDLMSProfileGeneric_GetAttributeCount(CGXDLMSProfileGeneric* p);

//Returns amount of methods.
extern int CGXDLMSProfileGeneric_GetMethodCount(CGXDLMSProfileGeneric* p);

extern int CGXDLMSProfileGeneric_GetDataType(CGXDLMSProfileGeneric* p, int index, DLMS_DATA_TYPE* type);

extern int CGXDLMSProfileGeneric_Invoke(CGXDLMSProfileGeneric* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

/*
* Returns value of given attribute.
*/
extern int CGXDLMSProfileGeneric_GetValue(CGXDLMSProfileGeneric* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

/*
    * Set value of given attribute.
    */
extern int CGXDLMSProfileGeneric_SetValue(CGXDLMSProfileGeneric* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

/**
* Clears the buffer.
*
* @param client
*            DLMS client.
* @param reply
*            Action bytes.
* @return Result code.
*/
extern int CGXDLMSProfileGeneric_Reset_2(CGXDLMSProfileGeneric* p, CGXDLMSClient* client, Vector* reply); //std::vector<CGXByteBuffer>&

/**
* Copies the values of the objects to capture into the buffer by reading
* each capture object.
*
* @param client
*            DLMS client.
* @param reply
*            Action bytes.
* @return Result code.
*/
extern int CGXDLMSProfileGeneric_Capture_2(CGXDLMSProfileGeneric* p, CGXDLMSClient* client, Vector* reply); //std::vector<CGXByteBuffer>&

#endif //GXDLMSPROFILEGENERIC_H
