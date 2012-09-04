local Ship = require "game.ship"
local ShipControllerBehaviour = require "game.behaviours.shipcontrollerbehaviour"
local KillableBehaviour = require "game.behaviours.killablebehaviour"

-- player1
local player1 = Ship("John Doe", "data.ships.player1")
player1:addBehaviour(ShipControllerBehaviour(35.0))
player1:addBehaviour(KillableBehaviour(100))
player1:addToScene()
-- /player1
	
-- player2
local player2 = Ship("Mr. Anderson", "data.ships.player2")
player2:addBehaviour(ShipControllerBehaviour(35.0))
player2:addBehaviour(KillableBehaviour(100))
player2:addToScene()
-- /player2