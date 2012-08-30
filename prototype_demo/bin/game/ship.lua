require "class"

Ship = class(GameObject, function(self, name, speed, hp)
	GameObject.init(self)
	self.name = name


	self.speed = speed

	self.points = 0
	self.hp = hp
end)

return Ship