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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/bye00035_lab4_v001.X_-_Copy.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/bye00035_lab4_v001.X_-_Copy.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=bye00035_lab4_polling.c ../bye00035_lab4_v001.X/bye00035_lab4_interrupt.c ../bye00035_lab4_v001.X/bye00035_lab4_main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/bye00035_lab4_polling.o ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_interrupt.o ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/bye00035_lab4_polling.o.d ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_interrupt.o.d ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/bye00035_lab4_polling.o ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_interrupt.o ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_main.o

# Source Files
SOURCEFILES=bye00035_lab4_polling.c ../bye00035_lab4_v001.X/bye00035_lab4_interrupt.c ../bye00035_lab4_v001.X/bye00035_lab4_main.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/bye00035_lab4_v001.X_-_Copy.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA002
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA002.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/bye00035_lab4_polling.o: bye00035_lab4_polling.c  .generated_files/flags/default/4689cf0bce741ee1c64e3f856ab0422f14b03fec .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bye00035_lab4_polling.o.d 
	@${RM} ${OBJECTDIR}/bye00035_lab4_polling.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bye00035_lab4_polling.c  -o ${OBJECTDIR}/bye00035_lab4_polling.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/bye00035_lab4_polling.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1768511409/bye00035_lab4_interrupt.o: ../bye00035_lab4_v001.X/bye00035_lab4_interrupt.c  .generated_files/flags/default/38f7aeb489d63a748438f30631aa75db02af23ae .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}/_ext/1768511409" 
	@${RM} ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bye00035_lab4_v001.X/bye00035_lab4_interrupt.c  -o ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1768511409/bye00035_lab4_interrupt.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1768511409/bye00035_lab4_main.o: ../bye00035_lab4_v001.X/bye00035_lab4_main.c  .generated_files/flags/default/1eb6d1703503e1ca33cf4748b64ac31cc9d4f046 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}/_ext/1768511409" 
	@${RM} ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bye00035_lab4_v001.X/bye00035_lab4_main.c  -o ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1768511409/bye00035_lab4_main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/bye00035_lab4_polling.o: bye00035_lab4_polling.c  .generated_files/flags/default/ab555345dde1024fb9596efdca61082b9a24cb3d .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bye00035_lab4_polling.o.d 
	@${RM} ${OBJECTDIR}/bye00035_lab4_polling.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bye00035_lab4_polling.c  -o ${OBJECTDIR}/bye00035_lab4_polling.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/bye00035_lab4_polling.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1768511409/bye00035_lab4_interrupt.o: ../bye00035_lab4_v001.X/bye00035_lab4_interrupt.c  .generated_files/flags/default/c6a34b0971cc5c5184909da8ab06f831f4244008 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}/_ext/1768511409" 
	@${RM} ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bye00035_lab4_v001.X/bye00035_lab4_interrupt.c  -o ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1768511409/bye00035_lab4_interrupt.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1768511409/bye00035_lab4_main.o: ../bye00035_lab4_v001.X/bye00035_lab4_main.c  .generated_files/flags/default/3aac06fcdc0baa7422f26d0e02fbfd64e3e06768 .generated_files/flags/default/b10d6bd140b348e29df3272eb1901b61423d793e
	@${MKDIR} "${OBJECTDIR}/_ext/1768511409" 
	@${RM} ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bye00035_lab4_v001.X/bye00035_lab4_main.c  -o ${OBJECTDIR}/_ext/1768511409/bye00035_lab4_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1768511409/bye00035_lab4_main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/bye00035_lab4_v001.X_-_Copy.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/bye00035_lab4_v001.X_-_Copy.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/bye00035_lab4_v001.X_-_Copy.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/bye00035_lab4_v001.X_-_Copy.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/bye00035_lab4_v001.X_-_Copy.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
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
