-- Called during script loader initialization to set up all the global tables and functions.
-- I try to put as much intialization as possible in lua files, but some needs to be done from the C++ side of things.
-- This is called before any C++ side initialization.

package.path = "./RFGR Script Loader/Core/?.lua;"
package.path = package.path .. "./RFGR Script Loader/Core/?/?.lua;"
package.path = package.path .. "./RFGR Script Loader/Scripts/?.lua;"

rsl = {}
rfg = require("rfg.Init")

rsl.LogType = require("LogType")

function Help()
    print("Lua help function")
end
