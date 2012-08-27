prototype
=========
A library for prototyping c++ class using LUA (from LUA's point of view).

What is prototype
-----------------
Although the name can be "slightly" missleading, it's purpose is straight on. The purpose of this library
is to enable the developer to prototype and extend exposed c++ class methods using the scripting language: LUA.

I've planned on using this library for a game engine i've planned to develop later and a scripting language
is a must when doing that. This project is in reality a project for myself learning the LUA API but if the end
result can be of use for other people then that would be awesome.

Note that it doens't replace pure c++ functions, but it extends methods that are called using the supplied "invoke" 
functionality (So it does not solve the world-hunger problem). But it gives us power of rapid development before
the optimization stage (where we move our code from script to complied code).

How does it work
----------------
Let's look at the LUA side for the moment before examining the how it integrates via C++. Lets assume that we have a
C++ class called "Player". But we decided to extend the method "onUpdateTick" which is called 32 times / second. 
How does that look like in LUA using this library?

    -- Create a player instance and move it to position x,y {10,10}
    local player = Player()
    player:moveToPos({10, 10})
    
    AIPlayer = class(Player, function(self)
        Player.init(self)
    end)
    
    function AIPlayer:onUpdateTick()
        local enemies = self:findEnemiesAroundMe()
        if enemies then
            attack(enemies)
        end
    end
    
    function AIPlayer:attack(target)
        self:moveTo(target:getPosition())
    end
    
    local aiPlayer = AIPlayer()
    aiPlayer:attack(player)

Credits
-------
http://www.lua.org - The Programming Language Lua.
