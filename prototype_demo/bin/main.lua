local AstroidsGame = require "game.astroidsgame"

print(cRoundf(10, 10.2)) -- Should print 20
print(cRoundf(10, 10.6)) -- Should print 21

printDictionary({
	value1 = "10",
	value2 = 101.10
})

-- Start the breakout game
game = AstroidsGame()
game:start()

delete(game)