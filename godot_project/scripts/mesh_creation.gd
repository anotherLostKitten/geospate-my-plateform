extends MeshInstance3D

signal spawn_camera

# Called when the node enters the scene tree for the first time.
func _ready():
	var geojson_string = Controller.geojson_load(Controller.FILE_TO_LOAD)
	Controller.geojson_parse(geojson_string)
	
	for shape in Controller.geometry_dictionary:
		
		#Tops of the polygons are bugged.
		if shape.get("geometry").get("type") == "Polygon":
			Controller.render_polygon(shape, mesh, Mesh.PRIMITIVE_TRIANGLE_STRIP)
		
		#Fully working.
		elif shape.get("geometry").get("type") == "LineString":
			Controller.render_line(shape, mesh, Mesh.PRIMITIVE_LINE_STRIP)
		#Fully working.
		elif shape.get("geometry").get("type") == "MultiLineString":
			Controller.render_multiline(shape, mesh, Mesh.PRIMITIVE_LINE_STRIP)
		
		elif shape.get("geometry").get("type") == "Point":
			Controller.render_point(shape, mesh, Mesh.PRIMITIVE_TRIANGLES)
		else:
			print("Unsupported object detected, please check geojson.")
	
	spawn_camera.emit()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
