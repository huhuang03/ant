local ecs = ...
local world = ecs.world
local w = world.w

local math3d = require "math3d"
local mc = import_package "ant.math".constant

local b = ecs.system "bounding_system"

local function init_bounding(bounding, bb)
    if bb and bb.aabb ~= mc.NULL then
		local aabb = bb.aabb
		math3d.unmark(bounding.aabb)
        bounding.aabb = math3d.mark(math3d.aabb(aabb[1], aabb[2]))
		math3d.unmark(bounding.scene_aabb)
        bounding.scene_aabb = math3d.mark(bounding.aabb)
    end
end

function b:entity_init()
	for e in w:select "INIT bounding:update mesh?in simplemesh?in" do
		local m = e.mesh or e.simplemesh
		if m then
			init_bounding(e.bounding, m.bounding)
		end
	end
end