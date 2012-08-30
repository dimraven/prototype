require "class"
local Ship = require "game.ship"
local ShipControllerBehaviour = require "game.behaviours.shipcontrollerbehaviour"
local KillableBehaviour = require "game.behaviours.killablebehaviour"

AstroidsGame = class(Game, function(self)
	Game.init(self)
end)

function AstroidsGame:start()
	local window = GameWindow()
	window:open(1024, 768, "Astroids The Game")

	-- Create our game objects and add a ship controller behaviour, which listens for key input
	local ship = Ship("John Doe")
	ship:addBehaviour(ShipControllerBehaviour(35.0))
	ship:addBehaviour(KillableBehaviour(100))

	while true do
		if not self:isRunning() then
			break
		end

		-- Do extra stuff here!!
	end

	delete(ship)
	delete(window)
end

return AstroidsGame