require "class"

local Ship = require "game.ship"
local ShipControllerBehaviour = require "game.behaviours.shipcontrollerbehaviour"
local KillableBehaviour = require "game.behaviours.killablebehaviour"

Scene0_Definition = class(SceneDefinition, function(self)
	SceneDefinition.init(self)
end)

function Scene0_Definition:onLoad()
	local objects = {}

	-- player1
	local player1 = Ship("John Doe")
	player1:addBehaviour(ShipControllerBehaviour(35.0))
	player1:addBehaviour(KillableBehaviour(100))
	table.insert(objects, player1)
	-- /player1
	
	-- player2
	local player2 = Ship("Mr. Anderson")
	player2:addBehaviour(ShipControllerBehaviour(35.0))
	player2:addBehaviour(KillableBehaviour(100))
	table.insert(objects, player2)
	-- /player2

	return objects
end

return Scene0_Definition