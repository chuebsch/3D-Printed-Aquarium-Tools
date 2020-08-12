// this is to get a smaller hose on the "saugrhohr" 
// print this with TPU!

$fn=60;
difference(){
union(){
translate([0,0,15])cylinder(d1=20,d2=19,h=12);
    translate([0,0,14])cylinder(d1=8,d2=8,h=20);
    /*
    translate([0,0,48])cylinder(d1=6.7,d2=7,h=0.4);
    translate([0,0,50])cylinder(d1=6.4,d2=6.7,h=0.4);
    translate([0,0,52])cylinder(d1=6.1,d2=6.5,h=0.4);
    translate([0,0,54])cylinder(d1=5.9,d2=6.2,h=0.4);
    translate([0,0,56])cylinder(d1=5.7,d2=6.0,h=0.4);
    translate([0,0,58])cylinder(d1=5.5,d2=5.8,h=0.4);
    translate([0,0,60])cylinder(d1=5.3,d2=5.6,h=0.4);
    translate([0,0,62])cylinder(d1=5.1,d2=5.4,h=0.4);
    */
}
    translate([0,0,13.9])
color("red")difference(){
  cylinder(d=17,h=12);
  translate([0,-0,1])cylinder(d1=11,d2=11,h=18);
}
//color("teal")translate([0,0,-1])cylinder(d=11,h=26);
translate([0,0,14])cylinder(d=5.9,h=46);
}