// This fits on a AQUAEL PAT MINI PUMP and is an angle of 
// 110 degrees. 110 degrees in order to make this thing printable
// without support. Print it with the smaller pipe verical.

$fn=90;
difference(){
    union(){
        cylinder(d1=14,d2=15,h=20);
        hull(){
        translate([0,0,7])rotate(110,[0,1,0])cylinder(d1=14.5,d2=12.5,h=20);
        translate([0,0,7])rotate(110,[0,1,0])cylinder(d=10.45,h=35);
        }
        }
    translate([0,0,1])cylinder(d1=11.3,d2=12.2,h=20);
        translate([2,0,7])rotate(111.5,[0,1,0])cylinder(d1=11.55,d2=8,h=35);
    }
    
    