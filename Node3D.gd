extends Node3D


# Called when the node enters the scene tree for the first time.
func _ready():
	print("hi")
	var data = Geodot.get_dataset("geodata/geopackage_sample.gpkg")
	print(data)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
