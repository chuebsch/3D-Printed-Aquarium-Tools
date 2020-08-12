// Petrischale

dicke=6*0.35;//6 x Duesen-durchmesser des Druckers 
$fn=90;
D=40;
H=15;
N=5;//0 fuer senkrechte Waende
difference(){
cylinder(d1=D,d2=D+N,h=H);
translate([0,0,dicke/2])cylinder(d1=D-dicke,d2=D+N-dicke,h=H);
}