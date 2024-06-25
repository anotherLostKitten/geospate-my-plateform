extends Node3D


# Called when the node enters the scene tree for the first time.
func _ready():
	print("hi")
	var data = Geodot.get_dataset("geodata/geopackage_sample.gpkg")
	print("hi2")
	print(data.is_valid())
	var feature = data.get_feature_layer("geopackage_sample")
	#print(data.get_feature_layers())
	print(data)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
