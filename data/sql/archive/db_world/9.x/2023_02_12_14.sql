-- DB update 2023_02_12_13 -> 2023_02_12_14
--

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 18385;

DELETE FROM `smart_scripts` WHERE (`entryorguid` = 18385) AND (`source_type` = 0) AND (`id` IN (0));
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(18385, 0, 0, 0, 20, 0, 100, 0, 10201, 0, 0, 0, 0, 80, 1838500, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Rakoria - On Quest \'And Now, the Moment of Truth\' Finished - Run Script');

DELETE FROM `smart_scripts` WHERE (`entryorguid` = 1838500) AND (`source_type` = 9) AND (`id` IN (0, 1, 2, 3, 4));
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1838500, 9, 0, 0, 0, 0, 100, 0, 100, 100, 0, 0, 0, 5, 11, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Rakoria - Actionlist - Play Emote 11'),
(1838500, 9, 1, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Rakoria - Actionlist - Say Line 0'),
(1838500, 9, 2, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 0, 5, 11, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Rakoria - Actionlist - Play Emote 11'),
(1838500, 9, 3, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Rakoria - Actionlist - Say Line 1'),
(1838500, 9, 4, 0, 0, 0, 100, 0, 100, 100, 0, 0, 0, 5, 29, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Rakoria - Actionlist - Play Emote 29');
