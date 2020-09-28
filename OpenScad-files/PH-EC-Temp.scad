$fn=120;
f6 =1/cos(180/6);
module konsole(){
difference(){
cube([13,13,25]);
    translate([6.5,6.5,-1])cylinder(d=3.5,h=30);
    translate([6.5,6.5,-0.05])cylinder(d1=5.6,d2=3.5,h=1.65);    
    hull(){
    translate([6.5,6.5,4])rotate(30)cylinder($fn=6, d=5.7*f6,h=3.6);
    translate([6.5,16.5,4])rotate(30)cylinder($fn=6, d=5.7*f6,h=3.6);
    }
    translate([-1,18,-0])rotate(35,[1,0,0])cube([15,13,40]);
}
}
module dcjack(){
  //  difference(){
        union(){
        rotate(90,[0,1,0])cylinder($fn=60,d=8.3,h=14);
        translate([0,-4.5,-6])cube([3,9,11]);
        translate([0,-4.5,-6])cube([14,9,6]);
        }
    rotate(90,[0,1,0])cylinder($fn=60,d=6,h=9);
   // }
}



*difference(){
union(){
        translate([ 0,12,0])cube([160,96,3],center=true);
        translate([ 46.5, 28.5,0])cylinder(h=9.7,d=7,$fn=50);
        translate([-46.5,-26.5,0])cylinder(h=9.7,d=7,$fn=50);
        translate([ 46.5,-26.5,0])cylinder(h=9.7,d=7,$fn=50);
        translate([-46.5, 28.5,0])cylinder(h=9.7,d=7,$fn=50);
        
        //translate([ -127.125, 60.5,0])cube([230.25,3.4,80]);  
        //translate([ -129.125,-33.0,0])cube([230.25,3.5,80]);  
        
        //translate([ -84.125,-33.0,-1])rotate(-20,[0,1,0])cube([3.5,96,90]);  
        //translate([  72.125,-33.0,1])rotate( 20,[0,1,0])cube([3.5,96,90]);  
    /*
        translate([-81,-30,78.5])rotate(180,[0,1,0])konsole();          
        translate([-94, 62,78.5])rotate(180,[1,0,0])konsole(); 
        translate([+94,-30,78.5])rotate(180,[0,1,0])konsole();          
        translate([+81, 62,78.5])rotate(180,[1,0,0])konsole();
    */
    }
    translate([ 0,1,0])cube([75,25,5],center=true);//window
    translate([ 46.5, 28.5,1])cylinder(h=15,d=2.97,$fn=50);//M3 self tapping
    translate([-46.5,-26.5,1])cylinder(h=15,d=2.97,$fn=50);
    translate([ 46.5,-26.5,1])cylinder(h=15,d=2.97,$fn=50);
    translate([-46.5, 28.5,1])cylinder(h=15,d=2.97,$fn=50);
    
translate([-75, -31, -2])cylinder(h=2,d1=8,d2=4,$fn=50);
translate([ 75, -31, -2])cylinder(h=2,d1=8,d2=4,$fn=50);
translate([-75,  55, -2])cylinder(h=2,d1=8,d2=4,$fn=50);
translate([ 75,  55, -2])cylinder(h=2,d1=8,d2=4,$fn=50);
translate([-75, -31, -2])cylinder(h=12,d=4,$fn=50);
translate([ 75, -31, -2])cylinder(h=12,d=4,$fn=50);
translate([-75,  55, -2])cylinder(h=12,d=4,$fn=50);
translate([ 75,  55, -2])cylinder(h=12,d=4,$fn=50);   
}
*color("green")
translate([-76,-14,45])
difference(){
cube([42.5,32.5,1.7]);
    translate([3.5,3.5,-0.5 ])cylinder(h=25,d=3.5,$fn=50);
    translate([42.5-3.5,3.5,-0.5 ])cylinder(h=25,d=3.5,$fn=50);
    translate([3.5,32.5-3.5,-0.5 ])cylinder(h=25,d=3.5,$fn=50);
    translate([42.5-3.5,32.5-3.5,-0.5 ])cylinder(h=25,d=3.5,$fn=50);
}

*color("green")
translate([-20,-14,45])
difference(){
cube([90,70,1.7]);
    translate([3.25+83,2.75,-0.5 ])cylinder(h=25,d=3.5,$fn=50);
    translate([3.25,2.75,-0.5 ])cylinder(h=25,d=3.5,$fn=50);
    translate([3.2+83,2.75+64.875,-0.5 ])cylinder(h=25,d=3.5,$fn=50);
    translate([3.25,2.75+64.875,-0.5 ])cylinder(h=25,d=3.5,$fn=50);
}




difference(){
    union(){
        difference(){
translate([-80+3.5,35.6,43])cube([15,8.7,12]);
translate([-80+3,40,47])dcjack();   
}
        translate([ 0,12,55])cube([160,96,3],center=true);
        translate([ -80,-36,1.5])cube([3,96,53.5]);
        translate([  77,-36,1.5])cube([3,96,53.5]);
        translate([ -80,-36,1.5])cube([160,3,53.5]);
        translate([ -80, 57,1.5])cube([160,3,53.5]);
        translate([-75, -31,1.5 ])cylinder(h=53.5,d=7,$fn=50);
        translate([ 75, -31,1.5])cylinder(h=53.5,d=7,$fn=50);
        translate([-75,  55,1.5])cylinder(h=53.5,d=7,$fn=50);
        translate([ 75,  55,1.5])cylinder(h=53.5,d=7,$fn=50);   
        translate([-20,-14,47.5]){
            translate([3.25+83,2.75,-0.5 ])cylinder(h=7,d=7,$fn=50);
            translate([3.25,2.75,-0.5 ])   cylinder(h=7,d=7,$fn=50);
            translate([3.2+83,2.75+64.875,-0.5 ])cylinder(h=7,d=7,$fn=50);
            translate([3.25,2.75+64.875,-0.5 ])  cylinder(h=7,d=7,$fn=50);
            }
            translate([-76,-14,47.5]){
    translate([3.5,3.5,-0.5 ])          cylinder(h=7,d=7,$fn=50);
    translate([42.5-3.5,3.5,-0.5 ])     cylinder(h=7,d=7,$fn=50);
    translate([3.5,32.5-3.5,-0.5 ])     cylinder(h=7,d=7,$fn=50);
    translate([42.5-3.5,32.5-3.5,-0.5 ])cylinder(h=7,d=7,$fn=50);
}
    }
    translate([-176,1,45-7.0])rotate(90,[0,1,0]) cylinder(d=16,h=200);
    translate([-176,45,15])rotate(90,[0,1,0]) cylinder(d=10,h=200);
    translate([-4,-14,30])cube([15,100,10]);
    translate([-75, -31,0.5])cylinder(h=25,d1=4,d2=3.9,$fn=50);
    translate([ 75, -31,0.5])cylinder(h=25,d1=4,d2=3.9,$fn=50);
    translate([-75,  55,0.5])cylinder(h=25,d1=4,d2=3.9,$fn=50);
    translate([ 75,  55,0.5])cylinder(h=25,d1=4,d2=3.9,$fn=50);   
    translate([-20,-14,45.0]){
        translate([3.25+83,2.75,-0.5 ])cylinder(h=9,d=2.97,$fn=50);
        translate([3.25,2.75,-0.5 ])cylinder(h=9,d=2.97,$fn=50);
        translate([3.2+83,2.75+64.875,-0.5 ])cylinder(h=9,d=2.97,$fn=50);
        translate([3.25,2.75+64.875,-0.5 ])cylinder(h=9,d=2.75,$fn=50);
        }
    translate([-76,-14,45.0]){
    translate([3.5,3.5,-0.5 ])          cylinder(h=9,d=2.97,$fn=50);
    translate([42.5-3.5,3.5,-0.5 ])     cylinder(h=9,d=2.97,$fn=50);
    translate([3.5,32.5-3.5,-0.5 ])     cylinder(h=9,d=2.97,$fn=50);
    translate([42.5-3.5,32.5-3.5,-0.5 ])cylinder(h=9,d=2.97,$fn=50);
}
fudge = 1/cos(180/6);
color("red")
translate([-20,0,25])
rotate(90,[1,0,0])cylinder(d=14*fudge,h=34,$fn=6);

color("red")
translate([-50,0,25])
rotate(90,[1,0,0])cylinder(d=14*fudge,h=34,$fn=6);
fudge1 = 1/cos(180/60);
color("red")
translate([10,0,25])
rotate(90,[1,0,0])cylinder(d=11*fudge1,h=34.5,$fn=60);

translate([-20,0,25])
rotate(90,[1,0,0])cylinder(d=12*fudge1,h=54,$fn=60);
translate([-50,0,25])
rotate(90,[1,0,0])cylinder(d=12*fudge1,h=54,$fn=60);
translate([10,0,25])
rotate(90,[1,0,0])cylinder(d=6*fudge1,h=54,$fn=60);
translate([-90,40,47])rotate(90,[0,1,0])cylinder(d=6,h=20);
}