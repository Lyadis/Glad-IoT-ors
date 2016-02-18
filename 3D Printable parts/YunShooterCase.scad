*union() {
	translate([-9.5,-10.8,-9])
	difference() {
		import_stl("ball_and_socket.stl",convexity=10);
		cube([50,50,11]);
	}
	
	translate([0,0,1])
	cube([40,20,2], center=true);
}

translate([-9.5,10.8,13])
rotate([180,0,0])
difference() {
	import_stl("ball_and_socket.stl",convexity=10);
	translate([0,0,12.5]) cube([50,50,11]);
}