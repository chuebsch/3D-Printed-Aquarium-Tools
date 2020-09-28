//no bottom and top perimeters just gyro infill

$fn=90;

difference(){
    union(){
    cylinder(d1=14,d2=15,h=20);
    translate([0,0,-8])hull(){
        translate([0,0,7])
        cylinder(d2=14, d1=14, h=1.01);
        translate([0,7,0])cylinder(d1=34,d2=33, h=1.01);
    }
    }
    translate([0,0,-5])cylinder(d1=11.3,d2=12.2,h=30);
}