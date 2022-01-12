$fn=90;
union(){
  translate([0,0,76])
    rotate(-1,[0,1,0])
    difference(){
        union(){
    hull(){
        cylinder(d1=40,d2=80,h=11);
        translate([-60,0,0])cylinder(d1=30,d2=90,h=11);
    }
    
translate([0,0,-65]){
translate([-58,0,58])scale([1.7,1.5,1])
difference(){
    cylinder(d2=35,d1=15,h=15);
    translate([0,0,-1])cylinder(d2=32.55,,d1=12.55,h=17);
    }
translate([-58,0,10])scale([1.7,1.5,1])
difference(){
    cylinder(d2=15,d1=15,h=25+23);
    translate([0,0,-1])cylinder(d2=13.55,,d1=13.55,h=27+23);
    }
}
}
    translate([0,0,1])hull(){
        cylinder(d1=39,d2=79,h=13);        
        translate([-60,0,0])cylinder(d1=29,d2=89,h=13);        
    }
    translate([0,0,-1])cylinder(d=11.55,h=5);
    translate([-58,0,-5])scale([1.7,1.5,1])cylinder(d2=32.55,,d1=12.55,h=17);
    }
    color("teal")
difference(){
    cylinder(d=13,h=77);
    translate([0,0,-1])cylinder(d=11.55,h=82);
    /*for (i=[2000:25:2500]){
        translate([0,0,i/50])rotate(i,[0,0,1])rotate(90,[0,1,0])cylinder($fn=36,d=1.5,
        center=true,h=20);
        }*/
    
}
translate([-19*sin(20),0,-18*cos(20)])
rotate(20,[0,1,0])difference(){
cylinder(d=13,h=20);    
translate([0,0,-1])cylinder(d=11.55,h=22);
}
}
    
//color("red")
/*
color("red")
/*for (i=[1500:25:2300]){
        translate([0,0,i/50])rotate(i,[0,0,1])rotate(90,[0,1,0])cylinder($fn=36,d=1.5,
        center=true,h=20);
        }* /
translate([0,0,45])
        for(i=[0:30:360]){
            rotate(i,[0,0,1])translate([15,0,0])cylinder($fn=36,d=1.5,h=5,center=true);
            }

*/