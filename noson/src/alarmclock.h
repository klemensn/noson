/*
 *      Copyright (C) 2018 Jean-Luc Barriere
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

#ifndef ALARMCLOCK_H
#define ALARMCLOCK_H

#include "local_config.h"
#include "service.h"
#include "eventhandler.h"
#include "subscriptionpool.h"
#include "locked.h"
#include "alarm.h"

#include <stdint.h>
#include <vector>

namespace NSROOT
{
  class Subscription;

  class ACProperty
  {
  public:
    ACProperty()
    : EventSEQ(0)
    , timeGeneration(0)
    { }

    virtual ~ACProperty();

    unsigned EventSEQ;
    std::string EventSID;
    std::string timeZone;
    std::string timeServer;
    unsigned timeGeneration;
    std::string timeFormat;
    std::string dateFormat;
    std::string dailyIndexRefreshTime;
    std::string alarmListVersion;
  };

  class AlarmClock : public Service, public EventSubscriber
  {
  public:
    AlarmClock(const std::string& serviceHost, unsigned servicePort);
    AlarmClock(const std::string& serviceHost, unsigned servicePort, SubscriptionPoolPtr& subscriptionPool, void* CBHandle = nullptr, EventCB eventCB = nullptr);
    ~AlarmClock() override;

    static const std::string Name;
    static const std::string ControlURL;
    static const std::string EventURL;
    static const std::string SCPDURL;

    const std::string& GetName() const override { return Name; }

    const std::string& GetControlURL() const override { return ControlURL; }

    const std::string& GetEventURL() const override { return EventURL; }

    const std::string& GetSCPDURL() const override { return SCPDURL; }

    typedef enum
    {
      RecurrenceDaily,
      RecurrenceWeekDays,
      RecurrenceWeekEnds,
      RecurrenceOnce,
      RecurrenceOn,
    } Recurrence_t;

    bool CreateAlarm(Alarm& alarm);

    bool UpdateAlarm(const Alarm& alarm);

    bool DestroyAlarm(const std::string& id);

    bool ListAlarms(std::vector<AlarmPtr>& alarms);

    // Implements EventSubscriber
    void HandleEventMessage(EventMessagePtr msg) override;

    bool Empty() const { return m_msgCount == 0; }

    Locked<ACProperty>& GetACProperty() { return m_property; }

  private:
    SubscriptionPoolPtr m_subscriptionPool;
    Subscription m_subscription;
    void* m_CBHandle;
    EventCB m_eventCB;
    unsigned m_msgCount;

    Locked<ACProperty> m_property;

    static bool ParseAlarmList(const std::string& xml, AlarmList& alarms);
  };
}

#endif /* ALARMCLOCK_H */

