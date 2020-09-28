H2=110; 
D1=15;
strength=3.5;
$fn=30;
rad=40;
step=5;
H=sin(step)*(D1*sqrt(2)+rad);

union(){
 for (i=[180:step:360]){
     //translate([-rad,0,0])
     rotate(i,[1,0,0])translate([0,-rad/2,0]){
         difference(){
             cylinder(d=D1,h=H,center=true);
             color("red")cylinder(d=D1-strength,h=2*H,center=true);
             }
         //sphere(d=1);
         }
      }//for
 
 
difference(){
 union(){
 translate([0,-rad/2,-H2])cylinder(d=D1,h=H2);
 translate([0,rad/2,-H2])cylinder(d=D1,h=H2);
 }
 color("teal")translate([0,-rad/2,-H2-1])cylinder(d=D1-strength,h=H2+2);
 translate([0,rad/2,-H2-1])cylinder(d=D1-strength,h=H2+2);
 translate([0,0,-H2+5])rotate(90,[1,0,0])cylinder(d=3,h=1.5*rad,center=true);
}//diff
}//union