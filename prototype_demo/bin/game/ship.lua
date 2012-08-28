require "class"

Ship = class(GameObject, function(self, name, speed, hp)
	GameObject.init(self)
	self.name = name

	self.left = false
	self.right = false
	self.up = false
	self.down = false

	self.speed = speed

	self.points = 0
	self.hp = hp
end)

function Ship:onUpdate(dt)
	-- Method called every frame
	local speedX = 0.0
	local speedY = 0.0

	if self.left then
		speedX = speedX - (self.speed * dt)
	end

	if self.right then
		speedX = speedX + (self.speed * dt)
	end

	if self.up then
		speedY = speedY - (self.speed * dt)
	end

	if self.down then
		speedY = speedY + (self.speed * dt)
	end
end

return Ship