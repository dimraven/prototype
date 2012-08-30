require "class"
local Ship = require "game.ship"
local ShipControllerBehaviour = require "game.behaviours.shipcontrollerbehaviour"

AstroidsGame = class(Game, function(self)
	Game.init(self)
end)

function AstroidsGame:start()
	local window = GameWindow()
	window:open(1024, 768, "Astroids The Game")

	-- Create our game objects and add a ship controller behaviour, which listens for key input
	local ship = Ship("John Doe", 10.0, 100)
	ship:addBehaviour(ShipControllerBehaviour(35.0))

	-- self:addGameObject(ship)

	delete(ship)
	delete(window)
end

return AstroidsGame