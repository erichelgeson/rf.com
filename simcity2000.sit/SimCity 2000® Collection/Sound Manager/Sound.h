/************************************************************ Sound Manager 3.0 release Created: Tuesday, June 29, 1993 3:28:55 PM Sound.h C Interface to the Macintosh Libraries  Copyright Apple Computer, Inc. 1986-1993  All rights reserved************************************************************/#ifndef __SOUND__#define __SOUND__#ifndef __TYPES__#include <Types.h>#endif#ifndef __FILES__#include <Files.h>#endif/*Gestalt information, to be merged into Gestalt interfaces*/enum {//#define gestaltSoundAttr  'snd '			/*sound attributes*///gestaltStereoCapability = 0,				/*sound hardware has stereo capability*///gestaltStereoMixing = 1,					/*stereo mixing on external speaker*///gestaltSoundIOMgrPresent = 3,				/*The Sound I/O Manager is present*///gestaltBuiltInSoundInput = 4,				/*built-in Sound Input hardware is present*///gestaltHasSoundInputDevice = 5,			/*Sound Input device available*/ gestaltPlayAndRecord = 6,					/*built-in hardware can play and											record simultaneously*//*the following bits were not defined prior to Sound Mgr 3.0*/ gestalt16BitSoundIO = 7,					/*sound hardware can play and record											16-bit samples*/ gestaltStereoInput = 8,					/*sound hardware can record stereo*/ gestaltLineLevelInput = 9,					/*sound input port requires line level*/ gestaltSndPlayDoubleBuffer = 10,			/*SndPlayDoubleBuffer available*/ gestaltMultiChannels = 11,					/*multiple channel support*/ gestalt16BitAudioSupport = 12				/*16 bit audio data supported*/};enum { swMode = -1,								/*Sound Driver modes*/ ftMode = 1, ffMode = 0,#define soundListRsrc 'snd '				/*Resource type used by Sound Manager*/#define kSoundHardwareType 'sdev'			/*component type for sound devices*/#define twelfthRootTwo 1.05946309434 rate44khz = 0xAC440000,					/*44100.00000 in fixed-point*/ rate22khz = 0x56EE8BA3,					/*22254.54545 in fixed-point*/ rate11khz = 0x2B7745D1,					/*11127.27273 in fixed-point*//*synthesizer numbers for SndNewChannel*/ squareWaveSynth = 1,						/*square wave synthesizer*/ waveTableSynth = 3,						/*wave table synthesizer*/ sampledSynth = 5,							/*sampled sound synthesizer*//*old Sound Manager MACE synthesizer numbers*/ MACE3snthID = 11, MACE6snthID = 13, kMiddleC = 60,								/*MIDI note value for middle C*/ kSimpleBeepID = 1,							/*reserved resource ID for Simple Beep*/ kFullVolume = 0x0100,						/*1.0, setting for full hardware output volume*//*command numbers for SndDoCommand and SndDoImmediate*/ nullCmd = 0, initCmd = 1, freeCmd = 2, quietCmd = 3, flushCmd = 4, reInitCmd = 5, waitCmd = 10, pauseCmd = 11, resumeCmd = 12, callBackCmd = 13};enum { syncCmd = 14, availableCmd = 24, versionCmd = 25, totalLoadCmd = 26, loadCmd = 27, freqDurationCmd = 40, restCmd = 41, freqCmd = 42, ampCmd = 43, timbreCmd = 44, getAmpCmd = 45, volumeCmd = 46,							/*sound manager 3.0 or later only*/ getVolumeCmd = 47,							/*sound manager 3.0 or later only*/ waveTableCmd = 60, phaseCmd = 61};enum { soundCmd = 80, bufferCmd = 81, rateCmd = 82, continueCmd = 83, doubleBufferCmd = 84, getRateCmd = 85, sizeCmd = 90, convertCmd = 91, stdQLength = 128, dataOffsetFlag = 0x8000,/*channel initialization parameters*/ waveInitChannelMask = 0x07, waveInitChannel0 = 0x04,					/*wave table only, Sound Manager 2.0 and earlier*/ waveInitChannel1 = 0x05,					/*wave table only, Sound Manager 2.0 and earlier*/ waveInitChannel2 = 0x06,					/*wave table only, Sound Manager 2.0 and earlier*/ waveInitChannel3 = 0x07,					/*wave table only, Sound Manager 2.0 and earlier*/ initChan0 = waveInitChannel0,				/*obsolete spelling*/ initChan1 = waveInitChannel1,				/*obsolete spelling*/ initChan2 = waveInitChannel2,				/*obsolete spelling*/ initChan3 = waveInitChannel3,				/*obsolete spelling*/ initPanMask = 0x0003,						/*mask for right/left pan values*/ initSRateMask = 0x0030,					/*mask for sample rate values*/ initStereoMask = 0x00C0,					/*mask for mono/stereo values*/ initCompMask = 0xFF00						/*mask for compression IDs*/};enum { initChanLeft = 0x0002,						/*left stereo channel*/ initChanRight = 0x0003,					/*right stereo channel*/ initNoInterp = 0x0004,						/*no linear interpolation*/ initNoDrop = 0x0008,						/*no drop-sample conversion*/ initMono = 0x0080,							/*monophonic channel*/ initStereo = 0x00C0,						/*stereo channel*/ initMACE3 = 0x0300,						/*MACE 3:1*/ initMACE6 = 0x0400,						/*MACE 6:1*/ kUseOptionalOutputDevice = -1,				/*only for Sound Manager 3.0 or later*/ stdSH = 0x00,								/*Standard sound header encode value*/ extSH = 0xFF,								/*Extended sound header encode value*/ cmpSH = 0xFE,								/*Compressed sound header encode value*/ notCompressed = 0,							/*compression ID's*/ fixedCompression = -1,						/*compression ID for fixed-sized compression*/ variableCompression = -2,					/*compression ID for variable-sized compression*/ twoToOne = 1, eightToThree = 2, threeToOne = 3, sixToOne = 4, outsideCmpSH = 0							/*MACE constants*/};enum { insideCmpSH = 1, aceSuccess = 0, aceMemFull = 1, aceNilBlock = 2, aceBadComp = 3, aceBadEncode = 4, aceBadDest = 5, aceBadCmd = 6, sixToOnePacketSize = 8, threeToOnePacketSize = 16, stateBlockSize = 64, leftOverBlockSize = 32, firstSoundFormat = 0x0001,					/*general sound format*/ secondSoundFormat = 0x0002,				/*special sampled sound format (HyperCard)*/ dbBufferReady = 0x00000001,				/*double buffer is filled*/ dbLastBuffer = 0x00000004,					/*last double buffer to play*/ sysBeepDisable = 0x0000,					/*SysBeep() enable flags*/ sysBeepEnable = 0x0001, unitTypeNoSelection = 0xFFFF,				/*unitTypes for AudioSelection.unitType*/ unitTypeSeconds = 0x0000};/*Structures for Sound Driver*/typedef unsigned char FreeWave[30001];struct FFSynthRec { short mode; Fixed count; FreeWave waveBytes;};typedef struct FFSynthRec FFSynthRec;typedef FFSynthRec *FFSynthPtr;struct Tone { short count; short amplitude; short duration;};typedef struct Tone Tone;typedef Tone Tones[5001];struct SWSynthRec { short mode; Tones triplets;};typedef struct SWSynthRec SWSynthRec;typedef SWSynthRec *SWSynthPtr;typedef unsigned char Wave[256];typedef Wave *WavePtr;struct FTSoundRec { short duration; Fixed sound1Rate; long sound1Phase; Fixed sound2Rate; long sound2Phase; Fixed sound3Rate; long sound3Phase; Fixed sound4Rate; long sound4Phase; WavePtr sound1Wave; WavePtr sound2Wave; WavePtr sound3Wave; WavePtr sound4Wave;};typedef struct FTSoundRec FTSoundRec;typedef FTSoundRec *FTSndRecPtr;struct FTSynthRec { short mode; FTSndRecPtr sndRec;};typedef struct FTSynthRec FTSynthRec;typedef FTSynthRec *FTSynthPtr;typedef pascal void (*SndCompletionProcPtr)(void);/*Structures for Sound Manager*/struct SndCommand { unsigned short cmd; short param1; long param2;};typedef struct SndCommand SndCommand;typedef struct SndChannel SndChannel;typedef SndChannel *SndChannelPtr;typedef pascal void (*SndCallBackProcPtr)(SndChannelPtr chan, SndCommand *cmd);struct SndChannel {    struct SndChannel *nextChan;    Ptr firstMod;                      		/*reserved for the Sound Manager*/    SndCallBackProcPtr callBack;    long userInfo;    long wait;                         		/*The following is for internal Sound Manager use only.*/    SndCommand cmdInProgress;    short flags;    short qLength;    short qHead;    short qTail;    SndCommand queue[stdQLength];};/*MACE structures*/struct StateBlock { short stateVar[stateBlockSize];};typedef struct StateBlock StateBlock;typedef StateBlock *StateBlockPtr;struct LeftOverBlock { unsigned long count; char sampleArea[leftOverBlockSize];};typedef struct LeftOverBlock LeftOverBlock;typedef LeftOverBlock *LeftOverBlockPtr;struct ModRef { unsigned short modNumber; long modInit;};typedef struct ModRef ModRef;struct SndListResource { short format; short numModifiers; ModRef modifierPart[1];					/*This is a variable length array*/ short numCommands; SndCommand commandPart[1];					/*This is a variable length array*/ char dataPart[1];							/*This is a variable length array*/};typedef struct SndListResource SndListResource;typedef SndListResource *SndListPtr;typedef SndListPtr *SndListHndl;struct Snd2ListResource {					/*HyperCard sound resource format*/ short format; short refCount; short numCommands; SndCommand commandPart[1];					/*This is a variable length array*/ char dataPart[1];							/*This is a variable length array*/};typedef struct Snd2ListResource Snd2ListResource;typedef Snd2ListResource *Snd2ListPtr;typedef Snd2ListPtr *Snd2ListHndl;struct SoundHeader { Ptr samplePtr;								/*if NIL then samples are in sampleArea*/ unsigned long length;						/*length of sound in bytes*/ Fixed sampleRate;							/*sample rate for this sound*/ unsigned long loopStart;					/*start of looping portion*/ unsigned long loopEnd;						/*end of looping portion*/ unsigned char encode;						/*header encoding*/ unsigned char baseFrequency;				/*baseFrequency value*/ unsigned char sampleArea[1];				/*space for when samples follow directly*/};typedef struct SoundHeader SoundHeader;typedef SoundHeader *SoundHeaderPtr;struct CmpSoundHeader { Ptr samplePtr;								/*if nil then samples are in sample area*/ unsigned long numChannels;					/*number of channels i.e. mono = 1*/ Fixed sampleRate;							/*sample rate in Apples Fixed point representation*/ unsigned long loopStart;					/*loopStart of sound before compression*/ unsigned long loopEnd;						/*loopEnd of sound before compression*/ unsigned char encode;						/*data structure used , stdSH, extSH, or cmpSH*/ unsigned char baseFrequency;				/*same meaning as regular SoundHeader*/ unsigned long numFrames;					/*length in frames ( packetFrames or sampleFrames )*/ extended80	 AIFFSampleRate;				/*IEEE sample rate*/ Ptr markerChunk;							/*sync track*/ OSType format;								/*data format type, was futureUse1*/ unsigned long futureUse2;					/*reserved by Apple*/ StateBlockPtr stateVars;					/*pointer to State Block*/ LeftOverBlockPtr leftOverSamples;			/*used to save truncated samples between compression calls*/ unsigned short compressionID;				/*0 means no compression, non zero means compressionID*/ unsigned short packetSize;					/*number of bits in compressed sample packet*/ unsigned short snthID;						/*resource ID of Sound Manager snth that contains NRT C/E*/ unsigned short sampleSize;					/*number of bits in non-compressed sample*/ unsigned char sampleArea[1];				/*space for when samples follow directly*/};typedef struct CmpSoundHeader CmpSoundHeader;typedef CmpSoundHeader *CmpSoundHeaderPtr;struct ExtSoundHeader { Ptr samplePtr;								/*if nil then samples are in sample area*/ unsigned long numChannels;					/*number of channels,  ie mono = 1*/ Fixed sampleRate;							/*sample rate in Apples Fixed point representation*/ unsigned long loopStart;					/*same meaning as regular SoundHeader*/ unsigned long loopEnd;						/*same meaning as regular SoundHeader*/ unsigned char encode;						/*data structure used , stdSH, extSH, or cmpSH*/ unsigned char baseFrequency;				/*same meaning as regular SoundHeader*/ unsigned long numFrames;					/*length in total number of frames*/ extended80 AIFFSampleRate;					/*IEEE sample rate*/ Ptr markerChunk;							/*sync track*/ Ptr instrumentChunks;						/*AIFF instrument chunks*/ Ptr AESRecording; unsigned short sampleSize;					/*number of bits in sample*/ unsigned short futureUse1;					/*reserved by Apple*/ unsigned long futureUse2;					/*reserved by Apple*/ unsigned long futureUse3;					/*reserved by Apple*/ unsigned long futureUse4;					/*reserved by Apple*/ unsigned char sampleArea[1];				/*space for when samples follow directly*/};typedef struct ExtSoundHeader ExtSoundHeader;typedef ExtSoundHeader *ExtSoundHeaderPtr;struct ConversionBlock { short destination; short unused; CmpSoundHeaderPtr inputPtr; CmpSoundHeaderPtr outputPtr;};typedef struct ConversionBlock ConversionBlock;typedef ConversionBlock *ConversionBlockPtr;struct SMStatus { short smMaxCPULoad; short smNumChannels; short smCurCPULoad;};typedef struct SMStatus SMStatus;typedef SMStatus *SMStatusPtr;struct SCStatus { Fixed scStartTime; Fixed scEndTime; Fixed scCurrentTime; Boolean scChannelBusy; Boolean scChannelDisposed; Boolean scChannelPaused; Boolean scUnused; unsigned long scChannelAttributes; long scCPULoad;};typedef struct SCStatus SCStatus;typedef SCStatus *SCStatusPtr;struct AudioSelection { long unitType; Fixed selStart; Fixed selEnd;};typedef pascal void (*FilePlayCompletionProcPtr)(SndChannelPtr chan);typedef struct AudioSelection AudioSelection;typedef AudioSelection *AudioSelectionPtr;struct SndDoubleBuffer { long dbNumFrames; long dbFlags; long dbUserInfo[2]; char dbSoundData[1];};typedef struct SndDoubleBuffer SndDoubleBuffer;typedef SndDoubleBuffer *SndDoubleBufferPtr;typedef pascal void (*SndDoubleBackProcPtr) (SndChannelPtr chan,           SndDoubleBufferPtr doubleBufferPtr);struct SndDoubleBufferHeader { short dbhNumChannels; short dbhSampleSize; short dbhCompressionID; short dbhPacketSize; Fixed dbhSampleRate; SndDoubleBufferPtr dbhBufferPtr[2]; SndDoubleBackProcPtr dbhDoubleBack;};typedef struct SndDoubleBufferHeader SndDoubleBufferHeader;typedef SndDoubleBufferHeader *SndDoubleBufferHeaderPtr;struct SndDoubleBufferHeader2 {	short					dbhNumChannels;	short					dbhSampleSize;	short					dbhCompressionID;	short					dbhPacketSize;	Fixed					dbhSampleRate;	SndDoubleBufferPtr		dbhBufferPtr[2];	SndDoubleBackProcPtr	dbhDoubleBack;	OSType					dbhFormat;};typedef struct SndDoubleBufferHeader2 SndDoubleBufferHeader2;typedef SndDoubleBufferHeader2 *SndDoubleBufferHeader2Ptr;#ifdef __cplusplusextern "C" {#endifpascal OSErr SndDoCommand(SndChannelPtr chan,const SndCommand *cmd,Boolean noWait) = 0xA803;pascal OSErr SndDoImmediate(SndChannelPtr chan,const SndCommand *cmd) = 0xA804;pascal OSErr SndNewChannel(SndChannelPtr *chan,short synth,long init, SndCallBackProcPtr userRoutine) = 0xA807;pascal OSErr SndDisposeChannel(SndChannelPtr chan,Boolean quietNow) = 0xA801;pascal OSErr SndPlay(SndChannelPtr chan,Handle sndHdl,Boolean async) = 0xA805;pascal OSErr SndAddModifier(SndChannelPtr chan,Ptr modifier, short id,long init) = 0xA802;pascal OSErr SndControl(short id,SndCommand *cmd) = 0xA806;pascal void SetSoundVol(short level);#pragma parameter GetSoundVol(__A0)pascal void GetSoundVol(short *level) = {0x4218,0x10B8,0x0260};pascal void StartSound(const void *synthRec,long numBytes,SndCompletionProcPtr completionRtn);pascal void StopSound(void);pascal Boolean SoundDone(void);pascal NumVersion SndSoundManagerVersion(void) = {0x203C,0x000C,0x0008,0xA800};pascal OSErr SndStartFilePlay(SndChannelPtr chan,short fRefNum,short resNum,	long bufferSize,void *theBuffer,AudioSelectionPtr theSelection,	FilePlayCompletionProcPtr theCompletion,Boolean async) = {0x203C,0x0D00,0x0008,0xA800};pascal OSErr SndPauseFilePlay(SndChannelPtr chan) = {0x203C,0x0204,0x0008,0xA800};pascal OSErr SndStopFilePlay(SndChannelPtr chan,Boolean quietNow) = {0x203C,0x0308,0x0008,0xA800};pascal OSErr SndChannelStatus(SndChannelPtr chan,short theLength,SCStatusPtr theStatus) = {0x203C,0x0010,0x0008,0xA800};pascal OSErr SndManagerStatus(short theLength,SMStatusPtr theStatus) = {0x203C,0x0014,0x0008,0xA800};pascal void SndGetSysBeepState(short *sysBeepState) = {0x203C,0x0018,0x0008,0xA800};pascal OSErr SndSetSysBeepState(short sysBeepState) = {0x203C,0x001C,0x0008,0xA800};pascal OSErr SndPlayDoubleBuffer(SndChannelPtr chan,SndDoubleBufferHeaderPtr theParams) = {0x203C,0x0020,0x0008,0xA800};pascal NumVersion MACEVersion(void) = {0x203C,0x0000,0x0010,0xA800};pascal void Comp3to1(const void *inBuffer,void *outBuffer,unsigned long cnt, const void *inState,void *outState,unsigned long numChannels,unsigned long whichChannel) = {0x203C,0x0004,0x0010,0xA800};pascal void Exp1to3(const void *inBuffer,void *outBuffer,unsigned long cnt, const void *inState,void *outState,unsigned long numChannels,unsigned long whichChannel) = {0x203C,0x0008,0x0010,0xA800};pascal void Comp6to1(const void *inBuffer,void *outBuffer,unsigned long cnt, const void *inState,void *outState,unsigned long numChannels,unsigned long whichChannel) = {0x203C,0x000C,0x0010,0xA800};pascal void Exp1to6(const void *inBuffer,void *outBuffer,unsigned long cnt, const void *inState,void *outState,unsigned long numChannels,unsigned long whichChannel) = {0x203C,0x0010,0x0010,0xA800};/*Sound Manager 3.0 and later calls*/pascal OSErr GetSysBeepVolume(long *level) = {0x203C,0x0224,0x0018,0xA800};pascal OSErr SetSysBeepVolume(long level) = {0x203C,0x0228,0x0018,0xA800};pascal OSErr GetDefaultOutputVolume(long *level) = {0x203C,0x022C,0x0018,0xA800};pascal OSErr SetDefaultOutputVolume(long level) = {0x203C,0x0230,0x0018,0xA800};pascal OSErr GetSoundHeaderOffset(Handle sndHandle, long *offset) = {0x203C,0x0404,0x0018,0xA800};#ifdef __cplusplus}#endif#endif