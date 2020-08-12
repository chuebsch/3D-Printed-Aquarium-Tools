//prints without support (rotate it upright Y)
$fn=60;
difference(){
union(){
    rotate(-25,[1,0,0])translate([0,0,-15]){
    translate([0,0,0])cylinder(d1=5,d2=5,h=15);    
    translate([0,0,1])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,3])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,5])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,7])cylinder(d1=5.1,d2=5.4,h=0.4);
    //translate([0,0,9])cylinder(d1=5.1,d2=5.4,h=0.4);
    //translate([0,0,11])cylinder(d1=5.1,d2=5.4,h=0.4);
    //translate([0,0,13])cylinder(d1=5.1,d2=5.4,h=0.4);
    //translate([0,0,14])cylinder(d1=5.1,d2=5.4,h=0.4);
    }
    rotate(25,[1,0,0])translate([0,0,-15]){
    translate([0,0,0])cylinder(d1=5,d2=5,h=15);    
    translate([0,0,1])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,3])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,5])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,7])cylinder(d1=5.1,d2=5.4,h=0.4);
    }
    rotate(180,[1,0,0])translate([0,0,-15]){
    translate([0,0,0])cylinder(d1=5,d2=5,h=15);    
    translate([0,0,1])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,3])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,5])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,7])cylinder(d1=5.1,d2=5.4,h=0.4);
    }
}    
rotate( -25,[1,0,0])translate([0,0,-16])cylinder(d=3.5,h=17);
rotate(  25,[1,0,0])translate([0,0,-16])cylinder(d=3.5,h=17);
rotate( 180,[1,0,0])translate([0,0,-16])cylinder(d=3.5,h=17);
}