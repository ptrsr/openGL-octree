require  'GameObject' 

-- PARAMETERS:
	--name			STRING
	--mesh			STRING (filename + .obj)
	--texture		STRING (filename + .png)
	--x, y and z	NUMBER
--//////////////////////////////////////////////////////////////////////

-- FUNCTIONS: (GameObject:)
	--new{name = "obj1", mesh = "box.obj", etc} - returns GameObject
	--get(STRING filename) 						- returns GameObject
	--rename(STRING name)
	
	--setMaterial(STRING filename)
	--setMesh(STRING filename)
	
	--getPos() 									- returns {x, y and z}
	--setPos(NUMBER x, y, z)
	--move(NUMBER x, y, z)

	--orbit(NUMBER distance)
	--delete()
	--info()
--//////////////////////////////////////////////////////////////////////
createObject()
a = GameObject:new{name = "obj1", mesh = "sphere_smooth.obj", texture = "ball.jpg", texture}


--a:delete()