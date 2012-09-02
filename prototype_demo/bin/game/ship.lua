require "class"

Ship = class(GameObject, function(self, name, metadata)
	self.name = name
	self.metadata = metadata
	GameObject.init(self)
end)

function Ship:onAdd()
	-- self:setMetaData(self.metadata)
end

return Ship