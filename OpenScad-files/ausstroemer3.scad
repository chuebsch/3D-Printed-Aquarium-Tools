$fn=90;
union(){
  translate([0,0,67])
    difference(){
    cylinder(d1=40,d2=40,h=11);
    translate([0,0,1])cylinder(d1=35,d2=35,h=9);
        translate([0,0,3])for(i=[0:30:360]){
            rotate(i,[0,0,1])translate([12,0,0])rotate(90,[0,1,0])cylinder($fn=36,d=2.5,h=14.5);
            rotate(i+15,[0,0,1])translate([10,0,2.5])rotate(90,[0,1,0])cylinder($fn=36,d=2.5,h=14.5);
            rotate(i,[0,0,1])translate([12,0,+5])rotate(90,[0,1,0])cylinder($fn=36,d=2.5,h=14.5);
            }
    translate([0,0,-1])cylinder(d=11.55,h=5);
    }
difference(){
    cylinder(d=13,h=67);
    translate([0,0,-1])cylinder(d=11.55,h=72);
    /*for (i=[2000:25:2500]){
        translate([0,0,i/50])rotate(i,[0,0,1])rotate(90,[0,1,0])cylinder($fn=36,d=1.5,
        center=true,h=20);
        }*/
    
}
translate([-19*sin(20),0,-18*cos(20)])
rotate(20,[0,1,0])difference(){
cylinder(d=13,h=20);    
translate([0,0,-1])cylinder(d=11.55,h=22);
}
}
    
/*
color("red")
/*for (i=[1500:25:2300]){
        translate([0,0,i/50])rotate(i,[0,0,1])rotate(90,[0,1,0])cylinder($fn=36,d=1.5,
        center=true,h=20);
        }* /
translate([0,0,45])
        for(i=[0:30:360]){
            rotate(i,[0,0,1])translate([15,0,0])cylinder($fn=36,d=1.5,h=5,center=true);
            }

*/