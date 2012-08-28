require "class"

local Player = require "game.player"

BreakoutGame = class(Game, function(self)
	Game.init(self)
end)

function BreakoutGame:start()
	local window = GameWindow()
	window:open()

	-- Create our game objects
	local player = Player()

	delete(player)
	delete(window)
end

-- Start the breakout game
game = BreakoutGame()
game:start()

delete(game)