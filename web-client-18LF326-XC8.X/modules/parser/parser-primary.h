/* 
 * File:   parser-primary.h
 * Author: Riko
 *
 * Created on 15 ???????? 2018, 18:13
 */

#ifndef PARSER_PRIMARY_H
#define	PARSER_PRIMARY_H

#define MODULE_NAME parser

/******************************************************************************* 
 * CONDITIONALS
 ******************************************************************************/
#ifdef CONFIG_raiseError
    #define __addGlobalError()   do{CONFIG_raiseError(MODULE_NAME);}while(0)
#else
    #define __addGlobalError()   
#endif


typedef struct {
}Self;


static char * getStartOfStr(char * endCh, uint16_t len);

const char SERVER_HTML_HOME[] = "<!DOCTYPE html><html><head><title>ESP Server</title></head> <script> function submitForm(){ var jp = '{\"swfid\":\"' + document.getElementById(\"i_ssid\").value + '\",\"swfpwd\":\"' + document.getElementById(\"i_pwd\").value + '\"}\nJSON\n' console.log(jp); } </script> <body> <h1>Change wifi credentials</h1> <div id=\"is_cont\"> <div id=\"b_ssid\"> <label>Access point SSID</label> <input id=\"i_ssid\" type=\"text\" placeholder=\"Enter network SSID...\"></input> </div> <div id=\"b_pwd\"> <label>Access point password</label> <input id=\"i_pwd\" type=\"text\" placeholder=\"Enter network password...\"></input> </div> </div> <div id=\"sbm_btn_wr\"> <button id=\"subm_btn\" onclick=\"submitForm()\">SUBMIT</button> </div> </body></html>";

#endif	/* PARSER_PRIMARY_H */

