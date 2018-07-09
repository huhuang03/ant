local clonefunc = require 'clonefunc'

local function calc_activelines(f, lines)
    local info = debug.getinfo(f, 'L')
    for l in pairs(info.activelines) do
        lines[l] = true
    end
    local id, n = clonefunc.proto(f)
    if id then
        for i = 1, n do
            local of = clonefunc.clone(f, i)
            calc_activelines(of, lines)
        end
    end
end

return function (src, f)
    src.activelines = {}
    calc_activelines(f, src.activelines)
    return src
end
