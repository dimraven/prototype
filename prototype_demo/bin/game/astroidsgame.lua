require "class"

AstroidsGame = class(Game, function(self)
	Game.init(self)
end)

function AstroidsGame:start()
	local window = GameWindow()
	window:open(1024, 768, "Astroids The Game")

	-- Load the first scene
	self:loadScene("scene0")
	local gameObjects = {}--self.currentScene:getObjects()

	while true do
		if not self:isRunning() then
			break
		end

		for _, object in pairs(gameObjects) do
			-- print(object)

		end
	end

	delete(self.currentScene)
	delete(ship)
	delete(window)
end

-- Load a scene based on it's name (i.e. "scene0")
function AstroidsGame:loadScene(scene)
	-- Loading scene
	require("data.scenes." .. scene)
end

return AstroidsGame