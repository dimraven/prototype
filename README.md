prototype
=========
A library for prototyping c++ class using Lua (from Lua's point of view).

What is prototype
-----------------
Although the name can be "slightly" missleading, it's purpose is straight on. The purpose of this library
is to enable the developer to prototype and extend exposed c++ class methods using the scripting language: Lua.

I've planned on using this library for a game engine i've planned to develop later and a scripting language
is a must when doing that. This project is in reality a project for myself learning the Lua API but if the end
result can be of use for other people then that would be awesome.

Note that it doens't replace pure c++ functions, but it extends methods that are called using the supplied "invoke" 
functionality (So it does not solve the world-hunger problem). But it gives us power of rapid development before
the optimization stage (where we move our code from script to complied code).

How does it work
----------------
Let's look at the Lua side for the moment before examining the how it integrates via C++. Lets assume that we have a
C++ class called "Player". But we decided to prototype an AI player class using the Player class as a base class.

The player class is also invoking the method "onUpdateTick" via the c++ method. It is called 32 times / second.
How does that look like in LUA using this library?

Here is an example of Lua:

    -- Create a player instance and move it to position x,y {10,10}
    local player = Player()
    player:moveToPos({10, 10})
    
    -- Extend the Player and copy it's exposed methods to a new class
    AIPlayer = class(Player, function(self)
        Player.init(self)
    end)
    
    -- Extend a method we know is invoked from C++.
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

Here is an example of C++:

    class Player : public ScriptObject
    {
    public:
        DEFINE_SCRIPT_OBJECT(Player);
        
        Player();
        virtual ~Player();
        
        inline void onUpdateTick()
        {
            Script::invoke(this, "onUpdateTick");
        }
        
        void moveTo(Vector2& pos)
        {
            // Move towards position
        }
        
        Vector2& getPosition()
        {
            return mPosition;
        }
    private:
        Vector2 mPosition;
    };

How do we prevent objects from being deleted?
---------------------------------------------

A problem I had to solve early on was which side was the master of the creation and deletion of the memory of
"scriptable" instances. The solution I ended up with was something of a hybrid. When a new instance is created and
**registered** it creates a Lua table internally and keeps it's reference using (luaL_ref). We then put the instance
and the className inside it. If we would create it using Lua it would look like this:

    local table = {
        _instance = <userdata: new Player()>,
        _className = "Player"
    }

When the object is **unregistered** and deleted on the C++ side it will set the **_instance** value to nil, which means
that we can prevent unneccessary null pointer exceptions. After the unregistration the table look like this:

    local table = {
        _instance = nil,
        _className = "Player"
    }

As you probably understand at this point is that it is only the C++ instance that's been deleted and NOT the Lua
table. I've let Lua's garbage collector handle the cleaning up of those objects.

Credits
-------
http://www.lua.org - The Programming Language Lua.
