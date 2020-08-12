$fn=7;
breite=190-96;
tiefe=97.5;
difference(){
    union(){
        cube([breite,tiefe,1]);
        for (i=[5:10:breite]){
          for (j=[5:10:tiefe-5]){
              translate([i,j,0])cylinder(d=6,h=7);
          }
        }
    }    
    for (i=[5:5:breite-5]){
      for (j=[5:5:tiefe-5]){
         translate([i,j,-1])cylinder(d=3,h=13);
      }
    }    
}