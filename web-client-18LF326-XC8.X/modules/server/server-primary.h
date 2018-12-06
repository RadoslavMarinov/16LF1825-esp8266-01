/* 
 * File:   server-primary.h
 * Author: Riko
 *
 * Created on 04 ???????? 2018, 13:27
 */

#ifndef SERVER_PRIMARY_H
#define	SERVER_PRIMARY_H

#include "server.h"

#define PACKAGE_MAX_SIZE            2048U

typedef enum{
    __serverCode_didNothing,
    __serverCode_didSomeWork,
    __serverCode_done,
}server_Code;

typedef struct {
    unsigned int __errTest:1;
}server_Errors;


typedef struct {
    union {
        struct {
            unsigned int evSendRes :1;
            unsigned int evMsgOk :1;
            unsigned int evCloseTcpCon :1;
            
        };
        uint16_t eventsCont;
    };
}server_Events;


typedef enum{
    __stIdle,
    __stSendingResHederStatusLineDataSize,
    __stSendingResHederStatusLine,
    __stSendingResHederStatusLineNotFoundDataSize,
    __stSendingBodySeparatorSize,
    __stSendingBodySeparator,
    __stSendingBody,
    __stClosingTcpConnection,
            
}server_State;



typedef struct {
     server_Events events; 
     server_State state;
     server_Errors errors;
     server_Routes route;
}server_SelfData;

/**********************************  SELF DATA ***********************************/
//== EVENTS
#define __events                            (server_self.events)
#define __evCont                            (__events.eventsCont)
#define __isRaisedEv(ev)                    ( __events.ev == 1 ? true :false )
#define __hasPendingEv()                    (!!__evCont)
#define __raiseEv(ev)                       do{ __events.ev = 1; }while(0);
#define __clearEv(ev)                       do{ __events.ev = 0; }while(0);
//== STATE
#define __state                             (server_self.state)
#define __setSt(st)                         do{ __state = (st); }while(0)
#define __isInSt(st)                        ( __state == (st) ? true : false )

//== ERRORS
#define __errors                            ( server_self.errors )
#define __raiseErr(err)                     do{ __errors.err = 1; }while(0)
#define __clearErr(err)                     do{ __errors.err = 0; }while(0)

//== ROUTE
#define __route                             ( server_self.route )
#define __setRoute(r)                       do{__route = (r); }while(0)

/**********************************  PRIVATE FUNCT DECLARATIONS ***********************************/
//== EVENT IDSPATCHERS
static uint8_t dispatchevSendRes(void);
static uint8_t dispatchEvMsgOk(void);
static uint8_t dispatchEvSendNotFound(void);
//== EVENT HANDLERS
static uint8_t sendHeaderStatusLine(void);

//== TRANSITIONS
static void enterSt_idle(void);
static void enterSt_sendingResHederStatusLineDataSize(void);
static void enterSt_sendingResHederStatusLine(void);

static void enterSt_sendingBodySeparatorSize(void);
static void enterSt_sendingBodySeparator(void);
static void enterSt_sendingBody(void);
static server_Code doSt_sendingBody(void);
static void enterSt_closinTcpConnection(void);
static uint8_t doSt_closinTcpConnection(void);
static void exitSt_closingTcpConnection(void);

//== OTHERS
static server_Code sendBoydRoot(void);


/**********************************  RESPONSE HEADERS AND PAGES ***********************************/
const static char CLOSE_TCP_CONNECTION[] = "AT+CIPCLOSE=0\r\n";
const static char HTTP_HEADER_OK_SIZE[] = "AT+CIPSEND=0,17\r\n";
const static char HTTP_HEADER_OK_STATUS_LINE_OK[] = "HTTP/1.1 200 OK\r\n";
const static char HTTP_BODY_SEPARATOR_SIZE[] = "AT+CIPSEND=0,2\r\n";
const static char HTTP_BODY_SEPARATOR[] = "\r\n";
const static char HTTP_HEADER_STATUS_NOT_FOUND_SIZE[] = "AT+CIPSEND=0,24\r\n";
const static char HTTP_HEADER_STATUS_LINE_NOT_FOUND[] = "HTTP/1.1 404 Not Found\r\n";
const static char HTTP_BODY_ROOT_SIZE[] = "AT+CIPSEND=0,134\r\n";
const static char HTTP_BODY_ROOT[]=  
"<!DOCTYPE html><html><head><title>ESP Server</title></head> <style> body { background-color: rgb(245, 245, 245); } h1{ text-align: center; font-family: sans-serif; color: lightslategrey; } #is_cont { padding-bottom: 20px; padding-top: 20px; } #is_cont label { display: block; padding-bottom: 8px; font-family: Tahoma, Geneva, sans-serif; } #is_cont { background-color: rgb(237, 239, 240); border-radius: 20px; } #b_ssid, #b_pwd{ margin: 20px; } #i_ssid, #i_pwd { width: 100%; } #sbm_btn_wr { text-align: center; } #subm_btn { margin-top: 10px; background-color: #4CAF50; border: none; color: white; padding: 15px 32px; text-decoration: none; font-size: 16px; } #subm_btn:hover { color: rgb(238, 231, 225); background-color: rgb(69, 153, 226); } #subm_btn:active { background-color: rgb(131, 121, 224); color: rgb(1, 3, 5); } </style> <script> function submitForm(){ var ssid = document.getElementById(\"i_ssid\").value; var pwd = document.getElementById(\"i_pwd\").value; var jp = \'{\"swfid\":\"\' + ssid + \'\",\"swfpwd\":\"\' + pwd + \'\"}\'; var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function() { if (this.readyState == 4 && this.status == 200) { document.getElementById(\"demo\").innerHTML = this.responseText; } }; xhttp.open(\"POST\", \"/\", true); xhttp.send(jp + \'\\r\\n\\r\\n\'); console.log(jp); } </script> <body> <h1>SET WIFI ACCESS POINT</h1> <div id=\"is_cont\"> <div id=\"b_ssid\"> <label>Access point SSID</label> <input id=\"i_ssid\" type=\"text\" placeholder=\"SSID...\"></input> </div> <div id=\"b_pwd\"> <label>Access point password</label> <input id=\"i_pwd\" type=\"text\" placeholder=\"Password...\"></input> </div> </div> <div id=\"sbm_btn_wr\"> <button id=\"subm_btn\" onclick=\"submitForm()\">SUBMIT</button> </div> </body></html>";



#endif	/* SERVER_PRIMARY_H */

