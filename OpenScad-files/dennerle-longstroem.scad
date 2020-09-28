$fn=60;
function cosh(x) = 0.5*(exp(x)+exp(-x));
module strebe(x,y,z,b=0.6){
    dx=(x)/$fn;
    ym=cosh(x*b);
    dy=y/ym;
    //echo($fn); 
    p=[for (j=[0:$fn])[x-j*dx,dy*cosh(j*dx*b)]];
    pp=concat(p,[[0,0]]);
        
        
   // echo(pp);
    linear_extrude(height=z,slices =$fn)
    polygon(pp);
}
//translate([-0.5,4.5,12.35])rotate(90,[0,1,0])color("red")strebe($fn=502,12,12,1,b=0.4);


difference(){
union(){
    translate([0,0,0])cylinder(d1=9.95,d2=10.75,h=16);
    translate([0,0,15.95])cylinder(d=10.5,h=180);
    for (i=[20:10:185]){
        translate([0,10.5/4+15,i])
    rotate(90,[1,0,0])cylinder(d1=5,d2=10,h=15);
    }
    translate([-0.5,0,20])cube([1,18,160]);
        translate([-0.5,4.5,17.35])
rotate(90,[0,1,0])
strebe($fn=502,12,12,1,b=0.4);
}
    
    translate([0,0,-1])cylinder(d=8,h=192);
    for (i=[20:10:185]){
        translate([0,10.5/4+16,i])
        rotate(90,[1,0,0])cylinder(d=2.5,h=15);
    }
//color("teal")translate([0,0,-1])cylinder(d=11,h=26);
//translate([0,0,])cylinder(d=3,h=46);
}