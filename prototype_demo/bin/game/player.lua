require "class"

Player = class(GameObject, function(self)
	GameObject.init(self)
end)


return Player