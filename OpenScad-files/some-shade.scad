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
//strebe($fn=102,10,100,2,b=1);
difference(){
    union(){
        cube([11,20,100]);
        translate([0,19,0])cube([150,1.2,100]);
        translate([11,19,0])rotate(-90,[0,0,1])strebe($fn=102,10,100,2,b=1);
        translate([11,19,98])rotate(-90,[0,0,1])strebe($fn=102,10,100,2,b=1);
        translate([11,19,98/2])rotate(-90,[0,0,1])strebe($fn=102,10,100,2,b=1);
    }
translate([3,-1,-1])cube([4.5,12,202]);
}