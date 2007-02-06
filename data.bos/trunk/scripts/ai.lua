--            ____            
--           / __ )____  _____
--          / __  / __ \/ ___/
--         / /_/ / /_/ (__  ) 
--        /_____/\____/____/  
--
--            Bos Wars                  
--   A GPL'd futuristic RTS game
--
--	ai.lua		-	Define the AI.
--
--	(c) Copyright 2000-2007 by Lutz Sammer, Frank Loeffler
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
--

-- The list of registered AIs in BOS
-- Every AI has an entry name: {internal_name, name, fun, initfun}
-- See at RegisterAi() for a description what these are
AiList = {}

-- Function to register an AI to BOS
-- Parameters:
-- internal_name : Internal name of the Ai (without leading "ai-"
-- name          : Name of the AI the Player sees and which gets translated
-- fun           : main AI function
-- initfun       : initialization function, can be obmitted
function RegisterAi(internal_name, name, fun, initfun)
print("RegisterAi")
local t = debug.getinfo(fun)
for k,v in pairs(t) do print(tostring(k) .. " = " .. tostring(v)) end
print("----------")
local t = debug.getinfo(print)
for k,v in pairs(t) do print(tostring(k) .. " = " .. tostring(v)) end
  DefineAi("ai-" .. internal_name, "ai-" .. internal_name, fun)
  AiList[name] = {internal_name, name, fun, initfun}
end

DefineAiHelper(
  --
  -- Unit can build which buildings.
  --
  {"build", "unit-engineer",
   "unit-msilo", "unit-dev-yard", "unit-gen", "unit-camp",
   "unit-rfac", "unit-hosp", "unit-vfac", "unit-vault", "unit-gturret",
   "unit-cam", "unit-cannon", "unit-nuke", "unit-radar"},
  --
  -- Building can train which units.
  --
  {"train", "unit-vault", "unit-engineer"},
  {"train", "unit-camp", "unit-assault", "unit-bazoo", "unit-grenadier",
   "unit-dorcoz"},
  {"train", "unit-hosp", "unit-medic"},
  {"train", "unit-vfac", "unit-apcs", "unit-harvester", "unit-artil",
   "unit-buggy", "unit-rtank", "unit-tank"},
  {"train", "unit-dev-yard", "unit-jet", "unit-bomber", "unit-chopper"},
  --
  -- Building can research which spells or upgrades.
  --
  {"research", "unit-rfac", "upgrade-expl", "upgrade-expl2",
   "upgrade-tdril", "upgrade-pdril", "upgrade-ddril"},
  --
  -- Unit can repair which units.
  --
  {"repair", "unit-engineer",
   "unit-msilo", "unit-dev-yard", "unit-gen", "unit-camp", "unit-apcs",
   "unit-rfac", "unit-hosp", "unit-vfac", "unit-vault", "unit-gturret",
   "unit-nuke", "unit-radar"},
  --
  -- Reduce unit limits.
  --
  {"unit-limit", "unit-gen", "food"})

-- Execute all AI init scripts
function InitAiScripts()
  for key,value in next,AiList do
    -- check if this AI actually has an init script
    if (value[4] ~= nil) then
      value[4]()
    end
  end
end

-- Find and load all Ais
local list
local i
local f
list = ListFilesInDirectory("scripts/ais/")

for i,f in ipairs(list) do
  if(string.find(f, "^.*%.lua$")) then
    print("Loading AI: " .. f)
    Load("scripts/ais/" .. f)
  end
end

