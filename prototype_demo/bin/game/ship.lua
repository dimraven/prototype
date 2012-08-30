require "class"

Ship = class(GameObject, function(self, name)
	GameObject.init(self)
	self.name = name
end)

return Ship