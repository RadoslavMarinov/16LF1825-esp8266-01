#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/web-client-18LF326-XC8.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/web-client-18LF326-XC8.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=mcc_generated_files/mcc.c mcc_generated_files/device_config.c mcc_generated_files/pin_manager.c mcc_generated_files/eusart.c mcc_generated_files/interrupt_manager.c mcc_generated_files/tmr1.c mcc_generated_files/memory.c modules/client/client.c modules/comander/comander.c modules/communicatior/communicator.c modules/eeprom/eeprom.c modules/endpoints/binary-switch/binary-switch.c modules/esp/esp.c modules/parser/http-parser/http-parser.c modules/parser/json-parser/json-parser.c modules/parser/parser.c modules/receiver/receiver.c modules/server/server.c modules/timer/timer.c modules/transmitter/transmitter.c modules/utils/utils.c main.c config.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/mcc_generated_files/mcc.p1 ${OBJECTDIR}/mcc_generated_files/device_config.p1 ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 ${OBJECTDIR}/mcc_generated_files/eusart.p1 ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 ${OBJECTDIR}/mcc_generated_files/tmr1.p1 ${OBJECTDIR}/mcc_generated_files/memory.p1 ${OBJECTDIR}/modules/client/client.p1 ${OBJECTDIR}/modules/comander/comander.p1 ${OBJECTDIR}/modules/communicatior/communicator.p1 ${OBJECTDIR}/modules/eeprom/eeprom.p1 ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1 ${OBJECTDIR}/modules/esp/esp.p1 ${OBJECTDIR}/modules/parser/http-parser/http-parser.p1 ${OBJECTDIR}/modules/parser/json-parser/json-parser.p1 ${OBJECTDIR}/modules/parser/parser.p1 ${OBJECTDIR}/modules/receiver/receiver.p1 ${OBJECTDIR}/modules/server/server.p1 ${OBJECTDIR}/modules/timer/timer.p1 ${OBJECTDIR}/modules/transmitter/transmitter.p1 ${OBJECTDIR}/modules/utils/utils.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/config.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/mcc_generated_files/mcc.p1.d ${OBJECTDIR}/mcc_generated_files/device_config.p1.d ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d ${OBJECTDIR}/mcc_generated_files/eusart.p1.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d ${OBJECTDIR}/mcc_generated_files/memory.p1.d ${OBJECTDIR}/modules/client/client.p1.d ${OBJECTDIR}/modules/comander/comander.p1.d ${OBJECTDIR}/modules/communicatior/communicator.p1.d ${OBJECTDIR}/modules/eeprom/eeprom.p1.d ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1.d ${OBJECTDIR}/modules/esp/esp.p1.d ${OBJECTDIR}/modules/parser/http-parser/http-parser.p1.d ${OBJECTDIR}/modules/parser/json-parser/json-parser.p1.d ${OBJECTDIR}/modules/parser/parser.p1.d ${OBJECTDIR}/modules/receiver/receiver.p1.d ${OBJECTDIR}/modules/server/server.p1.d ${OBJECTDIR}/modules/timer/timer.p1.d ${OBJECTDIR}/modules/transmitter/transmitter.p1.d ${OBJECTDIR}/modules/utils/utils.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/config.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/mcc_generated_files/mcc.p1 ${OBJECTDIR}/mcc_generated_files/device_config.p1 ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 ${OBJECTDIR}/mcc_generated_files/eusart.p1 ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 ${OBJECTDIR}/mcc_generated_files/tmr1.p1 ${OBJECTDIR}/mcc_generated_files/memory.p1 ${OBJECTDIR}/modules/client/client.p1 ${OBJECTDIR}/modules/comander/comander.p1 ${OBJECTDIR}/modules/communicatior/communicator.p1 ${OBJECTDIR}/modules/eeprom/eeprom.p1 ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1 ${OBJECTDIR}/modules/esp/esp.p1 ${OBJECTDIR}/modules/parser/http-parser/http-parser.p1 ${OBJECTDIR}/modules/parser/json-parser/json-parser.p1 ${OBJECTDIR}/modules/parser/parser.p1 ${OBJECTDIR}/modules/receiver/receiver.p1 ${OBJECTDIR}/modules/server/server.p1 ${OBJECTDIR}/modules/timer/timer.p1 ${OBJECTDIR}/modules/transmitter/transmitter.p1 ${OBJECTDIR}/modules/utils/utils.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/config.p1

# Source Files
SOURCEFILES=mcc_generated_files/mcc.c mcc_generated_files/device_config.c mcc_generated_files/pin_manager.c mcc_generated_files/eusart.c mcc_generated_files/interrupt_manager.c mcc_generated_files/tmr1.c mcc_generated_files/memory.c modules/client/client.c modules/comander/comander.c modules/communicatior/communicator.c modules/eeprom/eeprom.c modules/endpoints/binary-switch/binary-switch.c modules/esp/esp.c modules/parser/http-parser/http-parser.c modules/parser/json-parser/json-parser.c modules/parser/parser.c modules/receiver/receiver.c modules/server/server.c modules/timer/timer.c modules/transmitter/transmitter.c modules/utils/utils.c main.c config.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/web-client-18LF326-XC8.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16LF18326
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/mcc.p1: mcc_generated_files/mcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/mcc.p1 mcc_generated_files/mcc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/mcc.d ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/device_config.p1: mcc_generated_files/device_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/device_config.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/device_config.p1 mcc_generated_files/device_config.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/device_config.d ${OBJECTDIR}/mcc_generated_files/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.p1: mcc_generated_files/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 mcc_generated_files/pin_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/pin_manager.d ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/eusart.p1: mcc_generated_files/eusart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/eusart.p1 mcc_generated_files/eusart.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/eusart.d ${OBJECTDIR}/mcc_generated_files/eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1: mcc_generated_files/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 mcc_generated_files/interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr1.p1: mcc_generated_files/tmr1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr1.p1 mcc_generated_files/tmr1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr1.d ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/memory.p1: mcc_generated_files/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/memory.p1 mcc_generated_files/memory.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/memory.d ${OBJECTDIR}/mcc_generated_files/memory.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/memory.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/client/client.p1: modules/client/client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/client" 
	@${RM} ${OBJECTDIR}/modules/client/client.p1.d 
	@${RM} ${OBJECTDIR}/modules/client/client.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/client/client.p1 modules/client/client.c 
	@-${MV} ${OBJECTDIR}/modules/client/client.d ${OBJECTDIR}/modules/client/client.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/client/client.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/comander/comander.p1: modules/comander/comander.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/comander" 
	@${RM} ${OBJECTDIR}/modules/comander/comander.p1.d 
	@${RM} ${OBJECTDIR}/modules/comander/comander.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/comander/comander.p1 modules/comander/comander.c 
	@-${MV} ${OBJECTDIR}/modules/comander/comander.d ${OBJECTDIR}/modules/comander/comander.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/comander/comander.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/communicatior/communicator.p1: modules/communicatior/communicator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/communicatior" 
	@${RM} ${OBJECTDIR}/modules/communicatior/communicator.p1.d 
	@${RM} ${OBJECTDIR}/modules/communicatior/communicator.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/communicatior/communicator.p1 modules/communicatior/communicator.c 
	@-${MV} ${OBJECTDIR}/modules/communicatior/communicator.d ${OBJECTDIR}/modules/communicatior/communicator.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/communicatior/communicator.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/eeprom/eeprom.p1: modules/eeprom/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/eeprom" 
	@${RM} ${OBJECTDIR}/modules/eeprom/eeprom.p1.d 
	@${RM} ${OBJECTDIR}/modules/eeprom/eeprom.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/eeprom/eeprom.p1 modules/eeprom/eeprom.c 
	@-${MV} ${OBJECTDIR}/modules/eeprom/eeprom.d ${OBJECTDIR}/modules/eeprom/eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/eeprom/eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1: modules/endpoints/binary-switch/binary-switch.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/endpoints/binary-switch" 
	@${RM} ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1.d 
	@${RM} ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1 modules/endpoints/binary-switch/binary-switch.c 
	@-${MV} ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.d ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/esp/esp.p1: modules/esp/esp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/esp" 
	@${RM} ${OBJECTDIR}/modules/esp/esp.p1.d 
	@${RM} ${OBJECTDIR}/modules/esp/esp.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/esp/esp.p1 modules/esp/esp.c 
	@-${MV} ${OBJECTDIR}/modules/esp/esp.d ${OBJECTDIR}/modules/esp/esp.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/esp/esp.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/parser/http-parser/http-parser.p1: modules/parser/http-parser/http-parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/parser/http-parser" 
	@${RM} ${OBJECTDIR}/modules/parser/http-parser/http-parser.p1.d 
	@${RM} ${OBJECTDIR}/modules/parser/http-parser/http-parser.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/parser/http-parser/http-parser.p1 modules/parser/http-parser/http-parser.c 
	@-${MV} ${OBJECTDIR}/modules/parser/http-parser/http-parser.d ${OBJECTDIR}/modules/parser/http-parser/http-parser.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/parser/http-parser/http-parser.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/parser/json-parser/json-parser.p1: modules/parser/json-parser/json-parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/parser/json-parser" 
	@${RM} ${OBJECTDIR}/modules/parser/json-parser/json-parser.p1.d 
	@${RM} ${OBJECTDIR}/modules/parser/json-parser/json-parser.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/parser/json-parser/json-parser.p1 modules/parser/json-parser/json-parser.c 
	@-${MV} ${OBJECTDIR}/modules/parser/json-parser/json-parser.d ${OBJECTDIR}/modules/parser/json-parser/json-parser.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/parser/json-parser/json-parser.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/parser/parser.p1: modules/parser/parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/parser" 
	@${RM} ${OBJECTDIR}/modules/parser/parser.p1.d 
	@${RM} ${OBJECTDIR}/modules/parser/parser.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/parser/parser.p1 modules/parser/parser.c 
	@-${MV} ${OBJECTDIR}/modules/parser/parser.d ${OBJECTDIR}/modules/parser/parser.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/parser/parser.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/receiver/receiver.p1: modules/receiver/receiver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/receiver" 
	@${RM} ${OBJECTDIR}/modules/receiver/receiver.p1.d 
	@${RM} ${OBJECTDIR}/modules/receiver/receiver.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/receiver/receiver.p1 modules/receiver/receiver.c 
	@-${MV} ${OBJECTDIR}/modules/receiver/receiver.d ${OBJECTDIR}/modules/receiver/receiver.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/receiver/receiver.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/server/server.p1: modules/server/server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/server" 
	@${RM} ${OBJECTDIR}/modules/server/server.p1.d 
	@${RM} ${OBJECTDIR}/modules/server/server.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/server/server.p1 modules/server/server.c 
	@-${MV} ${OBJECTDIR}/modules/server/server.d ${OBJECTDIR}/modules/server/server.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/server/server.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/timer/timer.p1: modules/timer/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/timer" 
	@${RM} ${OBJECTDIR}/modules/timer/timer.p1.d 
	@${RM} ${OBJECTDIR}/modules/timer/timer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/timer/timer.p1 modules/timer/timer.c 
	@-${MV} ${OBJECTDIR}/modules/timer/timer.d ${OBJECTDIR}/modules/timer/timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/timer/timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/transmitter/transmitter.p1: modules/transmitter/transmitter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/transmitter" 
	@${RM} ${OBJECTDIR}/modules/transmitter/transmitter.p1.d 
	@${RM} ${OBJECTDIR}/modules/transmitter/transmitter.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/transmitter/transmitter.p1 modules/transmitter/transmitter.c 
	@-${MV} ${OBJECTDIR}/modules/transmitter/transmitter.d ${OBJECTDIR}/modules/transmitter/transmitter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/transmitter/transmitter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/utils/utils.p1: modules/utils/utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/utils" 
	@${RM} ${OBJECTDIR}/modules/utils/utils.p1.d 
	@${RM} ${OBJECTDIR}/modules/utils/utils.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/utils/utils.p1 modules/utils/utils.c 
	@-${MV} ${OBJECTDIR}/modules/utils/utils.d ${OBJECTDIR}/modules/utils/utils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/utils/utils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/config.p1: config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/config.p1.d 
	@${RM} ${OBJECTDIR}/config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/config.p1 config.c 
	@-${MV} ${OBJECTDIR}/config.d ${OBJECTDIR}/config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/mcc_generated_files/mcc.p1: mcc_generated_files/mcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/mcc.p1 mcc_generated_files/mcc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/mcc.d ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/device_config.p1: mcc_generated_files/device_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/device_config.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/device_config.p1 mcc_generated_files/device_config.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/device_config.d ${OBJECTDIR}/mcc_generated_files/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.p1: mcc_generated_files/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 mcc_generated_files/pin_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/pin_manager.d ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/eusart.p1: mcc_generated_files/eusart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/eusart.p1 mcc_generated_files/eusart.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/eusart.d ${OBJECTDIR}/mcc_generated_files/eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1: mcc_generated_files/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 mcc_generated_files/interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr1.p1: mcc_generated_files/tmr1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr1.p1 mcc_generated_files/tmr1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr1.d ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/memory.p1: mcc_generated_files/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/memory.p1 mcc_generated_files/memory.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/memory.d ${OBJECTDIR}/mcc_generated_files/memory.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/memory.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/client/client.p1: modules/client/client.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/client" 
	@${RM} ${OBJECTDIR}/modules/client/client.p1.d 
	@${RM} ${OBJECTDIR}/modules/client/client.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/client/client.p1 modules/client/client.c 
	@-${MV} ${OBJECTDIR}/modules/client/client.d ${OBJECTDIR}/modules/client/client.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/client/client.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/comander/comander.p1: modules/comander/comander.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/comander" 
	@${RM} ${OBJECTDIR}/modules/comander/comander.p1.d 
	@${RM} ${OBJECTDIR}/modules/comander/comander.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/comander/comander.p1 modules/comander/comander.c 
	@-${MV} ${OBJECTDIR}/modules/comander/comander.d ${OBJECTDIR}/modules/comander/comander.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/comander/comander.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/communicatior/communicator.p1: modules/communicatior/communicator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/communicatior" 
	@${RM} ${OBJECTDIR}/modules/communicatior/communicator.p1.d 
	@${RM} ${OBJECTDIR}/modules/communicatior/communicator.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/communicatior/communicator.p1 modules/communicatior/communicator.c 
	@-${MV} ${OBJECTDIR}/modules/communicatior/communicator.d ${OBJECTDIR}/modules/communicatior/communicator.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/communicatior/communicator.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/eeprom/eeprom.p1: modules/eeprom/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/eeprom" 
	@${RM} ${OBJECTDIR}/modules/eeprom/eeprom.p1.d 
	@${RM} ${OBJECTDIR}/modules/eeprom/eeprom.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/eeprom/eeprom.p1 modules/eeprom/eeprom.c 
	@-${MV} ${OBJECTDIR}/modules/eeprom/eeprom.d ${OBJECTDIR}/modules/eeprom/eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/eeprom/eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1: modules/endpoints/binary-switch/binary-switch.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/endpoints/binary-switch" 
	@${RM} ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1.d 
	@${RM} ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1 modules/endpoints/binary-switch/binary-switch.c 
	@-${MV} ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.d ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/endpoints/binary-switch/binary-switch.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/esp/esp.p1: modules/esp/esp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/esp" 
	@${RM} ${OBJECTDIR}/modules/esp/esp.p1.d 
	@${RM} ${OBJECTDIR}/modules/esp/esp.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/esp/esp.p1 modules/esp/esp.c 
	@-${MV} ${OBJECTDIR}/modules/esp/esp.d ${OBJECTDIR}/modules/esp/esp.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/esp/esp.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/parser/http-parser/http-parser.p1: modules/parser/http-parser/http-parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/parser/http-parser" 
	@${RM} ${OBJECTDIR}/modules/parser/http-parser/http-parser.p1.d 
	@${RM} ${OBJECTDIR}/modules/parser/http-parser/http-parser.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/parser/http-parser/http-parser.p1 modules/parser/http-parser/http-parser.c 
	@-${MV} ${OBJECTDIR}/modules/parser/http-parser/http-parser.d ${OBJECTDIR}/modules/parser/http-parser/http-parser.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/parser/http-parser/http-parser.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/parser/json-parser/json-parser.p1: modules/parser/json-parser/json-parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/parser/json-parser" 
	@${RM} ${OBJECTDIR}/modules/parser/json-parser/json-parser.p1.d 
	@${RM} ${OBJECTDIR}/modules/parser/json-parser/json-parser.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/parser/json-parser/json-parser.p1 modules/parser/json-parser/json-parser.c 
	@-${MV} ${OBJECTDIR}/modules/parser/json-parser/json-parser.d ${OBJECTDIR}/modules/parser/json-parser/json-parser.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/parser/json-parser/json-parser.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/parser/parser.p1: modules/parser/parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/parser" 
	@${RM} ${OBJECTDIR}/modules/parser/parser.p1.d 
	@${RM} ${OBJECTDIR}/modules/parser/parser.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/parser/parser.p1 modules/parser/parser.c 
	@-${MV} ${OBJECTDIR}/modules/parser/parser.d ${OBJECTDIR}/modules/parser/parser.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/parser/parser.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/receiver/receiver.p1: modules/receiver/receiver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/receiver" 
	@${RM} ${OBJECTDIR}/modules/receiver/receiver.p1.d 
	@${RM} ${OBJECTDIR}/modules/receiver/receiver.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/receiver/receiver.p1 modules/receiver/receiver.c 
	@-${MV} ${OBJECTDIR}/modules/receiver/receiver.d ${OBJECTDIR}/modules/receiver/receiver.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/receiver/receiver.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/server/server.p1: modules/server/server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/server" 
	@${RM} ${OBJECTDIR}/modules/server/server.p1.d 
	@${RM} ${OBJECTDIR}/modules/server/server.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/server/server.p1 modules/server/server.c 
	@-${MV} ${OBJECTDIR}/modules/server/server.d ${OBJECTDIR}/modules/server/server.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/server/server.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/timer/timer.p1: modules/timer/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/timer" 
	@${RM} ${OBJECTDIR}/modules/timer/timer.p1.d 
	@${RM} ${OBJECTDIR}/modules/timer/timer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/timer/timer.p1 modules/timer/timer.c 
	@-${MV} ${OBJECTDIR}/modules/timer/timer.d ${OBJECTDIR}/modules/timer/timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/timer/timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/transmitter/transmitter.p1: modules/transmitter/transmitter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/transmitter" 
	@${RM} ${OBJECTDIR}/modules/transmitter/transmitter.p1.d 
	@${RM} ${OBJECTDIR}/modules/transmitter/transmitter.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/transmitter/transmitter.p1 modules/transmitter/transmitter.c 
	@-${MV} ${OBJECTDIR}/modules/transmitter/transmitter.d ${OBJECTDIR}/modules/transmitter/transmitter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/transmitter/transmitter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/modules/utils/utils.p1: modules/utils/utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/modules/utils" 
	@${RM} ${OBJECTDIR}/modules/utils/utils.p1.d 
	@${RM} ${OBJECTDIR}/modules/utils/utils.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/modules/utils/utils.p1 modules/utils/utils.c 
	@-${MV} ${OBJECTDIR}/modules/utils/utils.d ${OBJECTDIR}/modules/utils/utils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/modules/utils/utils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/config.p1: config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/config.p1.d 
	@${RM} ${OBJECTDIR}/config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/config.p1 config.c 
	@-${MV} ${OBJECTDIR}/config.d ${OBJECTDIR}/config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/web-client-18LF326-XC8.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/web-client-18LF326-XC8.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -std=c99 -gdwarf-3 -mstack=compiled:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/web-client-18LF326-XC8.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/web-client-18LF326-XC8.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/web-client-18LF326-XC8.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/web-client-18LF326-XC8.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1  -fno-short-double -fno-short-float -O0 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/web-client-18LF326-XC8.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
