require "class"
local Ship = require "game.ship"

AstroidsGame = class(Game, function(self)
	Game.init(self)
end)

function AstroidsGame:start()
	local window = GameWindow()
	window:open()

	-- Create our game objects
	local ship = Ship()

	self:addGameObject(ship)

	delete(player)
	delete(window)
end

return AstroidsGame