require "class"
local Ship = require "game.ship"

AstroidsGame = class(Game, function(self)
	Game.init(self)
end)

function AstroidsGame:start()
	local window = GameWindow()
	window:open(1024, 768)

	-- Create our game objects
	local ship = Ship("John Doe", 10.0, 100)

	-- self:addGameObject(ship)

	delete(ship)
	delete(window)
end

return AstroidsGame