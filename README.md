prototype
=========
A library for prototyping c++ class using Lua (from Lua's point of view).

### What is prototype ###

Although the name can be "slightly" missleading, it's purpose is straight on. The purpose of this library
is to enable the developer to prototype and extend exposed c++ class methods using the scripting language: Lua.

I've planned on using this library for a game engine that i've planned on developing layer on. Integration with
a scripting language is of course required when doing this. This project is in reality a self-learning project 
for myself so that I can learn how the Lua API works, but if some other developer can use this or learn something from
this then that would be awesome.

Note that this library doens't give you the power of replacing pure c++ classes and methods. What it does is
that it give you the power of extending methods "invoked" using a supplied interface (No - it does not solve the world-hunger problem). 
It gives us power of rapid development before the optimization stage (where we move our code from script to complied code) when developing a game.

### How does it work ###

Let's look at the non-library code for the moment before examining the how it integrates via C++. Lets assume that we have a
C++ class called "Player". Using that class as a base class we've decided to prototype an new AI player class.

The Player class looks like this on the C++ side:

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
        
        void moveTo(Player* target)
        {
            // Move towards position
        }
        
        Vector2& getPosition()
        {
            return mPosition;
        }
        
        std::list<Player*> findEnemiesAroundMe()
        {
            return SceneGraph::scanForObjects(mPosition);
        }
        
    private:
        Vector2 mPosition;
    };

The exposed methods are:
* moveTo
* getPosition
* findEnemiesAroundMe

The methods we are calling on the script side are:
* onUpdateTick (called 32 times / second).

Here is an example of Lua:

    require "class"

    -- We begin by create a player instance and move it to position x,y {10,10}
    local player = Player()
    player:moveToPos({10, 10})
    
    -- Extend the Player class, copy it's exposed methods and extend the methods we want
    -- to achieve the result wew ant.
    AIPlayer = class(Player, function(self)
        -- This must be done to associate this object's "self" reference with the
        -- newely created player instance. The pointer of the player instance is set to self._instance.
        Player.init(self)
    end)
    
    function AIPlayer:onUpdateTick()
        local enemies = self:findEnemiesAroundMe()
        if enemies then
            attack(enemies)
        end
    end
    
    function AIPlayer:attack(target)
        self:moveTo(target)
    end
    
    -- Extend the AIPlayer class with a smarted AI class.
    SmartAIPlayer = class(AIPlayer, function(self)
        AIPlayer.init(self)
        self.sleeping = true
    end)
    
    function SmartAIPlayer:onUpdateTick()
        if not self.sleeping then
            AIPlayer.onUpdateTick(self)
        end
    end
    
    function AIPlayer:attack(target)
        local distance = self:getPosition():distanceTo(target:getPosition())
        if distance > 50.0 then
            self.sleeping = false
            self:moveTo(target)
        end
    end
    
    local aiPlayer = AIPlayer()
    aiPlayer:attack(player)
    
    local smartAiPlayer = SmartAIPlayer()
    smartAIPlayer:attack(player)

The aiPlayer- and the smartAIPlayer instance is still an instance of the class **Player**. But we now have the option of overloading
all the **script** methods associated with **Player** and any other class in the method hierarchy.
If we would perform something like this (Example in Lua):

    local player = Player()
    local aiPlayer = AIPlayer()
    
    player:moveTo(aiPlayer)
    
The "target" parameter available in the "moveTo" method on the C++ side whould still be an instance of the Player class 
but with the AIPlayer script methods associated with it.

### How does it work and how do we prevent deleted objects from being called or referenced? ###

A problem I had to solve early on was which side was the master of the creation and deletion of the memory of
"scriptable" instances. The solution I ended up with was something of a hybrid. When a new instance is created and
**registered** it creates a Lua table internally and keeps it's reference using **luaL_ref**. We then put the instance
in it as lightuserdata and the className as a string inside it. If we would create it using Lua it would look like this:

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

To register and expose a class from the C++ side we only need to do this:

    Player* player = new Player();
    player->registerObject();

We can now send it to the script side without being afraid of it being deleted (and cause a crash).

A deletion of the player instance after this is of course okay. Accessing deleted objects C++ related functionality 
will not crash the application. It will instead prints out an error message in the output console. 
Here is an example in Lua:

    -- Example:
    local player = Player()
    print(player:getPosition()) -- output: {<x_value>, <y_value>}
    delete(player)
    print(player:getPosition()) -- output: Cannot call object: Values is deleted.

### Functions added to lua ###

We can't rely on the garbage collector to delete the associated userdata even if it only exist on the script side. 
This is because we cannot know for sure that any references still exist anywhere on the compiled side of the application.
It is therefore up to the programmer to handle this by using a **delete** function. Example in Lua:

    -- Created instances
    local player1 = Player()
    local player2 = Player()
    delete(player1, player2)

The delete function can take any number of [1, n) arguments. Internally the delete function does something like this (Pseudo code):

    void delete(list_of_objects objs)
    {
        foreach objs as obj
        {
            obj.unregister();
            delete obj;
        }
    }

### Future plans ###

I have plans on reviewing if boost shared pointer is usable, but the problem still exist that we in that 
case are required to trust/wait for the garbage collector to delete all the potential instances of the associated table.
It might not be usable, but we'll see. It might be possible.


### Credits ###

http://www.lua.org - The Programming Language Lua.
