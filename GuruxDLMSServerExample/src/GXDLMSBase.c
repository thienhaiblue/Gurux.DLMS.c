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

#include <stdio.h>
#if defined(_WIN32) || defined(_WIN64)//Windows includes
#include <tchar.h>
#include <conio.h>
#include <Winsock.h> //Add support for sockets	
#include <time.h>
#include <process.h>//Add support for threads
#else //Linux includes.
#define closesocket close
#include <stdio.h>
#include <pthread.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/socket.h> //Add support for sockets
#include <unistd.h> //Add support for sockets
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include <netdb.h>
#endif

#include "../include/GXDLMSBase.h"

#include "../../development/include/GXTime.h"
#include "../../development/include/GXDate.h"
#include "../../development/include/GXDLMSClient.h"
#include "../../development/include/GXDLMSData.h"
#include "../../development/include/GXDLMSRegister.h"
#include "../../development/include/GXDLMSClock.h"
#include "../../development/include/GXDLMSTcpUdpSetup.h"
#include "../../development/include/GXDLMSProfileGeneric.h"
#include "../../development/include/GXDLMSAutoConnect.h"
#include "../../development/include/GXDLMSIECOpticalPortSetup.h"
#include "../../development/include/GXDLMSActivityCalendar.h"
#include "../../development/include/GXDLMSDemandRegister.h"
#include "../../development/include/GXDLMSRegisterMonitor.h"
#include "../../development/include/GXDLMSActionSchedule.h"
#include "../../development/include/GXDLMSSapAssignment.h"
#include "../../development/include/GXDLMSAutoAnswer.h"
#include "../../development/include/GXDLMSModemConfiguration.h"
#include "../../development/include/GXDLMSMacAddressSetup.h"
#include "../../development/include/GXDLMSModemInitialisation.h"
#include "../../development/include/GXDLMSActionSet.h"
#include "../../development/include/GXDLMSIp4Setup.h"
#include "../../development/include/GXDLMSPushSetup.h"
#include "../../development/include/GXDLMSAssociationLogicalName.h"
#include "../../development/include/GXDLMSAssociationShortName.h"
#include "../../development/include/GXDLMSImageTransfer.h"

#if defined(_WIN32) || defined(_WIN64)//Windows
TCHAR DATAFILE[FILENAME_MAX];
TCHAR IMAGEFILE[FILENAME_MAX];
#else
char DATAFILE[FILENAME_MAX];
char IMAGEFILE[FILENAME_MAX];
#endif
int imageSize;

void ListenerThread(void* pVoid)
{
    CGXByteBuffer reply;
    CGXByteBuffer_1(&reply);

    CGXDLMSBase* server = (CGXDLMSBase*)pVoid;

    struct sockaddr_in add = { 0 };
    int ret;
    char tmp[10];

    CGXByteBuffer bb;
    CGXByteBuffer_1(&bb);

    CGXByteBuffer_Capacity_2(&bb, 2048);
#if defined(_WIN32) || defined(_WIN64)//If Windows
    int len;
    int AddrLen = sizeof(add);
    SOCKET socket;
#else //If Linux
    socklen_t len;
    socklen_t AddrLen = sizeof(add);
    int socket;
#endif
    struct sockaddr_in client;
    memset(&client, 0, sizeof(client));

    //Get buffer data
    //basic_string<char> senderInfo;
    String senderInfo;
    String_(&senderInfo);

    while (CGXDLMSBase_IsConnected(server))
    {
        len = sizeof(client);
        String_clear(&senderInfo);
        socket = accept(CGXDLMSBase_GetSocket(server), (struct sockaddr*)&client, &len);
        CGXDLMSBase_Reset_2(server);
        if (CGXDLMSBase_IsConnected(server))
        {
        	CGXDLMSBase_Reset_2(server);
            if ((ret = getpeername(socket, (struct sockaddr*)&add, &AddrLen)) == -1)
            {
                closesocket(socket);
#if defined(_WIN32) || defined(_WIN64)//If Windows
                socket = INVALID_SOCKET;
#else //If Linux
                socket = -1;
#endif
                continue;
                //Notify error.
            }
            String_copy_2(&senderInfo, inet_ntoa(add.sin_addr));
            String_append_1(&senderInfo, ":");
#if _MSC_VER > 1000
            _ltoa_s(add.sin_port, tmp, 10, 10);
#else
            sprintf(tmp, "%d", add.sin_port);
#endif
            String_append_1(&senderInfo, tmp);
            while (CGXDLMSBase_IsConnected(server))
            {
                //If client is left wait for next client.
                if ((ret = recv(socket, (char*) (bb.m_Data) + bb.m_Size,
                                bb.m_Capacity - bb.m_Size, 0)) == -1)
                {
                    //Notify error.
                    CGXDLMSBase_Reset_2(server);
#if defined(_WIN32) || defined(_WIN64)//If Windows
                    closesocket(socket);
                    socket = INVALID_SOCKET;
#else //If Linux
                    close(socket);
                    socket = -1;
#endif
                    break;
                }
                //If client is closed the connection.
                if (ret == 0)
                {
                    CGXDLMSBase_Reset_2(server);
#if defined(_WIN32) || defined(_WIN64)//If Windows
                    closesocket(socket);
                    socket = INVALID_SOCKET;
#else //If Linux
                    close(socket);
                    socket = -1;
#endif
                    break;
                }
                CGXByteBuffer_SetSize(&bb, bb.m_Size + ret);
                if (server->m_Trace == GX_TRACE_LEVEL_VERBOSE)
                {
                    String str = CGXByteBuffer_ToHexString(&bb);

                    printf("-> %s\r\n", String_c_str(&str));

                    String_d(&str);
                }
                if (CGXDLMSBase_HandleRequest_1(server, &bb, &reply) != 0)
                {
#if defined(_WIN32) || defined(_WIN64)//If Windows
                    closesocket(socket);
                    socket = INVALID_SOCKET;
#else //If Linux
                    close(socket);
                    socket = -1;
#endif
                }
                CGXByteBuffer_SetSize(&bb, 0);
                if (reply.m_Size != 0)
                {
                    if (server->m_Trace == GX_TRACE_LEVEL_VERBOSE)
                    {
                        String str = CGXByteBuffer_ToHexString(&reply);

                        printf("<- %s\r\n", String_c_str(&str));

                        String_d(&str);
                    }
                    if (send(socket, (const char*)(reply.m_Data),
                        reply.m_Size - reply.m_Position, 0) == -1)
                    {
                        //If error has occured
                        CGXDLMSBase_Reset_2(server);
#if defined(_WIN32) || defined(_WIN64)//If Windows
                        closesocket(socket);
                        socket = INVALID_SOCKET;
#else //If Linux
                        close(socket);
                        socket = -1;
#endif
                    }
                    CGXByteBuffer_Clear(&reply);
                }
            }
            CGXDLMSBase_Reset_2(server);
        }
    }

    CGXByteBuffer_d(&reply);
    CGXByteBuffer_d(&bb);
    String_d(&senderInfo);
}

#if defined(_WIN32) || defined(_WIN64)//If Windows
#else //If Linux
void * UnixListenerThread(void * pVoid)
{
    ListenerThread(pVoid);
    return NULL;
}
#endif

bool CGXDLMSBase_IsConnected(CGXDLMSBase* p)
{
#if defined(_WIN32) || defined(_WIN64)//If Windows
    return p->m_ServerSocket != INVALID_SOCKET;
#else //If Linux
    return p->m_ServerSocket != -1;
#endif
}

int CGXDLMSBase_GetSocket(CGXDLMSBase* p)
{
    return (int)p->m_ServerSocket;
}

int CGXDLMSBase_StartServer(CGXDLMSBase* p, int port)
{
    int ret;
    if ((ret = CGXDLMSBase_StopServer(p)) != 0)
    {
        return ret;
    }
    p->m_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (!CGXDLMSBase_IsConnected(p))
    {
        //socket creation.
        return -1;
    }
    int fFlag = 1;
    if (setsockopt(p->m_ServerSocket, SOL_SOCKET, SO_REUSEADDR,
                   (char *)&fFlag, sizeof(fFlag)) == -1)
    {
        //setsockopt.
        return -1;
    }
    struct sockaddr_in add = { 0 };
    add.sin_port = htons(port);
    add.sin_addr.s_addr = htonl(INADDR_ANY);
#if defined(_WIN32) || defined(_WIN64)//Windows includes
    add.sin_family = AF_INET;
#else
    add.sin_family = AF_INET;
#endif
    if ((ret = bind(p->m_ServerSocket, (struct sockaddr*)&add, sizeof(add))) == -1)
    {
        //bind;
        return -1;
    }
    if ((ret = listen(p->m_ServerSocket, 1)) == -1)
    {
        //socket listen failed.
        return -1;
    }
#if defined(_WIN32) || defined(_WIN64)//Windows includes
    p->m_ReceiverThread = (HANDLE)_beginthread(ListenerThread, 0, (LPVOID)p);
#else
    ret = pthread_create(&p->m_ReceiverThread, NULL, UnixListenerThread, (void *)p);
#endif
    return ret;
}

int CGXDLMSBase_StopServer(CGXDLMSBase* p)
{
    if (CGXDLMSBase_IsConnected(p))
    {
#if defined(_WIN32) || defined(_WIN64)//Windows includes
        closesocket(p->m_ServerSocket);
        p->m_ServerSocket = INVALID_SOCKET;
        if (p->m_ReceiverThread != INVALID_HANDLE_VALUE)
        {
            int ret = WaitForSingleObject(p->m_ReceiverThread, 5000);
            p->m_ReceiverThread = INVALID_HANDLE_VALUE;
        }
#else
        close(p->m_ServerSocket);
        p->m_ServerSocket = -1;
        void *res;
        pthread_join(p->m_ReceiverThread, (void **)&res);
        free(res);
#endif
    }
    return 0;
}

int GetIpAddress(String* address)
{
    int ret;
    struct hostent *phe;
    char ac[80];
    if ((ret = gethostname(ac, sizeof(ac))) == 0)
    {
        phe = gethostbyname(ac);
        if (phe == 0)
        {
            ret = -1;
        }
        else
        {
            struct in_addr* addr = (struct in_addr*)phe->h_addr_list[0];
            String_copy_2(address, inet_ntoa(*addr));
        }
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////
//Add Logical Device Name. 123456 is meter serial number.
///////////////////////////////////////////////////////////////////////
// COSEM Logical Device Name is defined as an octet-string of 16 octets.
// The first three octets uniquely identify the manufacturer of the device and it corresponds
// to the manufacturer's identification in IEC 62056-21.
// The following 13 octets are assigned by the manufacturer.
//The manufacturer is responsible for guaranteeing the uniqueness of these octets.
CGXDLMSData* AddLogicalDeviceName(CGXDLMSObjectCollection* items, unsigned long sn)
{
    char buff[17];
#if defined(_WIN32) || defined(_WIN64)//Windows
    sprintf(buff, "GRX%.13d", sn);
#else
    sprintf(buff, "GRX%.13d", sn);
#endif
    CGXDLMSVariant id;
    CGXDLMSVariant_1(&id);

    CGXDLMSVariant_Add_2(&id, (const char*)buff, 16);

    // CGXDLMSData* ldn = new CGXDLMSData("0.0.42.0.0.255");
    String str;
    String_3(&str, "0.0.42.0.0.255");

    CGXDLMSData* ldn = DLMSPort_malloc(sizeof(CGXDLMSData));
    CGXDLMSData_3(ldn, str);

    String_d(&str);

    CGXDLMSData_SetValue_1(ldn, &id);
    CGXDLMSObjectCollection_push_back(items, &ldn);

    CGXDLMSVariant_d(&id);
    return ldn;
}

/*
* Add firmware version.
*/
void AddFirmwareVersion(CGXDLMSObjectCollection* items)
{
    CGXDLMSVariant version;
    CGXDLMSVariant_1(&version);

    CGXDLMSVariant_copy_3(&version, "Gurux FW 0.0.1");

    //CGXDLMSData* fw = new CGXDLMSData("1.0.0.2.0.255");
    String str;
    String_3(&str, "1.0.0.2.0.255");

    CGXDLMSData* fw = DLMSPort_malloc(sizeof(CGXDLMSData));
    CGXDLMSData_3(fw, str);

    String_d(&str);


    CGXDLMSData_SetValue_1(fw, &version);
    CGXDLMSObjectCollection_push_back(items, &fw);

    CGXDLMSVariant_d(&version);
}

/*
* Add Electricity ID 1.
*/
void AddElectricityID1(CGXDLMSObjectCollection* items, unsigned long sn)
{
    char buff[17];
#if defined(_WIN32) || defined(_WIN64)//Windows
    sprintf(buff, "GRX%.13d", sn);
#else
    sprintf(buff, "GRX%.13d", sn);
#endif
    CGXDLMSVariant id;
    CGXDLMSVariant_1(&id);

    CGXDLMSVariant_Add_2(&id, (const char*)buff, 16);

    // CGXDLMSData* d = new CGXDLMSData("1.1.0.0.0.255");
    String str;
    String_3(&str, "1.1.0.0.0.255");

    CGXDLMSData* d = DLMSPort_malloc(sizeof(CGXDLMSData));
    CGXDLMSData_3(d, str);

    String_d(&str);

    CGXDLMSData_SetValue_1(d, &id);

    CGXDLMSAttribute att;
    CGXDLMSAttribute_(&att, 2, DLMS_DATA_TYPE_STRING,
                      DLMS_DATA_TYPE_NONE, DLMS_ACCESS_MODE_READ, -1);

    CGXDLMSObjectCollection_push_back(CGXDLMSData_GetAttributes(d), &att);

    // Do not CGXDLMSAttribute_d(&att);

    CGXDLMSObjectCollection_push_back(items, &d);

    CGXDLMSVariant_d(&id);
}

/*
* Add Electricity ID 2.
*/
void AddElectricityID2(CGXDLMSObjectCollection* items, unsigned long sn)
{
    CGXDLMSVariant id2;
    CGXDLMSVariant_21(&id2, sn);

    // CGXDLMSData* d = new CGXDLMSData("1.1.0.0.1.255");
    String str;
    String_3(&str, "1.1.0.0.1.255");

    CGXDLMSData* d = DLMSPort_malloc(sizeof(CGXDLMSData));
    CGXDLMSData_3(d, str);

    String_d(&str);

    //d->SetValue(id2);
    //d->GetAttributes().push_back(CGXDLMSAttribute(2, DLMS_DATA_TYPE_UINT32));
    //items.push_back(d);
    CGXDLMSData_SetValue_1(d, &id2);

    CGXDLMSAttribute att;
    CGXDLMSAttribute_(&att, 2, DLMS_DATA_TYPE_UINT32,
                      DLMS_DATA_TYPE_NONE, DLMS_ACCESS_MODE_READ, -1);

    CGXDLMSObjectCollection_push_back(CGXDLMSData_GetAttributes(d), &att);

    // Do not CGXDLMSAttribute_d(&att);

    CGXDLMSObjectCollection_push_back(items, &d);

    CGXDLMSVariant_d(&id2);
}

/*
* Add Auto connect object.
*/
void AddAutoConnect(CGXDLMSObjectCollection* items)
{
    //CGXDLMSAutoConnect* pAC = new CGXDLMSAutoConnect();
    CGXDLMSAutoConnect* pAC = DLMSPort_malloc(sizeof(CGXDLMSAutoConnect));
    CGXDLMSAutoConnect_1(pAC);

    pAC->m_Mode = AUTO_CONNECT_MODE_AUTO_DIALLING_ALLOWED_ANYTIME;
    pAC->m_Repetitions = 10;
    pAC->m_RepetitionDelay = 60;

    //Calling is allowed between 1am to 6am.
    //pAC->GetCallingWindow().push_back(std::make_pair(CGXTime(1, 0, 0, -1), CGXTime(6, 0, 0, -1)));
    CGXTime t1;
    CGXTime_3(&t1, 1, 0, 0, -1);

    CGXTime t2;
    CGXTime_3(&t2, 6, 0, 0, -1);

    Pair pair;
    Pair_(&pair, sizeof(CGXDateTime), sizeof(CGXDateTime),
          NULL, NULL, NULL, NULL, &t1, &t2);

    Vector_push_back(CGXDLMSAutoConnect_GetCallingWindow(pAC), &pair);

    Pair_d(&pair);

    // pAC->GetDestinations().push_back("www.gurux.org");
    String str;
    String_3(&str, "www.gurux.org");

    Vector_push_back(CGXDLMSAutoConnect_GetDestinations(pAC), &str);

    String_d(&str);

    //items.push_back(pAC);
    CGXDLMSObjectCollection_push_back(items, &pAC);
}

/*
* Add Activity Calendar object.
*/
void AddActivityCalendar(CGXDLMSObjectCollection* items)
{
    //CGXDLMSActivityCalendar* pActivity = new CGXDLMSActivityCalendar();
	CGXDLMSActivityCalendar* pActivity = DLMSPort_malloc(sizeof(CGXDLMSActivityCalendar));
	CGXDLMSActivityCalendar_1(pActivity);

	String str;
	String_3(&str, "Active");

    CGXDLMSActivityCalendar_SetCalendarNameActive(pActivity, str);

    String_d(&str);

    // pActivity->GetSeasonProfileActive().push_back(new CGXDLMSSeasonProfile("Summer time", CGXDate(-1, 3, 31), ""));
    String name;
    String_3(&name, "Summer time");

    String weekName;
    String_3(&weekName, "");

    CGXDate start;
    CGXDate_3(&start, -1, 3, 31);

    CGXDLMSSeasonProfile* pss = DLMSPort_malloc(sizeof(CGXDLMSSeasonProfile));
    CGXDLMSSeasonProfile_2(pss, name, *((CGXDateTime*) &start), weekName);

    Vector_push_back(CGXDLMSActivityCalendar_GetSeasonProfileActive(pActivity), &pss);

    String_d(&name);
    String_d(&weekName);

    //pActivity->GetWeekProfileTableActive().push_back(new CGXDLMSWeekProfile("Monday", 1, 1, 1, 1, 1, 1, 1));
    String_3(&name, "Monday");

    CGXDLMSWeekProfile* pwp = DLMSPort_malloc(sizeof(CGXDLMSWeekProfile));
    CGXDLMSWeekProfile_2(pwp, name, 1, 1, 1, 1, 1, 1, 1);

    Vector_push_back(CGXDLMSActivityCalendar_GetWeekProfileTableActive(pActivity), &pwp);

    String_d(&name);

    //CGXDLMSDayProfile *aDp = new CGXDLMSDayProfile();
    CGXDLMSDayProfile *aDp = DLMSPort_malloc(sizeof(CGXDLMSDayProfile));
    CGXDLMSDayProfile_1(aDp);

    aDp->m_DayId = 1;

    CGXDateTime now = CGXDateTime_Now();
    CGXTime time;
    CGXTime_4(&time, &now);

    // new CGXDLMSDayProfileAction(time, "test", 1)
    String_3(&name, "test");

    CGXDLMSDayProfileAction* ppa = DLMSPort_malloc(sizeof(CGXDLMSDayProfileAction));
    CGXDLMSDayProfileAction_2(ppa, &time, name, 1);

    Vector_push_back(CGXDLMSDayProfile_GetDaySchedules(aDp), &ppa);

    String_d(&name);

    //pActivity->GetDayProfileTableActive().push_back(aDp);
    Vector_push_back(CGXDLMSActivityCalendar_GetDayProfileTableActive(pActivity), &aDp);

    //pActivity->SetCalendarNamePassive("Passive");
    String value;
    String_3(&value, "Passive");

    CGXDLMSActivityCalendar_SetCalendarNamePassive(pActivity, value);

    String_d(&value);

    //pActivity->GetSeasonProfilePassive().push_back(new CGXDLMSSeasonProfile("Winter time", CGXDate(-1, 10, 30), ""));
    String_3(&name, "Winter time");

    String_3(&weekName, "");

    CGXDate_3(&start, -1, 10, 30);

    CGXDLMSSeasonProfile* pss2 = DLMSPort_malloc(sizeof(CGXDLMSSeasonProfile));
    CGXDLMSSeasonProfile_2(pss2, name, *((CGXDateTime*) &start), weekName);

    Vector_push_back(CGXDLMSActivityCalendar_GetSeasonProfilePassive(pActivity), &pss2);

    String_d(&name);
    String_d(&weekName);

    //pActivity->GetWeekProfileTablePassive().push_back(new CGXDLMSWeekProfile("Tuesday", 1, 1, 1, 1, 1, 1, 1));
    String_3(&name, "Tuesday");

    CGXDLMSWeekProfile* pwp2 = DLMSPort_malloc(sizeof(CGXDLMSWeekProfile));
    CGXDLMSWeekProfile_2(pwp2, name, 1, 1, 1, 1, 1, 1, 1);

    Vector_push_back(CGXDLMSActivityCalendar_GetWeekProfileTablePassive(pActivity), &pwp2);

    String_d(&name);

    //CGXDLMSDayProfile* passive = new CGXDLMSDayProfile();
    CGXDLMSDayProfile* passive = DLMSPort_malloc(sizeof(CGXDLMSDayProfile));
    CGXDLMSDayProfile_1(passive);

    passive->m_DayId = 1;

    //passive->GetDaySchedules().push_back(new CGXDLMSDayProfileAction(time, "0.0.1.0.0.255", 1));
    String_3(&name, "0.0.1.0.0.255");

    CGXDLMSDayProfileAction* ppa2 = DLMSPort_malloc(sizeof(CGXDLMSDayProfileAction));
    CGXDLMSDayProfileAction_2(ppa2, &time, name, 1);

    Vector_push_back(CGXDLMSDayProfile_GetDaySchedules(passive), &ppa2);

    String_d(&name);

    //pActivity->GetDayProfileTablePassive().push_back(passive);
    Vector_push_back(CGXDLMSActivityCalendar_GetDayProfileTablePassive(pActivity), &passive);

    CGXDateTime dt = CGXDateTime_Now();

    pActivity->m_Time = dt;

    CGXDLMSObjectCollection_push_back(items, &pActivity);
}

/*
* Add Optical Port Setup object.
*/
void AddOpticalPortSetup(CGXDLMSObjectCollection* items)
{
    //CGXDLMSIECOpticalPortSetup* pOptical = new CGXDLMSIECOpticalPortSetup();
    CGXDLMSIECOpticalPortSetup* pOptical = DLMSPort_malloc(sizeof(CGXDLMSIECOpticalPortSetup));
    CGXDLMSIECOpticalPortSetup_1(pOptical);

    pOptical->m_DefaultMode = DLMS_OPTICAL_PROTOCOL_MODE_DEFAULT;
    pOptical->m_ProposedBaudrate = DLMS_BAUD_RATE_9600;
    pOptical->m_DefaultBaudrate = DLMS_BAUD_RATE_300;
    pOptical->m_ResponseTime = DLMS_LOCAL_PORT_RESPONSE_TIME_200_MS;

    String str;
    String_3(&str, "Gurux");

    CGXDLMSIECOpticalPortSetup_SetDeviceAddress(pOptical, str);

    String_d(&str);

    String_3(&str, "Gurux1");

    CGXDLMSIECOpticalPortSetup_SetPassword1(pOptical, str);

    String_d(&str);

    String_3(&str, "Gurux2");

    CGXDLMSIECOpticalPortSetup_SetPassword2(pOptical, str);

    String_d(&str);

    String_3(&str, "Gurux5");

    CGXDLMSIECOpticalPortSetup_SetPassword5(pOptical, str);

    String_d(&str);

    CGXDLMSObjectCollection_push_back(items, &pOptical);
}

/*
* Add Demand Register object.
*/
void AddDemandRegister(CGXDLMSObjectCollection* items)
{
    //CGXDLMSDemandRegister* pDr = new CGXDLMSDemandRegister("0.0.1.0.0.255");
    String str;
    String_3(&str, "0.0.1.0.0.255");

	CGXDLMSDemandRegister* pDr = DLMSPort_malloc(sizeof(CGXDLMSDemandRegister));
	CGXDLMSDemandRegister_2(pDr, str);

	String_d(&str);

	CGXDLMSVariant var1;
	CGXDLMSVariant_10(&var1, 10);

    CGXDLMSDemandRegister_SetCurrentAvarageValue(pDr, var1);

    CGXDLMSVariant_d(&var1);

	CGXDLMSVariant var2;
	CGXDLMSVariant_10(&var2, 20);

    CGXDLMSDemandRegister_SetLastAvarageValue(pDr, var2);

    CGXDLMSVariant_d(&var2);

	CGXDLMSVariant var3;
	CGXDLMSVariant_10(&var3, 1);

    CGXDLMSDemandRegister_SetStatus(pDr, var3);

    CGXDLMSVariant_d(&var3);

    pDr->m_StartTimeCurrent = CGXDateTime_Now();
    pDr->m_CaptureTime = CGXDateTime_Now();
    pDr->m_Period = 10;
    pDr->m_NumberOfPeriods = 1;

    // items.push_back(pDr);
    CGXDLMSObjectCollection_push_back(items, &pDr);
}

/*
* Add Register Monitor object.
*/
void AddRegisterMonitor(CGXDLMSObjectCollection* items, CGXDLMSRegister* pRegister)
{
    //CGXDLMSRegisterMonitor* pRm = new CGXDLMSRegisterMonitor("0.0.1.0.0.255");
    String str;
    String_3(&str, "0.0.1.0.0.255");

    CGXDLMSRegisterMonitor* pRm = DLMSPort_malloc(sizeof(CGXDLMSRegisterMonitor));
    CGXDLMSRegisterMonitor_2(pRm, str);

    String_d(&str);

    CGXDLMSVariant threshold;
    CGXDLMSVariant_1(&threshold);

    Vector thresholds; // vector<CGXDLMSVariant>
    Vector_(&thresholds, sizeof(CGXDLMSVariant), CGXDLMSVariant_v_c, CGXDLMSVariant_v_d);

    CGXDLMSVariant_Add_2(&threshold, "Gurux1", 6);

    Vector_push_back(&thresholds, &threshold);

    CGXDLMSVariant_Clear(&threshold);

    CGXDLMSVariant_Add_2(&threshold, "Gurux2", 6);

    Vector_push_back(&thresholds, &threshold);

    CGXDLMSRegisterMonitor_SetThresholds(pRm, thresholds);

    Vector_d(&thresholds);
    CGXDLMSVariant_d(&threshold);


    CGXDLMSMonitoredValue mv;
    CGXDLMSMonitoredValue_(&mv);

    CGXDLMSMonitoredValue_Update(&mv, (CGXDLMSObject*) pRegister, 2);

    CGXDLMSRegisterMonitor_SetMonitoredValue(pRm, &mv);

    CGXDLMSMonitoredValue_d(&mv);


    //CGXDLMSActionSet * action = new CGXDLMSActionSet();
    CGXDLMSActionSet* action = DLMSPort_malloc(sizeof(CGXDLMSActionSet));
    CGXDLMSActionSet_(action);

    String ln;
    String_(&ln);

    CGXDLMSRegisterMonitor_GetLogicalName_2(pRm, &ln);
    CGXDLMSActionItem_SetLogicalName(&(action->m_ActionDown), ln);
    action->m_ActionDown.m_ScriptSelector = 1;

    CGXDLMSRegisterMonitor_GetLogicalName_2(pRm, &ln);
    CGXDLMSActionItem_SetLogicalName(&action->m_ActionUp, ln);
    action->m_ActionUp.m_ScriptSelector = 1;

    String_d(&ln);

    Vector_push_back(CGXDLMSRegisterMonitor_GetActions(pRm), &action);

    CGXDLMSObjectCollection_push_back(items, &pRm);
}

/*
* Add action schedule object.
*/
void AddActionSchedule(CGXDLMSObjectCollection* items)
{
    //CGXDLMSActionSchedule* pActionS = new CGXDLMSActionSchedule("0.0.1.0.0.255");
    String str;
    String_3(&str, "0.0.1.0.0.255");

    CGXDLMSActionSchedule* pActionS = DLMSPort_malloc(sizeof(CGXDLMSActionSchedule));
    CGXDLMSActionSchedule_2(pActionS, str);

	String_d(&str);

	String_3(&str, "1.2.3.4.5.6");

    CGXDLMSActionSchedule_SetExecutedScriptLogicalName(pActionS, str);

    String_d(&str);

    pActionS->m_ExecutedScriptSelector = 1;
    pActionS->m_Type = DLMS_SINGLE_ACTION_SCHEDULE_TYPE1;

    CGXDateTime now = CGXDateTime_Now();

    Vector_push_back(CGXDLMSActionSchedule_GetExecutionTime(pActionS), &now);

    CGXDLMSObjectCollection_push_back(items, &pActionS);
}

/*
* Add SAP Assignment object.
*/
void AddSapAssignment(CGXDLMSObjectCollection* items)
{
    //CGXDLMSSapAssignment* pSap = new CGXDLMSSapAssignment();
    CGXDLMSSapAssignment* pSap = DLMSPort_malloc(sizeof(CGXDLMSSapAssignment));
    CGXDLMSSapAssignment_1(pSap);

    //std::map<int, basic_string<char> > list;
    //list[1] = "Gurux";
    //list[16] = "Gurux-2";
    Map list;
    Map_(&list, sizeof(int), sizeof(String),
         NULL, NULL, String_v_c, String_v_d);

    int key = 1;
    String item;
    String_3(&item, "Gurux");

    Map_insert(&list, &key, &item);

    String_d(&item);

    key = 16;
    String_3(&item, "Gurux-2");

    Map_insert(&list, &key, &item);

    String_d(&item);

    CGXDLMSSapAssignment_SetSapAssignmentList(pSap, &list);

    Map_d(&list);

    CGXDLMSObjectCollection_push_back(items, &pSap);
}

/**
* Add Auto Answer object.
*/
void AddAutoAnswer(CGXDLMSObjectCollection* items)
{
    //CGXDLMSAutoAnswer* pAa = new CGXDLMSAutoAnswer();
	CGXDLMSAutoAnswer* pAa = DLMSPort_malloc(sizeof(CGXDLMSAutoAnswer));
	CGXDLMSAutoAnswer_1(pAa);

    pAa->m_Mode = AUTO_CONNECT_MODE_EMAIL_SENDING;

    //pAa->GetListeningWindow(pAa).push_back(std::pair<CGXDateTime, CGXDateTime>(CGXDateTime(-1, -1, -1, 6, -1, -1, -1), CGXDateTime(-1, -1, -1, 8, -1, -1, -1)));
    CGXDateTime t1;
    CGXDateTime_4(&t1, -1, -1, -1, 6, -1, -1, -1);

    CGXDateTime t2;
    CGXDateTime_4(&t2, -1, -1, -1, 8, -1, -1, -1);

    Pair pair;
    Pair_(&pair, sizeof(CGXDateTime), sizeof(CGXDateTime),
          NULL, NULL, NULL, NULL, &t1, &t2);

    Vector_push_back(CGXDLMSAutoAnswer_GetListeningWindow(pAa), &pair);

    Pair_d(&pair);

    pAa->m_Status = AUTO_ANSWER_STATUS_INACTIVE;
    pAa->m_NumberOfCalls = 0;
    pAa->m_NumberOfRingsInListeningWindow = 1;
    pAa->m_NumberOfRingsOutListeningWindow = 2;

    CGXDLMSObjectCollection_push_back(items, &pAa);
}

/*
* Add Modem Configuration object.
*/
void AddModemConfiguration(CGXDLMSObjectCollection* items)
{
    // CGXDLMSModemConfiguration* pMc = new CGXDLMSModemConfiguration();
	CGXDLMSModemConfiguration* pMc = DLMSPort_malloc(sizeof(CGXDLMSModemConfiguration));
	CGXDLMSModemConfiguration_1(pMc);

    pMc->m_CommunicationSpeed = DLMS_BAUD_RATE_38400;

    CGXDLMSModemInitialisation init;
    CGXDLMSModemInitialisation_(&init);

    Vector initialisationStrings; // vector<CGXDLMSModemInitialisation>
    Vector_(&initialisationStrings, sizeof(CGXDLMSModemInitialisation),
    		CGXDLMSModemInitialisation_v_c, CGXDLMSModemInitialisation_v_d);

    String str;
    String_3(&str, "AT");

    CGXDLMSModemInitialisation_SetRequest(&init, str);

    String_d(&str);

    String_3(&str, "OK");

    CGXDLMSModemInitialisation_SetResponse(&init, str);

    String_d(&str);

    init.m_Delay = 0;

    Vector_push_back(&initialisationStrings, &init);

    CGXDLMSModemConfiguration_SetInitialisationStrings(pMc, &initialisationStrings);

    Vector_d(&initialisationStrings);
    CGXDLMSModemInitialisation_d(&init);

    CGXDLMSObjectCollection_push_back(items, &pMc);
}

/**
* Add MAC Address Setup object.
*/
void AddMacAddressSetup(CGXDLMSObjectCollection* items)
{
    // CGXDLMSMacAddressSetup* pMac = new CGXDLMSMacAddressSetup();
	CGXDLMSMacAddressSetup* pMac = DLMSPort_malloc(sizeof(CGXDLMSMacAddressSetup));
	CGXDLMSMacAddressSetup_1(pMac);

    String str;
    String_3(&str, "00:11:22:33:44:55:66");

    CGXDLMSMacAddressSetup_SetMacAddress(pMac, str);

    String_d(&str);

    CGXDLMSObjectCollection_push_back(items, &pMac);
}

/**
* Add IP4 setup object.
*/
CGXDLMSIp4Setup* AddIp4Setup(CGXDLMSObjectCollection* items, String* address)
{
    //CGXDLMSIp4Setup* pIp4 = new CGXDLMSIp4Setup();
	CGXDLMSIp4Setup* pIp4 = DLMSPort_malloc(sizeof(CGXDLMSIp4Setup));
	CGXDLMSIp4Setup_1(pIp4);

    CGXDLMSIp4Setup_SetIPAddress(pIp4, address);

    CGXDLMSObjectCollection_push_back(items, &pIp4);

    return pIp4;
}

/*
* Generic initialize for all servers.
*/
int CGXDLMSBase_Init(CGXDLMSBase* p, int port, GX_TRACE_LEVEL trace)
{
    int ret;
    p->m_Trace = trace;
    if ((ret = CGXDLMSBase_StartServer(p, port)) != 0)
    {
        return ret;
    }
    //Get local IP address.
    String address;
    String_(&address);

    GetIpAddress(&address);

    unsigned long sn = 123456;
    CGXDLMSData* ldn = AddLogicalDeviceName(CGXDLMSBase_GetItems(p), sn);
    //Add firmaware.
    AddFirmwareVersion(CGXDLMSBase_GetItems(p));
    AddElectricityID1(CGXDLMSBase_GetItems(p), sn);
    AddElectricityID2(CGXDLMSBase_GetItems(p), sn);

    //Add Last avarage.
    //CGXDLMSRegister* pRegister = new CGXDLMSRegister("1.1.21.25.0.255");
    String str;
    String_3(&str, "1.1.21.25.0.255");

    CGXDLMSRegister* pRegister = DLMSPort_malloc(sizeof(CGXDLMSRegister));
    CGXDLMSRegister_4(pRegister, str);

	String_d(&str);

    //Set access right. Client can't change Device name.
    CGXDLMSRegister_SetAccess(pRegister, 2, DLMS_ACCESS_MODE_READ);

    CGXDLMSObjectCollection_push_back(CGXDLMSBase_GetItems(p), &pRegister);

    //Add default clock. Clock's Logical Name is 0.0.1.0.0.255.
    //CGXDLMSClock* pClock = new CGXDLMSClock();
    CGXDLMSClock* pClock = DLMSPort_malloc(sizeof(CGXDLMSClock));
    CGXDLMSClock_1(pClock);

    CGXDateTime begin;
    CGXDateTime_4(&begin, -1, 9, 1, -1, -1, -1, -1);

    pClock->m_Begin = begin;

    CGXDateTime end;
    CGXDateTime_4(&end, -1, 3, 1, -1, -1, -1, -1);

    pClock->m_End = end;

    CGXDLMSObjectCollection_push_back(CGXDLMSBase_GetItems(p), &pClock);

    ///////////////////////////////////////////////////////////////////////
    //Add profile generic (historical data) object.
    //CGXDLMSProfileGeneric* profileGeneric = new CGXDLMSProfileGeneric("1.0.99.1.0.255");
    String_3(&str, "1.0.99.1.0.255");

    CGXDLMSProfileGeneric* profileGeneric = DLMSPort_malloc(sizeof(CGXDLMSProfileGeneric));
    CGXDLMSProfileGeneric_3(profileGeneric, str);

	String_d(&str);

    //Set capture period to 60 second.
    profileGeneric->m_CapturePeriod = 60;
    profileGeneric->m_SortMethod = DLMS_SORT_METHOD_FIFO;
    profileGeneric->m_SortObject = (CGXDLMSObject*) pClock;

    //Add colums.
    //Set saved attribute index.
    //CGXDLMSCaptureObject * capture = new CGXDLMSCaptureObject(2, 0);
    CGXDLMSCaptureObject* capture = DLMSPort_malloc(sizeof(CGXDLMSCaptureObject));
    CGXDLMSCaptureObject_2(capture, 2, 0);

    Pair pair1;
    Pair_(&pair1, sizeof(CGXDLMSObject*), sizeof(CGXDLMSCaptureObject*),
    	  NULL, NULL, NULL, NULL, &pClock, &capture);

    Vector_push_back(CGXDLMSProfileGeneric_GetCaptureObjects(profileGeneric), &pair1);

    Pair_d(&pair1);

    //Set saved attribute index.
    //capture = new CGXDLMSCaptureObject(2, 0);
    capture = DLMSPort_malloc(sizeof(CGXDLMSCaptureObject));
    CGXDLMSCaptureObject_2(capture, 2, 0);

    Pair pair2;
    Pair_(&pair2, sizeof(CGXDLMSObject*), sizeof(CGXDLMSCaptureObject*),
    	  NULL, NULL, NULL, NULL, &pRegister, &capture);

    Vector_push_back(CGXDLMSProfileGeneric_GetCaptureObjects(profileGeneric), &pair2);

    Pair_d(&pair2);

    CGXDLMSObjectCollection_push_back(CGXDLMSBase_GetItems(p), &profileGeneric);

    // Create 10 000 rows for profile generic file.
    // In example profile generic we have two columns.
    // Date time and integer value.
    int rowCount = 10000;
    CGXDateTime tm = CGXDateTime_Now();

    CGXDateTime_AddMinutes(&tm, -tm.m_Value.tm_min);
    CGXDateTime_AddSeconds(&tm, tm.m_Value.tm_sec);
    CGXDateTime_AddHours(&tm, -(rowCount - 1));

#if defined(_WIN32) || defined(_WIN64)//Windows
    FILE* f = fopen(DATAFILE, _T("w"));
#else
    FILE* f = fopen(DATAFILE, "w");
#endif
    for (int pos = 0; pos != rowCount; ++pos)
    {
    	String tmp = CGXDateTime_ToString(&tm);

        fprintf(f, "%s;%d\n", String_c_str(&tmp), pos + 1);

        String_d(&tmp);

        CGXDateTime_AddHours(&tm, 1);
    }
    fclose(f);
    //Maximum row count.
    profileGeneric->m_EntriesInUse = rowCount;
    profileGeneric->m_ProfileEntries = rowCount;

    ///////////////////////////////////////////////////////////////////////
    //Add Auto connect object.
    AddAutoConnect(CGXDLMSBase_GetItems(p));

    ///////////////////////////////////////////////////////////////////////
    //Add Activity Calendar object.
    AddActivityCalendar(CGXDLMSBase_GetItems(p));

    ///////////////////////////////////////////////////////////////////////
    //Add Optical Port Setup object.
    AddOpticalPortSetup(CGXDLMSBase_GetItems(p));
    ///////////////////////////////////////////////////////////////////////
    //Add Demand Register object.
    AddDemandRegister(CGXDLMSBase_GetItems(p));

    ///////////////////////////////////////////////////////////////////////
    //Add Register Monitor object.
    AddRegisterMonitor(CGXDLMSBase_GetItems(p), pRegister);

    ///////////////////////////////////////////////////////////////////////
    //Add action schedule object.
    AddActionSchedule(CGXDLMSBase_GetItems(p));

    ///////////////////////////////////////////////////////////////////////
    //Add SAP Assignment object.
    AddSapAssignment(CGXDLMSBase_GetItems(p));

    ///////////////////////////////////////////////////////////////////////
    //Add Auto Answer object.
    AddAutoAnswer(CGXDLMSBase_GetItems(p));

    ///////////////////////////////////////////////////////////////////////
    //Add Modem Configuration object.
    AddModemConfiguration(CGXDLMSBase_GetItems(p));

    ///////////////////////////////////////////////////////////////////////
    //Add Mac Address Setup object.
    AddMacAddressSetup(CGXDLMSBase_GetItems(p));
    ///////////////////////////////////////////////////////////////////////
    //Add IP4 Setup object.
    CGXDLMSIp4Setup* pIp4 = AddIp4Setup(CGXDLMSBase_GetItems(p), &address);

    ///////////////////////////////////////////////////////////////////////
    //Add Push Setup object.
    // CGXDLMSPushSetup* pPush = new CGXDLMSPushSetup();
    CGXDLMSPushSetup* pPush = DLMSPort_malloc(sizeof(CGXDLMSPushSetup));
    CGXDLMSPushSetup_1(pPush);

    CGXDLMSPushSetup_SetDestination(pPush, &address);

    CGXDLMSObjectCollection_push_back(CGXDLMSBase_GetItems(p), &pPush);

    // Add push object itself. This is needed to tell structure of data to
    // the Push listener.
    // CGXDLMSPushSetup_GetPushObjectList(pPush).push_back(std::pair<CGXDLMSObject*, CGXDLMSCaptureObject>(pPush, CGXDLMSCaptureObject(2, 0)));
    CGXDLMSCaptureObject t_cap;
    CGXDLMSCaptureObject_2(&t_cap, 2, 0);

    Pair pair3;
    Pair_(&pair3, sizeof(CGXDLMSObject*), sizeof(CGXDLMSCaptureObject),
    	  NULL, NULL, NULL, NULL, &pPush, &t_cap);

    Vector_push_back(CGXDLMSPushSetup_GetPushObjectList(pPush), &pair3);

    Pair_d(&pair3);

    //Add logical device name.
    //pPush->GetPushObjectList().push_back(std::pair<CGXDLMSObject*, CGXDLMSCaptureObject>(ldn, CGXDLMSCaptureObject(2, 0)));
    Pair pair4;
    Pair_(&pair4, sizeof(CGXDLMSObject*), sizeof(CGXDLMSCaptureObject),
    	  NULL, NULL, NULL, NULL, &ldn, &t_cap);

    Vector_push_back(CGXDLMSPushSetup_GetPushObjectList(pPush), &pair4);

    Pair_d(&pair4);

    // Add 0.0.25.1.0.255 Ch. 0 IPv4 setup IP address.
    //pPush->GetPushObjectList().push_back(std::pair<CGXDLMSObject*, CGXDLMSCaptureObject>(pIp4, CGXDLMSCaptureObject(3, 0)));
    CGXDLMSCaptureObject_2(&t_cap, 3, 0);

    Pair pair5;
    Pair_(&pair5, sizeof(CGXDLMSObject*), sizeof(CGXDLMSCaptureObject),
    	  NULL, NULL, NULL, NULL, &pIp4, &t_cap);

    Vector_push_back(CGXDLMSPushSetup_GetPushObjectList(pPush), &pair5);

    Pair_d(&pair5);

    ///////////////////////////////////////////////////////////////////////
    //Add image transfer object.
    //CGXDLMSImageTransfer* image = new CGXDLMSImageTransfer();
    CGXDLMSImageTransfer* image = DLMSPort_malloc(sizeof(CGXDLMSImageTransfer));
    CGXDLMSImageTransfer_1(image);

    CGXDLMSObjectCollection_push_back(CGXDLMSBase_GetItems(p), &image);

    String_d(&address);

    ///////////////////////////////////////////////////////////////////////
    //Server must initialize after all objects are added.
    ret = CGXDLMSBase_Initialize(p);
    if (ret != DLMS_ERROR_CODE_OK)
    {
        return ret;
    }
    return DLMS_ERROR_CODE_OK;
}

CGXDLMSObject* CGXDLMSBase_FindObject(CGXDLMSBase* p,
        							  DLMS_OBJECT_TYPE objectType,
									  int sn,
									  String* ln)
{
    return NULL;
}

/**
* Return data using start and end indexes.
*
* @param p
*            ProfileGeneric
* @param index
* @param count
* @return Add data Rows
*/
void GetProfileGenericDataByEntry(CGXDLMSProfileGeneric* p, long index, long count)
{
    int len, month = 0, day = 0, year = 0, hour = 0, minute = 0, second = 0, value = 0;
    // Clear old data. It's already serialized.
    Vector_clear(CGXDLMSProfileGeneric_GetBuffer(p));
    if (count != 0)
    {
#if defined(_WIN32) || defined(_WIN64)//Windows
        FILE* f = fopen(DATAFILE, _T("r"));
#else
        FILE* f = fopen(DATAFILE, "r");
#endif
        if (f != NULL)
        {
#if defined(_WIN32) || defined(_WIN64)//Windows
            while ((len = fscanf(f, "%d/%d/%d %d:%d:%d;%d", &month, &day, &year, &hour, &minute, &second, &value)) != -1)
#else
            while ((len = fscanf(f, "%d/%d/%d %d:%d:%d;%d", &month, &day, &year, &hour, &minute, &second, &value)) != -1)
#endif
            {
                // Skip row
                if (index > 0)
                {
                    --index;
                }
                else if (len == 7)
                {
                    if (Vector_size(CGXDLMSProfileGeneric_GetBuffer(p)) == count)
                    {
                        break;
                    }
                    CGXDateTime tm;
                    CGXDateTime_5(&tm, 2000 + year, month, day, hour, minute, second, 0, 0x8000);

                    Vector row; // std::vector<CGXDLMSVariant>
                    Vector_(&row, sizeof(CGXDLMSVariant), CGXDLMSVariant_v_c, CGXDLMSVariant_v_d);

                    CGXDLMSVariant var1;
                    CGXDLMSVariant_16(&var1, &tm);

                    Vector_push_back(&row, &var1);

                    CGXDLMSVariant_d(&var1);

                    CGXDLMSVariant var2;
                    CGXDLMSVariant_10(&var2, value);

                    Vector_push_back(&row, &var2);

                    CGXDLMSVariant_d(&var2);

                    Vector_push_back(CGXDLMSProfileGeneric_GetBuffer(p), &row);

                    Vector_d(&row);
                }
                if (Vector_size(CGXDLMSProfileGeneric_GetBuffer(p)) == count)
                {
                    break;
                }
            }
            fclose(f);
        }
    }
}

/**
* Find start index and row count using start and end date time.
*
* @param start
*            Start time.
* @param end
*            End time
* @param index
*            Start index.
* @param count
*            Item count.
*/
void GetProfileGenericDataByRange(CGXDLMSValueEventArg* e)
{
    int len, month = 0, day = 0, year = 0, hour = 0, minute = 0, second = 0, value = 0;

    CGXDLMSVariant start, end;
    CGXDLMSVariant_1(&start);
    CGXDLMSVariant_1(&end);

    CGXByteBuffer bb;
    CGXByteBuffer_1(&bb);

    CGXByteBuffer_Set_1(&bb, ((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 1))->st.un.byteArr,
                           ((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 1))->size);
    CGXDLMSClient_ChangeType_1(&bb, DLMS_DATA_TYPE_DATETIME, &start);
    CGXByteBuffer_Clear(&bb);
    CGXByteBuffer_Set_1(&bb, ((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 2))->st.un.byteArr,
                             ((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 2))->size);
    CGXDLMSClient_ChangeType_1(&bb, DLMS_DATA_TYPE_DATETIME, &end);
#if defined(_WIN32) || defined(_WIN64)//Windows
    FILE* f = fopen(DATAFILE, _T("r"));
#else
    FILE* f = fopen(DATAFILE, "r");
#endif
    if (f != NULL)
    {
#if defined(_WIN32) || defined(_WIN64)//Windows
        while ((len = fscanf(f, "%d/%d/%d %d:%d:%d;%d", &month, &day, &year, &hour, &minute, &second, &value)) != -1)
#else
        while ((len = fscanf(f, "%d/%d/%d %d:%d:%d;%d", &month, &day, &year, &hour, &minute, &second, &value)) != -1)
#endif
        {
            CGXDateTime tm;
            CGXDateTime_5(&tm, 2000 + year, month, day, hour, minute, second, 0, 0x8000);

            if (CGXDateTime_CompareTo(&tm, &end.dateTime) > 0)
            {
                // If all data is read.
                break;
            }
            if (CGXDateTime_CompareTo(&tm, &start.dateTime) < 0)
            {
                // If we have not find first item.
                e->m_RowBeginIndex = e->m_RowBeginIndex + 1;
            }
            e->m_RowEndIndex = e->m_RowEndIndex + 1;
        }
        fclose(f);
    }

    CGXDLMSVariant_d(&start);
    CGXDLMSVariant_d(&end);
    CGXByteBuffer_d(&bb);
}

/**
* Get row count.
*
* @return
*/
int GetProfileGenericDataCount() {
    int rows = 0;
    int ch;
#if defined(_WIN32) || defined(_WIN64)//Windows
    FILE* f = fopen(DATAFILE, _T("r"));
#else
    FILE* f = fopen(DATAFILE, "r");
#endif
    if (f != NULL)
    {
        while ((ch = fgetc(f)) != EOF)
        {
            if (ch == '\n')
            {
                ++rows;
            }
        }
        fclose(f);
    }
    return rows;
}


/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CGXDLMSBase_PreRead(CGXDLMSBase* p, Vector* args) // std::vector<CGXDLMSValueEventArg*>&
{
    CGXDLMSVariant value;
    CGXDLMSVariant_1(&value);

    CGXDLMSObject* pObj;

    int ret, index;
    DLMS_OBJECT_TYPE type;

    //String ln;
    //String_(&ln);

    // std::vector<CGXDLMSValueEventArg*>
    for (unsigned int i = Vector_begin(args); i != Vector_end(args); ++i)
    {
        CGXDLMSValueEventArg** it = Vector_at(args, i);

        //Let framework handle Logical Name read.
        if ((*it)->m_Index == 1)
        {
            continue;
        }
        //Get attribute index.
        index = (*it)->m_Index;
        pObj = (*it)->m_Target;
        //Get target type.
        type = pObj->m_ObjectType;
        if (type == DLMS_OBJECT_TYPE_PROFILE_GENERIC)
        {
            CGXDLMSProfileGeneric* pg = (CGXDLMSProfileGeneric*)pObj;
            // If buffer is read and we want to save memory.
            if (index == 7)
            {
                // If client wants to know EntriesInUse.
                pg->m_EntriesInUse = GetProfileGenericDataCount();
            }
            else if (index == 2)
            {
                // Read rows from file.
                // If reading first time.
                if ((*it)->m_RowEndIndex == 0)
                {
                    if ((*it)->m_Selector == 0)
                    {
                        (*it)->m_RowEndIndex = GetProfileGenericDataCount();
                    }
                    else if ((*it)->m_Selector == 1)
                    {
                        // Read by entry.
                        GetProfileGenericDataByRange((*it));
                    }
                    else if ((*it)->m_Selector == 2)
                    {
                        // Read by range.
                        unsigned int begin = ((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetParameters(*it)->Arr), 0))->st.un.ulVal;
                        (*it)->m_RowBeginIndex = begin;
                        (*it)->m_RowEndIndex = begin + ((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetParameters(*it)->Arr), 1))->st.un.ulVal;
                        // If client wants to read more data what we have.
                        int cnt = GetProfileGenericDataCount();
                        if ((*it)->m_RowEndIndex - (*it)->m_RowBeginIndex > cnt - (*it)->m_RowBeginIndex)
                        {
                            (*it)->m_RowEndIndex = cnt - (*it)->m_RowBeginIndex;
                            if ((*it)->m_RowEndIndex < 0)
                            {
                                (*it)->m_RowEndIndex = 0;
                            }
                        }
                    }
                }
                long count = (*it)->m_RowEndIndex - (*it)->m_RowBeginIndex;
                // Read only rows that can fit to one PDU.
                if ((*it)->m_RowEndIndex - (*it)->m_RowBeginIndex
                                            > (*it)->m_RowToPdu)
                {
                    count = (*it)->m_RowToPdu;
                }
                GetProfileGenericDataByEntry(pg, (*it)->m_RowBeginIndex, count);
            }
            continue;
        }
        //Framework will handle Association objects automatically.
        if (type == DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME ||
            type == DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME ||
            //Framework will handle profile generic automatically.
            type == DLMS_OBJECT_TYPE_PROFILE_GENERIC)
        {
            continue;
        }
        DLMS_DATA_TYPE ui, dt;

        (*it)->m_Target->GetUIDataType((*it)->m_Target,
                                                           index, &ui);
        (*it)->m_Target->GetDataType((*it)->m_Target,
                                                         index, &dt);
        //Update date and time of clock object.
        if (type == DLMS_OBJECT_TYPE_CLOCK && index == 2)
        {
            CGXDateTime tm = CGXDateTime_Now();
            ((CGXDLMSClock*)pObj)->m_Time = tm;
            continue;
        }
        else if (type == DLMS_OBJECT_TYPE_REGISTER_MONITOR)
        {
            CGXDLMSRegisterMonitor* pRm = (CGXDLMSRegisterMonitor*)pObj;
            if (index == 2)
            {
                //Initialize random seed.
                srand((unsigned int)time(NULL));
                Vector_clear(CGXDLMSRegisterMonitor_GetThresholds(pRm));

                CGXDLMSVariant var;
                CGXDLMSVariant_10(&var, rand() % 100 + 1);

                Vector_push_back(CGXDLMSRegisterMonitor_GetThresholds(pRm), &var);

                CGXDLMSVariant_d(&var);

                continue;
            }
        }
        else
        {
            //CGXDLMSVariant null;
            //CGXDLMSVariant_1(&null);

            CGXDLMSValueEventArg e;
            CGXDLMSValueEventArg_3(&e, pObj, index);

            ret = pObj->GetValue(pObj, &p->m_Settings, &e);
            if (ret != DLMS_ERROR_CODE_OK)
            {
                //TODO: Show error.
                continue;
            }

            //If data is not assigned and value type is unknown return number.
            DLMS_DATA_TYPE tp = CGXDLMSValueEventArg_GetValue(&e)->st.vt;

            if (tp == DLMS_DATA_TYPE_INT8 ||
                tp == DLMS_DATA_TYPE_INT16 ||
                tp == DLMS_DATA_TYPE_INT32 ||
                tp == DLMS_DATA_TYPE_INT64 ||
                tp == DLMS_DATA_TYPE_UINT8 ||
                tp == DLMS_DATA_TYPE_UINT16 ||
                tp == DLMS_DATA_TYPE_UINT32 ||
                tp == DLMS_DATA_TYPE_UINT64)
            {
                //Initialize random seed.
                srand((unsigned int)time(NULL));
                CGXDLMSVariant_copy_12(&value, rand() % 100 + 1);
                value.st.vt = tp;
                CGXDLMSValueEventArg_SetValue(&e, &value);
            }

            CGXDLMSValueEventArg_d(&e);
        }
    }

    CGXDLMSVariant_d(&value);
}

void CGXDLMSBase_PostRead(CGXDLMSBase* p, Vector* args) // std::vector<CGXDLMSValueEventArg*>&
{
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CGXDLMSBase_PreWrite(CGXDLMSBase* p, Vector* args) // std::vector<CGXDLMSValueEventArg*>&
{
    String ln;
    String_(&ln);

    // std::vector<CGXDLMSValueEventArg*>
    for (unsigned int i = Vector_begin(args); i != Vector_end(args); ++i)
    {
        CGXDLMSValueEventArg** it = Vector_at(args, i);

        if (p->m_Trace > GX_TRACE_LEVEL_WARNING)
        {
            CGXDLMSObject_GetLogicalName_2((*it)->m_Target, &ln);
            printf("Writing: %s \r\n", String_c_str(&ln));
            String_clear(&ln);
        }
    }

    String_d(&ln);
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CGXDLMSBase_PostWrite(CGXDLMSBase* p, Vector* args) // std::vector<CGXDLMSValueEventArg*>&
{
}

void HandleImageTransfer(CGXDLMSValueEventArg* e)
{
    CGXDLMSImageTransfer* i = (CGXDLMSImageTransfer*)(e->m_Target);
    //Image name and size to transfer 
    FILE *f;
    if (e->m_Index == 1)
    {
        if (Vector_size(&(CGXDLMSValueEventArg_GetParameters(e)->Arr)) != 2)
        {
            e->m_Error = DLMS_ERROR_CODE_HARDWARE_FAULT;
            return;
        }
        imageSize = CGXDLMSVariant_ToInteger(Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 1));
        char *p = strrchr(IMAGEFILE, '\\');
        ++p;
        *p = '\0';
        strncat(IMAGEFILE, (char*)((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 0))->st.un.byteArr,
                           (int)CGXDLMSVariant_GetSize_1(Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 0)));
        strcat(IMAGEFILE, ".bin");
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)//If Windows or Linux
        printf("Updating image %s Size: %d", IMAGEFILE, imageSize);
#endif
        f = fopen(IMAGEFILE, "wb");
        if (!f)
        {
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)//If Windows or Linux
            printf("Unable to open file %s", IMAGEFILE);
#endif
            e->m_Error = DLMS_ERROR_CODE_HARDWARE_FAULT;
            return;
        }
        fclose(f);
    }
    //Transfers one block of the Image to the server
    else if (e->m_Index == 2)
    {
        if (Vector_size(&(CGXDLMSValueEventArg_GetParameters(e)->Arr)) != 2)
        {
            e->m_Error = DLMS_ERROR_CODE_HARDWARE_FAULT;
            return;
        }
        f = fopen(IMAGEFILE, "ab");
        if (!f)
        {
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)//If Windows or Linux
            printf("Unable to open file %s", IMAGEFILE);
#endif
            e->m_Error = DLMS_ERROR_CODE_HARDWARE_FAULT;
            return;
        }

        int ret = fwrite(((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 1))->st.un.byteArr,
                         1, (int)CGXDLMSVariant_GetSize_1(Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 1)), f);
        fclose(f);
        if (ret != CGXDLMSVariant_GetSize_1(Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 1)))
        {
            e->m_Error = DLMS_ERROR_CODE_HARDWARE_FAULT;
        }
        return;
    }
    //Verifies the integrity of the Image before activation.
    else if (e->m_Index == 3)
    {
        i->m_ImageTransferStatus = DLMS_IMAGE_TRANSFER_STATUS_VERIFICATION_INITIATED;
        f = fopen(IMAGEFILE, "rb");
        if (!f)
        {
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)//If Windows or Linux
            printf("Unable to open file %s", IMAGEFILE);
#endif
            e->m_Error = DLMS_ERROR_CODE_HARDWARE_FAULT;
            return;
        }
        fseek(f, 0L, SEEK_END);
        int size = (int)ftell(f);
        fclose(f);
        if (size != imageSize)
        {
            i->m_ImageTransferStatus = DLMS_IMAGE_TRANSFER_STATUS_VERIFICATION_FAILED;
        }
        else
        {
            i->m_ImageTransferStatus = DLMS_IMAGE_TRANSFER_STATUS_VERIFICATION_SUCCESSFUL;
        }
    }
    //Activates the Image.
    else if (e->m_Index == 4)
    {

    }
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CGXDLMSBase_PreAction(CGXDLMSBase* p, Vector* args) // std::vector<CGXDLMSValueEventArg*>&
{
    // std::vector<CGXDLMSValueEventArg*>
    for (unsigned int i = Vector_begin(args); i != Vector_end(args); ++i)
    {
        CGXDLMSValueEventArg** it = Vector_at(args, i);

        if ((*it)->m_Target->m_ObjectType
                                                == DLMS_OBJECT_TYPE_IMAGE_TRANSFER)
        {
            HandleImageTransfer(*it);
        }
    }
}

void Capture(CGXDLMSProfileGeneric* pg)
{
    Vector values; // std::vector<std::string>
    Vector_(&values, sizeof(String), String_v_c, String_v_d);

    String value;
    String_(&value);

    unsigned char first = 1;
    int cnt = GetProfileGenericDataCount();
#if defined(_WIN32) || defined(_WIN64)//Windows
    FILE* f = fopen(DATAFILE, _T("a"));
#else
    FILE* f = fopen(DATAFILE, "a");
#endif
    // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
    Vector* vec = CGXDLMSProfileGeneric_GetCaptureObjects(pg);
    for (unsigned int i = Vector_begin(vec); i != Vector_end(vec); ++i)
    {
        Pair* it = Vector_at(vec, i);

        if (first)
        {
            first = 0;
        }
        else
        {
            fprintf(f, ";");
            Vector_clear(&values);
        }

        CGXDLMSObject* it_first = *((CGXDLMSObject**) it->first);
        CGXDLMSCaptureObject* it_second = *((CGXDLMSCaptureObject**) it->second);

        if (it_first->m_ObjectType == DLMS_OBJECT_TYPE_CLOCK
                && it_second->m_AttributeIndex == 2)
        {
            CGXDateTime tm = CGXDateTime_Now();

            String_d(&value);
            value = CGXDateTime_ToString(&tm);
        }
        else
        {
            // TODO: Read value here example from the meter if it's not
            // updated automatically.
            it_first->GetValues(it_first, &values);
            String_copy_1(&value, Vector_at(&values, it_second->m_AttributeIndex - 1));
            if (String_compare(&value, "") == 0)
            {
                char tmp[20]; 
                // Generate random value here.
                sprintf(tmp, "%d", ++cnt);
                String_copy_2(&value, tmp);
            }
        }
        fprintf(f, "%s", String_c_str(&value));
    }
    fprintf(f, "\n");
    fclose(f);

    Vector_d(&values);
    String_d(&value);
}

void HandleProfileGenericActions(CGXDLMSValueEventArg* it)
{
    //CGXDLMSProfileGeneric* pg = (CGXDLMSProfileGeneric*)CGXDLMSValueEventArg_GetTarget(it);

    if (it->m_Index == 1)
    {
        // Profile generic clear is called. Clear data.
#if defined(_WIN32) || defined(_WIN64)//Windows
        FILE* f = fopen(DATAFILE, _T("w"));
#else
        FILE* f = fopen(DATAFILE, "w");
#endif
        fclose(f);
    }
    else if (it->m_Index == 2)
    {
        // Profile generic Capture is called.
    }
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CGXDLMSBase_PostAction(CGXDLMSBase* p, Vector* args) // std::vector<CGXDLMSValueEventArg*>&
{
    // std::vector<CGXDLMSValueEventArg*>
    for (unsigned int i = Vector_begin(args); i != Vector_end(args); ++i)
    {
        CGXDLMSValueEventArg** it = Vector_at(args, i);

        if ((*it)->m_Target->m_ObjectType
                                                    == DLMS_OBJECT_TYPE_PROFILE_GENERIC)
        {
            HandleProfileGenericActions(*it);
        }
    }
}


bool CGXDLMSBase_IsTarget(CGXDLMSBase* p, unsigned long int serverAddress, unsigned long clientAddress)
{
    return true;
}

DLMS_SOURCE_DIAGNOSTIC CGXDLMSBase_ValidateAuthentication(CGXDLMSBase* p,
                                                          DLMS_AUTHENTICATION authentication,
                                                          CGXByteBuffer* password)
{
    if (authentication == DLMS_AUTHENTICATION_NONE)
    {
        //Uncomment this if authentication is always required.
        //return DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_MECHANISM_NAME_REQUIRED;
    }

    if (authentication == DLMS_AUTHENTICATION_LOW)
    {
        CGXByteBuffer expected;
        CGXByteBuffer_1(&expected);

        String name;
        String_3(&name, "0.0.40.0.0.255");

        if (CGXDLMSBase_GetUseLogicalNameReferencing(p))
        {
            CGXDLMSAssociationLogicalName* ln =
                (CGXDLMSAssociationLogicalName*)CGXDLMSObjectCollection_FindByLN_1(CGXDLMSBase_GetItems(p),
                                                   DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, &name);
            CGXByteBuffer_copy(&expected, CGXDLMSAssociationLogicalName_GetSecret(ln));
        }
        else
        {
            CGXDLMSAssociationShortName* sn =
                (CGXDLMSAssociationShortName*)CGXDLMSObjectCollection_FindByLN_1(CGXDLMSBase_GetItems(p),
                                                    DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME, &name);
            CGXByteBuffer_copy(&expected, CGXDLMSAssociationShortName_GetSecret(sn));
        }
        if (CGXByteBuffer_Compare(&expected,
                                  password->m_Data,
                                  password->m_Size))
        {
            CGXByteBuffer_d(&expected);
            String_d(&name);
            return DLMS_SOURCE_DIAGNOSTIC_NONE;
        }

        CGXByteBuffer_d(&expected);
        String_d(&name);
        return DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE;
    }
    // Other authentication levels are check on phase two.
    return DLMS_SOURCE_DIAGNOSTIC_NONE;
}

DLMS_ACCESS_MODE CGXDLMSBase_GetAttributeAccess(CGXDLMSBase* p, CGXDLMSValueEventArg* arg)
{
    // Only read is allowed
    if (arg->m_Settings->m_Authentication == DLMS_AUTHENTICATION_NONE)
    {
        return DLMS_ACCESS_MODE_READ;
    }
    // Only clock write is allowed.
    if (arg->m_Settings->m_Authentication == DLMS_AUTHENTICATION_LOW)
    {
        if (arg->m_Target->m_ObjectType == DLMS_OBJECT_TYPE_CLOCK)
        {
            return DLMS_ACCESS_MODE_READ_WRITE;
        }
        return DLMS_ACCESS_MODE_READ;
    }
    // All writes are allowed.
    return DLMS_ACCESS_MODE_READ_WRITE;
}

/**
* Get method access mode.
*
* @param arg
*            Value event argument.
* @return Method access mode.
* @throws Exception
*             Server handler occurred exceptions.
*/
DLMS_METHOD_ACCESS_MODE CGXDLMSBase_GetMethodAccess(CGXDLMSBase* p, CGXDLMSValueEventArg* arg)
{
    // Methods are not allowed.
    if (arg->m_Settings->m_Authentication
                                                                    == DLMS_AUTHENTICATION_NONE)
    {
        return DLMS_METHOD_ACCESS_MODE_NONE;
    }
    // Only clock and profile generic methods are allowed.
    if (arg->m_Settings->m_Authentication
                                                                    == DLMS_AUTHENTICATION_LOW)
    {
        if (arg->m_Target->m_ObjectType == DLMS_OBJECT_TYPE_CLOCK
         || arg->m_Target->m_ObjectType == DLMS_OBJECT_TYPE_PROFILE_GENERIC)
        {
            return DLMS_METHOD_ACCESS_MODE_ACCESS;
        }
        return DLMS_METHOD_ACCESS_MODE_NONE;
    }
    return DLMS_METHOD_ACCESS_MODE_ACCESS;
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CGXDLMSBase_Connected(CGXDLMSBase* p, CGXDLMSConnectionEventArgs* connectionInfo)
{
    if (p->m_Trace > GX_TRACE_LEVEL_WARNING)
    {
        printf("Connected.\r\n");
    }
}

void CGXDLMSBase_InvalidConnection(CGXDLMSBase* p, CGXDLMSConnectionEventArgs* connectionInfo)
{
    if (p->m_Trace > GX_TRACE_LEVEL_WARNING)
    {
        printf("InvalidConnection.\r\n");
    }
}
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void CGXDLMSBase_Disconnected(CGXDLMSBase* p, CGXDLMSConnectionEventArgs* connectionInfo)
{
    if (p->m_Trace > GX_TRACE_LEVEL_WARNING)
    {
        printf("Disconnected.\r\n");
    }
}

void CGXDLMSBase_PreGet(CGXDLMSBase* p, Vector* args) // std::vector<CGXDLMSValueEventArg*>&
{
    // std::vector<CGXDLMSValueEventArg*>
    for (unsigned int i = Vector_begin(args); i != Vector_end(args); ++i)
    {
        CGXDLMSValueEventArg** it = Vector_at(args, i);

        if ((*it)->m_Target->m_ObjectType == DLMS_OBJECT_TYPE_PROFILE_GENERIC)
        {
            CGXDLMSProfileGeneric* pg = (CGXDLMSProfileGeneric*)(*it)->m_Target;

            Capture(pg);
            (*it)->m_Handled = true;
        }
    }
}

void CGXDLMSBase_PostGet(CGXDLMSBase* p, Vector* args) // std::vector<CGXDLMSValueEventArg*>&
{

}

/////////////////////////////////////////////////////////////////////////
//Constructor.
/////////////////////////////////////////////////////////////////////////
static void CGXDLMSBase__(CGXDLMSBase* p)
{
    p->IsTarget = CGXDLMSBase_IsTarget;
    p->ValidateAuthentication = CGXDLMSBase_ValidateAuthentication;
    p->FindObject = CGXDLMSBase_FindObject;
    p->PreRead = CGXDLMSBase_PreRead;
    p->PreWrite = CGXDLMSBase_PreWrite;
    p->Connected = CGXDLMSBase_Connected;
    p->InvalidConnection = CGXDLMSBase_InvalidConnection;
    p->Disconnected = CGXDLMSBase_Disconnected;
    p->GetAttributeAccess = CGXDLMSBase_GetAttributeAccess;
    p->GetMethodAccess = CGXDLMSBase_GetMethodAccess;
    p->PreAction = CGXDLMSBase_PreAction;
    p->PostRead = CGXDLMSBase_PostRead;
    p->PostWrite = CGXDLMSBase_PostWrite;
    p->PostAction = CGXDLMSBase_PostAction;
    p->PreGet = CGXDLMSBase_PreGet;
    p->PostGet = CGXDLMSBase_PostGet;
}

void CGXDLMSBase_2(CGXDLMSBase* p,
    CGXDLMSAssociationLogicalName* ln,
    CGXDLMSIecHdlcSetup* hdlc)
{
    CGXDLMSSecureServer_2((CGXDLMSSecureServer*) p, ln, hdlc);

    CGXDLMSBase__(p);

#if defined(_WIN32) || defined(_WIN64)//If Windows
    p->m_ReceiverThread = INVALID_HANDLE_VALUE;
    p->m_ServerSocket = INVALID_SOCKET;
#else //If Linux.
    p->m_ServerSocket = -1;
    p->m_ReceiverThread = -1;
#endif
    CGXDLMSBase_SetMaxReceivePDUSize(p, 1024);
}

/////////////////////////////////////////////////////////////////////////
//Constructor.
/////////////////////////////////////////////////////////////////////////
void CGXDLMSBase_3(CGXDLMSBase* p,
    CGXDLMSAssociationLogicalName* ln,
    CGXDLMSTcpUdpSetup* wrapper)
{
    CGXDLMSSecureServer_3((CGXDLMSSecureServer*) p, ln, wrapper);

    CGXDLMSBase__(p);

#if defined(_WIN32) || defined(_WIN64)//If Windows
    p->m_ReceiverThread = INVALID_HANDLE_VALUE;
    p->m_ServerSocket = INVALID_SOCKET;
#else //If Linux.
    p->m_ServerSocket = -1;
    p->m_ReceiverThread = -1;
#endif
    CGXDLMSBase_SetMaxReceivePDUSize(p, 1024);
}

/////////////////////////////////////////////////////////////////////////
//Constructor.
/////////////////////////////////////////////////////////////////////////
void CGXDLMSBase_4(CGXDLMSBase* p,
    CGXDLMSAssociationShortName* sn,
    CGXDLMSIecHdlcSetup* hdlc)
{
    CGXDLMSSecureServer_4((CGXDLMSSecureServer*) p, sn, hdlc);

    CGXDLMSBase__(p);

#if defined(_WIN32) || defined(_WIN64)//If Windows
    p->m_ReceiverThread = INVALID_HANDLE_VALUE;
    p->m_ServerSocket = INVALID_SOCKET;
#else //If Linux.
    p->m_ServerSocket = -1;
    p->m_ReceiverThread = -1;
#endif
    CGXDLMSBase_SetMaxReceivePDUSize(p, 1024);
}

/////////////////////////////////////////////////////////////////////////
//Constructor.
/////////////////////////////////////////////////////////////////////////
void CGXDLMSBase_5(CGXDLMSBase* p,
    CGXDLMSAssociationShortName* sn,
    CGXDLMSTcpUdpSetup* wrapper)
{
    CGXDLMSSecureServer_5((CGXDLMSSecureServer*) p, sn, wrapper);

    CGXDLMSBase__(p);

#if defined(_WIN32) || defined(_WIN64)//If Windows
    p->m_ReceiverThread = INVALID_HANDLE_VALUE;
    p->m_ServerSocket = INVALID_SOCKET;
#else //If Linux.
    p->m_ServerSocket = -1;
    p->m_ReceiverThread = -1;
#endif
    CGXDLMSBase_SetMaxReceivePDUSize(p, 1024);
}

/////////////////////////////////////////////////////////////////////////
//Destructor.
/////////////////////////////////////////////////////////////////////////
void CGXDLMSBase_d(CGXDLMSBase* p)
{
    CGXDLMSBase_StopServer(p);

    CGXDLMSSecureServer_d((CGXDLMSSecureServer*) p);
}
