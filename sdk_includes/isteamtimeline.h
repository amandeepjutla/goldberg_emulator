//====== Copyright Valve Corporation, All rights reserved. ====================
//
// Purpose: Interface to Steam Timeline
//
//=============================================================================

#ifndef ISTEAMTIMELINE_H
#define ISTEAMTIMELINE_H
#ifdef _WIN32
#pragma once
#endif

#include "steam_api_common.h"

enum ETimelineGameMode
{
    k_ETimelineGameMode_Invalid = 0,
    k_ETimelineGameMode_Playing = 1,
    k_ETimelineGameMode_Staging = 2,
    k_ETimelineGameMode_Menus = 3,
    k_ETimelineGameMode_LoadingScreen = 4,

    k_ETimelineGameMode_Max,
};

enum ETimelineEventClipPriority
{
    k_ETimelineEventClipPriority_Invalid = 0,
    k_ETimelineEventClipPriority_None = 1,
    k_ETimelineEventClipPriority_Standard = 2,
    k_ETimelineEventClipPriority_Featured = 3,
};

const uint32 k_unMaxTimelinePriority = 1000;
const uint32 k_unTimelinePriority_KeepCurrentValue = 1000000;
const float k_flMaxTimelineEventDuration = 600.f;
const uint32 k_cchMaxPhaseIDLength = 64;

typedef uint64 TimelineEventHandle_t;

#if defined( VALVE_CALLBACK_PACK_SMALL )
#pragma pack( push, 4 )
#elif defined( VALVE_CALLBACK_PACK_LARGE )
#pragma pack( push, 8 )
#else
#error steam_api_common.h should define VALVE_CALLBACK_PACK_xxx
#endif

class ISteamTimeline
{
public:
    virtual void SetTimelineTooltip( const char *pchDescription, float flTimeDelta ) = 0;
    virtual void ClearTimelineTooltip( float flTimeDelta ) = 0;
    virtual void SetTimelineGameMode( ETimelineGameMode eMode ) = 0;

    virtual TimelineEventHandle_t AddInstantaneousTimelineEvent(
        const char *pchTitle,
        const char *pchDescription,
        const char *pchIcon,
        uint32 unIconPriority,
        float flStartOffsetSeconds = 0.f,
        ETimelineEventClipPriority ePossibleClip = k_ETimelineEventClipPriority_None ) = 0;

    virtual TimelineEventHandle_t AddRangeTimelineEvent(
        const char *pchTitle,
        const char *pchDescription,
        const char *pchIcon,
        uint32 unIconPriority,
        float flStartOffsetSeconds = 0.f,
        float flDuration = 0.f,
        ETimelineEventClipPriority ePossibleClip = k_ETimelineEventClipPriority_None ) = 0;

    virtual TimelineEventHandle_t StartRangeTimelineEvent(
        const char *pchTitle,
        const char *pchDescription,
        const char *pchIcon,
        uint32 unPriority,
        float flStartOffsetSeconds,
        ETimelineEventClipPriority ePossibleClip ) = 0;

    virtual void UpdateRangeTimelineEvent(
        TimelineEventHandle_t ulEvent,
        const char *pchTitle,
        const char *pchDescription,
        const char *pchIcon,
        uint32 unPriority,
        ETimelineEventClipPriority ePossibleClip ) = 0;

    virtual void EndRangeTimelineEvent( TimelineEventHandle_t ulEvent, float flEndOffsetSeconds ) = 0;
    virtual void RemoveTimelineEvent( TimelineEventHandle_t ulEvent ) = 0;

    STEAM_CALL_RESULT( SteamTimelineEventRecordingExists_t )
    virtual SteamAPICall_t DoesEventRecordingExist( TimelineEventHandle_t ulEvent ) = 0;

    virtual void StartGamePhase() = 0;
    virtual void EndGamePhase() = 0;
    virtual void SetGamePhaseID( const char *pchPhaseID ) = 0;

    STEAM_CALL_RESULT( SteamTimelineGamePhaseRecordingExists_t )
    virtual SteamAPICall_t DoesGamePhaseRecordingExist( const char *pchPhaseID ) = 0;

    virtual void AddGamePhaseTag( const char *pchTagName, const char *pchTagIcon, const char *pchTagGroup, uint32 unPriority ) = 0;
    virtual void SetGamePhaseAttribute( const char *pchAttributeGroup, const char *pchAttributeValue, uint32 unPriority ) = 0;
    virtual void OpenOverlayToGamePhase( const char *pchPhaseID ) = 0;
    virtual void OpenOverlayToTimelineEvent( const TimelineEventHandle_t ulEvent ) = 0;
};

#define STEAMTIMELINE_INTERFACE_VERSION "STEAMTIMELINE_INTERFACE_V004"

inline ISteamTimeline *SteamTimeline();
STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamTimeline *, SteamTimeline, STEAMTIMELINE_INTERFACE_VERSION );

struct SteamTimelineGamePhaseRecordingExists_t
{
    enum { k_iCallback = k_iSteamTimelineCallbacks + 1 };
    char m_rgchPhaseID[k_cchMaxPhaseIDLength];
    uint64 m_ulRecordingMS;
    uint64 m_ulLongestClipMS;
    uint32 m_unClipCount;
    uint32 m_unScreenshotCount;
};

struct SteamTimelineEventRecordingExists_t
{
    enum { k_iCallback = k_iSteamTimelineCallbacks + 2 };
    uint64 m_ulEventID;
    bool m_bRecordingExists;
};

#pragma pack( pop )

#endif // ISTEAMTIMELINE_H
