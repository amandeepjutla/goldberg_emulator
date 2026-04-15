/* Copyright (C) 2019 Mr Goldberg
   This file is part of the Goldberg Emulator

   The Goldberg Emulator is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   The Goldberg Emulator is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the Goldberg Emulator; if not, see
   <http://www.gnu.org/licenses/>.  */

#include "base.h"

class Steam_Timeline :
public ISteamTimeline
{
    std::atomic<TimelineEventHandle_t> next_timeline_event_handle { 1 };

    TimelineEventHandle_t generate_timeline_event_handle()
    {
        return next_timeline_event_handle++;
    }

public:
    void SetTimelineTooltip( const char *pchDescription, float flTimeDelta )
    {
        PRINT_DEBUG("Steam_Timeline::SetTimelineTooltip %s %f\n", pchDescription ? pchDescription : "", flTimeDelta);
    }

    void ClearTimelineTooltip( float flTimeDelta )
    {
        PRINT_DEBUG("Steam_Timeline::ClearTimelineTooltip %f\n", flTimeDelta);
    }

    void SetTimelineGameMode( ETimelineGameMode eMode )
    {
        PRINT_DEBUG("Steam_Timeline::SetTimelineGameMode %i\n", eMode);
    }

    TimelineEventHandle_t AddInstantaneousTimelineEvent( const char *pchTitle, const char *pchDescription, const char *pchIcon, uint32 unIconPriority, float flStartOffsetSeconds, ETimelineEventClipPriority ePossibleClip )
    {
        PRINT_DEBUG("Steam_Timeline::AddInstantaneousTimelineEvent %s %s %s %u %f %i\n", pchTitle ? pchTitle : "", pchDescription ? pchDescription : "", pchIcon ? pchIcon : "", unIconPriority, flStartOffsetSeconds, ePossibleClip);
        return generate_timeline_event_handle();
    }

    TimelineEventHandle_t AddRangeTimelineEvent( const char *pchTitle, const char *pchDescription, const char *pchIcon, uint32 unIconPriority, float flStartOffsetSeconds, float flDuration, ETimelineEventClipPriority ePossibleClip )
    {
        PRINT_DEBUG("Steam_Timeline::AddRangeTimelineEvent %s %s %s %u %f %f %i\n", pchTitle ? pchTitle : "", pchDescription ? pchDescription : "", pchIcon ? pchIcon : "", unIconPriority, flStartOffsetSeconds, flDuration, ePossibleClip);
        return generate_timeline_event_handle();
    }

    TimelineEventHandle_t StartRangeTimelineEvent( const char *pchTitle, const char *pchDescription, const char *pchIcon, uint32 unPriority, float flStartOffsetSeconds, ETimelineEventClipPriority ePossibleClip )
    {
        PRINT_DEBUG("Steam_Timeline::StartRangeTimelineEvent %s %s %s %u %f %i\n", pchTitle ? pchTitle : "", pchDescription ? pchDescription : "", pchIcon ? pchIcon : "", unPriority, flStartOffsetSeconds, ePossibleClip);
        return generate_timeline_event_handle();
    }

    void UpdateRangeTimelineEvent( TimelineEventHandle_t ulEvent, const char *pchTitle, const char *pchDescription, const char *pchIcon, uint32 unPriority, ETimelineEventClipPriority ePossibleClip )
    {
        PRINT_DEBUG("Steam_Timeline::UpdateRangeTimelineEvent %llu %s %s %s %u %i\n", ulEvent, pchTitle ? pchTitle : "", pchDescription ? pchDescription : "", pchIcon ? pchIcon : "", unPriority, ePossibleClip);
    }

    void EndRangeTimelineEvent( TimelineEventHandle_t ulEvent, float flEndOffsetSeconds )
    {
        PRINT_DEBUG("Steam_Timeline::EndRangeTimelineEvent %llu %f\n", ulEvent, flEndOffsetSeconds);
    }

    void RemoveTimelineEvent( TimelineEventHandle_t ulEvent )
    {
        PRINT_DEBUG("Steam_Timeline::RemoveTimelineEvent %llu\n", ulEvent);
    }

    SteamAPICall_t DoesEventRecordingExist( TimelineEventHandle_t ulEvent )
    {
        PRINT_DEBUG("Steam_Timeline::DoesEventRecordingExist %llu\n", ulEvent);
        return k_uAPICallInvalid;
    }

    void StartGamePhase()
    {
        PRINT_DEBUG("Steam_Timeline::StartGamePhase\n");
    }

    void EndGamePhase()
    {
        PRINT_DEBUG("Steam_Timeline::EndGamePhase\n");
    }

    void SetGamePhaseID( const char *pchPhaseID )
    {
        PRINT_DEBUG("Steam_Timeline::SetGamePhaseID %s\n", pchPhaseID ? pchPhaseID : "");
    }

    SteamAPICall_t DoesGamePhaseRecordingExist( const char *pchPhaseID )
    {
        PRINT_DEBUG("Steam_Timeline::DoesGamePhaseRecordingExist %s\n", pchPhaseID ? pchPhaseID : "");
        return k_uAPICallInvalid;
    }

    void AddGamePhaseTag( const char *pchTagName, const char *pchTagIcon, const char *pchTagGroup, uint32 unPriority )
    {
        PRINT_DEBUG("Steam_Timeline::AddGamePhaseTag %s %s %s %u\n", pchTagName ? pchTagName : "", pchTagIcon ? pchTagIcon : "", pchTagGroup ? pchTagGroup : "", unPriority);
    }

    void SetGamePhaseAttribute( const char *pchAttributeGroup, const char *pchAttributeValue, uint32 unPriority )
    {
        PRINT_DEBUG("Steam_Timeline::SetGamePhaseAttribute %s %s %u\n", pchAttributeGroup ? pchAttributeGroup : "", pchAttributeValue ? pchAttributeValue : "", unPriority);
    }

    void OpenOverlayToGamePhase( const char *pchPhaseID )
    {
        PRINT_DEBUG("Steam_Timeline::OpenOverlayToGamePhase %s\n", pchPhaseID ? pchPhaseID : "");
    }

    void OpenOverlayToTimelineEvent( const TimelineEventHandle_t ulEvent )
    {
        PRINT_DEBUG("Steam_Timeline::OpenOverlayToTimelineEvent %llu\n", ulEvent);
    }
};
