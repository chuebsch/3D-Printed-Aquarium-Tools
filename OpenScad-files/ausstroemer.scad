$fn=90;
union(){
difference(){
    cylinder(d=13,h=50);
    translate([0,0,-1])cylinder(d=11.55,h=49);
    for (i=[1500:25:2300]){
        translate([0,0,i/50])rotate(i,[0,0,1])rotate(90,[0,1,0])cylinder($fn=36,d=1.5,
        center=true,h=20);
        }
}
translate([-19*sin(20),0,-18*cos(20)])
rotate(20,[0,1,0])difference(){
cylinder(d=13,h=20);    
translate([0,0,-1])cylinder(d=11.55,h=22);
}
}