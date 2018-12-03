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

const char SERVER_HTML_HOME[] = "<!DOCTYPE html><html><head><title>ESP Server</title></head> <style> body { background-color: rgb(171, 214, 197); } #is_cont { padding-bottom: 20px; padding-top: 20px; } #is_cont label { display: block; padding-bottom: 8px; } #is_cont { background-color: rgb(237, 239, 240); border-radius: 20px; } #b_ssid, #b_pwd{ margin: 20px; } #i_ssid, #i_pwd { width: 100%; } #sbm_btn_wr { text-align: center; } #subm_btn { margin-top: 10px; background-color: #4CAF50; border: none; color: white; padding: 15px 32px; text-decoration: none; font-size: 16px; } #subm_btn:hover { color: rgb(175, 85, 0); background-color: aliceblue; } #subm_btn:active { background-color: rgb(175, 85, 0); color: aliceblue; } </style> <script> function submitForm(){ var jp = '{\"swfid\":\"' + document.getElementById(\"i_ssid\").value + '\",\"swfpwd\":\"' + document.getElementById(\"i_pwd\").value + '\"}\nJSON\n' console.log(jp); } </script> <body> <h1>Change wifi credentials</h1> <div id=\"is_cont\"> <div id=\"b_ssid\"> <label>Access point SSID</label> <input id=\"i_ssid\" type=\"text\" placeholder=\"Enter network SSID...\"></input> </div> <div id=\"b_pwd\"> <label>Access point password</label> <input id=\"i_pwd\" type=\"text\" placeholder=\"Enter network password...\"></input> </div> </div> <div id=\"sbm_btn_wr\"> <button id=\"subm_btn\" onclick=\"submitForm()\">SUBMIT</button> </div> </body></html>";

#endif	/* PARSER_PRIMARY_H */

