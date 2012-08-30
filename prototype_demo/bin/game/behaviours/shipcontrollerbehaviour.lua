require "class"

ShipControllerBehaviour = class(Behaviour, function(self, speed)
	Behaviour.init(self)
	self.speed = speed
end)

function ShipControllerBehaviour:onAdd()
	self.left = false
	self.right = false
	self.up = false
	self.down = false
end

function ShipControllerBehaviour:onKeyDown(key)
	if key == 'W' then
		self.up = true
	end

	if key == 'S' then
		self.down = true
	end

	if key == 'A' then
		self.left = true
	end

	if key == 'D' then
		self.right = true
	end
end

function ShipControllerBehaviour:onKeyUp(key)
	if key == 'W' then
		self.up = false
	end

	if key == 'S' then
		self.down = false
	end

	if key == 'A' then
		self.left = false
	end

	if key == 'D' then
		self.right = false
	end
end

function ShipControllerBehaviour:onUpdate(dt)
	-- Dont have real property support yet!
	-- local owner = self:getOwner()
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

	-- owner.setVelocity({speedX, speedY})
end

return ShipControllerBehaviour