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


translate([0,-3,0])cube([15,57,5]);
translate([0,3,4.9])cube([15,3,50]);
translate([0,6+38,4.9])cube([15,3,50]);
%translate([0,6,4.9])cube([15,38,50]);
//color("red")
translate([0,9+38,4])rotate(90,[0,0,1])rotate(90,[1,0,0])strebe($fn=102,5,50,2,b=1);
translate([13,9+38,4])rotate(90,[0,0,1])rotate(90,[1,0,0])strebe($fn=102,5,50,2,b=1);
translate([2,3,4])rotate(-90,[0,0,1])rotate(90,[1,0,0])strebe($fn=102,5,50,2,b=1);

translate([15,3,4])rotate(-90,[0,0,1])rotate(90,[1,0,0])strebe($fn=102,5,50,2,b=1);