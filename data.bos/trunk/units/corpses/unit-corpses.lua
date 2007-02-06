--            ____            
--           / __ )____  _____
--          / __  / __ \/ ___/
--         / /_/ / /_/ (__  ) 
--        /_____/\____/____/  
--
--            Bos Wars
--   A GPL'd futuristic RTS game
--
--	unit-corpses.lua	-	Define the dead
--
--	(c) Copyright 2001-2005 by Fran�ois Beerten, Lutz Sammer and Crestez Leonard
--
--      This program is free software; you can redistribute it and/or modify
--      it under the terms of the GNU General Public License as published by
--      the Free Software Foundation; either version 2 of the License, or
--      (at your option) any later version.
--  
--      This program is distributed in the hope that it will be useful,
--      but WITHOUT ANY WARRANTY; without even the implied warranty of
--      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--      GNU General Public License for more details.
--  
--      You should have received a copy of the GNU General Public License
--      along with this program; if not, write to the Free Software
--      Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
--
--	$Id$


DefineAnimations("animations-elitebuild2", {
    Death = {"unbreakable begin", "wait 1", "frame 0", "wait 2000", 
        "frame 0", "wait 200", "frame 0", "wait 200", "frame 1", "wait 200",
        "frame 1", "wait 200", "frame 1", "wait 1", "unbreakable end", "wait 1", },
    })

DefineUnitType("build-dead-body2", {
	Name = "BuildingCrater",
	Image = {"file", "units/corpses/build-dead-2.png", "size", {64, 64}},
	Animations = "animations-elitebuild2", Icon = "icon-cancel",
	Speed = 0, HitPoints = 999, DrawLevel = 10,
	TileSize = {2, 2}, BoxSize = {60, 60}, SightRange = 1,
	BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
	Priority = 0, Type = "land", Building = true, Vanishes = true
	})


