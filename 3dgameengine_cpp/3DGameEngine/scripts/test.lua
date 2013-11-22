local a = Object.find("bunny")

function update()

if isKeyDown('w') == true then
	x,y,z = a:getTranslation()
	a:setTranslation(x, y, z + 0.1)
end
if isKeyDown('s') == true then
	x,y,z = a:getTranslation()
	a:setTranslation(x, y, z - 0.1)
end
if isKeyDown('a') == true then
	x,y,z = a:getTranslation()
	a:setRotation(0, 0, 0)
	a:setTranslation(x - 0.1, y, z)
end
if isKeyDown('d') == true then
	x,y,z = a:getTranslation()
	a:setRotation(0, 180, 0)
	a:setTranslation(x + 0.1, y, z)
end

end