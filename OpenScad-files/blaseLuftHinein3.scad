// this is to get a smaller hose on the "saugrhohr" 
// print this with PLA or PTG the smooth part goes in 
// "blaseLuftHinein"

$fn=60;
difference(){
union(){
//translate([0,0,41])cylinder(d1=10,d2=9.7,h=3);
    translate([0,0,47])cylinder(d1=5,d2=5,h=15);
    
    translate([0,0,48])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,50])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,52])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,54])cylinder(d1=5.1,d2=5.4,h=0.4);
    //translate([0,0,56])cylinder(d1=5.1,d2=5.4,h=0.4);
    //translate([0,0,58])cylinder(d1=5.1,d2=5.4,h=0.4);
    //translate([0,0,60])cylinder(d1=5.1,d2=5.4,h=0.4);
    //translate([0,0,62])cylinder(d1=5.1,d2=5.4,h=0.4);
    
}
    /*translate([0,0,14])
color("red")difference(){
  cylinder(d=17,h=12);
  translate([0,0,-1])cylinder(d1=15,d2=13.45,h=18);
}
translate([0,0,-1])cylinder(d=11,h=26);
*/
translate([0,0,14])cylinder(d=3.5,h=76);

}