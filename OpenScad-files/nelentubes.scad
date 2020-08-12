// Ein Zuhause fuer Garnelen
$fn=6;
dia=9;//durchmesser der Rohren
leng=25;//laenge
n=4;//n+1 = Anzal der Roehren in eine Richtung


module pipe(length,diameter,wall){
    fudge = 1/cos(180/$fn);
difference(){
    cylinder(d=diameter*fudge,h=length);
    translate([0,0,-1])cylinder(d=diameter*fudge-wall,h=length+2);
    }
}

union(){
    for(j=[0:n]){
    for(i=[0:(n-j)]){
        translate([sqrt(0.75)*dia*i,j*dia+i*dia*.5,-(i+j)*5])pipe(leng+(j+i)*5,dia,6*0.35);
    
        }
    }
}