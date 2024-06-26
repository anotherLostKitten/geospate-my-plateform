extends Node

var FILE_TO_LOAD = "res://geo_json/usa.geojson"
var GEOMETRY_SCALE = 10

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
	#var temp_geometry = triangulate_polygon(polygon.get("geometry").get("coordinates")[0])
	mesh.surface_end()
	mesh.surface_begin(render_mode)
	for i in polygon.get("geometry").get("coordinates")[0]:
		mesh.surface_add_vertex(Vector3(i[0]*GEOMETRY_SCALE, 1, i[1]*GEOMETRY_SCALE))
	
	mesh.surface_end()

func render_line(line, mesh, render_mode):
	mesh.surface_begin(render_mode)
	for i in line.get("geometry").get("coordinates"):
		mesh.surface_add_vertex(Vector3(i[0]*GEOMETRY_SCALE, 0, i[1]*GEOMETRY_SCALE))
	mesh.surface_end()

func render_multiline(line, mesh, render_mode):
	for i in line.get("geometry").get("coordinates"):
		mesh.surface_begin(render_mode)
		for j in i:
			mesh.surface_add_vertex(Vector3(j[0]*GEOMETRY_SCALE, 0, j[1]*GEOMETRY_SCALE))
			print(j[0])
			print(j[1])
		mesh.surface_end()
	
func render_point(point, mesh, render_mode):
	mesh.surface_begin(render_mode)
	mesh.surface_end()

