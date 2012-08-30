require "class"
local Ship = require "game.ship"
local ShipControllerBehaviour = require "game.behaviours.shipcontrollerbehaviour"

AstroidsGame = class(Game, function(self)
	Game.init(self)
end)

function AstroidsGame:start()
	local window = GameWindow()
	window:open(1024, 768)

	-- Create our game objects and add a ship controller behaviour, which listens for key input
	local ship = Ship("John Doe", 10.0, 100)
	local behaviour = ShipControllerBehaviour(35.0)
	ship:addBehaviour(behaviour)

	-- self:addGameObject(ship)

	delete(behaviour)
	delete(ship)
	delete(window)
end

return AstroidsGame