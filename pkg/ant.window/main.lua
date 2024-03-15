local function start(initargs)
    local platform = require "bee.platform"
    if platform.os == "ios" then
        dofile "/engine/ltask.lua" {
            bootstrap = {
                ["logger"] = {},
                ["ant.window|boot"] = {
                    args = {initargs},
                    unique = false,
                }
            },
            exclusive = {
                "ant.window|ios",
            },
            mainthread = -1,
            worker = 6,
            worker_bind = {
                ["ant.window|window"] = 0,
                ["ant.hwi|bgfx"] = 1,
            },
        }
    else
        dofile "/engine/ltask.lua" {
            bootstrap = {
                ["logger"] = {},
                ["ant.window|boot"] = {
                    args = {initargs},
                    unique = false,
                }
            },
            mainthread = 0,
            worker = 6,
            worker_bind = {
                ["ant.window|window"] = 0,
                ["ant.hwi|bgfx"] = 1,
            },
        }
    end
end

local function newproxy(t, k)
    local ltask = require "ltask"
    local ServiceWindow = ltask.queryservice "ant.window|window"

    local function reboot(initargs)
        ltask.send(ServiceWindow, "reboot", initargs)
    end

    local function set_cursor(cursor)
        ltask.call(ServiceWindow, "set_cursor", cursor)
    end

    local function set_title(title)
        ltask.call(ServiceWindow, "set_title", title)
    end

    t.reboot = reboot
    t.set_cursor = set_cursor
    t.set_title = set_title
    return t[k]
end

return setmetatable({ start = start }, { __index = newproxy })