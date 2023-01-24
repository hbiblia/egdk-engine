local System = { function create(name, props) end}
local Component = { function create(name, field, value) end}
local Query

-- 
-- Creamos un componente

Component.create("Color", {"r","g", "b", "a"},{r = 0, g = 0, b = 0, a = 255})
local color = Component.load("Color")

-- 
-- Creamos un sistema

System.create("TilingSprite",{
    function init() print("Init System") end,
    function draw() print("Draw System") end,
    function update() print("Update System") end,
}, {"ComponentTexture"})

