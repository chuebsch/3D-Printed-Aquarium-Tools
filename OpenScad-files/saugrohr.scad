//Thist is for a soil filter 
// a AQUAEL PAT MINI PUMP fits on this.
// the small tube is for a hose which makes water change much
// easier and more pleasant for AQ-life. 
$fn=36;
H=7;
color("red")

difference(){


}


union(){
    
difference(){
cube([96,97.5,H],center=true);

    translate([-96/2+25,0,0]){
cylinder(d=44,h=18,center=true);
    color("red")translate([0,0,-3])rotate(90,[0,1,0])cylinder(d1=H*1.5,d2=H*0.6,h=230,center=true);
    translate([0,0,-3])scale([0.7,0.7,1.9]){    
    rotate(30)
    rotate(90,[0,1,0])cylinder(d=H*0.8,h=250);
    rotate(60)
    rotate(90,[0,1,0])cylinder(d=H*0.8,h=250);
    rotate(90)
    rotate(90,[0,1,0])cylinder(d=H*0.8,h=250,center=true);
    rotate(-60)
    rotate(90,[0,1,0])cylinder(d=H*0.8,h=250);
    rotate(-30)
    rotate(90,[0,1,0])cylinder(d=H*0.8,h=250);
    rotate(45)
    rotate(90,[0,1,0])cylinder(d=H*0.8,h=250);
    rotate(75)
    rotate(90,[0,1,0])cylinder(d=H*0.8,h=250,center=true);
    rotate(-75)
    rotate(90,[0,1,0])cylinder(d=H*0.8,h=250,center=true);
    rotate(-45)
    rotate(90,[0,1,0])cylinder(d=H*0.8,h=250);
    rotate(-15)
    rotate(90,[0,1,0])cylinder(d=H*0.8,h=250);
    rotate(15)
    rotate(90,[0,1,0])cylinder(d=H*0.8,h=250);
}

}
}
translate([-96/2+25,0,H/2-2])
{
difference(){
    union(){
  cylinder(d1=50,d2=17,h=22);
        translate([96/2-25,0,-H/2+2])translate([-H*1.4,0,H*1.4])rotate( 220,[0,1,0])translate([0,0,-15]){
    translate([0,0,0])cylinder(d1=5,d2=5,h=15);    
    translate([0,0,1])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,3])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,5])cylinder(d1=5.1,d2=5.4,h=0.4);
    translate([0,0,7])cylinder(d1=5.1,d2=5.4,h=0.4);
    }
    }
  translate([0,0,-1])cylinder(d1=47,d2=12,h=23.1);
    translate([96/2-25,0,-H/2+2])
  translate([-H*1.4,0,H*1.4])rotate( 220,[0,1,0])translate([0,0,-16])cylinder(d=3.5,h=17);  
}
translate([0,0,21.9])
color("red")difference(){
  cylinder(d=17,h=22);
  translate([0,0,-1])cylinder(d1=15,d2=13.45,h=24);
}
}
}