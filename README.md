

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=daohoangyen282%40gmail%2ecom&lc=VN&item_name=NGUYEN%20VAN%20HAI&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donateCC_LG%2egif%3aNonHosted)



See An [Gurux](http://www.gurux.org/ "Gurux") for an overview.

Join the Gurux Community or follow [@Gurux](https://twitter.com/guruxorg "@Gurux") for project updates.

GuruxDLMS.c library is a high-performance ANSI C component that helps you to read you DLMS/COSEM compatible electricity, gas or water meters. We have try to make component so easy to use that you do not need understand protocol at all.

For more info check out [Gurux.DLMS](http://www.gurux.fi/index.php?q=Gurux.DLMS "Gurux.DLMS").

We are updating documentation on Gurux web page. 

Read should read [DLMS/COSEM FAQ](http://www.gurux.org/index.php?q=DLMSCOSEMFAQ) first to get started. Read Instructions for making your own [meter reading application](http://www.gurux.org/index.php?q=DLMSIntro) or build own 
DLMS/COSEM [meter/simulator/proxy](http://www.gurux.org/index.php?q=OwnDLMSMeter).

If you have problems you can ask your questions in Gurux [Forum](http://www.gurux.org/forum).

You can use any connection (TCP, serial, PLC) library you want to.
Gurux.DLMS classes only parse the data.

Before start
=========================== 

If you find an issue, please report it here:
http://www.gurux.fi/fi/project/issues/gurux.dlms.cpp

We have made makefile for linux environment. You should go development folder and create lib and obj directories.
Then run make. gurux_dlms_cpp static library is made.

For Client example you should also create bin and obj -directories.
Change Host name, port and DLMS settings for example. Run make and you are ready to test.

Simple example
=========================== 
Before use you must set following device parameters. 
Parameters are manufacturer spesific.


```C

All default parameters are given in constructor.
// Is used Logican Name or Short Name referencing.
CGXDLMSClient client(true);

```

HDLC addressing
=========================== 

Each meter has own server address. Server address is divided to Logical address and Physical address.
Usually you can use value 1 for meter address. You can count server address from serial number of the meter.
You can use GetServerAddress method for that.

```C++
//Count server address from serial number.
int serverAddress = CGXDLMSClient::GetServerAddress(Serial number);
//Count server address from logican and physical address.
serverAddress = CGXDLMSClient::GetServerAddress(logical Address, physical Address);
```


If you are using IEC handshake you must first send identify command and move to mode E.

```

After you have set parameters you can try to connect to the meter.
First you should send SNRM request and handle UA response.
After that you will send AARQ request and handle AARE response.
