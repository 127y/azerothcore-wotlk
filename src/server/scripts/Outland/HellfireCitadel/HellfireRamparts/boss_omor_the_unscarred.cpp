/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "hellfire_ramparts.h"

enum Says
{
    SAY_AGGRO                   = 0,
    SAY_SUMMON                  = 1,
    SAY_CURSE                   = 2,
    SAY_KILL                    = 3,
    SAY_DIE                     = 4,
    SAY_WIPE                    = 5
};

enum Spells
{
    SPELL_SHADOW_BOLT           = 30686,
    SPELL_SUMMON_FIENDISH_HOUND = 30707,
    SPELL_TREACHEROUS_AURA      = 30695,
    SPELL_DEMONIC_SHIELD        = 31901,
};

enum Misc
{
    EVENT_SUMMON1               = 1,
    EVENT_SUMMON2               = 2,
    EVENT_TREACHEROUS_AURA      = 3,
    EVENT_DEMONIC_SHIELD        = 4,
    EVENT_KILL_TALK             = 5
};

class boss_omor_the_unscarred : public CreatureScript
{
public:
    boss_omor_the_unscarred() : CreatureScript("boss_omor_the_unscarred") { }

    struct boss_omor_the_unscarredAI : public BossAI
    {
        boss_omor_the_unscarredAI(Creature* creature) : BossAI(creature, DATA_OMOR_THE_UNSCARRED)
        {
            SetCombatMovement(false);
        }

        void Reset() override
        {
            Talk(SAY_WIPE);
            BossAI::Reset();
            _targetGUID.Clear();
        }

        void JustEngagedWith(Unit* who) override
        {
            Talk(SAY_AGGRO);
            BossAI::JustEngagedWith(who);

            events.ScheduleEvent(EVENT_SUMMON1, 10000);
            events.ScheduleEvent(EVENT_SUMMON2, 25000);
            events.ScheduleEvent(EVENT_TREACHEROUS_AURA, 6000);
            events.ScheduleEvent(EVENT_DEMONIC_SHIELD, 1000);
        }

        void KilledUnit(Unit*) override
        {
            if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
            {
                Talk(SAY_KILL);
                events.ScheduleEvent(EVENT_KILL_TALK, 6000);
            }
        }

        void JustSummoned(Creature* summon) override
        {
            Talk(SAY_SUMMON);
            summons.Summon(summon);
            summon->SetInCombatWithZone();
        }

        void JustDied(Unit* killer) override
        {
            Talk(SAY_DIE);
            BossAI::JustDied(killer);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
                case EVENT_SUMMON1:
                    Talk(SAY_SUMMON);
                    me->CastSpell(me, SPELL_SUMMON_FIENDISH_HOUND, false);
                    break;
                case EVENT_SUMMON2:
                    me->CastSpell(me, SPELL_SUMMON_FIENDISH_HOUND, false);
                    events.ScheduleEvent(EVENT_SUMMON2, 15000);
                    break;
                case EVENT_TREACHEROUS_AURA:
                    if (roll_chance_i(33))
                        Talk(SAY_CURSE);
                    if (Unit* target = SelectTarget(SelectTargetMethod::Random, 0))
                        me->CastSpell(target, SPELL_TREACHEROUS_AURA, false);
                    events.ScheduleEvent(EVENT_TREACHEROUS_AURA, urand(12000, 18000));
                    break;
                case EVENT_DEMONIC_SHIELD:
                    if (me->HealthBelowPct(21))
                    {
                        me->CastSpell(me, SPELL_DEMONIC_SHIELD, false);
                        events.ScheduleEvent(EVENT_DEMONIC_SHIELD, 15000);
                    }
                    else
                        events.ScheduleEvent(EVENT_DEMONIC_SHIELD, 1000);
                    break;
            }

            if (!me->GetVictim() || !me->isAttackReady())
                return;

            if (me->IsWithinMeleeRange(me->GetVictim()))
            {
                me->GetMotionMaster()->MoveChase(me->GetVictim());
                DoMeleeAttackIfReady();
            }
            else
            {
                me->GetMotionMaster()->Clear();
                me->CastSpell(me->GetVictim(), SPELL_SHADOW_BOLT, false);
                me->resetAttackTimer();
            }
        }

    private:
        ObjectGuid _targetGUID;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetHellfireRampartsAI<boss_omor_the_unscarredAI>(creature);
    }
};

void AddSC_boss_omor_the_unscarred()
{
    new boss_omor_the_unscarred();
}
