/*
AQUARIUM FAN MOUNT for 2 120mm computer fans
*/
breite=50;
AQWandstaerke=4.5;
bohrung=4.2;
bohrungsabstand=8;
difference(){
union(){
    cube([11,20,breite]);
    translate([5,13,0])rotate(35,[0,0,1])cube([4,20,breite]);    
    
}
translate([3,-1,-1])cube([AQWandstaerke,12,202]);
translate([-20,13,25-bohrungsabstand])
rotate(90+35,[0,0,1])
rotate(90,[1,0,0])cylinder($fn=60,h=300,d=bohrung,center=true);

translate([-20,13,25+bohrungsabstand])
rotate(90+35,[0,0,1])
rotate(90,[1,0,0])cylinder($fn=60,h=300,d=bohrung,center=true);
}
