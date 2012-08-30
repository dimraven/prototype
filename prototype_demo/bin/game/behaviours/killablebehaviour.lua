require "class"

KillableBehaviour = class(Behaviour, function(self, hp)
	Behaviour.init(self)
	self.hp = hp
end)


return KillableBehaviour