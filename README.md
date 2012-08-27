prototype
=========
A library for prototyping c++ class using Lua (from Lua's point of view).

### What is prototype ###

Although the name can be "slightly" missleading, it's purpose is straight on. The purpose of this library
is to enable the developer to prototype and extend exposed c++ class methods using the scripting language: Lua.

I've planned on using this library for a game engine i've planned to develop later and a scripting language
is a must when doing that. This project is in reality a project for myself learning the Lua API but if the end
result can be of use for other people then that would be awesome.

Note that it doens't replace pure c++ functions, but it extends methods that are called using the supplied "invoke" 
functionality (So it does not solve the world-hunger problem). But it gives us power of rapid development before
the optimization stage (where we move our code from script to complied code).

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
        
        void moveTo(Vector2& pos)
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

    -- We begin by create a player instance and move it to position x,y {10,10}
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

### How do we prevent deleted objects from being called or referenced? ###

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

A deletion of the player instance is of course still okay, but accessing a deleted object simply 
prints an error message in the output console. Here is an example in Lua:

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
