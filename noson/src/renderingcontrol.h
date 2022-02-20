/*
 *      Copyright (C) 2014-2018 Jean-Luc Barriere
 *
 *  This file is part of Noson
 *
 *  Noson is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Noson is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef RENDERINGCONTROL_H
#define	RENDERINGCONTROL_H

#include "local_config.h"
#include "service.h"
#include "eventhandler.h"
#include "subscriptionpool.h"
#include "locked.h"

#include <stdint.h>

namespace NSROOT
{
  class Subscription;

  class RenderingControl : public Service, public EventSubscriber
  {
  public:
    RenderingControl(const std::string& serviceHost, unsigned servicePort);
    RenderingControl(const std::string& serviceHost, unsigned servicePort, SubscriptionPoolPtr& subscriptionPool, void* CBHandle = nullptr, EventCB eventCB = nullptr);
    ~RenderingControl() override;

    static const std::string Name;
    static const std::string ControlURL;
    static const std::string EventURL;
    static const std::string SCPDURL;

    static const char* CH_MASTER;

    const std::string& GetName() const override { return Name; }

    const std::string& GetControlURL() const override { return ControlURL; }

    const std::string& GetEventURL() const override { return EventURL; }

    const std::string& GetSCPDURL() const override { return SCPDURL; }

    bool GetVolume(uint8_t* value, const char* channel = CH_MASTER);

    bool SetVolume(uint8_t value, const char* channel = CH_MASTER);

    bool GetVolumeDecibel(int16_t *value, const char* channel = CH_MASTER);

    bool SetVolumeDecibel(int16_t value, const char* channel = CH_MASTER);

    bool GetMute(uint8_t* value, const char* channel = CH_MASTER);

    bool SetMute(uint8_t value, const char* channel = CH_MASTER);

    bool GetNightmode(int16_t* value);

    bool SetNightmode(int16_t value);

    bool GetSubGain(int16_t* value);

    bool SetSubGain(int16_t value);

    bool GetTreble(int8_t* value);

    bool SetTreble(int8_t value);

    bool GetBass(int8_t* value);

    bool SetBass(int8_t value);

    bool GetSupportsOutputFixed(uint8_t* value);

    bool GetOutputFixed(uint8_t* value);

    bool SetOutputFixed(uint8_t value);

    bool GetLoudness(uint8_t* value, const char* channel = CH_MASTER);

    bool SetLoudness(uint8_t value, const char* channel = CH_MASTER);

    bool GetDecibelRange(int16_t *minimum, int16_t *maximum, const char *channel = CH_MASTER);

    // Implements EventSubscriber
    void HandleEventMessage(EventMessagePtr msg) override;

    bool Empty() const { return m_msgCount == 0; }

    Locked<RCSProperty>& GetRenderingProperty() { return m_property; }

  private:
    SubscriptionPoolPtr m_subscriptionPool;
    Subscription m_subscription;
    void* m_CBHandle;
    EventCB m_eventCB;
    unsigned m_msgCount;

    Locked<RCSProperty> m_property;
  };
}

#endif	/* RENDERINGCONTROL_H */

