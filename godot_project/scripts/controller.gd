extends Node

var FILE_TO_LOAD = "res://geo_json/multilinestrings.geojson"
var GEOMETRY_SCALE = 100
var SCALE_SPAWN_TO_LOCATION = true
var SCALE_SPEED_TO_LOCATION = true

var bias_max = Vector2()
var bias_min = Vector2()
var bias_speed = 1
var bias_x = 0
var bias_z = 0
var bias_amount = 0
var geometry_dictionary = null
	
func geojson_load(file_location):
	var file = FileAccess.open(file_location, FileAccess.READ)
	var content = file.get_as_text()
	file.close()
	return content

func geojson_parse(geojson_string):
	#create new json reader
	var json = JSON.new()
	#load geojson as string and parse
	json.parse(geojson_string)
	geometry_dictionary = json.data.get("features")

func render_polygon(polygon, mesh, render_mode):
	
	mesh.surface_begin(render_mode)
	for i in polygon.get("geometry").get("coordinates")[0]:
		mesh.surface_add_vertex(Vector3(i[0]*GEOMETRY_SCALE, 1, i[1]*GEOMETRY_SCALE))
		mesh.surface_add_vertex(Vector3(i[0]*GEOMETRY_SCALE, 0, i[1]*GEOMETRY_SCALE))
		if SCALE_SPAWN_TO_LOCATION: calculate_spawn(i[0],i[1])
		if SCALE_SPEED_TO_LOCATION: calculate_map_bounds(i[0],i[1])
	#var temp_geometry = triangulate_polygon(polygon.get("geometry").get("coordinates")[0])
	mesh.surface_end()
	mesh.surface_begin(render_mode)
	for i in polygon.get("geometry").get("coordinates")[0]:
		mesh.surface_add_vertex(Vector3(i[0]*GEOMETRY_SCALE, 1, i[1]*GEOMETRY_SCALE))
		if SCALE_SPAWN_TO_LOCATION: calculate_spawn(i[0],i[1])
		if SCALE_SPEED_TO_LOCATION: calculate_map_bounds(i[0],i[1])
	mesh.surface_end()

func render_line(line, mesh, render_mode):
	mesh.surface_begin(render_mode)
	for i in line.get("geometry").get("coordinates"):
		mesh.surface_add_vertex(Vector3(i[0]*GEOMETRY_SCALE, 0, i[1]*GEOMETRY_SCALE))
		if SCALE_SPAWN_TO_LOCATION: calculate_spawn(i[0],i[1])
		if SCALE_SPEED_TO_LOCATION: calculate_map_bounds(i[0],i[1])
	mesh.surface_end()

func render_multiline(line, mesh, render_mode):
	for i in line.get("geometry").get("coordinates"):
		mesh.surface_begin(render_mode)
		for j in i:
			mesh.surface_add_vertex(Vector3(j[0]*GEOMETRY_SCALE, 0, j[1]*GEOMETRY_SCALE))
			if SCALE_SPAWN_TO_LOCATION: calculate_spawn(j[0],j[1])
			if SCALE_SPEED_TO_LOCATION: calculate_map_bounds(j[0],j[1])
		mesh.surface_end()
	
func render_point(point, mesh, render_mode):
	mesh.surface_begin(render_mode)
	mesh.surface_end()

func calculate_spawn(x_val, z_val):
	bias_x += x_val*GEOMETRY_SCALE
	bias_z += z_val*GEOMETRY_SCALE
	bias_amount += 1
	
func calculate_map_bounds(x_val, y_val):
	if bias_min == Vector2(0,0):
		bias_max.x = x_val
		bias_max.y = y_val
		bias_min.x = x_val
		bias_min.y = y_val
	else:
		bias_max.x = max(x_val,bias_max.x)
		bias_max.y = max(y_val,bias_max.y)
		bias_min.x = min(x_val,bias_min.x)
		bias_min.y = min(y_val,bias_min.y)
 
func calculate_camera_speed():
	bias_speed*=bias_max.distance_to(bias_min)

